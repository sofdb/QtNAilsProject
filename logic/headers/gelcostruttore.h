#ifndef GELCOSTRUTTORE_H
#define GELCOSTRUTTORE_H

#include "logic/headers/nailsproduct.h"
#include "logic/headers/scala3.h"
using std::string;

class GelCostruttore : public NailsProduct
{
private:
    Scala3 coverage;
    Scala3 viscosity;
    unsigned int stapling_time;//in sec
    unsigned int durability; //in settimane

public:
    GelCostruttore(const string& n, const string& im, const double& ml, const unsigned int& pol_sec, const Scala3& cov, const Scala3& vis, const unsigned int& st_sec, const unsigned int dur);
    ~GelCostruttore() override = default;
    GelCostruttore* clone() const override;

    Scala3 getCoverage() const;
    void setCoverage(const Scala3& newCoverage);

    Scala3 getViscosity() const;
    void setViscosity(const Scala3& newViscosity);

    unsigned int getStap_time() const;
    void setStap_time(const unsigned int& newStap_time);

    unsigned int getDurability() const;
    void setDurability(const unsigned int& newDurability);

    bool operator==(const NailsProduct& nProd) const override;

    void accept(NailsProductVisitor& visitor) const override;
};

#endif // GELCOSTRUTTORE_H
