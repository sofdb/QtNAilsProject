#ifndef PRODUCTWIDGET_H
#define PRODUCTWIDGET_H

#include <QWidget>
#include <QPushButton>

#include "logic/headers/nailsproduct.h"
#include "UI/headers/infopanel.h"
#include "UI/headers/imagewidget.h"

class ProductWidget : public QWidget {
    Q_OBJECT
private:
    NailsProduct* prodotto;
    InfoPanel* infoPanel;
    ImageWidget* imageWidget;

    void refreshLabels();

public:
    explicit ProductWidget(NailsProduct* prodotto, QWidget* parent = nullptr);
    NailsProduct* getProdotto() const;
    void refresh();
};

#endif // PRODUCTWIDGET_H
