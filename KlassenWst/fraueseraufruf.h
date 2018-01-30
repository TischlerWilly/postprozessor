#ifndef FRAUESERAUFRUF_H
#define FRAUESERAUFRUF_H

#include <QString>

#include "../allgemKlassen/text_zeilenweise.h"
#include "../Definitionen/def_bearbeitungen.h"
#include "../eigeneFunktionen/umwandeln.h"
#include "../geometrie/punkt3d.h"

class fraueseraufruf
{
public:
    fraueseraufruf();
    fraueseraufruf(QString text);

    void set_x(double x);
    void set_x(QString x);
    void set_y(double y);
    void set_y(QString y);
    void set_z(double z);
    void set_z(QString z);
    void set_tiefe(double ti);
    void set_tiefe(QString ti);
    void set_bezug(QString bezugsflaeche);
    void set_afb(QString ausfuehrbedingung);
    void set_radkor(QString kor);
    void set_wkznum(QString nummer);

    double get_x();
    QString get_x_qstring();
    double get_y();
    QString get_y_qstring();
    double get_z();
    QString get_z_qstring();
    double get_tiefe();
    QString get_tiefe_qstring();
    QString get_bezug();
    QString get_afb();
    QString get_radkor();
    QString get_wkznum();
    punkt3d get_pos_vertikal();

    QString get_text();
    void set_text(QString text);

private:
    double pos_x;
    double pos_y;
    double pos_z;   //für horizontale Fräseraufrufe
    double tiefe;   //ist die Eintauchtiefe = Oberfläche-Wst bis gesamte Bahntiefe
    QString bezug;
    QString afb;
    QString korrektur;
    QString werkzeugnummer;

    void setup();

};

#endif // FRAUESERAUFRUF_H
