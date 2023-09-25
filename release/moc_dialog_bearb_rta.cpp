/****************************************************************************
** Meta object code from reading C++ file 'dialog_bearb_rta.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Dialoge/dialog_bearb_rta.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog_bearb_rta.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialog_bearb_rta_t {
    QByteArrayData data[10];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_bearb_rta_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_bearb_rta_t qt_meta_stringdata_Dialog_bearb_rta = {
    {
QT_MOC_LITERAL(0, 0, 16), // "Dialog_bearb_rta"
QT_MOC_LITERAL(1, 17, 10), // "signal_rta"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 14), // "rechtecktasche"
QT_MOC_LITERAL(4, 44, 3), // "rta"
QT_MOC_LITERAL(5, 48, 24), // "on_btn_abbrechen_clicked"
QT_MOC_LITERAL(6, 73, 17), // "on_btn_ok_clicked"
QT_MOC_LITERAL(7, 91, 29), // "on_pushButton_wkzwahl_clicked"
QT_MOC_LITERAL(8, 121, 7), // "get_wkz"
QT_MOC_LITERAL(9, 129, 3) // "wkz"

    },
    "Dialog_bearb_rta\0signal_rta\0\0"
    "rechtecktasche\0rta\0on_btn_abbrechen_clicked\0"
    "on_btn_ok_clicked\0on_pushButton_wkzwahl_clicked\0"
    "get_wkz\0wkz"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog_bearb_rta[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,
       7,    0,   44,    2, 0x08 /* Private */,
       8,    1,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,

       0        // eod
};

void Dialog_bearb_rta::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog_bearb_rta *_t = static_cast<Dialog_bearb_rta *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_rta((*reinterpret_cast< rechtecktasche(*)>(_a[1]))); break;
        case 1: _t->on_btn_abbrechen_clicked(); break;
        case 2: _t->on_btn_ok_clicked(); break;
        case 3: _t->on_pushButton_wkzwahl_clicked(); break;
        case 4: _t->get_wkz((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Dialog_bearb_rta::*)(rechtecktasche );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog_bearb_rta::signal_rta)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Dialog_bearb_rta::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog_bearb_rta.data,
      qt_meta_data_Dialog_bearb_rta,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Dialog_bearb_rta::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog_bearb_rta::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog_bearb_rta.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog_bearb_rta::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Dialog_bearb_rta::signal_rta(rechtecktasche _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
