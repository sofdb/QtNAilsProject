#ifndef NAILSPRODUCT_H
#define NAILSPRODUCT_H

#include "UI/headers/nailsproductvisitor.h"

#include <string>
#include <vector>
using std::string;
using std::vector;

class NailsProduct
{
private:
    string name;
    string image;
    double size; //in ml
    unsigned int polimerization_time; //in secondi

public:
    NailsProduct(const string& n, const string& im, const double& ml, const unsigned int& pol_sec);
    virtual ~NailsProduct() = default;
    virtual NailsProduct* clone() const = 0;

    string getName() const;
    void setName(const string& newName);

    string getImage() const;
    void setImage(const string& newImage);

    double getSize() const;
    void setSize(const double& newSize);

    int getPolTime() const;
    void setPolTime(const unsigned int& newPolTime);

    virtual bool operator==(const NailsProduct& nProd) const;

    virtual void accept(NailsProductVisitor& visitor) const = 0;
};

#endif // NAILSPRODUCT_H
