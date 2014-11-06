/****************************************************************************
** Meta object code from reading C++ file 'PlayList.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../playlist/PlayList.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PlayList.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PlayList_t {
    QByteArrayData data[13];
    char stringdata[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_PlayList_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_PlayList_t qt_meta_stringdata_PlayList = {
    {
QT_MOC_LITERAL(0, 0, 8),
QT_MOC_LITERAL(1, 9, 12),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 8),
QT_MOC_LITERAL(4, 32, 12),
QT_MOC_LITERAL(5, 45, 7),
QT_MOC_LITERAL(6, 53, 12),
QT_MOC_LITERAL(7, 66, 8),
QT_MOC_LITERAL(8, 75, 17),
QT_MOC_LITERAL(9, 93, 17),
QT_MOC_LITERAL(10, 111, 17),
QT_MOC_LITERAL(11, 129, 16),
QT_MOC_LITERAL(12, 146, 4)
    },
    "PlayList\0mediaChanged\0\0filePath\0"
    "change_index\0addFile\0QStringList*\0"
    "fileList\0show_default_list\0show_current_list\0"
    "doubleSelectMedia\0QListWidgetItem*\0"
    "item\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x05,
       4,    1,   47,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    1,   50,    2, 0x0a,
       8,    0,   53,    2, 0x08,
       9,    0,   54,    2, 0x08,
      10,    1,   55,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,

       0        // eod
};

void PlayList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayList *_t = static_cast<PlayList *>(_o);
        switch (_id) {
        case 0: _t->mediaChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->change_index((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->addFile((*reinterpret_cast< QStringList*(*)>(_a[1]))); break;
        case 3: _t->show_default_list(); break;
        case 4: _t->show_current_list(); break;
        case 5: _t->doubleSelectMedia((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PlayList::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayList::mediaChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (PlayList::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PlayList::change_index)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject PlayList::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_PlayList.data,
      qt_meta_data_PlayList,  qt_static_metacall, 0, 0}
};


const QMetaObject *PlayList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlayList.stringdata))
        return static_cast<void*>(const_cast< PlayList*>(this));
    return QWidget::qt_metacast(_clname);
}

int PlayList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void PlayList::mediaChanged(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlayList::change_index(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_DefaultList_t {
    QByteArrayData data[9];
    char stringdata[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_DefaultList_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_DefaultList_t qt_meta_stringdata_DefaultList = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 16),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 12),
QT_MOC_LITERAL(4, 43, 10),
QT_MOC_LITERAL(5, 54, 11),
QT_MOC_LITERAL(6, 66, 4),
QT_MOC_LITERAL(7, 71, 16),
QT_MOC_LITERAL(8, 88, 11)
    },
    "DefaultList\0sequence_changed\0\0"
    "change_index\0write_file\0search_text\0"
    "text\0modify_item_text\0delete_item\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DefaultList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x05,
       3,    1,   45,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       4,    0,   48,    2, 0x08,
       5,    1,   49,    2, 0x08,
       7,    0,   52,    2, 0x08,
       8,    0,   53,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DefaultList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DefaultList *_t = static_cast<DefaultList *>(_o);
        switch (_id) {
        case 0: _t->sequence_changed(); break;
        case 1: _t->change_index((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->write_file(); break;
        case 3: _t->search_text((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->modify_item_text(); break;
        case 5: _t->delete_item(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DefaultList::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DefaultList::sequence_changed)) {
                *result = 0;
            }
        }
        {
            typedef void (DefaultList::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DefaultList::change_index)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject DefaultList::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_DefaultList.data,
      qt_meta_data_DefaultList,  qt_static_metacall, 0, 0}
};


const QMetaObject *DefaultList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DefaultList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DefaultList.stringdata))
        return static_cast<void*>(const_cast< DefaultList*>(this));
    return QListWidget::qt_metacast(_clname);
}

int DefaultList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void DefaultList::sequence_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DefaultList::change_index(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_CurrentList_t {
    QByteArrayData data[12];
    char stringdata[130];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_CurrentList_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_CurrentList_t qt_meta_stringdata_CurrentList = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 16),
QT_MOC_LITERAL(2, 29, 0),
QT_MOC_LITERAL(3, 30, 12),
QT_MOC_LITERAL(4, 43, 6),
QT_MOC_LITERAL(5, 50, 16),
QT_MOC_LITERAL(6, 67, 4),
QT_MOC_LITERAL(7, 72, 10),
QT_MOC_LITERAL(8, 83, 11),
QT_MOC_LITERAL(9, 95, 4),
QT_MOC_LITERAL(10, 100, 16),
QT_MOC_LITERAL(11, 117, 11)
    },
    "CurrentList\0sequence_changed\0\0"
    "change_index\0to_top\0QListWidgetItem*\0"
    "item\0write_file\0search_text\0text\0"
    "modify_item_text\0delete_item\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CurrentList[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x05,
       3,    1,   50,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       4,    1,   53,    2, 0x08,
       7,    0,   56,    2, 0x08,
       8,    1,   57,    2, 0x08,
      10,    0,   60,    2, 0x08,
      11,    0,   61,    2, 0x08,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CurrentList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CurrentList *_t = static_cast<CurrentList *>(_o);
        switch (_id) {
        case 0: _t->sequence_changed(); break;
        case 1: _t->change_index((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->to_top((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->write_file(); break;
        case 4: _t->search_text((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->modify_item_text(); break;
        case 6: _t->delete_item(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CurrentList::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CurrentList::sequence_changed)) {
                *result = 0;
            }
        }
        {
            typedef void (CurrentList::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CurrentList::change_index)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject CurrentList::staticMetaObject = {
    { &QListWidget::staticMetaObject, qt_meta_stringdata_CurrentList.data,
      qt_meta_data_CurrentList,  qt_static_metacall, 0, 0}
};


const QMetaObject *CurrentList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CurrentList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_CurrentList.stringdata))
        return static_cast<void*>(const_cast< CurrentList*>(this));
    return QListWidget::qt_metacast(_clname);
}

int CurrentList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
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
void CurrentList::sequence_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void CurrentList::change_index(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
