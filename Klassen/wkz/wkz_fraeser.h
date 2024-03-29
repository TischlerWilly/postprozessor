#ifndef WKZ_FRAESER_H
#define WKZ_FRAESER_H

#include <QString>
#include "Klassen/text_zw.h"
#include "Funktionen/umwandeln.h"
#include "Defines/werkzeug.h"

class wkz_fraeser
{
public:
    wkz_fraeser();
    wkz_fraeser(text_zw wkz);

    //----------------------------------set:
    void set_wkznr(QString nr);
    void set_istaktiv(bool ja);
    void set_dm(double dm);
    void set_nutzl(double n);
    void set_zustmavert(double zm);
    void set_zustmahori(double zm);
    void set_minzust(double mindestzustellung);
    void set_vorschub(double vorschub);
    void set_alias(QString alias);
    void set_spiegelwkz(QString wkz);
    void set_nurdirektzuw(bool ja);
    void set_isthori(bool ja);
    void set_istverti(bool ja);
    //----------------------------------get:
    text_zw daten();
    QString wkznr();
    bool istaktiv();
    double dm();
    double nutzl();
    double zustmavert();
    double zustmahori();
    double minzust();
    double vorschub();
    QString alias();
    QString spiegelwkz();
    bool nurdirektzuw();
    bool isthori();
    bool istverti();

private:
    //Werkzeugtyp               //0: WKZ-Typ
    QString Wkznr;              //1: Werkzeugnummer
    bool    IstAktiv;           //2: Ist Aktiv
    double  DM;                 //3: Durchmesser
    double  Nutzlaenge;         //4: Nutzlänge
    double  ZustMasVert;        //5: Zustellmaß vertikal
    double  MinZust;            //6: Mindest-Zustelltiefe
    double  Vorschub;           //7: Vorschub
    QString Alias;              //8: Alias-Name
    QString Spiegelwkz;         //9: Siegelwerkzeug
    bool    NurDirektZuweisen;  //10: Ist nur direkt Zuweisbar
    bool    IstHori;            //11: Ist horizontaler Fräser / kann horizontal fräsen
    bool    IstVerti;           //12: Ist vertikaler Fräser / kann vertikal fräsen
    double  ZustMasHori;        //13: Zustellmaß vertikal

};

#endif // WKZ_FRAESER_H
