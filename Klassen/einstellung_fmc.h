#ifndef EINSTELLUNG_FMC_H
#define EINSTELLUNG_FMC_H

#include <QString>
#include <QMessageBox>
#include "Klassen/text_zw.h"
#include "Funktionen/umwandeln.h"

class einstellung_fmc
{
public:
    einstellung_fmc();

    //set:
    void set_text(QString t);
    void set_kenObsei(QString kennung_oberseite);
    void set_kenUnsei(QString kennung_unterseite);
    void set_dretypUnsei(QString drehtyp);

    //get:
    QString text();
    QString kenObsei();
    QString kenUnsei();
    QString drehtypUnsei();
    bool drehtyp_L();
    bool drehtyp_B();

private:
    QString KennungOberseite;
    QString KennungUnterseite;
    QString DrehtypUnterseite; // "L" "B"
};

#endif // EINSTELLUNG_FMC_H

//-------------------Funktionen nicht innerhalb der Klasse:
bool operator ==(einstellung_fmc e1, einstellung_fmc e2);
bool operator !=(einstellung_fmc e1, einstellung_fmc e2);
