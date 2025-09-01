#ifndef PRODUCTFILTERS_H
#define PRODUCTFILTERS_H

#include "logic/headers/nailsproduct.h"
#include "logic/headers/catalogo.h"

#include <QString>
#include <QComboBox>
#include <QLineEdit>

class ProductFilters {
public:
    static QList<NailsProduct*> filtra(
        const Catalogo& catalogo,
        const QString& searchText,
        const QString& tipoProdotto,
        const QString& color,
        const QString& finish,
        const QString& elasticity,
        const QString& grip,
        const QString& tbType,
        const QString& coverage,
        const QString& viscosity
    );
};

#endif // PRODUCTFILTERS_H
