#ifndef BOHRUNG_H
#define BOHRUNG_H

#include <QString>

#include "../allgemKlassen/text_zeilenweise.h"
#include "../Definitionen/def_bearbeitungen.h"
#include "../eigeneFunktionen/umwandeln.h"

class bohrung
{
public:
    bohrung();
    bohrung(QString text);

    void set_dm(double dm);
    void set_dm(QString dm);
    void set_tiefe(double ti);
    void set_tiefe(QString ti);
    void set_x(double x);
    void set_x(QString x);
    void set_y(double y);
    void set_y(QString y);
    void set_z(double z);
    void set_z(QString z);
    void set_bezug(QString bezugsflaeche);
    void set_afb(QString ausfuehrbedingung);

    double get_dm();
    QString get_dm_qstring();
    double get_tiefe();
    QString get_tiefe_qstring();
    double get_x();
    QString get_x_qstring();
    double get_y();
    QString get_y_qstring();
    double get_z();
    QString get_z_qstring();
    QString get_bezug();
    QString get_afb();

    QString get_text();
    void set_text(QString text);


private:
    double durchmesser;
    double tiefe;
    double pos_x;
    double pos_y;
    double pos_z;
    QString bezug;
    QString afb;

    void setup();

};

#endif // BOHRUNG_H
