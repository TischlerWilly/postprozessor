/****************************************************************************
** Meta object code from reading C++ file 'dialog_exportuebersicht.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../Dialoge/dialog_exportuebersicht.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialog_exportuebersicht.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Dialog_ExportUebersicht_t {
    QByteArrayData data[17];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Dialog_ExportUebersicht_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Dialog_ExportUebersicht_t qt_meta_stringdata_Dialog_ExportUebersicht = {
    {
QT_MOC_LITERAL(0, 0, 23), // "Dialog_ExportUebersicht"
QT_MOC_LITERAL(1, 24, 13), // "slot_wstnamen"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 7), // "text_zw"
QT_MOC_LITERAL(4, 47, 5), // "namen"
QT_MOC_LITERAL(5, 53, 14), // "slot_wstexport"
QT_MOC_LITERAL(6, 68, 4), // "name"
QT_MOC_LITERAL(7, 73, 6), // "format"
QT_MOC_LITERAL(8, 80, 10), // "exportiert"
QT_MOC_LITERAL(9, 91, 19), // "slot_wst_umbenennen"
QT_MOC_LITERAL(10, 111, 8), // "name_vor"
QT_MOC_LITERAL(11, 120, 9), // "name_nach"
QT_MOC_LITERAL(12, 130, 19), // "slot_wst_ausblenden"
QT_MOC_LITERAL(13, 150, 10), // "ausblenden"
QT_MOC_LITERAL(14, 161, 11), // "resizeEvent"
QT_MOC_LITERAL(15, 173, 13), // "QResizeEvent*"
QT_MOC_LITERAL(16, 187, 5) // "event"

    },
    "Dialog_ExportUebersicht\0slot_wstnamen\0"
    "\0text_zw\0namen\0slot_wstexport\0name\0"
    "format\0exportiert\0slot_wst_umbenennen\0"
    "name_vor\0name_nach\0slot_wst_ausblenden\0"
    "ausblenden\0resizeEvent\0QResizeEvent*\0"
    "event"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Dialog_ExportUebersicht[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       5,    3,   42,    2, 0x0a /* Public */,
       9,    2,   49,    2, 0x0a /* Public */,
      12,    2,   54,    2, 0x0a /* Public */,
      14,    1,   59,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    6,    7,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    6,   13,
    QMetaType::Void, 0x80000000 | 15,   16,

       0        // eod
};

void Dialog_ExportUebersicht::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog_ExportUebersicht *_t = static_cast<Dialog_ExportUebersicht *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_wstnamen((*reinterpret_cast< text_zw(*)>(_a[1]))); break;
        case 1: _t->slot_wstexport((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 2: _t->slot_wst_umbenennen((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->slot_wst_ausblenden((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 4: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Dialog_ExportUebersicht::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Dialog_ExportUebersicht.data,
      qt_meta_data_Dialog_ExportUebersicht,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Dialog_ExportUebersicht::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Dialog_ExportUebersicht::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Dialog_ExportUebersicht.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Dialog_ExportUebersicht::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
