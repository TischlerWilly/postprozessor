#ifndef FUNKTIONEN_PRGTEXT_H
#define FUNKTIONEN_PRGTEXT_H

#include <QString>

#include "Defines/def_bearbeitungen.h"
#include "Klassen/wst/rechtecktasche.h"
#include "Klassen/wst/bohrung.h"
#include "Klassen/wst/bohrraster.h"
#include "Klassen/wst/nut.h"
#include "Klassen/wst/fraueseraufruf.h"
#include "Klassen/wst/fraesergerade.h"
#include "Klassen/wst/fraeserbogen.h"


QString bezug(QString b);
QString rta_zu_prgeile(QString text);
QString bohr_zu_prgeile(QString text);
QString bohrRaster_zu_prgeile(QString text);
QString nut_zu_prgeile(QString text);
QString fauf_zu_prgeile(QString text);
QString fgerade_zu_prgeile(QString text);
QString fbogen_zu_prgeile(QString text);

#endif // FUNKTIONEN_PRGTEXT_H


