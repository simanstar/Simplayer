/****************************************************************************
** Meta object code from reading C++ file 'ControlPanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../panel/ControlPanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ControlPanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ControlPanel_t {
    QByteArrayData data[17];
    char stringdata[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ControlPanel_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ControlPanel_t qt_meta_stringdata_ControlPanel = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 12),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 5),
QT_MOC_LITERAL(4, 33, 5),
QT_MOC_LITERAL(5, 39, 13),
QT_MOC_LITERAL(6, 53, 12),
QT_MOC_LITERAL(7, 66, 4),
QT_MOC_LITERAL(8, 71, 5),
QT_MOC_LITERAL(9, 77, 4),
QT_MOC_LITERAL(10, 82, 12),
QT_MOC_LITERAL(11, 95, 13),
QT_MOC_LITERAL(12, 109, 9),
QT_MOC_LITERAL(13, 119, 5),
QT_MOC_LITERAL(14, 125, 7),
QT_MOC_LITERAL(15, 133, 12),
QT_MOC_LITERAL(16, 146, 4)
    },
    "ControlPanel\0stateChanged\0\0State\0state\0"
    "stateChanging\0updateButton\0play\0pause\0"
    "stop\0seek_forward\0seek_backward\0"
    "setVolume\0value\0setMute\0change_media\0"
    "item\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    0,   72,    2, 0x0a,
       6,    0,   73,    2, 0x08,
       7,    0,   74,    2, 0x08,
       8,    0,   75,    2, 0x08,
       9,    0,   76,    2, 0x08,
      10,    0,   77,    2, 0x08,
      11,    0,   78,    2, 0x08,
      12,    1,   79,    2, 0x08,
      14,    0,   82,    2, 0x08,
      15,    1,   83,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,

       0        // eod
};

void ControlPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ControlPanel *_t = static_cast<ControlPanel *>(_o);
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< State(*)>(_a[1]))); break;
        case 1: _t->stateChanging(); break;
        case 2: _t->updateButton(); break;
        case 3: _t->play(); break;
        case 4: _t->pause(); break;
        case 5: _t->stop(); break;
        case 6: _t->seek_forward(); break;
        case 7: _t->seek_backward(); break;
        case 8: _t->setVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setMute(); break;
        case 10: _t->change_media((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ControlPanel::*_t)(State );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlPanel::stateChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ControlPanel::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ControlPanel.data,
      qt_meta_data_ControlPanel,  qt_static_metacall, 0, 0}
};


const QMetaObject *ControlPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ControlPanel.stringdata))
        return static_cast<void*>(const_cast< ControlPanel*>(this));
    if (!strcmp(_clname, "BaseConstant"))
        return static_cast< BaseConstant*>(const_cast< ControlPanel*>(this));
    return QWidget::qt_metacast(_clname);
}

int ControlPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ControlPanel::stateChanged(State _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
