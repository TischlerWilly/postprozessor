#ifndef WERKSTUECKE_H
#define WERKSTUECKE_H

#include "werkstueck.h"
#include "../allgemKlassen/text_zeilenweise.h"


class werkstuecke
{
public:
    werkstuecke();

    bool ist_bekannt(QString Werkstueckname);
    bool neu(QString Werkstueckname, QString Quellformat);
    void clear();

private:
    text_zeilenweise namen;         //namen der Wst
    text_zeilenweise quellformate;  //aus welchem Dateiformat wurde das Wst eingelesen
    //text_zeilenweise memory;    //hier werden alle Werkstücke gespeichert

};

#endif // WERKSTUECKE_H
