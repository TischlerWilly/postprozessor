/****************************************************************************
** Meta object code from reading C++ file 'dialog_programmtext.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Dialoge/dialog_programmtext.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog_programmtext.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialog_programmtext_t {
    QByteArrayData data[16];
    char stringdata0[200];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_programmtext_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_programmtext_t qt_meta_stringdata_Dialog_programmtext = {
    {
QT_MOC_LITERAL(0, 0, 19), // "Dialog_programmtext"
QT_MOC_LITERAL(1, 20, 17), // "signalIndexChange"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 5), // "index"
QT_MOC_LITERAL(4, 45, 16), // "signalWstChanged"
QT_MOC_LITERAL(5, 62, 11), // "werkstueck*"
QT_MOC_LITERAL(6, 74, 1), // "w"
QT_MOC_LITERAL(7, 76, 8), // "slot_wst"
QT_MOC_LITERAL(8, 85, 17), // "slot_zeilennummer"
QT_MOC_LITERAL(9, 103, 2), // "nr"
QT_MOC_LITERAL(10, 106, 10), // "bearbeiten"
QT_MOC_LITERAL(11, 117, 11), // "resizeEvent"
QT_MOC_LITERAL(12, 129, 13), // "QResizeEvent*"
QT_MOC_LITERAL(13, 143, 5), // "event"
QT_MOC_LITERAL(14, 149, 39), // "on_listWidget_prgtext_current..."
QT_MOC_LITERAL(15, 189, 10) // "currentRow"

    },
    "Dialog_programmtext\0signalIndexChange\0"
    "\0index\0signalWstChanged\0werkstueck*\0"
    "w\0slot_wst\0slot_zeilennummer\0nr\0"
    "bearbeiten\0resizeEvent\0QResizeEvent*\0"
    "event\0on_listWidget_prgtext_currentRowChanged\0"
    "currentRow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog_programmtext[] = {

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
       1,    1,   44,    2, 0x06 /* Public */,
       4,    2,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   52,    2, 0x0a /* Public */,
       8,    2,   55,    2, 0x0a /* Public */,
      11,    1,   60,    2, 0x08 /* Private */,
      14,    1,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::UInt, QMetaType::Bool,    9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

void Dialog_programmtext::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog_programmtext *_t = static_cast<Dialog_programmtext *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalIndexChange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signalWstChanged((*reinterpret_cast< werkstueck*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->slot_wst((*reinterpret_cast< werkstueck*(*)>(_a[1]))); break;
        case 3: _t->slot_zeilennummer((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 5: _t->on_listWidget_prgtext_currentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Dialog_programmtext::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog_programmtext::signalIndexChange)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Dialog_programmtext::*)(werkstueck * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog_programmtext::signalWstChanged)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Dialog_programmtext::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog_programmtext.data,
      qt_meta_data_Dialog_programmtext,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Dialog_programmtext::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog_programmtext::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog_programmtext.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog_programmtext::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void Dialog_programmtext::signalIndexChange(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Dialog_programmtext::signalWstChanged(werkstueck * _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
