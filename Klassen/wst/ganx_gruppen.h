#ifndef GANX_GRUPPEN_H
#define GANX_GRUPPEN_H

#include "Klassen/text_zeilenweise.h"
#include "Funktionen/umwandeln.h"




class ganx_Gruppen
{
public:
    ganx_Gruppen();    
    void clear();
    void neue_gruppe(QString bezugsflaeche);
    QString gruppen();
    QString letzten_gruppennamen();


private:

    void setup();

    text_zeilenweise Gruppen;
    text_zeilenweise Gruppenzeile;  //wird nach bedarf mit einem Mitgleid der Gruppe gefüllt
                                    //wird zum Auslesen der einzelnen Werte eines Gruppenmitgliedes benötigt
                                    //Parameter:
                                    //      Zeile 01:     Bezugsfläche
                                    //      derzeit nur 1 Parameter


};

#endif // GANX_GRUPPEN_H
