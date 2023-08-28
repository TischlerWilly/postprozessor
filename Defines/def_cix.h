#ifndef DEF_CIX_H
#define DEF_CIX_H

//-----------------------------------------------------Werkstück:
#define CIX_WST_L   "LPX"   //Länge
#define CIX_WST_B   "LPY"   //Breite
#define CIX_WST_D   "LPZ"   //Dicke
#define CIX_WST_NULLPUNKTLISTE "ORLST"
    //Wird verwendet, um die Liste der Nullpunkte anzugeben
    //(als Separator das Komma benutzen)
#define CIX_WST_SPIEGELBAR  "SIMMETRY"
    //aktiviert/deaktiviert die Symmetrierung des Programms
    //Ermöglicht die Verwendung der symmetrischen Spindeln, wenn das Werkstück am
    //spiegelbildlichen Nullpunkt bearbeitet wird
#define CIX_WST_WKZ_OPTI    "TLCHK"
    //Wird verwendet, um die Optimierung der aktiven Bestückung zu aktivieren
    // 0 = aktiviert
    // 1 = deaktiviert/nicht aktiv
#define CIX_WST_WKZ_BESTUECKUNG "TOOLING"
    //Zahl der Konfiguration der Maschinendaten, die in der entsprechenden Umgebung
    //der numerischen Steuerung gespeichert wurde und für die Bearbeitung des Werkstücks
    //verwendet wird
#define CIX_WST_BENUTZERDATEN   "CUSTSTR"
    //Wird verwendet, um die kundenspezifischen Parameter anzugeben
    //Den String mit den individuell gestalteten Daten, getrennt durch Beistrich, angeben
#define CIX_WST_MASSEINHEIT "FCN"
    //Ermöglicht die Eingabe der Maßeinheit
    // 0 = Millimeter
    // 1 = Zoll
#define CIX_WST_BEARB_REFKANTENABST_X   "XCUT"
    //Abstandsmaß von der Kante bis zu dem eine Bearbeitung durch die
    //WST-Vermessung an die WST-Größe angepasst (verschoben) wird
#define CIX_WST_BEARB_REFKANTENABST_Y   "YCUT"
    //Abstandsmaß von der Kante bis zu dem eine Bearbeitung durch die
    //WST-Vermessung an die WST-Größe angepasst (verschoben) wird
#define CIX_WST_SCHABLONENHOEHE     "JIGTH"
    //Schablonenhöhe
#define CIX_WST_FREIGABE_AX_AY   "CKOP"
    //gibt die Verwendung der Tastatur an der Maschine frei, um im Bedarfsfall den
    //Nullpunkt verschieben zu können
    // Bit 0 = Verschiebung in X
    // Bit 1 = Verschiebung in Y
#define CIX_WST_EINZIGER_NULLPUNKT  "UNIQUE"
    //Wird verwendet, um den einzigen Nullpunkt freizugeben
    // 0 = “NO”
    // 1 = "YES"
#define CIX_WST_MATERIAL "MATERIAL"
    //Bezeichnung des Werkstückmaterials
    //Die zulässigen Werte sind jene, die in der Liste der Bilder der Werkstücke erscheinen
#define CIX_WST_BEARB_ENTGEGENGESETZT   "OPPWKRS"
    //nur für die Maschine “Skipper”
    // 0 = “NO”
    // 1 = “YES”
#define CIX_WST_SPANNER_UNNICLAMP   "UNICLAMP"
    //gibt den Einsatz der Spannvorrichtungen frei (Uniclamp)
    // 0 = deaktiviert
    // 1 = aktiviert
#define CIX_WST_KOLLISIONSKONTROLLE_TISCH   "CHKCOLL"
    //aktiviert die Kontrolle über die Positionierung der beweglichen Teile des
    //Tischs (anpassbare Saugnäpfe und bewegliche Auflagen)
#define CIX_WST_AUFSPANNZONE    "WTPIANI"
    //ermöglicht die Wahl des Konfigurationstyps der unabhängigen
    //Aufspannbereiche. Eine Konfiguration aus der Konfigurationsliste auswählen. Will man eine
    //Konfiguration, die man zu einem späteren Zeitpunkt, also in der Bestückungsphase (im
    //Anwendungsprogramm WorkTableTooling) individuell gestalten möchte, im
    //Bearbeitungsprogramm inkludieren, auf die Option manuelle Konfiguration klicken.
    //Will man sie nicht inkludieren, auf die Option Keine Konfiguration klicken.
