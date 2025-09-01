#ifndef SCALA3CONVERTERS_H
#define SCALA3CONVERTERS_H

#include "logic/headers/scala3.h"

class Scala3Converters
{
public:
    static string Scala3toString(Scala3 value);
    static Scala3 StringToScala3(const string& s);
};

#endif // SCALA3CONVERTERS_H
