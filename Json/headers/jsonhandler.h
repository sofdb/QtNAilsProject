#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include "logic/headers/catalogo.h"

#include <QString>
#include <QJsonArray>
#include <QJsonDocument>

class JsonHandler
{
private:
    static NailsProduct* createProductFromJson(const QJsonObject& obj);
public:
    static void saveCatalogToFile(const Catalogo& catalogo, const QString& fileName);
    static void loadCatalogFromFile(Catalogo& catalogo, const QString& fileName);
};

#endif // JSONHANDLER_H
