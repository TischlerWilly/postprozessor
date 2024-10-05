#ifndef EWX_REFERENCE_H
#define EWX_REFERENCE_H

#include <QString>
#include "Klassen/geo/punkt3d.h"
#include "Funktionen/text.h"
#include "Klassen/text_zw.h"
#include "Defines/def_bearbeitungen.h"

class ewx_reference
{
public:
    ewx_reference();
    void set_text(QString zeile);
    void set_wst_dicke(double dicke);

    punkt3d refpu();
    punkt3d vector_x();
    punkt3d vector_y();
    punkt3d vector_z();
    QString bezug();
    punkt3d bearbpos(punkt3d pos_in_ewx);

private:
    //Referenzpunkt:
    //Nullpunkt des ewx-wst in z ist Oberkante wst
    //Unterkante wst in z ist z.B. -19
    punkt3d Refpunkt;
    double Wst_dicke;
    punkt3d Vector_x;
    punkt3d Vector_y;
    punkt3d Vector_z;
    QString Bezug;

};

#endif // EWX_REFERENCE_H
