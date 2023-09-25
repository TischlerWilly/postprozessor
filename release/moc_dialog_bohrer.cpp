/****************************************************************************
** Meta object code from reading C++ file 'dialog_bohrer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Dialoge/dialog_bohrer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog_bohrer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialog_bohrer_t {
    QByteArrayData data[11];
    char stringdata0[128];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_bohrer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_bohrer_t qt_meta_stringdata_Dialog_bohrer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "Dialog_bohrer"
QT_MOC_LITERAL(1, 14, 4), // "Data"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 7), // "text_zw"
QT_MOC_LITERAL(4, 28, 3), // "wkz"
QT_MOC_LITERAL(5, 32, 13), // "ist_neues_wkz"
QT_MOC_LITERAL(6, 46, 8), // "set_Data"
QT_MOC_LITERAL(7, 55, 3), // "msg"
QT_MOC_LITERAL(8, 59, 11), // "neuerBohrer"
QT_MOC_LITERAL(9, 71, 31), // "on_pushButton_abbrechen_clicked"
QT_MOC_LITERAL(10, 103, 24) // "on_pushButton_ok_clicked"

    },
    "Dialog_bohrer\0Data\0\0text_zw\0wkz\0"
    "ist_neues_wkz\0set_Data\0msg\0neuerBohrer\0"
    "on_pushButton_abbrechen_clicked\0"
    "on_pushButton_ok_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog_bohrer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   49,    2, 0x0a /* Public */,
       6,    1,   54,    2, 0x2a /* Public | MethodCloned */,
       8,    0,   57,    2, 0x0a /* Public */,
       9,    0,   58,    2, 0x08 /* Private */,
      10,    0,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    7,    5,
    QMetaType::Void, 0x80000000 | 3,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Dialog_bohrer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog_bohrer *_t = static_cast<Dialog_bohrer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Data((*reinterpret_cast< text_zw(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->set_Data((*reinterpret_cast< text_zw(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->set_Data((*reinterpret_cast< text_zw(*)>(_a[1]))); break;
        case 3: _t->neuerBohrer(); break;
        case 4: _t->on_pushButton_abbrechen_clicked(); break;
        case 5: _t->on_pushButton_ok_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Dialog_bohrer::*)(text_zw , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog_bohrer::Data)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Dialog_bohrer::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog_bohrer.data,
      qt_meta_data_Dialog_bohrer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Dialog_bohrer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog_bohrer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog_bohrer.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog_bohrer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Dialog_bohrer::Data(text_zw _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
