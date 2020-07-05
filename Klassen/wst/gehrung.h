#ifndef GEHRUNG_H
#define GEHRUNG_H

#include "Klassen/text_zeilenweise.h"
#include "Defines/def_bearbeitungen.h"
#include "Funktionen/umwandeln.h"
#include "Klassen/geo/strecke.h"

class gehrung
{
public:
    gehrung();
    gehrung(QString text);

    void set_pfad(strecke s);
    void set_stapu(punkt3d sp);
    void set_endpu(punkt3d ep);
    void set_winkel(double w);
    void set_winkel(QString w);
    void set_bezug(QString bezugsflaeche);
    void set_afb(QString ausfuehrbedingung);
    void set_wkznum(QString nummer);

    strecke pfad();
    punkt3d stapu();
    punkt3d endpu();
    double winkel();
    QString winkel_qstring();
    QString bezug();
    QString afb();
    QString wkznum();

    QString text();
    void set_text(QString text);

private:
    strecke Pfad; //Definiert die Lage der Gehrung
    //Das WKZ befindet sich gedanklich immer auf der rechten Seite der Pfadlinie
    double Winkel; //Winkel ist immer Positiv und gibt die den Schwenkwinkel des Blattes an
    //0° == Blatt steht senkrecht
    QString Bezug; //Gehrungsspitze ist immer auf der gegenüberliegenden Fläche zur Bezugsfläche
    //Beispiel: Bezug ist oben --> Spitze der Gehrung ist unten
    QString Afb;
    QString Werkzeugnummer;

    void setup();
};

#endif // GEHRUNG_H
