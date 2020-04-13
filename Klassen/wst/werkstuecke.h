#ifndef WERKSTUECKE_H
#define WERKSTUECKE_H

#include <QMessageBox>
#include <vector>
#include <QVector>

#include "werkstueck.h"
#include "Klassen/text_zeilenweise.h"
#include "Defines/dateinamen.h"
#include "Defines/def_fmc.h"
#include "Defines/def_vw.h"
#include "Funktionen/text.h"
#include "Funktionen/myfunktion.h"

class werkstuecke
{
public:
    werkstuecke();

    //--------------------------------------------------set_xy:
    bool neu(QString Werkstueckname, QString Quellformat);
    bool import_fmc_oberseite(QString Werkstueckname, QString importtext);
    bool import_fmc_unterseite(QString Werkstueckname, QString importtext);
    void set_fkon_gerade_laenge(double wert);
    void set_kurze_geraden_importieren(bool wert);

    //--------------------------------------------------get_xy:
    bool        ist_bekannt(QString Werkstueckname);
    werkstueck  wst(uint index);
    QString     name(uint index);
    QString     cad_fehler();

    inline uint             anzahl()
    {
        return Namen.zeilenanzahl();
    }
    inline QString          namen()
    {
        return Namen.text();
    }
    inline text_zeilenweise namen_tz()
    {
        return Namen;
    }

    //--------------------------------------------------Manipulationen:
    void clear();
    void stdnamen(text_zeilenweise namen_alt, text_zeilenweise namen_neu);

    //--------------------------------------------------

private:
    //Variabeln:
    text_zeilenweise    Namen;        //namen der Wst
    text_zeilenweise    Quellformate; //aus welchem Dateiformat wurde das Wst eingelesen
    QVector<werkstueck> Wste;         //hier werden alle Werkstücke gespeichert
    double              Min_fkon_gerade_laenge;  //minimale Geradenlänge. kürzere Geraden werden beim Import ignoriert
    bool                Kurze_geraden_import;

    //Funktionen:
    //--------------------------------------------------set_xy:

    //--------------------------------------------------get_xy:
    uint    index(QString Werkstueckname);
    QString wert_nach_istgleich(QString text);
    bool    ist_ziffer(const QChar zeichen);

    //--------------------------------------------------Manipulationen:
    QString var_einsetzen(werkstueck w, QString formel);

    //--------------------------------------------------

};

#endif // WERKSTUECKE_H
