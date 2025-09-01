/****************************************************************************
** Meta object code from reading C++ file 'catalogviewer.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../UI/headers/catalogviewer.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'catalogviewer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN13CatalogViewerE_t {};
} // unnamed namespace

template <> constexpr inline auto CatalogViewer::qt_create_metaobjectdata<qt_meta_tag_ZN13CatalogViewerE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "CatalogViewer",
        "aggiornaSelezione",
        "",
        "gestisciModifica",
        "gestisciRimozione",
        "gestisciInserimento",
        "filtraProdotti",
        "testo",
        "applyFilters"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'aggiornaSelezione'
        QtMocHelpers::SlotData<void()>(1, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'gestisciModifica'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'gestisciRimozione'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'gestisciInserimento'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'filtraProdotti'
        QtMocHelpers::SlotData<void(const QString &)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 7 },
        }}),
        // Slot 'applyFilters'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<CatalogViewer, qt_meta_tag_ZN13CatalogViewerE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject CatalogViewer::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13CatalogViewerE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13CatalogViewerE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13CatalogViewerE_t>.metaTypes,
    nullptr
} };

void CatalogViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<CatalogViewer *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->aggiornaSelezione(); break;
        case 1: _t->gestisciModifica(); break;
        case 2: _t->gestisciRimozione(); break;
        case 3: _t->gestisciInserimento(); break;
        case 4: _t->filtraProdotti((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->applyFilters(); break;
        default: ;
        }
    }
}

const QMetaObject *CatalogViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CatalogViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13CatalogViewerE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CatalogViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
