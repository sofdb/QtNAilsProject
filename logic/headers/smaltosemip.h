#ifndef SMALTOSEMIP_H
#define SMALTOSEMIP_H

#include "logic/headers/nailsproduct.h"
using std::string;

enum class SemiColor{
    RossoCiliegia,
    Bordeaux,
    RosaConfetto,
    NudeBeige,
    ViolaLavanda,
    BluNotte,
    VerdeSmeraldo,
    NeroClassico,
    BiancoGhiaccio,
    GlitterArgento
};

class SmaltoSemip : public NailsProduct
{
private:
    SemiColor color;
public:
    SmaltoSemip(const string& n, const string& im, const double& ml, const unsigned int& pol_sec, const SemiColor& col);
    ~SmaltoSemip() override = default;

    SmaltoSemip* clone() const override;

    SemiColor getColor() const;
    void setColor(const SemiColor& newColor);

    bool operator==(const NailsProduct& nProd) const override;

    void accept(NailsProductVisitor& visitor) const override;

    static string SemicolorToString(const SemiColor& semiColor);
    static SemiColor StringToSemicolor(const string& s);
};

#endif // SMALTOSEMIP_H
