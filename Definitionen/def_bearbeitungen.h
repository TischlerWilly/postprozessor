#ifndef DEF_BEARBEITUNGEN_H
#define DEF_BEARBEITUNGEN_H


#define WST_BEZUG_OBSEI     "bezug_obsei"     //Bezugsfläche Wst-Oberseite
#define WST_BEZUG_UNSEI     "bezug_unsei"     //Bezugsfläche Wst-Unterseite
//der Programminterne WST-Nullpunkt ist links-unten
#define WST_BEZUG_LI        "bezug_li"        //Bezugsfläche Wst-Schmalfläche links (Westen)
#define WST_BEZUG_RE        "bezug_re"        //Bezugsfläche Wst-Schmalfläche rechts (Osten)
#define WST_BEZUG_VO        "bezug_vo"        //Bezugsfläche Wst-Schmalfläche vorne (Süden)
#define WST_BEZUG_HI        "bezug_hi"        //Bezugsfläche Wst-Schmalfläche hinten (Norden)

#define TRENNZ_BEARB_PARAM  '\t'             //Trennzeichen zur Trennung der einzelnen Parameter einer Bearbeitung
#define TRENNZ_BEARB_PARAM_ "\t"

#define BEARBART_BOHR       "bohrung"       //Bearbeitungsart Bohrung
/*
    Reihenfolge der Parameter:
    1: Bearbeitungsart: "bohrung"
    2: Bezugsfläche
    3: Durchmesser
    4: Tiefe
    5: Posision in X
    6: Position in Y
    7: Position in Z
    8: Ausführbedingung
    9: Zustellmaß           //optionaler Parameter, wenn Werk 0 ist, dann Zustellung gem Wkz-Magazin
*/

#define BEARBART_RTA        "rechtecktasche"    //Bearbeitungsart Rechtecktasche und Stulpfräsung
/*
    Reihenfolge der Parameter:
    1 : Bearbeitungsart: "rechtecktasche"
    2 : Bezugsfläche
    3 : Taschenlänge
    4 : Taschenbreite
    5 : Tiefe
    6 : Posision in X
    7 : Position in Y
    8 : Position in Z
    9 : Drehwinkel              //im Uhrzeigersinn
    10: Eckenradius
    11: Ausräumen
    12: Ausführbedingung
    13: Zustellmaß              //optionaler Parameter, wenn Werk 0 ist, dann Zustellung gem Wkz-Magazin
*/


























#endif // DEF_BEARBEITUNGEN_H
