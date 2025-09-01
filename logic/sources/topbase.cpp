#include "logic/headers/topbase.h"

TopBase::TopBase(const string& n, const string& im, const double& ml, const unsigned int& pol_sec, const Finish& f, const Scala3& el, const Scala3& gr, const TopBaseType&TBt) :
    NailsProduct(n, im, ml, pol_sec),
    finish(f),
    elasticity(el),
    grip(gr),
    TBtype(TBt) {}


TopBase* TopBase::clone() const {
    return new TopBase(*this);
}

Finish TopBase::getFinish() const { return finish; }
void TopBase::setFinish(const Finish& newFinish) { finish = newFinish; }

Scala3 TopBase::getElasticity() const { return elasticity; }
void TopBase::setElasticity(const Scala3& newElasticity) {elasticity = newElasticity; }

Scala3 TopBase::getGrip() const { return grip; }
void TopBase::setGrip(const Scala3& newGrip) { grip = newGrip; }

TopBaseType TopBase::getTBtype() const { return TBtype; }
void TopBase::setTBtype(const TopBaseType& newTBtype) { TBtype = newTBtype; }

bool TopBase::operator==(const NailsProduct& nProd) const  {
    return NailsProduct::operator==(nProd) &&
           finish == static_cast<const TopBase&>(nProd).finish &&
           elasticity == static_cast<const TopBase&>(nProd).elasticity &&
           grip == static_cast<const TopBase&>(nProd).grip &&
           TBtype == static_cast<const TopBase&>(nProd).TBtype;
}

void TopBase::accept(NailsProductVisitor& visitor) const {
    visitor.visitTopBase(*this);
}


string TopBase::FinishToString(Finish f){
    switch (f) {
    case Finish::Lucido:
        return "Lucido";
    case Finish::Opaco:
        return "Opaco";
    case Finish::Glitter:
        return "Glitter";
    default:
        return "Sconosciuto";
    }
}

Finish TopBase::StringToFinish(const string& s){
    if (s == "Lucido"){
        return Finish::Lucido;
    }
    if (s == "Opaco"){
        return Finish::Opaco;
    }
    if (s == "Glitter"){
        return Finish::Glitter;
    }
    return Finish::Lucido;
}

string TopBase::TBtypeToString(TopBaseType t){
    switch (t) {
    case TopBaseType::Bonder:
        return "Bonder";
    case TopBaseType::Fiber:
        return "Fiber";
    case TopBaseType::Rubber:
        return "Rubber";
    case TopBaseType::Hard:
        return "Hard";
    default:
        return "Sconosciuto";
    }
}

TopBaseType TopBase::StringToTBtype(const string& s){
    if (s == "Bonder"){
        return TopBaseType::Bonder;
    }
    if (s == "Fiber"){
        return TopBaseType::Fiber;
    }
    if (s == "Rubber"){
        return TopBaseType::Rubber;
    }
    if (s == "Hard"){
        return TopBaseType::Hard;
    }
    return TopBaseType::Bonder;
}
