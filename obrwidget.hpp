#include <stdlib.h>
#include <GL/glu.h>
#include <stdio.h>
#include <QMenuBar>
#include <string.h> 
#include <QApplication>
#include <QtGui>
#include <iomanip>
#include <QtOpenGL>
#include <fstream>
#include <sstream>
#include <vector>
#include "geom_high.hpp"
#include "map_prop.hpp"
#include "ster.hpp"
#include "ust_obiekt.hpp"
#include "bmpread.hpp"
#ifndef OBRWIDGET
#define OBRWIDGET
class utpWidget;
class MapaReceiver
{
	public:
	virtual void onMouseClick(double x, double y) //ONLYRIGHT
	{
	}
	virtual void onPaint()
	{
	}
	virtual void onZoomChanged()
	{
	}
};
class MapaWidget : public QWidget, public map_prop
{
        Q_OBJECT
	MapaReceiver* receiver;
	utpWidget* obraz2;
	QPushButton* plus;
	QPushButton* minus;
	bool tryb_move;
	int sx;
	int sy;
public:
	void onMouseClick(bool left, int x, int y);
	void onMouseMove(int x, int y);
	void onMouseRealase(bool left, int x, int y);
	void update_request();
	void onPaint()
	{
		receiver->onPaint();
	}
	MapaWidget(QWidget* parent, MapaReceiver* rec);
	~MapaWidget();
protected:
public slots:
	void modPlus();
	void modMinus();
};
class utpWidget : public QGLWidget
{
	MapaWidget* al;
	public:
	utpWidget(MapaWidget* parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent), al(parent)
	{
		setMouseTracking(true);
	}
	~utpWidget() {}
	protected:
	void resizeGL(int width, int height)
	{
	}
	void paintGL()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, width(), height());
		glColor3ub(255, 255, 255);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(al->starex(0), al->starex(width()), al->starey(height()), al->starey(0));
		glBegin(GL_POLYGON);
		glVertex2f(al->starex(0), al->starey(0));
		glVertex2f(al->starex(width()), al->starey(0));
		glVertex2f(al->starex(width()), al->starey(height()));
		glVertex2f(al->starex(0), al->starey(height()));
		glEnd();
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		al->onPaint();
	}
	void initializeGL()
	{	
		glShadeModel(GL_SMOOTH);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	}
	bool event(QEvent * event)
	{
		event -> accept ();
		if (event -> type () == QEvent::MouseButtonPress)
		{
			int x,y;
			x=(static_cast <QMouseEvent*>(event) -> x ());
			y=(static_cast <QMouseEvent*>(event) -> y ());
			Qt::MouseButton btu=(static_cast <QMouseEvent*>(event)->button());
			bool key=1;
			if(btu==Qt::RightButton)
				key=0;
			al->onMouseClick(key,x,y);
			return true;
		}
		if (event -> type () == QEvent::MouseMove)
		{
			int x,y;
			x=(static_cast <QMouseEvent*>(event) -> x ());
			y=(static_cast <QMouseEvent*>(event) -> y ());
			al->onMouseMove(x,y);
			return true;
		}
		
		if (event -> type () == QEvent::MouseButtonRelease)
		{
			int x,y;
			x=(static_cast <QMouseEvent*>(event) -> x ());
			y=(static_cast <QMouseEvent*>(event) -> y ());
			Qt::MouseButton btu=(static_cast <QMouseEvent*>(event)->button());
			bool key=1;
			if(btu==Qt::RightButton)
				key=0;
			al->onMouseRealase(key, x,y);
		
			return true;
		}
		return QWidget::event(event);
	}
};
#endif
