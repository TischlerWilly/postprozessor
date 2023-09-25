/****************************************************************************
** Meta object code from reading C++ file 'dialog_doppelteil_erzeugen.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Dialoge/dialog_doppelteil_erzeugen.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog_doppelteil_erzeugen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialog_doppelteil_erzeugen_t {
    QByteArrayData data[15];
    char stringdata0[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_doppelteil_erzeugen_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_doppelteil_erzeugen_t qt_meta_stringdata_Dialog_doppelteil_erzeugen = {
    {
QT_MOC_LITERAL(0, 0, 26), // "Dialog_doppelteil_erzeugen"
QT_MOC_LITERAL(1, 27, 20), // "send_dlg_einstellung"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 5), // "bezug"
QT_MOC_LITERAL(4, 55, 5), // "wst_l"
QT_MOC_LITERAL(5, 61, 5), // "wst_b"
QT_MOC_LITERAL(6, 67, 8), // "spiegeln"
QT_MOC_LITERAL(7, 76, 6), // "drehen"
QT_MOC_LITERAL(8, 83, 24), // "on_pushButton_ok_clicked"
QT_MOC_LITERAL(9, 108, 31), // "on_pushButton_abbrechen_clicked"
QT_MOC_LITERAL(10, 140, 25), // "on_radioButton_vo_clicked"
QT_MOC_LITERAL(11, 166, 7), // "checked"
QT_MOC_LITERAL(12, 174, 25), // "on_radioButton_hi_clicked"
QT_MOC_LITERAL(13, 200, 25), // "on_radioButton_li_clicked"
QT_MOC_LITERAL(14, 226, 25) // "on_radioButton_re_clicked"

    },
    "Dialog_doppelteil_erzeugen\0"
    "send_dlg_einstellung\0\0bezug\0wst_l\0"
    "wst_b\0spiegeln\0drehen\0on_pushButton_ok_clicked\0"
    "on_pushButton_abbrechen_clicked\0"
    "on_radioButton_vo_clicked\0checked\0"
    "on_radioButton_hi_clicked\0"
    "on_radioButton_li_clicked\0"
    "on_radioButton_re_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog_doppelteil_erzeugen[] = {

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
       1,    5,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,
      10,    1,   62,    2, 0x08 /* Private */,
      12,    1,   65,    2, 0x08 /* Private */,
      13,    1,   68,    2, 0x08 /* Private */,
      14,    1,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Double, QMetaType::Double, QMetaType::Bool, QMetaType::Bool,    3,    4,    5,    6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   11,
    QMetaType::Void, QMetaType::Bool,   11,

       0        // eod
};

void Dialog_doppelteil_erzeugen::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog_doppelteil_erzeugen *_t = static_cast<Dialog_doppelteil_erzeugen *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_dlg_einstellung((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 1: _t->on_pushButton_ok_clicked(); break;
        case 2: _t->on_pushButton_abbrechen_clicked(); break;
        case 3: _t->on_radioButton_vo_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_radioButton_hi_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_radioButton_li_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_radioButton_re_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Dialog_doppelteil_erzeugen::*)(QString , double , double , bool , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Dialog_doppelteil_erzeugen::send_dlg_einstellung)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Dialog_doppelteil_erzeugen::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog_doppelteil_erzeugen.data,
      qt_meta_data_Dialog_doppelteil_erzeugen,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Dialog_doppelteil_erzeugen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog_doppelteil_erzeugen::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog_doppelteil_erzeugen.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog_doppelteil_erzeugen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void Dialog_doppelteil_erzeugen::send_dlg_einstellung(QString _t1, double _t2, double _t3, bool _t4, bool _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
