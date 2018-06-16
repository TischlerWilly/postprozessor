#ifndef BOHRRASTER_H
#define BOHRRASTER_H

#include <QString>

#include "../allgemKlassen/text_zeilenweise.h"
#include "../Definitionen/def_bearbeitungen.h"
#include "../eigeneFunktionen/umwandeln.h"
#include "../eigeneFunktionen/myfunktion.h"
#include "bohrung.h"

class bohrraster : public bohrung
{
public:
    bohrraster();
    bohrraster(QString text);

    QString get_text();
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

    inline uint get_anz_x()
    {
        return anz_x;
    }
    inline QString get_anz_x_qstring()
    {
        return double_to_qstring(anz_x);
    }
    inline uint get_anz_y()
    {
        return anz_y;
    }
    inline QString get_anz_y_qstring()
    {
        return double_to_qstring(anz_y);
    }
    inline uint get_anz_z()
    {
        return anz_z;
    }
    inline QString get_anz_z_qstring()
    {
        return double_to_qstring(anz_z);
    }
    inline double get_raster_x()
    {
        return raster_x;
    }
    inline QString get_raster_x_qstring()
    {
        return double_to_qstring(raster_x);
    }
    inline double get_raster_y()
    {
        return raster_y;
    }
    inline QString get_raster_y_qstring()
    {
        return double_to_qstring(raster_y);
    }
    inline double get_raster_z()
    {
        return raster_z;
    }
    inline QString get_raster_z_qstring()
    {
        return double_to_qstring(raster_z);
    }

    bool finde_bohrraster(text_zeilenweise bearb, \
                          QString bezug, double dm, \
                          double tiefe, QString rasterrichtung, \
                          double wst_L, double wst_B, double wst_D);

private:
    uint anz_x;
    uint anz_y;
    uint anz_z;

    double raster_x;
    double raster_y;
    double raster_z;

    void setup();
};

#endif // BOHRRASTER_H
