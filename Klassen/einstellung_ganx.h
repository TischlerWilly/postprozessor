#ifndef EINSTELLUNG_GANX_H
#define EINSTELLUNG_GANX_H

#include <QString>
#include <QMessageBox>
#include "Klassen/text_zeilenweise.h"
#include "Funktionen/umwandeln.h"

class einstellung_ganx
{
public:
    einstellung_ganx();
    void set_text(QString t);
    QString text();

public:
    double bezugsmass();
    bool bezugsmass_in_use();

    void set_bezugskantenmass(double b);
    void use_bezugsmass(bool in_use);
    void use_bezugsmass(QString in_use);

private:
    double Bezugskantenmass;
    bool Bezugsmass_in_use;
};

#endif // EINSTELLUNG_GANX_H
