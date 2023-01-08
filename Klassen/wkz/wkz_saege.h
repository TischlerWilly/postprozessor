#ifndef WKZ_SAEGE_H
#define WKZ_SAEGE_H

#include <QString>
#include "Klassen/text_zw.h"
#include "Funktionen/umwandeln.h"
#include "Defines/werkzeug.h"

class wkz_saege
{
public:
    wkz_saege();
    wkz_saege(text_zw wkz);

    //----------------------------------set:
    void set_wkznr(QString nr);
    void set_istaktiv(bool ja);
    void set_dm(double dm);
    void set_zustma(double zm);
    void set_sbreite(double schnittbreite);
    void set_isthori(bool ja);
    void set_istverti(bool ja);
    //----------------------------------get:
    text_zw daten();
    QString wkznr();
    bool istaktiv();
    double dm();
    double zustma();
    double sbreite();
    bool isthori();
    bool istverti();

private:
    //Werkzeugtyp           //0: WKZ-Typ
    QString Wkznr;          //1: Werkzeugnummer
    bool    IstAktiv;       //2: Ist Aktiv
    double  DM;             //3: Durchmesser
    double  Zustellmass;    //4: Zustellmaß
    double  Schnittbreite;  //5:Schnittbreite
    bool    IstHori;        //6: Ist horizontale Säge / kann horizontal sägen
    bool    IstVerti;       //7: Ist vertikale Säge / kann vertikal sägen


};

#endif // WKZ_SAEGE_H
