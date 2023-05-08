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

#define RASTERRICHTUNG_0_BIS_L  "0_bis_L"
#define RASTERRICHTUNG_0_BIS_B  "0_bis_B"
#define RASTERRICHTUNG_0_BIS_D  "0_bis_D"


#define BEARBART_BOHR       "bohrung"       //Bearbeitungsart Bohrung
/*
    Reihenfolge der Parameter:
    0 : Bearbeitungsart: "bohrung"
    1 : Bezugsfläche
    2 : Durchmesser
    3 : Tiefe
    4 : Posision in X
    5 : Position in Y
    6 : Position in Z
    7 : Ausführbedingung
    8 : Zustellmaß           //optionaler Parameter, wenn Werk 0 ist, dann Zustellung gem Wkz-Magazin
    9: WKZ-Nummer           //optionaler Parameter, für dierekte Fräserzuweisung KTA
*/

#define BEARBART_BOHRRASTER "borast"    //Bearbeitungsart Bohrraster
/*
    Reihenfolge der Parameter:
    0 : Bearbeitungsart: "bohrraster"
    1 : Bezugsfläche
    2 : Durchmesser
    3 : Tiefe
    4 : Posision in X
    5 : Position in Y
    6 : Position in Z
    7 : Ausführbedingung
    8 : Zustellmaß           //optionaler Parameter, wenn Werk 0 ist, dann Zustellung gem Wkz-Magazin
    9: WKZ-Nummer           //optionaler Parameter, für dierekte Fräserzuweisung KTA
    10: Anzahl der Bohrungen in X
    11: Anzahl der Bohrungen in Y
    12: Anzahl der Bohrungen in Z
    13: Rastermaß in X
    14: Rastermaß in Y
    15: Rastermaß in Z
*/

#define BEARBART_RTA        "rechtecktasche"    //Bearbeitungsart Rechtecktasche und Stulpfräsung
/*
    Reihenfolge der Parameter:
    0 : Bearbeitungsart: "rechtecktasche"
    1 : Bezugsfläche
    2 : Taschenlänge
    3 : Taschenbreite
    4 : Tiefe
    5 : Posision in X
    6 : Position in Y
    7 : Position in Z
    8 : Drehwinkel              //im Uhrzeigersinn
    9: Eckenradius
    10: Ausräumen
    11: Ausführbedingung
    12: Zustellmaß              //optionaler Parameter, wenn Werk 0 ist, dann Zustellung gem Wkz-Magazin
    13: WKZ-Nummer             //optionaler Parameter, für dierekte Fräserzuweisung RTA
*/

#define BEARBART_NUT        "nut"    //Bearbeitungsart Nut
/*
    Reihenfolge der Parameter:
    0 : Bearbeitungsart: "nut"
    1 : Bezugsfläche
    2 : Startpunkt in X
    3 : Startpunkt in Y
    4 : Endpunkt in X
    5 : Endpunkt in Y
    6 : Nuttiefe
    7 : Nutbreite
    8 : Ausführbedingung
*/

#define BEARBART_FRAESERAUFRUF  "fraufr"    //Bearbeitungsart Fräser-Aufruf
/*
    Reihenfolge der Parameter:
    0 : Bearbeitungsart: "fraufr"
    1 : Bezugsfläche
    2 : Startpunkt in X
    3 : Startpunkt in Y
    4 : Startpunkt in Z     //für Horizuntale Fräseraufrufe
    5 : Tiefe
    6 : Korrektur       L | M | R
    7 : Werkzeugnummer
    8 : Ausführbedingung
*/

//Fräser-Radius-Korrektur:
#define FRKOR_L     "L"
#define FRKOR_M     "M"
#define FRKOR_R     "R"

#define BEARBART_FRAESERGERADE  "frgradv"    //Bearbeitungsart Fräser-Gerade für vertikale Fräser
/*
    Reihenfolge der Parameter:
    0 : Bearbeitungsart: "frgrad"
    1 : Bezugsfläche
    2 : Startpunkt in X
    3 : Startpunkt in Y
    4 : Startpunkt Tiefe
    5 : Endtpunkt in X
    6 : Endtpunkt in Y
    7 : Endtpunkt Tiefe
    8 : Ausführbedingung
*/

#define BEARBART_FRAESERBOGEN  "frbogv"    //Bearbeitungsart Fräser-Bogen für vertikale Fräser
/*
    Reihenfolge der Parameter:
    0 : Bearbeitungsart: "frbog"
    1 : Bezugsfläche
    2 : Startpunkt in X
    3 : Startpunkt in Y
    4 : Startpunkt Tiefe
    5 : Endtpunkt in X
    6 : Endtpunkt in Y
    7 : Endtpunkt Tiefe
    8 : Radius
    9: im Urhreigersinn
        1 = uzs
        0 = guzs
    10: Ausführbedingung
*/

#define BEARBART_GEHRUNG       "gehrung"       //Bearbeitungsart Gehrung
/*
    Reihenfolge der Parameter:
    0 : Bearbeitungsart: "gehrung"
    1 : Bezugsfläche
    2 : Posision in X Stratpunkt
    3 : Posision in Y Startpunkt
    4 : Posision in X Endpunkt
    5 : Position in Y Endpunkt
    6 : Winkel
    7 : Ausführbedingung
    8 : WKZ-Nummer
    9: Ritz-Tiefe
    10: Schnitt-Tiefe
*/











#endif // DEF_BEARBEITUNGEN_H
