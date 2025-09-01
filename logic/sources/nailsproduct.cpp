#include "logic/headers/nailsproduct.h"
#include <stdexcept>

//costruttore
NailsProduct::NailsProduct(const string& n, const string& im, const double& ml, const unsigned int& pol_sec = 0) :
    name(n),
    image(im),
    size(ml),
    polimerization_time(pol_sec)
{
    if (ml <= 0) {
        throw std::invalid_argument("Il formato deve essere maggiore di zero.");
    }
}


string NailsProduct::getName() const { return name; }
void NailsProduct::setName(const string& newName){ name = newName; }

string NailsProduct::getImage() const { return image; }
void NailsProduct::setImage(const string& newImage){
    if (newImage.empty()) {
        image = "default.png";
    }
    else {
        image = newImage;
    }
}

double NailsProduct::getSize() const { return size; }
void NailsProduct::setSize(const double& newSize) {
    if (newSize <= 0) {
        throw std::invalid_argument("Il formato deve essere maggiore di zero.");
    }
    size = newSize;
}

int NailsProduct::getPolTime() const { return polimerization_time; }
void NailsProduct::setPolTime(const unsigned int &newPolTime){ polimerization_time = newPolTime; }

bool NailsProduct::operator==(const NailsProduct& nProd) const {// quando si hanno due puntatori a nailsProduct di cui non si conosce il tipo dinamico per fare il check di ugualianza devono avere lo stesso tipo dinamico
    return typeid(*this) == typeid(nProd) &&
           name == nProd.name &&
           image == nProd.image &&
           size == nProd.size &&
           polimerization_time == nProd.polimerization_time;
}
