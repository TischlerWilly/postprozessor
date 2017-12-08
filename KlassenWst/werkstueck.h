#ifndef WERKSTUECK_H
#define WERKSTUECK_H


class werkstueck
{
public:
    werkstueck();

    inline double get_laenge()
    {
        return l;
    }
    inline double get_breite()
    {
        return b;
    }
    inline double get_dicke()
    {
        return d;
    }

private:
    double l;
    double b;
    double d;


};

#endif // WERKSTUECK_H
