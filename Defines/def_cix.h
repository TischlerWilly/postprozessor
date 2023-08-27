#ifndef DEF_CIX_H
#define DEF_CIX_H

//Werkstück:
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











#endif // DEF_CIX_H
