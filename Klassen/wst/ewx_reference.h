#ifndef EWX_REFERENCE_H
#define EWX_REFERENCE_H

#include <QString>
#include "Klassen/geo/punkt3d.h"
#include "Funktionen/text.h"
#include "Klassen/text_zw.h"

class ewx_reference
{
public:
    ewx_reference();
    void set_text(QString zeile);

    punkt3d refpu();
    double richtung_x();
    double richtung_y();
    double richtung_z();

private:
    //Referenzpunkt:
    //Nullpunkt des ewx-wst in z ist Oberkante wst
    //Unterkante wst in z ist z.B. -19
    punkt3d Refpunkt;

    //Richtungen der Achsen:
    //1 == positiv , 2 == negativ
    double Richtung_x;
    double Richtung_y;
    double Richtung_z;


};

#endif // EWX_REFERENCE_H
