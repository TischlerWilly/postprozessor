/****************************************************************************
** Meta object code from reading C++ file 'dialog_stdnamen.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Dialoge/dialog_stdnamen.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog_stdnamen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialog_stdnamen_t {
    QByteArrayData data[19];
    char stringdata0[305];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_stdnamen_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_stdnamen_t qt_meta_stringdata_Dialog_stdnamen = {
    {
QT_MOC_LITERAL(0, 0, 15), // "Dialog_stdnamen"
QT_MOC_LITERAL(1, 16, 14), // "signalEditNane"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 3), // "vor"
QT_MOC_LITERAL(4, 36, 4), // "nach"
QT_MOC_LITERAL(5, 41, 5), // "zeile"
QT_MOC_LITERAL(6, 47, 15), // "signal_sendData"
QT_MOC_LITERAL(7, 63, 7), // "text_zw"
QT_MOC_LITERAL(8, 71, 9), // "namen_vor"
QT_MOC_LITERAL(9, 81, 10), // "namen_nach"
QT_MOC_LITERAL(10, 92, 10), // "slot_setup"
QT_MOC_LITERAL(11, 103, 12), // "slot_getName"
QT_MOC_LITERAL(12, 116, 25), // "on_pushButton_neu_clicked"
QT_MOC_LITERAL(13, 142, 26), // "on_pushButton_edit_clicked"
QT_MOC_LITERAL(14, 169, 26), // "on_pushButton_entf_clicked"
QT_MOC_LITERAL(15, 196, 24), // "on_pushButton_ok_clicked"
QT_MOC_LITERAL(16, 221, 31), // "on_pushButton_abbrechen_clicked"
QT_MOC_LITERAL(17, 253, 24), // "on_pushButton_up_clicked"
QT_MOC_LITERAL(18, 278, 26) // "on_pushButton_down_clicked"

    },
    "Dialog_stdnamen\0signalEditNane\0\0vor\0"
    "nach\0zeile\0signal_sendData\0text_zw\0"
    "namen_vor\0namen_nach\0slot_setup\0"
    "slot_getName\0on_pushButton_neu_clicked\0"
    "on_pushButton_edit_clicked\0"
    "on_pushButton_entf_clicked\0"
    "on_pushButton_ok_clicked\0"
    "on_pushButton_abbrechen_clicked\0"
    "on_pushButton_up_clicked\0"
    "on_pushButton_down_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog_stdnamen[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   69,    2, 0x06 /* Public */,
       6,    2,   76,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    2,   81,    2, 0x0a /* Public */,
      11,    3,   86,    2, 0x0a /* Public */,
      12,    0,   93,    2, 0x08 /* Private */,
      13,    0,   94,    2, 0x08 /* Private */,
      14,    0,   95,    2, 0x08 /* Private */,
      15,    0,   96,    2, 0x08 /* Private */,
      16,    0,   97,    2, 0x08 /* Private */,
      17,    0,   98,    2, 0x08 /* Private */,
      18,    0,   99,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7,    8,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 7,    8,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Int,    3,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Dialog_stdnamen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog_stdnamen *_t = static_cast<Dialog_stdnamen *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalEditNane((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->signal_sendData((*reinterpret_cast< text_zw(*)>(_a[1])),(*reinterpret_cast< text_zw(*)>(_a[2]))); break;
        case 2: _t->slot_setup((*reinterpret_cast< text_zw(*)>(_a[1])),(*reinterpret_cast< text_zw(*)>(_a[2]))); break;
        case 3: _t->slot_getName((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->on_pushButton_neu_clicked(); break;
        case 5: _t->on_pushButton_edit_clicked(); break;
        case 6: _t->on_pushButton_entf_clicked(); break;
        case 7: _t->on_pushButton_ok_clicked(); break;
        case 8: _t->on_pushButton_abbrechen_clicked(); break;
        case 9: _t->on_pushButton_up_clicked(); break;
        case 10: _t->on_pushButton_down_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Dialog_stdnamen::*)(QString , QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog_stdnamen::signalEditNane)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Dialog_stdnamen::*)(text_zw , text_zw );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog_stdnamen::signal_sendData)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Dialog_stdnamen::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog_stdnamen.data,
      qt_meta_data_Dialog_stdnamen,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Dialog_stdnamen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog_stdnamen::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog_stdnamen.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog_stdnamen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void Dialog_stdnamen::signalEditNane(QString _t1, QString _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Dialog_stdnamen::signal_sendData(text_zw _t1, text_zw _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
