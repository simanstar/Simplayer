/****************************************************************************
** Meta object code from reading C++ file 'ToolBar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tool/ToolBar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ToolBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ToolBar_t {
    QByteArrayData data[11];
    char stringdata[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_ToolBar_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_ToolBar_t qt_meta_stringdata_ToolBar = {
    {
QT_MOC_LITERAL(0, 0, 7),
QT_MOC_LITERAL(1, 8, 10),
QT_MOC_LITERAL(2, 19, 0),
QT_MOC_LITERAL(3, 20, 12),
QT_MOC_LITERAL(4, 33, 8),
QT_MOC_LITERAL(5, 42, 8),
QT_MOC_LITERAL(6, 51, 9),
QT_MOC_LITERAL(7, 61, 8),
QT_MOC_LITERAL(8, 70, 16),
QT_MOC_LITERAL(9, 87, 9),
QT_MOC_LITERAL(10, 97, 6)
    },
    "ToolBar\0addNewFile\0\0QStringList*\0"
    "fileList\0openFile\0aboutInfo\0snapShot\0"
    "synchronizeVideo\0adjustSet\0rotate\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ToolBar[] = {

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
       1,    1,   49,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    0,   52,    2, 0x08,
       6,    0,   53,    2, 0x08,
       7,    0,   54,    2, 0x08,
       8,    0,   55,    2, 0x08,
       9,    0,   56,    2, 0x08,
      10,    0,   57,    2, 0x08,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ToolBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ToolBar *_t = static_cast<ToolBar *>(_o);
        switch (_id) {
        case 0: _t->addNewFile((*reinterpret_cast< QStringList*(*)>(_a[1]))); break;
        case 1: _t->openFile(); break;
        case 2: _t->aboutInfo(); break;
        case 3: _t->snapShot(); break;
        case 4: _t->synchronizeVideo(); break;
        case 5: _t->adjustSet(); break;
        case 6: _t->rotate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ToolBar::*_t)(QStringList * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ToolBar::addNewFile)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ToolBar::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ToolBar.data,
      qt_meta_data_ToolBar,  qt_static_metacall, 0, 0}
};


const QMetaObject *ToolBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ToolBar.stringdata))
        return static_cast<void*>(const_cast< ToolBar*>(this));
    return QWidget::qt_metacast(_clname);
}

int ToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ToolBar::addNewFile(QStringList * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
