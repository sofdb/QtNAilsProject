#include "Json/headers/jsonhandler.h"
#include "Json/headers/jsonvisitor.h"
#include "logic/headers/catalogo.h"
#include "logic/headers/nailsproduct.h"
#include "logic/headers/smaltosemip.h"
#include "logic/headers/topbase.h"
#include "logic/headers/gelcostruttore.h"
#include "logic/headers/scala3.h"
#include "logic/headers/scala3converters.h"

#include <QFile>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QDebug>
#include <QJsonValue>

NailsProduct* JsonHandler::createProductFromJson(const QJsonObject& obj)
{
    string name = obj["name"].toString().toStdString();
    string image = obj["image"].toString().toStdString();
    double size = obj["size"].toDouble();
    unsigned int polTime = obj["polimerization_time"].toInt();

    QString type = obj["type"].toString();

    if (type == "SmaltoSemip") {
        SemiColor color = SmaltoSemip::StringToSemicolor(obj["color"].toString().toStdString());
        SmaltoSemip temp(name, image, size, polTime, color);
        return temp.clone();
    }
    else if (type == "TopBase") {
        Finish finish = TopBase::StringToFinish(obj["finish"].toString().toStdString());
        Scala3 elasticity = Scala3Converters::StringToScala3(obj["elasticity"].toString().toStdString());
        Scala3 grip = Scala3Converters::StringToScala3(obj["grip"].toString().toStdString());
        TopBaseType TBtype = TopBase::StringToTBtype(obj["TBtype"].toString().toStdString());

        TopBase temp(name, image, size, polTime, finish, elasticity, grip, TBtype);
        return temp.clone();
    }
    else if (type == "GelCostruttore") {
        Scala3 coverage = Scala3Converters::StringToScala3(obj["coverage"].toString().toStdString());
        Scala3 viscosity = Scala3Converters::StringToScala3(obj["viscosity"].toString().toStdString());
        unsigned int stapTime = obj["stapling_time"].toInt();
        unsigned int durability = obj["durability"].toInt();

        GelCostruttore temp(name, image, size, polTime, coverage, viscosity, stapTime, durability);
        return temp.clone();
    }

    return nullptr;
}

void JsonHandler::saveCatalogToFile(const Catalogo& catalogo, const QString& fileName)
{
    QJsonArray jsonArray;
    JsonVisitor visitor;

    for(int i = 0; i < catalogo.size(); ++i) { // Itera su tutti i prodotti del catalogo
        NailsProduct* prod = catalogo.getProduct(i);
        prod->accept(visitor);
        jsonArray.append(visitor.getJsonProduct());
    }

    QJsonDocument doc(jsonArray);
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
    } else {
        qWarning("Couldn't open file for writing");
    }
}

void JsonHandler::loadCatalogFromFile(Catalogo& catalogo, const QString& fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open file for reading");
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray jsonArray = doc.array();

    catalogo.clear(); // Pulisce il catalogo prima di ricaricare

    for (int i = 0; i < jsonArray.size(); ++i) {
        const QJsonValue& value = jsonArray.at(i);
        if (value.isObject()) {
            QJsonObject obj = value.toObject();
            NailsProduct* prod = createProductFromJson(obj);
            if (prod) {
                catalogo.addProduct(prod);
            }
        }
    }
}
