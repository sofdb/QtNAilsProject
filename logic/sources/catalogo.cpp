#include "logic/headers/catalogo.h"
#include "Json/headers/jsonhandler.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <stdexcept>

Catalogo::Product::Product(const NailsProduct* prod) : ptr(prod->clone()) {} //agisce anche da convertitore da nailsProducto* => Product

Catalogo::Product::~Product() { delete ptr; }
Catalogo::Product::Product(const Product& prod) : ptr((prod.ptr)->clone()) {} // copia profonde polimorfa

Catalogo::Product& Catalogo::Product::operator=(const Product& prod) {
    if(this != &prod){
        delete ptr;
        ptr = (prod.ptr)->clone();
    }
    return *this;
}

void Catalogo::addProduct(NailsProduct* nProd){
    if (nProd){ //INV: vettore non vuoto
        bool found = false;
        for(unsigned int i = 0; i < products.size() && !found; ++i){
            if(products[i].ptr && (*(products[i].ptr) == *nProd)){ //diversi in modo che non ci sia già memorizzato
                found = true;
            }
        }
        if(!found){ //non trovato
            products.push_back(nProd);
        } else {
            throw std::runtime_error("Errore: prodotto già presente nel catalogo");
        }
    }
}
void Catalogo::removeProduct(int index){
    if (index < 0 || index >= products.size()){
        throw std::out_of_range("Indice non valido");
    }
    products.remove(index);
}

NailsProduct*& Catalogo::getProduct(int index) {
    if (index < 0 || index >= products.size()) {
        throw std::out_of_range("Indice non valido");
    }
    return products[index].ptr;
}

NailsProduct* Catalogo::getProduct(int index) const {
    if (index < 0 || index >= products.size()) {
        throw std::out_of_range("Indice non valido");
    }
    return products[index].ptr;
}


int Catalogo::size() const {
    return products.size();
}

void Catalogo::clear() {
    products.clear();
}

QVector<NailsProduct*> Catalogo::getAllProducts() const {
    QVector<NailsProduct*> list;
    for (const Product& p : products)
        list.push_back(p.ptr);
    return list;
}

int Catalogo::findProductByName(const std::string& name) const {
    for (int i = 0; i < products.size(); ++i){
        if (products[i].ptr->getName() == name){
            return i;
        }
    }
    return -1;
}

QVector<SmaltoSemip*> Catalogo::getSmaltoSemip() const {
    return getCategory<SmaltoSemip>();
}

QVector<TopBase*> Catalogo::getTopBase() const {
    return getCategory<TopBase>();
}

QVector<GelCostruttore*> Catalogo::getGelCostruttore() const {
    return getCategory<GelCostruttore>();
}

// Filtri per SmaltoSemip
QVector<SmaltoSemip*> Catalogo::filterSmaltoByColor(SemiColor color) const{
    QVector<SmaltoSemip*> result;
    for(unsigned int i = 0; i < products.size(); ++i) {
        SmaltoSemip* s = dynamic_cast<SmaltoSemip*>(products[i].ptr);
        if(s && s->getColor() == color)
            result.append(s);
    }
    return result;
}

// Filtri per TopBase
QVector<TopBase*> Catalogo::filterTopBase(std::optional<Finish> finish, std::optional<Scala3> elasticity, std::optional<Scala3> grip, std::optional<TopBaseType> TBtype) const {
    QVector<TopBase*> result;
    for(unsigned int i = 0; i < products.size(); ++i) {
        TopBase* tb = dynamic_cast<TopBase*>(products[i].ptr);
        if(tb &&
            (!finish.has_value() || tb->getFinish() == finish.value()) &&
            (!elasticity.has_value() || tb->getElasticity() == elasticity.value()) &&
            (!grip.has_value() || tb->getGrip() == grip.value()) &&
            (!TBtype.has_value() || tb->getTBtype() == TBtype.value())){
            result.append(tb);
        }
    }
    return result;
}

// Filtri per GelCostruttore
QVector<GelCostruttore*> Catalogo::filterGelCostruttore(std::optional<Scala3> coverage, std::optional<Scala3> viscosity, std::optional<unsigned int> stapTime, std::optional<unsigned int> durability) const {
    QVector<GelCostruttore*> result;
    for(unsigned int i = 0; i < products.size(); ++i) {
        GelCostruttore* gel = dynamic_cast<GelCostruttore*>(products[i].ptr);
        if (gel &&
            (!coverage.has_value() || gel->getCoverage() == coverage.value()) &&
            (!viscosity.has_value() || gel->getViscosity() == viscosity.value()) &&
            (!stapTime.has_value() || gel->getStap_time() == stapTime.value()) &&
            (!durability.has_value() || gel->getDurability() == durability.value())){
            result.append(gel);
        }
    }
    return result;
}


// persistenza in JSON
void Catalogo::saveToJson(const QString& fileName) const {
    JsonHandler::saveCatalogToFile(*this, fileName);
}


void Catalogo::loadFromJson(const QString& fileName) {
    JsonHandler::loadCatalogFromFile(*this, fileName);
}

