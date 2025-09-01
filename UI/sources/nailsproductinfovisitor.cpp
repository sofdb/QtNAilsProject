#include "UI/headers/nailsproductinfovisitor.h"
#include "logic/headers/smaltosemip.h"
#include "logic/headers/topbase.h"
#include "logic/headers/gelcostruttore.h"
#include "logic/headers/scala3converters.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QString>

QWidget* NailsProductInfoVisitor::getWidget(){
    return widget;
}

void NailsProductInfoVisitor::visitSmaltoSemip(const SmaltoSemip& prod){
    widget = new QLabel("Colore: " + QString::fromStdString(prod.SemicolorToString(prod.getColor())));
}

void NailsProductInfoVisitor::visitTopBase(const TopBase& prod){
    QWidget* w = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(w);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    layout->addWidget(new QLabel("Finish: " + QString::fromStdString(prod.FinishToString(prod.getFinish()))));
    layout->addWidget(new QLabel("Elasticità: " + QString::fromStdString(Scala3Converters::Scala3toString(prod.getElasticity()))));
    layout->addWidget(new QLabel("Aderenza: " + QString::fromStdString(Scala3Converters::Scala3toString(prod.getGrip()))));
    layout->addWidget(new QLabel("Tipologia: " + QString::fromStdString(prod.TBtypeToString(prod.getTBtype()))));

    widget = w;
}

void NailsProductInfoVisitor::visitGelCostruttore(const GelCostruttore& prod){
    QWidget* w = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(w);
    layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    layout->addWidget(new QLabel("Copertura: " + QString::fromStdString(Scala3Converters::Scala3toString(prod.getCoverage()))));
    layout->addWidget(new QLabel("Viscosità: " + QString::fromStdString(Scala3Converters::Scala3toString(prod.getViscosity()))));
    layout->addWidget(new QLabel("Tempo di pinzatura: " + QString::number(prod.getStap_time()) + " sec"));
    layout->addWidget(new QLabel("Durata: " + QString::number(prod.getDurability()) + " settimane"));

    widget = w;
}

