#include "UI/headers/infopanel.h"
#include "UI/headers/nailsproductinfovisitor.h"

#include <QVBoxLayout>
#include <QString>

InfoPanel::InfoPanel(NailsProduct& nailsProduct, QWidget* parent) :
    QWidget(parent),
    nailsProduct(nailsProduct)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignCenter); // flag di allineamento con ancoraggio al bordo superiore

    nameLabel = new QLabel();
    layout->addWidget(nameLabel); //append nel layout verticale

    sizeLabel = new QLabel();
    layout->addWidget(sizeLabel);

    polTimeLabel = new QLabel();
    layout->addWidget(polTimeLabel);

    NailsProductInfoVisitor visitor; // agiunge un widget contenente le informazioni specifiche di classe concreta
    nailsProduct.accept(visitor);
    layout->addWidget(visitor.getWidget());

    refresh();
}

void InfoPanel::refresh() {
    nameLabel->setText(QString::fromStdString(nailsProduct.getName()));
    sizeLabel->setText("Formato: " + QString::number(nailsProduct.getSize()) + " ml");
    polTimeLabel->setText("Tempo di polimerizzazione: " + QString::number(nailsProduct.getPolTime()) + " secondi");
}
