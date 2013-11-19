/****************************************************************************
** Meta object code from reading C++ file 'obrwidget.hpp'
**
** Created: Wed Nov 13 04:29:26 2013
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "obrwidget.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'obrwidget.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MapaWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      22,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MapaWidget[] = {
    "MapaWidget\0\0modPlus()\0modMinus()\0"
};

void MapaWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MapaWidget *_t = static_cast<MapaWidget *>(_o);
        switch (_id) {
        case 0: _t->modPlus(); break;
        case 1: _t->modMinus(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MapaWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MapaWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MapaWidget,
      qt_meta_data_MapaWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MapaWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MapaWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MapaWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MapaWidget))
        return static_cast<void*>(const_cast< MapaWidget*>(this));
    if (!strcmp(_clname, "map_prop"))
        return static_cast< map_prop*>(const_cast< MapaWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MapaWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
