/****************************************************************************
** Meta object code from reading C++ file 'CWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../../../Qt_projects/ParsingAssistant/CWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CWindow_t {
    QByteArrayData data[14];
    char stringdata0[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CWindow_t qt_meta_stringdata_CWindow = {
    {
QT_MOC_LITERAL(0, 0, 7), // "CWindow"
QT_MOC_LITERAL(1, 8, 13), // "cWindowClosed"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 13), // "onBackClicked"
QT_MOC_LITERAL(4, 37, 18), // "onParseModeClicked"
QT_MOC_LITERAL(5, 56, 14), // "onStartClicked"
QT_MOC_LITERAL(6, 71, 13), // "onStepClicked"
QT_MOC_LITERAL(7, 85, 16), // "onShowAllClicked"
QT_MOC_LITERAL(8, 102, 15), // "onRepeatClicked"
QT_MOC_LITERAL(9, 118, 17), // "onNewParseClicked"
QT_MOC_LITERAL(10, 136, 15), // "onInformClicked"
QT_MOC_LITERAL(11, 152, 15), // "onGenCorClicked"
QT_MOC_LITERAL(12, 168, 17), // "onGenIncorClicked"
QT_MOC_LITERAL(13, 186, 16) // "onGenRandClicked"

    },
    "CWindow\0cWindowClosed\0\0onBackClicked\0"
    "onParseModeClicked\0onStartClicked\0"
    "onStepClicked\0onShowAllClicked\0"
    "onRepeatClicked\0onNewParseClicked\0"
    "onInformClicked\0onGenCorClicked\0"
    "onGenIncorClicked\0onGenRandClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cWindowClosed(); break;
        case 1: _t->onBackClicked(); break;
        case 2: _t->onParseModeClicked(); break;
        case 3: _t->onStartClicked(); break;
        case 4: _t->onStepClicked(); break;
        case 5: _t->onShowAllClicked(); break;
        case 6: _t->onRepeatClicked(); break;
        case 7: _t->onNewParseClicked(); break;
        case 8: _t->onInformClicked(); break;
        case 9: _t->onGenCorClicked(); break;
        case 10: _t->onGenIncorClicked(); break;
        case 11: _t->onGenRandClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CWindow::cWindowClosed)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject CWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_CWindow.data,
    qt_meta_data_CWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void CWindow::cWindowClosed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
