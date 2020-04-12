#ifndef MYFUNKTION_H
#define MYFUNKTION_H

#include <QString>
#include "Klassen/wenndannsonst.h"
#include "text.h"
#include "umwandeln.h"
#include "Klassen/geo/punkt3d.h"
#include "Klassen/geo/punkt2d.h"


QString ausdruck_auswerten (QString ausdruck);

bool ist_ziffer(const QChar zeichen);
bool ist_zahl(const QString text);
bool ist_buchstabe(QChar zeichen);

QString genauigkeit_reduzieren(QString zahl, uint nachkommastellen);

QString genauigkeit_reduzieren(double zahl, uint nachkommastellen);


#endif // MYFUNKTION_H
