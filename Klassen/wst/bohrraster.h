#ifndef BOHRRASTER_H
#define BOHRRASTER_H

#include <QString>

#include "Klassen/text_zeilenweise.h"
#include "Klassen/text_zw.h"
#include "Defines/def_bearbeitungen.h"
#include "Funktionen/umwandeln.h"
#include "Funktionen/myfunktion.h"
#include "bohrung.h"
#include "Klassen/geo/punkt3d.h"

class bohrraster : public bohrung
{
public:
    bohrraster();
    bohrraster(QString text);

    QString text();
    QString text_erste_bohrung();
    void set_text(QString text);

    void set_anz_x(uint a);
    void set_anz_x(QString a);
    void set_anz_y(uint a);
    void set_anz_y(QString a);
    void set_anz_z(uint a);
    void set_anz_z(QString a);
    void set_raster_x(double rastermas);
    void set_raster_x(QString rastermas);
    void set_raster_y(double rastermas);
    void set_raster_y(QString rastermas);
    void set_raster_z(double rastermas);
    void set_raster_z(QString rastermas);
    void set_startbohrung(bohrung b);

    inline uint     anz_x()
    {
        return Anz_x;
    }
    inline QString  anz_x_qstring()
    {
        return double_to_qstring(Anz_x);
    }
    inline uint     anz_y()
    {
        return Anz_y;
    }
    inline QString  anz_y_qstring()
    {
        return double_to_qstring(Anz_y);
    }
    inline uint     anz_z()
    {
        return Anz_z;
    }
    inline QString  anz_z_qstring()
    {
        return double_to_qstring(Anz_z);
    }
    inline double   raster_x()
    {
        return Raster_x;
    }
    inline QString  raster_x_qstring()
    {
        return double_to_qstring(Raster_x);
    }
    inline double   raster_y()
    {
        return Raster_y;
    }
    inline QString  raster_y_qstring()
    {
        return double_to_qstring(Raster_y);
    }
    inline double   raster_z()
    {
        return Raster_z;
    }
    inline QString  raster_z_qstring()
    {
        return double_to_qstring(Raster_z);
    }

    bool finde_bohrraster(text_zeilenweise *bearb, \
                          QString Bezug, double dm, \
                          double tiefe, QString rasterrichtung, \
                          double wst_L, double wst_B, double wst_D,\
                          uint mindanz, double rasterabst);
    bool finde_bohrraster(text_zw *bearb, \
                          QString Bezug, double dm, \
                          double tiefe, QString rasterrichtung, \
                          double wst_L, double wst_B, double wst_D,\
                          uint mindanz, double rasterabst);

private:
    uint Anz_x;
    uint Anz_y;
    uint Anz_z;

    double Raster_x;
    double Raster_y;
    double Raster_z;

    void setup();
    void clear();
};

#endif // BOHRRASTER_H
