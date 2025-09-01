#ifndef TOPBASE_H
#define TOPBASE_H

#include "logic/headers/scala3.h"
#include "logic/headers/nailsproduct.h"
using std::string;

enum class TopBaseType{
    Bonder,
    Fiber,
    Rubber,
    Hard
};

enum class Finish {
    Lucido,
    Opaco,
    Glitter
};

class TopBase : public NailsProduct
{
private:
    Finish finish;
    Scala3 elasticity;
    Scala3 grip;
    TopBaseType TBtype;

public:
    TopBase(const string& n, const string& im, const double& ml, const unsigned int& pol_sec, const Finish& f, const Scala3& el, const Scala3& gr, const TopBaseType& TBt);
    ~TopBase() override = default;

    TopBase* clone() const override;

    Finish getFinish() const;
    void setFinish(const Finish& newFinish);

    Scala3 getElasticity() const;
    void setElasticity(const Scala3& newElasticity);

    Scala3 getGrip() const;
    void setGrip(const Scala3& newGrip);

    TopBaseType getTBtype() const;
    void setTBtype(const TopBaseType& newTBtype);

    bool operator==(const NailsProduct& nProd) const override;

    void accept(NailsProductVisitor& visitor) const override;

    static string FinishToString(Finish f);
    static Finish StringToFinish(const string& s);
    static string TBtypeToString(TopBaseType t);
    static TopBaseType StringToTBtype(const string& s);
};


#endif // TOPBASE_H
