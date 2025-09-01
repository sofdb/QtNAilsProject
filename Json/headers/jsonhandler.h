#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QString>
#include <QJsonArray>
#include <QJsonDocument>
#include "logic/headers/catalogo.h"

class JsonHandler
{
private:
    static NailsProduct* createProductFromJson(const QJsonObject& obj);
public:
    static void saveCatalogToFile(const Catalogo& catalogo, const QString& fileName);
    static void loadCatalogFromFile(Catalogo& catalogo, const QString& fileName);
};

#endif // JSONHANDLER_H
