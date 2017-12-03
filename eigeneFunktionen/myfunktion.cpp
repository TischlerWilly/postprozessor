#include "myfunktion.h"


QString ausdruck_auswerten(QString ausdruck)
{
    QString returnstring ="";
    WennDannSonst f(ausdruck);
    returnstring = f.bekomme_Ergebnis_als_String();
    return returnstring;
}

