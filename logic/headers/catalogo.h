#ifndef CATALOGO_H
#define CATALOGO_H

#include "logic/headers/nailsproduct.h"
#include "logic/headers/smaltosemip.h"
#include "logic/headers/topbase.h"
#include "logic/headers/gelcostruttore.h"

#include <QVector>
#include <QString>

class Catalogo
{
private:
    class Product { //classe di puntatori smart (super)polimorfi a NailsProduct
    public:
        NailsProduct* ptr; //puntatore (super)polimorfo dato che nailsProduct è astratta
        Product(const NailsProduct* prod);

        ~Product();
        Product(const Product& prod);
        Product& operator=(const Product& prod);
    };

    template<typename T>
    QVector<T*> getCategory() const {
        QVector<T*> categoryList;
        for (QVector<Catalogo::Product>::const_iterator cit = products.begin(); cit != products.end(); ++cit) {
            T* p = dynamic_cast<T*>(cit->ptr);
            if (p) {
                categoryList.push_back(p);
            }
        }
        return categoryList;
    }

    QVector<Product> products;

public:
    void addProduct(NailsProduct* nProd);
    void removeProduct(int index);
    NailsProduct*& getProduct(int index);
    NailsProduct* getProduct(int index) const; // versione con catalogo costante per sola lettura
    int size() const;

    void clear();
    QVector<NailsProduct*> getAllProducts() const;
    int findProductByName(const string& name) const;
    QVector<SmaltoSemip*> getSmaltoSemip() const;
    QVector<TopBase*> getTopBase() const;
    QVector<GelCostruttore*> getGelCostruttore() const;

    // Filtri per SmaltoSemip
    QVector<SmaltoSemip*> filterSmaltoByColor(SemiColor color) const;

    // Filtri per TopBase
    QVector<TopBase*> filterTopBase(std::optional<Finish> finish, std::optional<Scala3> elasticity, std::optional<Scala3> grip, std::optional<TopBaseType> TBtype) const;

    // Filtri per GelCostruttore
    QVector<GelCostruttore*> filterGelCostruttore(std::optional<Scala3> coverage, std::optional<Scala3> viscosity, std::optional<unsigned int> stapTime, std::optional<unsigned int> durability) const;

    // persistenza in JSON
    void saveToJson(const QString& fileName) const;
    void loadFromJson(const QString& fileName);
};

#endif // CATALOGO_H
