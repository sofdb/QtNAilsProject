#include "Json/headers/jsonvisitor.h"
#include "logic/headers/smaltosemip.h"
#include "logic/headers/topbase.h"
#include "logic/headers/gelcostruttore.h"
#include "logic/headers/scala3converters.h"

QJsonObject JsonVisitor::getJsonProduct() const{
    return jsonProduct;
}

void JsonVisitor::visitSmaltoSemip(const SmaltoSemip& prod) {
    QJsonObject json;
    json["type"] = "SmaltoSemip";
    json["name"] = QString::fromStdString(prod.getName());
    json["image"] = QString::fromStdString(prod.getImage());
    json["size"] = prod.getSize();
    json["polimerization_time"] = prod.getPolTime();
    json["color"] = QString::fromStdString(prod.SemicolorToString(prod.getColor()));
    jsonProduct = json;
}

void JsonVisitor::visitTopBase(const TopBase& prod) {
    QJsonObject json;
    json["type"] = "TopBase";
    json["name"] = QString::fromStdString(prod.getName());
    json["image"] = QString::fromStdString(prod.getImage());
    json["size"] = prod.getSize();
    json["polimerization_time"] = prod.getPolTime();
    json["finish"] = QString::fromStdString(prod.FinishToString(prod.getFinish()));
    json["elasticity"] = QString::fromStdString(Scala3Converters::Scala3toString(prod.getElasticity()));
    json["grip"] = QString::fromStdString(Scala3Converters::Scala3toString(prod.getGrip()));
    json["tbtype"] = QString::fromStdString(prod.TBtypeToString(prod.getTBtype()));
    jsonProduct = json;
}

void JsonVisitor::visitGelCostruttore(const GelCostruttore& prod) {
    QJsonObject json;
    json["type"] = "GelCostruttore";
    json["name"] = QString::fromStdString(prod.getName());
    json["image"] = QString::fromStdString(prod.getImage());
    json["size"] = prod.getSize();
    json["polimerization_time"] = prod.getPolTime();
    json["coverage"] = QString::fromStdString(Scala3Converters::Scala3toString(prod.getCoverage()));
    json["viscosity"] = QString::fromStdString(Scala3Converters::Scala3toString(prod.getViscosity()));
    json["stapling_time"] = static_cast<int>(prod.getStap_time());
    json["durability"] = static_cast<int>(prod.getDurability());
    jsonProduct = json;
}

