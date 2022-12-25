#ifndef BOGENAC_H
#define BOGENAC_H

#include <math.h>
#include "punkt3d.h"
#include "strecke.h"
#include "darstellungsatribute.h"

class bogenac : public darstellungsatribute
{
public:
    bogenac();

    //set:
    void set_text(QString geotext);
    void set_mipu(punkt3d p);
    void set_rad(double rad);
    void set_swi(double w);
    void set_ewi(double w);

    //get:
    QString text();
    punkt3d mipu();
    double rad();
    QString rad_QString();
    double swi();
    QString swi_QString();
    double ewi();
    QString ewi_QString();
    punkt3d spu();
    punkt3d epu();
    bool im_uzs();

    //Manipulationen:
    void    richtung_unkehren();

private:
    punkt3d Mipu;
    double Rad;
    double Swi;
    double Ewi;

};

#endif // BOGENAC_H