#define CIX_WST_WKZ_DM_QUELLE   "COLLTOOL"
    //ermöglicht es die Art der Kontrolle über den Platzbedarf der
    //Werkzeuge festzulegen, um Kollisionen zu vermeiden
    //Maximaler Durchmesser: die Kontrolle erfolgt im Fenster der Werkzeugdaten unter
        //Berücksichtigung des maximalen Durchmessers des im Feld Max. Durchm. [mm]  definierten
        //Werkzeugs.
    //Durchmesser: die Kontrolle erfolgt im Fenster der Werkzeugdaten unter Berücksichtigung des
        //Durchmessers des im Feld Durchm. [mm]  definierten Werkzeugs.
#define CIX_WST_ETTIKETTENDRUCKER   "ENABLELABEL"
    //ermöglicht die Erzeugung des ISO Codes für die Etikettenbearbeitungen.
    //Dieser Parameter erscheint im Dialogfenster Werkstück-Variablen nur
    //dann, wenn die Maschine mit dem Etikettendrucker ausgestattet ist
    // 0 = “NO”
    // 1 = “YES”
#define CIX_WST_AUSWURFSPERRE   "LOCKWASTE"
    //aktiviert das Einspannen über die entsprechenden Vorrichtungen (anpassbare
    //Saugnäpfe usw.) all jener Bereiche des Werkstücks, die als Abfall betrachtet werden. Dieser
    //Befehl hat nur dann Gültigkeit, wenn der Tisch über die halbautomatische Positionierung bestückt
    //wird
    // 0 = “NO”
    // 1 = “YES”
#define CIX_WST_SAUGER_OPTIMIEREN   "RUNPAV"
    //ermöglicht die Aktivierung der Optimierung der Saugnäpfe, so dass in der
    //Ausführungsphase des Programms auch die halbautomatische Positionierung der Objekte des
    //Arbeitstisches durchgeführt wird. Diese Funktion vermeidet das Starten der halbautomatischen
    //Positionierung

//-----------------------------------------------------allgemein:
#define CIX_SEITE  "SIDE"
    //Seite des Werkstücks
    #define CIX_SEITE_OBSEI    "0"  //Oberseite
    #define CIX_SEITE_LI       "1"  //links
    #define CIX_SEITE_VO       "2"  //vorne
    #define CIX_SEITE_RE       "3"  //rechts
    #define CIX_SEITE_HI       "4"  //hinten
    #define CIX_SEITE_UNSEI    "5"  //Unterseite
#define CIX_BEZUG  "CRN"
    //Bezugsecke der Bearbeitung:
    #define CIX_BEZUG_OL  "1" //oben links
    #define CIX_BEZUG_UL  "2" //unten links
    #define CIX_BEZUG_OR  "3" //unte rechts
    #define CIX_BEZUG_UR  "4" //oben rechts
#define CIX_BEARB_ID    "ID"    //ID der Bearbeitung
#define CIX_BEARB_WKZ  "TNM"   //Werkzeugcode
#define CIX_BEARB_WKZART "TTP" //Werkzeugart
//Zulässige Werte bei Werkzeugklasse C_DRILLING:
    #define CIX_BEARB_WKZART_BO_STD "0" // 0 = NORMALE
    // 1 = LANCIA
    // 2 = SVASATA
    // 3 = NORMALEG
//Zulässige Werte bei Werkzeugklasse C_ROUTING
    // 100 = CANDELA
    // 101 = SAGOMATA
    // 102 = ROUT0
    // 103 = ROUT1

//-----------------------------------------------------Bohrungen:
#define CIX_BO_X    "X"     //X-Position
#define CIX_BO_Y    "Y"     //Y-Position
#define CIX_BO_Z    "Z"     //Z-Position
#define CIX_BO_BOTI "DP"    //Bohrtiefe
#define CIX_BO_DM   "DIA"   //Bohrdurchmesser
#define CIX_BO_IST_DUBO "THR"   //ist Durchgangsbohrung
    //1 = Durchgangsbearbeitung aktiviert.
    //0 = Durchgangsbearbeitung deaktiviert.
#define CIX_BO_WDH_TYP "RTY"    //Wiederholungstyp
    #define CIX_BO_WDH_TYP_KEIN "rpNO "   //-1 = Wiederholungen deaktiviert
    // 0 = “rpX”
    // 1 = “rpY”
    // 2 = “rpXY”
    // 3 = “rpCIR”
    // 5 = “rpAL”
