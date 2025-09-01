#include "logic/headers/smaltosemip.h"

SmaltoSemip::SmaltoSemip(const string& n, const string& im, const double& ml, const unsigned int& pol_sec, const SemiColor &col) :
    NailsProduct(n, im, ml, pol_sec),
    color(col){}

SmaltoSemip* SmaltoSemip::clone() const {
    return new SmaltoSemip(*this);
}

SemiColor SmaltoSemip::getColor() const { return color; }
void SmaltoSemip::setColor(const SemiColor& newColor) { color = newColor; }

bool SmaltoSemip::operator==(const NailsProduct& nProd) const  {
    return NailsProduct::operator==(nProd) &&
           color == static_cast<const SmaltoSemip&>(nProd).color;
}

void SmaltoSemip::accept(NailsProductVisitor& visitor) const {
    visitor.visitSmaltoSemip(*this);
}

string SmaltoSemip::SemicolorToString(const SemiColor& semiColor) {
    switch (semiColor) {
    case SemiColor::RossoCiliegia:
        return "RossoCiliegia";
    case SemiColor::Bordeaux:
        return "Bordeaux";
    case SemiColor::RosaConfetto:
        return "RosaConfetto";
    case SemiColor::NudeBeige:
        return "NudeBeige";
    case SemiColor::ViolaLavanda:
        return "ViolaLavanda";
    case SemiColor::BluNotte:
        return "BluNotte";
    case SemiColor::VerdeSmeraldo:
        return "VerdeSmeraldo";
    case SemiColor::NeroClassico:
        return "NeroClassico";
    case SemiColor::BiancoGhiaccio:
        return "BiancoGhiaccio";
    case SemiColor::GlitterArgento:
        return "GlitterArgento";
    default:
        return "Sconosciuto";
    }
}

SemiColor SmaltoSemip::StringToSemicolor(const string &s){
    if(s == "RossoCiliegia")
        return SemiColor::RossoCiliegia;
    if(s == "Bordeaux")
        return SemiColor::Bordeaux;
    if(s == "RosaConfetto")
        return SemiColor::RosaConfetto;
    if(s == "NudeBeige")
        return SemiColor::NudeBeige;
    if(s == "ViolaLavanda")
        return SemiColor::ViolaLavanda;
    if(s == "BluNotte")
        return SemiColor::BluNotte;
    if(s == "VerdeSmeraldo")
        return SemiColor::VerdeSmeraldo;
    if(s == "NeroClassico")
        return SemiColor::NeroClassico;
    if(s == "BiancoGhiaccio")
        return SemiColor::BiancoGhiaccio;
    if(s == "GlitterArgento")
        return SemiColor::GlitterArgento;
    return SemiColor::RossoCiliegia;
}
