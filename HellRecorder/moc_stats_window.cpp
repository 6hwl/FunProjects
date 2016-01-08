/****************************************************************************
** Meta object code from reading C++ file 'stats_window.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stats_window.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stats_window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_StatsWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      29,   12,   12,   12, 0x08,
      39,   12,   12,   12, 0x08,
      52,   12,   12,   12, 0x08,
      70,   12,   12,   12, 0x08,
      86,   12,   12,   12, 0x08,
      99,   12,   12,   12, 0x08,
     113,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_StatsWindow[] = {
    "StatsWindow\0\0clickedUpdate()\0fixSize()\0"
    "clickedAll()\0clickedHardcore()\0"
    "clickedInsane()\0clickedRun()\0clickedName()\0"
    "clickedClose()\0"
};

void StatsWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        StatsWindow *_t = static_cast<StatsWindow *>(_o);
        switch (_id) {
        case 0: _t->clickedUpdate(); break;
        case 1: _t->fixSize(); break;
        case 2: _t->clickedAll(); break;
        case 3: _t->clickedHardcore(); break;
        case 4: _t->clickedInsane(); break;
        case 5: _t->clickedRun(); break;
        case 6: _t->clickedName(); break;
        case 7: _t->clickedClose(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData StatsWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject StatsWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_StatsWindow,
      qt_meta_data_StatsWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &StatsWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *StatsWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *StatsWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_StatsWindow))
        return static_cast<void*>(const_cast< StatsWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int StatsWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
