#ifndef WKZ_BOHRER_H
#define WKZ_BOHRER_H

#include <QString>
#include "Klassen/text_zw.h"
#include "Funktionen/umwandeln.h"

class wkz_bohrer
{
public:
    wkz_bohrer();
    wkz_bohrer(text_zw wkz);

    //----------------------------------set:
    void set_wkznr(QString nr);
    void set_istaktiv(bool ja);
    void set_dmimport(double dm);
    void set_dmexport(double dm);
    void set_nutzl(double n);
    void set_zustma(double zm);
    void set_istdubo(bool ja);
    void set_isthori(bool ja);
    void set_istverti(bool ja);
    //----------------------------------get:
    text_zw daten();
    QString wkznr();
    bool istaktiv();
    double dmimport();
    double dmexport();
    double nutzl();
    double zustma();
    bool istdubo();
    bool isthori();
    bool istverti();

private:
    //Werkzeugtyp           //0: WKZ-Typ
    QString Wkznr;          //1: Werkzeugnummer
    bool    IstAktiv;       //2: Ist Aktiv
    double  DMimport;       //3: DM für den Import in den pp
    double  DMexport;       //4: DM für den Export aus dem pp
    double  Nutzlaenge;     //5: Nutzlänge
    double  Zustellmass;    //6: Zustellmaß
    bool    IstDuBo;        //7: Ist Durchgangsbohrer
    bool    IstHori;        //8: Ist Horizontalbohrer / kann horizontal bohren
    bool    IstVerti;       //9: Ist Vertikalbohrer / kann vertikal bohren


};

#endif // WKZ_BOHRER_H
