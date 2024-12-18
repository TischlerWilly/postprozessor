#ifndef WERKSTUECKE_H
#define WERKSTUECKE_H

#include <QMessageBox>
#include <vector>
#include <QVector>

#include "werkstueck.h"
#include "Defines/dateinamen.h"
#include "Defines/def_fmc.h"
#include "Defines/def_dxf.h"
#include "Defines/def_vw.h"
#include "Funktionen/text.h"
#include "Funktionen/myfunktion.h"
#include "Klassen/einstellung_fmc.h"
#include "Klassen/einstellung_dxf.h"
#include "Klassen/einstellung_dxf_klassen.h"
#include "Klassen/geo/geofunktionen.h"
#include "Klassen/geo/geo_text.h"
#include "Klassen/wst/ewx_reference.h"

class werkstuecke
{
public:
    werkstuecke();

    //--------------------------------------------------set_xy:
    bool neu(QString Werkstueckname, QString Quellformat);
    bool import_ppf(QString Werkstueckname, QString importtext);
    QString eigen_import_parameter(QString parameterzeile, QString parameterbezeichnung);
    bool import_fmc(QString Werkstueckname, QString importtext, bool istOberseite);
    bool import_dxf(QString Werkstueckname, QString importtext, bool istOberseite);
    bool import_ewx(QString Werkstueckname, QString importtext);
    void set_fkon_gerade_laenge(double wert);
    void set_kurze_geraden_importieren(bool wert);
    void set_zugabe_gehrungen(double wert);
    bool entf(QString Werkstueckname);

    inline void set_einstellung_fmc(einstellung_fmc e)
    {
        Einstellung_fmc = e;
    }
    inline void set_einstellung_dxf(einstellung_dxf e)
    {
        Einstellung_dxf = e;
    }
    inline void set_einstellung_dxf_klassen(einstellung_dxf_klassen e)
    {
        Einstellung_dxf_klassen = e;
    }
    inline void set_name(uint zeilennummer,  QString neuer_name)
    {
        Namen.edit(zeilennummer, neuer_name);
    }
    //--------------------------------------------------get_xy:
    bool        ist_bekannt(QString Werkstueckname);
    int        get_index(QString Werkstueckname);
    werkstueck* wst(uint index);
    QString     name(uint index);
    QString     cad_fehler();

    inline uint             anzahl()
    {
        return Namen.count();
    }
    inline QString          namen()
    {
        return Namen.text();
    }
    inline text_zw namen_tz()
    {
        return Namen;
    }

    //--------------------------------------------------Manipulationen:
    void clear();
    QString stdnamen(text_zw namen_alt, text_zw namen_neu);
    void sortieren();
    //void ersetzen(werkstueck w, uint index);

    //--------------------------------------------------

private:
    //Variabeln:
    text_zw    Namen;        //namen der Wst
    text_zw    Quellformate; //aus welchem Dateiformat wurde das Wst eingelesen
    QVector<werkstueck> Wste;         //hier werden alle Werkstücke gespeichert
    double              Min_fkon_gerade_laenge;  //minimale Geradenlänge. kürzere Geraden werden beim Import ignoriert
    bool                Kurze_geraden_import;
    double              Zugabe_gehrungen;
    einstellung_fmc Einstellung_fmc;
    einstellung_dxf Einstellung_dxf;
    einstellung_dxf_klassen Einstellung_dxf_klassen;

    //Funktionen:
    //--------------------------------------------------set_xy:

    //--------------------------------------------------get_xy:
    int    index(QString Werkstueckname);
    QString wert_nach_istgleich(QString text);
    bool    ist_ziffer(const QChar zeichen);
    QString dxf_wert(QString namen, QString werte, QString gesucht);
    strecke dxf_strecke(QString namen, QString werte, QString dxf_version);
    kreis dxf_kreis(QString namen, QString werte, QString dxf_version);
    bogen dxf_bogen(QString namen, QString werte, QString dxf_version);
    bogenac dxf_bogenac(QString namen, QString werte, QString dxf_version);

    //--------------------------------------------------Manipulationen:
    QString var_einsetzen(werkstueck w, QString formel);

    //--------------------------------------------------

};

#endif // WERKSTUECKE_H
