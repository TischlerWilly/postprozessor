#ifndef WERKSTUECKE_H
#define WERKSTUECKE_H

#include <QMessageBox>
#include <vector>
#include <QVector>

#include "werkstueck.h"
#include "../allgemKlassen/text_zeilenweise.h"
#include "../Definitionen/dateinamen.h"
#include "../Definitionen/def_fmc.h"
#include "../eigeneFunktionen/text.h"

class werkstuecke
{
public:
    werkstuecke();

    bool ist_bekannt(QString Werkstueckname);
    bool neu(QString Werkstueckname, QString Quellformat);
    void clear();
    bool import_fmc_oberseite(QString Werkstueckname, QString importtext);

private:
    //Variabeln:
    text_zeilenweise namen;         //namen der Wst
    text_zeilenweise quellformate;  //aus welchem Dateiformat wurde das Wst eingelesen
    QVector<werkstueck> wste;       //hier werden alle Werkstücke gespeichert


    //Funktionen:
    uint get_index(QString Werkstueckname);
    QString wert_nach_istgleich(QString text);

};

#endif // WERKSTUECKE_H
