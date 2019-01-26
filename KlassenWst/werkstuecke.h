#ifndef WERKSTUECKE_H
#define WERKSTUECKE_H

#include <QMessageBox>
#include <vector>
#include <QVector>

#include "werkstueck.h"
#include "../allgemKlassen/text_zeilenweise.h"
#include "../Definitionen/dateinamen.h"
#include "../Definitionen/def_fmc.h"
#include "../Definitionen/def_vw.h"
#include "../eigeneFunktionen/text.h"
#include "../eigeneFunktionen/myfunktion.h"

class werkstuecke
{
public:
    werkstuecke();

    bool ist_bekannt(QString Werkstueckname);
    bool neu(QString Werkstueckname, QString Quellformat);
    void clear();
    bool import_fmc_oberseite(QString Werkstueckname, QString importtext);
    bool import_fmc_unterseite(QString Werkstueckname, QString importtext);
    inline uint anzahl()
    {
        return namen.zeilenanzahl();
    }
    void stdnamen(text_zeilenweise namen_alt, text_zeilenweise namen_neu);
    void set_fkon_gerade_laenge(double wert);
    void set_kurze_geraden_importieren(bool wert);

    werkstueck get_wst(uint index);
    QString get_name(uint index);
    inline QString get_namen()
    {
        return namen.get_text();
    }
    inline text_zeilenweise get_namen_tz()
    {
        return namen;
    }
    QString suche_cad_fehler();

private:
    //Variabeln:
    text_zeilenweise namen;         //namen der Wst
    text_zeilenweise quellformate;  //aus welchem Dateiformat wurde das Wst eingelesen
    QVector<werkstueck> wste;       //hier werden alle Werkstücke gespeichert
    QString var_einsetzen(werkstueck w, QString formel);
    double min_fkon_gerade_laenge;  //minimale Geradenlänge. kürzere Geraden werden beim Import ignoriert
    bool kurze_geraden_import;

    //Funktionen:
    uint get_index(QString Werkstueckname);
    QString wert_nach_istgleich(QString text);
    bool ist_ziffer(const QChar zeichen);

};

#endif // WERKSTUECKE_H
