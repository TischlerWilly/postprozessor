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










#endif // DEF_CIX_H
