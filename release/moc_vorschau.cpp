/****************************************************************************
** Meta object code from reading C++ file 'vorschau.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Klassen/geo/vorschau.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vorschau.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_vorschau_t {
    QByteArrayData data[26];
    char stringdata0[312];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vorschau_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vorschau_t qt_meta_stringdata_vorschau = {
    {
QT_MOC_LITERAL(0, 0, 8), // "vorschau"
QT_MOC_LITERAL(1, 9, 23), // "anfrage_werkstueckmasse"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 14), // "sende_maus_pos"
QT_MOC_LITERAL(4, 49, 1), // "p"
QT_MOC_LITERAL(5, 51, 18), // "sende_zeilennummer"
QT_MOC_LITERAL(6, 70, 2), // "nr"
QT_MOC_LITERAL(7, 73, 10), // "bearbeiten"
QT_MOC_LITERAL(8, 84, 12), // "sende_wstmas"
QT_MOC_LITERAL(9, 97, 1), // "l"
QT_MOC_LITERAL(10, 99, 1), // "b"
QT_MOC_LITERAL(11, 101, 1), // "d"
QT_MOC_LITERAL(12, 103, 11), // "sende_drewi"
QT_MOC_LITERAL(13, 115, 1), // "w"
QT_MOC_LITERAL(14, 117, 18), // "slot_aktualisieren"
QT_MOC_LITERAL(15, 136, 10), // "werkstueck"
QT_MOC_LITERAL(16, 147, 5), // "w_neu"
QT_MOC_LITERAL(17, 153, 12), // "aktive_zeile"
QT_MOC_LITERAL(18, 166, 28), // "slot_aktualisieren_einzelwst"
QT_MOC_LITERAL(19, 195, 11), // "wkz_magazin"
QT_MOC_LITERAL(20, 207, 4), // "wkzm"
QT_MOC_LITERAL(21, 212, 31), // "slot_aktives_Element_einfaerben"
QT_MOC_LITERAL(22, 244, 12), // "zeilennummer"
QT_MOC_LITERAL(23, 257, 19), // "slot_zf_gleich_eins"
QT_MOC_LITERAL(24, 277, 10), // "slot_tunix"
QT_MOC_LITERAL(25, 288, 23) // "slot_sende_zeilennummer"

    },
    "vorschau\0anfrage_werkstueckmasse\0\0"
    "sende_maus_pos\0p\0sende_zeilennummer\0"
    "nr\0bearbeiten\0sende_wstmas\0l\0b\0d\0"
    "sende_drewi\0w\0slot_aktualisieren\0"
    "werkstueck\0w_neu\0aktive_zeile\0"
    "slot_aktualisieren_einzelwst\0wkz_magazin\0"
    "wkzm\0slot_aktives_Element_einfaerben\0"
    "zeilennummer\0slot_zf_gleich_eins\0"
    "slot_tunix\0slot_sende_zeilennummer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vorschau[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    1,   70,    2, 0x06 /* Public */,
       5,    2,   73,    2, 0x06 /* Public */,
       8,    3,   78,    2, 0x06 /* Public */,
      12,    1,   85,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    2,   88,    2, 0x0a /* Public */,
      18,    3,   93,    2, 0x0a /* Public */,
      21,    1,  100,    2, 0x0a /* Public */,
      23,    0,  103,    2, 0x08 /* Private */,
      24,    0,  104,    2, 0x08 /* Private */,
      25,    0,  105,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    4,
    QMetaType::Void, QMetaType::UInt, QMetaType::Bool,    6,    7,
    QMetaType::Void, QMetaType::Double, QMetaType::Double, QMetaType::Double,    9,   10,   11,
    QMetaType::Void, QMetaType::QString,   13,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int,   16,   17,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int, 0x80000000 | 19,   16,   17,   20,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void vorschau::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        vorschau *_t = static_cast<vorschau *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->anfrage_werkstueckmasse(); break;
        case 1: _t->sende_maus_pos((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 2: _t->sende_zeilennummer((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->sende_wstmas((*reinterpret_cast< double(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 4: _t->sende_drewi((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->slot_aktualisieren((*reinterpret_cast< werkstueck(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->slot_aktualisieren_einzelwst((*reinterpret_cast< werkstueck(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< wkz_magazin(*)>(_a[3]))); break;
        case 7: _t->slot_aktives_Element_einfaerben((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->slot_zf_gleich_eins(); break;
        case 9: _t->slot_tunix(); break;
        case 10: _t->slot_sende_zeilennummer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (vorschau::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vorschau::anfrage_werkstueckmasse)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (vorschau::*)(QPoint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vorschau::sende_maus_pos)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (vorschau::*)(uint , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vorschau::sende_zeilennummer)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (vorschau::*)(double , double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vorschau::sende_wstmas)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (vorschau::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&vorschau::sende_drewi)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject vorschau::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_vorschau.data,
      qt_meta_data_vorschau,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *vorschau::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vorschau::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_vorschau.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int vorschau::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void vorschau::anfrage_werkstueckmasse()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void vorschau::sende_maus_pos(QPoint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void vorschau::sende_zeilennummer(uint _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void vorschau::sende_wstmas(double _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void vorschau::sende_drewi(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
