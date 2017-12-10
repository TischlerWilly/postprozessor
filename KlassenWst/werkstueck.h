#ifndef WERKSTUECK_H
#define WERKSTUECK_H

#include <QString>
#include "../eigeneFunktionen/umwandeln.h"

class werkstueck
{
public:
    werkstueck();

    void set_laenge(double l);
    void set_laenge(QString l);
    void set_breite(double b);
    void set_breite(QString b);
    void set_dicke(double d);
    void set_dicke(QString d);

    inline double get_laenge() const
    {
        return laenge;
    }
    inline QString get_laenge_qstring() const
    {
        return double_to_qstring(laenge);
    }
    inline double get_breite() const
    {
        return breite;
    }
    inline QString get_breite_qstring() const
    {
        return double_to_qstring(breite);
    }
    inline double get_dicke() const
    {
        return dicke;
    }
    inline QString get_dicke_qstring() const
    {
        return double_to_qstring(dicke);
    }

private:
    double laenge;
    double breite;
    double dicke;


};

#endif // WERKSTUECK_H
