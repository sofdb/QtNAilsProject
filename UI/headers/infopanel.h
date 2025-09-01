#ifndef INFOPANEL_H
#define INFOPANEL_H

#include "logic/headers/nailsproduct.h"

#include <QLabel>


class InfoPanel : public QWidget // informazioni generali di NailsProduct
{
    Q_OBJECT
private:
    NailsProduct& nailsProduct;
    QLabel* nameLabel;
    QLabel* sizeLabel;
    QLabel* polTimeLabel;

public:
    InfoPanel(NailsProduct& nailProduct, QWidget* parent = 0);
    void refresh();
};

#endif // INFOPANEL_H
