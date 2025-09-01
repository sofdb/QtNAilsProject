#include "UI/headers/productwidget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>

ProductWidget::ProductWidget(NailsProduct* prodotto, QWidget* parent) :
    QWidget(parent),
    prodotto(prodotto)
{
    infoPanel = new InfoPanel(*prodotto, this);
    imageWidget = new ImageWidget(this, QString::fromStdString(prodotto->getImage()));

    QHBoxLayout* productLayout = new QHBoxLayout();
    productLayout->setAlignment(Qt::AlignCenter);
    productLayout->addWidget(imageWidget);
    productLayout->addWidget(infoPanel);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(productLayout);
    setObjectName("productWidget");
    setLayout(mainLayout);
}

NailsProduct* ProductWidget::getProdotto() const {
    return prodotto;
}

void ProductWidget::refresh() {
    infoPanel->refresh();
    imageWidget->setImage(QString::fromStdString(prodotto->getImage()));
}

