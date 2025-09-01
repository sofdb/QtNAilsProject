#include "logic/headers/gelcostruttore.h"

GelCostruttore::GelCostruttore(const string &n, const string &im, const double &ml, const unsigned int &pol_sec, const Scala3& cov, const Scala3& vis, const unsigned int& st_sec, const unsigned int dur) :
    NailsProduct(n, im, ml, pol_sec),
    coverage(cov),
    viscosity(vis),
    stapling_time(st_sec),
    durability(dur)
{}

GelCostruttore* GelCostruttore::clone() const {
    return new GelCostruttore(*this);
}

Scala3 GelCostruttore::getCoverage() const{ return coverage; }
void GelCostruttore::setCoverage(const Scala3& newCoverage){ coverage = newCoverage; }

Scala3 GelCostruttore::getViscosity() const{ return viscosity; }
void GelCostruttore::setViscosity(const Scala3& newViscosity){ viscosity = newViscosity; }

unsigned int GelCostruttore::getStap_time() const{ return stapling_time; }
void GelCostruttore::setStap_time(const unsigned int& newStap_time){ stapling_time = newStap_time; }

unsigned int GelCostruttore::getDurability() const{ return durability; }
void GelCostruttore::setDurability(const unsigned int& newDurability){ durability = newDurability; }

bool GelCostruttore::operator==(const NailsProduct& nProd) const  {
    return NailsProduct::operator==(nProd) &&
           coverage == static_cast<const GelCostruttore&>(nProd).coverage &&
           viscosity == static_cast<const GelCostruttore&>(nProd).viscosity &&
           stapling_time == static_cast<const GelCostruttore&>(nProd).stapling_time &&
           durability == static_cast<const GelCostruttore&>(nProd).durability ;
}

void GelCostruttore::accept(NailsProductVisitor& visitor) const {
    visitor.visitGelCostruttore(*this);
}

