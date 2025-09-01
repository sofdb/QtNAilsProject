#include "logic/headers/scala3converters.h"

string Scala3Converters::Scala3toString(Scala3 value) {
    switch (value) {
    case Scala3::Bassa:
        return "Bassa";
    case Scala3::Media:
        return "Media";
    case Scala3::Alta:
        return "Alta";
    default:
        return "Sconosciuta";
    }
}

Scala3 Scala3Converters::StringToScala3(const string& s){
    if (s == "Bassa"){
        return Scala3::Bassa;
    }
    if (s == "Media"){
        return Scala3::Media;
    }
    if (s == "Alta"){
        return Scala3::Alta;
    }
    return Scala3::Media;
}

