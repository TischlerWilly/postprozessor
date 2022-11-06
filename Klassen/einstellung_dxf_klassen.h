#ifndef EINSTELLUNG_DXF_KLASSEN_H
#define EINSTELLUNG_DXF_KLASSEN_H

#include <QString>
#include <QMessageBox>
#include "Klassen/text_zeilenweise.h"
#include "Funktionen/umwandeln.h"

class einstellung_dxf_klassen
{
public:
    einstellung_dxf_klassen();

    //set:
    void set_text(QString t);
    void set_wst(QString wstklasse);
    void set_bohr_vert(QString klasse);

    //get:
    QString text();
    QString wst();
    QString bohr_vert();

    private:
        QString Wst;
        QString BohrVert;

};

#endif // EINSTELLUNG_DXF_KLASSEN_H

//-------------------Funktionen nicht innerhalb der Klasse:
bool operator ==(einstellung_dxf_klassen e1, einstellung_dxf_klassen e2);
bool operator !=(einstellung_dxf_klassen e1, einstellung_dxf_klassen e2);
