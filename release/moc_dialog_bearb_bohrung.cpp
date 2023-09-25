/****************************************************************************
** Meta object code from reading C++ file 'dialog_bearb_bohrung.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Dialoge/dialog_bearb_bohrung.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog_bearb_bohrung.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialog_bearb_bohrung_t {
    QByteArrayData data[11];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_bearb_bohrung_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_bearb_bohrung_t qt_meta_stringdata_Dialog_bearb_bohrung = {
    {
QT_MOC_LITERAL(0, 0, 20), // "Dialog_bearb_bohrung"
QT_MOC_LITERAL(1, 21, 9), // "signal_bo"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 7), // "bohrung"
QT_MOC_LITERAL(4, 40, 2), // "bo"
QT_MOC_LITERAL(5, 43, 17), // "on_btn_ok_clicked"
QT_MOC_LITERAL(6, 61, 24), // "on_btn_abbrechen_clicked"
QT_MOC_LITERAL(7, 86, 28), // "on_pushButton_invert_clicked"
QT_MOC_LITERAL(8, 115, 29), // "on_pushButton_wkzwahl_clicked"
QT_MOC_LITERAL(9, 145, 7), // "get_wkz"
QT_MOC_LITERAL(10, 153, 3) // "wkz"

    },
    "Dialog_bearb_bohrung\0signal_bo\0\0bohrung\0"
    "bo\0on_btn_ok_clicked\0on_btn_abbrechen_clicked\0"
    "on_pushButton_invert_clicked\0"
    "on_pushButton_wkzwahl_clicked\0get_wkz\0"
    "wkz"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog_bearb_bohrung[] = {

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
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,
       8,    0,   50,    2, 0x08 /* Private */,
       9,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void Dialog_bearb_bohrung::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog_bearb_bohrung *_t = static_cast<Dialog_bearb_bohrung *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_bo((*reinterpret_cast< bohrung(*)>(_a[1]))); break;
        case 1: _t->on_btn_ok_clicked(); break;
        case 2: _t->on_btn_abbrechen_clicked(); break;
        case 3: _t->on_pushButton_invert_clicked(); break;
        case 4: _t->on_pushButton_wkzwahl_clicked(); break;
        case 5: _t->get_wkz((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Dialog_bearb_bohrung::*)(bohrung );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog_bearb_bohrung::signal_bo)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Dialog_bearb_bohrung::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog_bearb_bohrung.data,
      qt_meta_data_Dialog_bearb_bohrung,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Dialog_bearb_bohrung::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog_bearb_bohrung::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog_bearb_bohrung.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog_bearb_bohrung::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void Dialog_bearb_bohrung::signal_bo(bohrung _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
