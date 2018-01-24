#ifndef GEOMETRIE_H
#define GEOMETRIE_H

#include <math.h>

#include "makro_geometrie.h"
#include "punkt2d.h"
#include "strecke.h"
#include "bogen.h"




punkt2d drehen(punkt2d drehzentrum, punkt2d alter_punkt, \
             float drehwinkel, bool drehrichtung_im_uhrzeigersinn);
punkt3d drehen(punkt3d drehzentrum, punkt3d alter_punkt, \
             float drehwinkel, bool drehrichtung_im_uhrzeigersinn);

double winkel(double endpunkt_x, double endpunkt_y,\
              double mittelpunkt_x, double mittelpunkt_y);

double winkel(double endpunkt1_x, double endpunkt1_y,\
              double mittelpunkt_x, double mittelpunkt_y,\
              double endpunkt2_x, double endpunkt2_y);

void trimmen(QString *geo1, QString *geo2);

#endif // GEOMETRIE_H
