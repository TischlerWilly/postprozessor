/****************************************************************************
** Meta object code from reading C++ file 'dialog_fraeserauswahl.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Dialoge/dialog_fraeserauswahl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog_fraeserauswahl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialog_fraeserauswahl_t {
    QByteArrayData data[9];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_fraeserauswahl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_fraeserauswahl_t qt_meta_stringdata_Dialog_fraeserauswahl = {
    {
QT_MOC_LITERAL(0, 0, 21), // "Dialog_fraeserauswahl"
QT_MOC_LITERAL(1, 22, 8), // "send_wkz"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 1), // "w"
QT_MOC_LITERAL(4, 34, 11), // "resizeEvent"
QT_MOC_LITERAL(5, 46, 13), // "QResizeEvent*"
QT_MOC_LITERAL(6, 60, 5), // "event"
QT_MOC_LITERAL(7, 66, 24), // "on_pushButton_ok_clicked"
QT_MOC_LITERAL(8, 91, 31) // "on_pushButton_abbrechen_clicked"

    },
    "Dialog_fraeserauswahl\0send_wkz\0\0w\0"
    "resizeEvent\0QResizeEvent*\0event\0"
    "on_pushButton_ok_clicked\0"
    "on_pushButton_abbrechen_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog_fraeserauswahl[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   37,    2, 0x08 /* Private */,
       7,    0,   40,    2, 0x08 /* Private */,
       8,    0,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Dialog_fraeserauswahl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog_fraeserauswahl *_t = static_cast<Dialog_fraeserauswahl *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_wkz((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 2: _t->on_pushButton_ok_clicked(); break;
        case 3: _t->on_pushButton_abbrechen_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Dialog_fraeserauswahl::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog_fraeserauswahl::send_wkz)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Dialog_fraeserauswahl::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog_fraeserauswahl.data,
      qt_meta_data_Dialog_fraeserauswahl,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Dialog_fraeserauswahl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog_fraeserauswahl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog_fraeserauswahl.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog_fraeserauswahl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Dialog_fraeserauswahl::send_wkz(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
