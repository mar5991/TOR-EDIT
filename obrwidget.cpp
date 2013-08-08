#include "obrwidget.hpp"
MapaWidget::MapaWidget(QWidget* parent, MapaReceiver* rec) : QWidget(parent), map_prop(600, 600, -1000, 2100, 2100, -1000), receiver(rec)
{
	tryb_move=0;
	plus=new QPushButton(this);
	minus=new QPushButton(this);
	obraz2=new utpWidget(this);
	connect(plus, SIGNAL(clicked()), this, SLOT(modPlus()));
	connect(minus, SIGNAL(clicked()), this, SLOT(modMinus()));
	plus->setGeometry(0,0,100, 100);
	plus->setText("+");
	minus->setGeometry(100,0,100, 100);
	minus->setText("-");
	obraz2->setGeometry(0,100,600, 600);
}
MapaWidget::~MapaWidget()
{
	delete plus;
	delete minus;
}
void MapaWidget::onMouseClick(bool left, int x, int y)
{
	if(left)
	{
		tryb_move=1;
		sx=x;
		sy=y;
	}
	else
		receiver->onMouseClick(starex(x), starey(y));
}
void MapaWidget::onMouseMove(int x, int y)
{
	if(tryb_move)
	{
		przesuncentrum(-starex(x)+starex(sx), -starey(y)+starey(sy));
		sx=x;
		sy=y;
		obraz2->updateGL();
	}
}
void MapaWidget::onMouseRealase(bool left, int x, int y)
{
	if(left)
		tryb_move=0;
}

void MapaWidget::modPlus()
{
	powiekszzoom(2);
	receiver->onZoomChanged();
	obraz2->updateGL();
}
void MapaWidget::modMinus()
{
	powiekszzoom(0.5);
	receiver->onZoomChanged();
	obraz2->updateGL();
}
void MapaWidget::update_request()
{
	obraz2->updateGL();
}