#define CIX_BO_WDH_ABST_X   "DX"    //Wert des Achsenabstands in Richtung der Achse X
#define CIX_BO_WDH_ABST_Y   "DY"    //Wert des Achsenabstands in Richtung der Achse Y
#define CIX_BO_WDH_RAD      "R"     //Radius, um den die Wiederholungen ausgeführt werden
#define CIX_BO_WDH_STARTWINKEL    "A" //Anfangswinkel der Wiederholungen
#define CIX_BO_WDH_WINKEL   "DA"    //Winkelschritt zwischen den einzelnen Wiederholungen
#define CIX_BO_WDH_DREHZENTRUM_X    "XRC"   //X-Position des Drehzentrums der Kreislinie, um das die Wiederholung ausgeführt wird
#define CIX_BO_WDH_DREHZENTRUM_Y    "YRC"   //Y-Position des Drehzentrums der Kreislinie, um das die Wiederholung ausgeführt wird
#define CIX_BO_WDH_GERADENWINKEL    "ARP"   //Abwinkelung der Geraden, entlang der die Wiederholungen durchgeführt werden
#define CIX_BO_WDH_ABST     "LRP"   //Längenschritt/Abstand der Wiederholungen

#define CIX_BO_WDH_ANZAHL   "NRP"   //Anzahl der Wiederholungen

#define CIX_BO_OPTIMIEREN   "OPT"   //Optimierung der Bearbeitung
    // 0 = “NO”
    // 1 = “YES”
#define CIX_BO_WKZ_NEIGUNG  "AZ"    //Neigungswinkel des Werkzeugs
    //Neigungswinkel der Drehachse der Spindel im Vergleich zur Ebene X, Y
#define CIX_BO_WKZ_DREHWI   "AR"    //Drehwinkel des Werkzeugs
    //Drehwinkel der Spindelachse an der Ebene X, Y
#define CIX_BO_WKZ_DREHTYP  "CKA"   //aktiviert den Neigungstyp AR/AZ
    #define CIX_BO_WKZ_DREHTYP_KEIN "azrNO" // 0 = nicht gedreht/geneigt
    // 1 = “azrABS
    // 2 = “azrINC”
#define CIX_BO_BEZUG_SIABST "TOS"   //Beeiflusst den Sicherheitsabstand
    #define CIX_BO_BEZUG_SIABST_BEARBGRUND    "NO"  // 0 = bezieht sich auf den Grund der Bearbeitung
    #define CIX_BO_BEZUG_SIABST_WSTOBSEI "YES" // 1 = bezieht sich auf WST-Oberseite
#define CIX_BO_DREHZAHL "RSP"   //Drehzahl U/Min
#define CIX_BO_SPEED_ANAB   "IOS"   //An- und Abfahr-Geschwindigkeit
#define CIX_BO_SPEED        "WSP"   //Arbeitsgeschwindigkeit [mm/min]
    //Geschwindigkeit, mit der das Werkzeug die Bohrung durchführt
#define CIX_BO_REBOMA   "DDS"   //Restbohrmaß ab dem der Bohrer mit dem Abbremsen beginnen muss
    // 0 = Bohrer verlangsamt seine Geschwindigkeit nicht
#define CIX_BO_REBODREHZ    "DSP"   //Drehzahl der Spitze während des Durchschlagens des Werkstücks
    //wird wirksam wenn "DDS != 0"
    //Bleibt das Feld leer wird der Parameter aus dem wkz genommen
#define CIX_BO_ABBLASEN "BFC"   //Gebläse für Reinigung von den Sägespänen
    // 0 = “NO”
    // 1 = “YES”
#define CIX_BO_HAUBENPOS    "SHP"   //Haubenposition
    // Zulässige Werte von 0 bis 6
    #define CIX_BO_HAUBENPOS_AUTO "0"//automatisch
    // 1 = ganz oben
    // 6 = ganz unten
#define CIX_BO_LAYER    "LAY"   //Kennstring des der Geometrie zugeordneten Layers.
    //Dieser String wird nicht unter den Programmierungszeilen angezeigt, sondern im
    //Dialogfenster Layer-Verwaltung
#define CIX_BO_PRESSVORRICHTUNG_AKTV    "PRS"   //aktiviert oder deaktiviert die Anwendung der Pressvorrichtung
    // 0 = “NO”
    // 1 = “YES”












#endif // DEF_CIX_H
