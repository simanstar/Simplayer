/****************************************************************************
** Meta object code from reading C++ file 'SeekBar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../panel/SeekBar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SeekBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SeekBar_t {
    QByteArrayData data[10];
    char stringdata[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_SeekBar_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_SeekBar_t qt_meta_stringdata_SeekBar = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 10),
QT_MOC_LITERAL(2, 19, 0),
QT_MOC_LITERAL(3, 20, 10),
QT_MOC_LITERAL(4, 31, 4),
QT_MOC_LITERAL(5, 36, 5),
QT_MOC_LITERAL(6, 42, 15),
QT_MOC_LITERAL(7, 58, 26),
QT_MOC_LITERAL(8, 85, 9),
QT_MOC_LITERAL(9, 95, 17)
    },
    "SeekBar\0UpdateTime\0\0UpdateSkin\0seek\0"
    "value\0seek_only_pause\0close_audio_for_slidermove\0"
    "set_value\0change_is_pressed\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SeekBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       3,    0,   50,    2, 0x08,
       4,    1,   51,    2, 0x08,
       6,    1,   54,    2, 0x08,
       7,    0,   57,    2, 0x08,
       8,    1,   58,    2, 0x08,
       9,    0,   61,    2, 0x08,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,

       0        // eod
};

void SeekBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SeekBar *_t = static_cast<SeekBar *>(_o);
        switch (_id) {
        case 0: _t->UpdateTime(); break;
        case 1: _t->UpdateSkin(); break;
        case 2: _t->seek((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->seek_only_pause((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->close_audio_for_slidermove(); break;
        case 5: _t->set_value((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->change_is_pressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SeekBar::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SeekBar::UpdateTime)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject SeekBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SeekBar.data,
      qt_meta_data_SeekBar,  qt_static_metacall, 0, 0}
};


const QMetaObject *SeekBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SeekBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SeekBar.stringdata))
        return static_cast<void*>(const_cast< SeekBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int SeekBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void SeekBar::UpdateTime()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
struct qt_meta_stringdata_ClickBar_t {
    QByteArrayData data[3];
    char stringdata[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ClickBar_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ClickBar_t qt_meta_stringdata_ClickBar = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 22),
QT_MOC_LITERAL(2, 32, 0)
    },
    "ClickBar\0value_changed_by_click\0\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClickBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x05,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void ClickBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClickBar *_t = static_cast<ClickBar *>(_o);
        switch (_id) {
        case 0: _t->value_changed_by_click((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ClickBar::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ClickBar::value_changed_by_click)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ClickBar::staticMetaObject = {
    { &QSlider::staticMetaObject, qt_meta_stringdata_ClickBar.data,
      qt_meta_data_ClickBar,  qt_static_metacall, 0, 0}
};


const QMetaObject *ClickBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClickBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ClickBar.stringdata))
        return static_cast<void*>(const_cast< ClickBar*>(this));
    return QSlider::qt_metacast(_clname);
}

int ClickBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void ClickBar::value_changed_by_click(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
