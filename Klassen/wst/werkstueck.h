#ifndef WERKSTUECK_H
#define WERKSTUECK_H

#include <QString>
#include <QMessageBox>

#include "Defines/werkzeug.h"
#include "Klassen/einstellung_ganx.h"
#include "Klassen/wst/wstzustand.h"
#include "Funktionen/umwandeln.h"
#include "Funktionen/runden.h"
#include "Funktionen/myfunktion.h"
#include "Defines/def_fmc.h"
#include "Defines/def_ganx.h"
#include "Klassen/text_zw.h"
#include "Klassen/wkz/wkz_magazin.h"
#include "bohrung.h"
#include "rechtecktasche.h"
#include "nut.h"
#include "fraeseraufruf.h"
#include "fraesergerade.h"
#include "fraeserbogen.h"
#include "bohrraster.h"
#include "Defines/dateinamen.h"
#include "ganx_gruppen.h"
#include "gehrung.h"
#include "Klassen/geo/geo_text.h"


class werkstueck
{
public:
    werkstueck();
    werkstueck(QString neuer_name);

    //--------------------------------------------------set_xy:
    void set_laenge(double l);
    void set_laenge(QString l);
    void set_breite(double b);
    void set_breite(QString b);
    void set_dicke(double d);
    void set_dicke(QString d);
    void neue_bearbeitung(QString text);
    void set_bearb(text_zw b);
    void set_kante_vo(QString artiklenummer);
    void set_kante_hi(QString artiklenummer);
    void set_kante_li(QString artiklenummer);
    void set_kante_re(QString artiklenummer);
    void set_zugabe_gehrungen(double wert);
    void set_zustand(QString format, wkz_magazin* wkzmag, QString drehung, \
                     bool formartierungen_aufbrechen, QString zust_fkon, \
                     bool gut_ist_oben);
    void set_einstellung_ganx(einstellung_ganx e);
    void set_use_ax(bool benutzen);
    void set_use_ay(bool benutzen);

    inline void set_name(QString neuer_name)
    {
        Name = neuer_name;
        Zustand.set_name(neuer_name);
    }
    inline void set_gute_seite(bool ist_oben)
    {
        Gut_ist_oben = ist_oben;
        Zustand.set_gute_seite(ist_oben);
    }

    //--------------------------------------------------get_xy:
    QString cad_fehler(bool kurz = false);
    double max_x(QString format);
    double min_x(QString format);
    double max_y(QString format);
    double min_y(QString format);
    double max_x();
    double max_x_einzelwst();
    double min_x();
    double max_y();
    double max_y_einzelwst();
    double min_y();
    geo_text geo(wkz_magazin wkzm);
    geo_text geofkon(wkz_magazin wkzm);
    inline double   laenge() const
    {
        return Laenge;
    }
    inline QString  laenge_qstring() const
    {
        return double_to_qstring(Laenge);
    }
    inline double   breite() const
    {
        return Breite;
    }
    inline QString  breite_qstring() const
    {
        return double_to_qstring(Breite);
    }
    inline double   dicke() const
    {
        return Dicke;
    }
    inline QString  dicke_qstring() const
    {
        return double_to_qstring(Dicke);
    }
    inline QString  name()
    {
        return Name;
    }
    inline text_zw bearb()
    {
        return Bearb;
    }
    inline text_zw *bearb_ptr()
    {
        return &Bearb;
    }
    inline wstzustand zustand()
    {
        return Zustand;
    }
    inline wstzustand *zustand_ptr()
    {
        return &Zustand;
    }
    inline QString kante_vo()
    {
        return Kante_vo;
    }
    inline QString kante_hi()
    {
        return Kante_hi;
    }
    inline QString kante_li()
    {
        return Kante_li;
    }
    inline QString kante_re()
    {
        return Kante_re;
    }
    inline bool use_ax()
    {
        return Zustand.use_ax();
    }
    inline bool use_ay()
    {
        return Zustand.use_ay();
    }
    inline bool ist_gut_oben()
    {
        return Gut_ist_oben;
    }
    //--------------------------------------------------Manipulationen:
    void gute_seite_ermitteln();
    //--------------------------------------------------

private:
    //Variabeln:
    double Laenge;  //X-Wert
    double Breite;  //Y-Wert
    double Dicke;   //Z-Wert
    text_zw Bearb;
    QString Name;
    QString Kante_vo; //Kante an X
    QString Kante_hi;
    QString Kante_li; //Kante an Y
    QString Kante_re;
    double  Zugabe_gehrungen;
    wstzustand Zustand;
    bool Gut_ist_oben;

    //Funktionen:

    inline QString drehung()
    {
        if(zustand().count())
        {
            return zustand().drehung();
        }else
        {
            return 0;
        }
    }
    inline double ay()
    {
        if(zustand().count())
        {
            return zustand().ay();
        }else
        {
            return 0;
        }
    }

};

#endif // WERKSTUECK_H
