#include "werkstueck.h"

werkstueck::werkstueck()
{
    laenge=0;
    breite=0;
    dicke=0;
}

void werkstueck::set_laenge(double l)
{
    if(l>0 && l<5000)
    {
        laenge = l;
    }
}

void werkstueck::set_laenge(QString l)
{
    set_laenge(l.toDouble());
}

void werkstueck::set_breite(double b)
{
    if(b>0 && b<5000)
    {
        breite = b;
    }
}

void werkstueck::set_breite(QString b)
{
    set_breite(b.toDouble());
}

void werkstueck::set_dicke(double d)
{
    if(d>0 && d<200)
    {
        dicke = d;
    }
}

void werkstueck::set_dicke(QString d)
{
    set_dicke(d.toDouble());
}
