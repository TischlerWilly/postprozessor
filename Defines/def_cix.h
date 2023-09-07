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
//---------------------------------------------Werkzeug:
#define CIX_WKZ  "TNM"   //Werkzeugcode
#define CIX_WKZGRUPPE "TCL"   //Werkzeuggruppe/Werkzeugklasse
    #define CIX_WKZGRUPPE_BOHRER  "0"  //C_DRILLING
    #define CIX_WKZGRUPPE_FRAESER "1"  //C_ROUTING
    #define CIX_WKZGRUPPE_SAEGER  "2"  //C_Cutting
#define CIX_WKZART "TTP" //Werkzeugart
//Zulässige Werte bei Werkzeugklasse C_DRILLING:
    #define CIX_WKZART_BO_STD "0" // 0 = NORMALE
    // 1 = LANCIA
    // 2 = SVASATA
    // 3 = NORMALEG
//Zulässige Werte bei Werkzeugklasse C_ROUTING
    // 100 = CANDELA
    // 101 = SAGOMATA
    // 102 = ROUT0
    // 103 = ROUT1
//Zulässige Werte bei Werkzeugklasse C_Cutting
    #define CIX_WKZART_SAEGE_STD "200" // 200 = Säge
#define CIX_WKZSPINDEL "SPI"  //Angabe der Elektrospindel, mit der die Bearbeitung auszuführen ist
    //Dieses Feld kann dann nützlich sein, wenn die Notwendigkeit besteht, eine Bearbeitung mit einem
    //Aggregat/Werkzeug durchzuführen, das nur von einer spezifischen Elektrospindel aufgenommen
    //werden kann. Unbedingt sicherstellen, dass die gewählte Elektrospindel an der Maschine
    //vorhanden ist oder dass die mit dem Magazin kompatibel ist, in dem sich das zu montierende
    //Werkzeug befindet, andernfalls hat die Optimierung keinen Erfolg. Das leere Datenfeld autorisiert
    //das CAM-System, die Wahl der Elektrospindel vorzunehmen.
    #define CIX_WKZSPINDEL_AUTO   ""
#define CIX_DREHZAHL "RSP"   //Drehzahl U/Min
#define CIX_SPEED_ANAB   "IOS"   //An- und Abfahr-Geschwindigkeit
#define CIX_SPEED        "WSP"   //Arbeitsgeschwindigkeit [mm/min]
    //Geschwindigkeit, mit der das Werkzeug die Bohrung/Fräsung durchführt
#define CIX_DREHZ_LETZTE_ZUST    "DSP"   //Drehzahl der Spitze während des Durchschlagens des Werkstücks
    //wird wirksam wenn "Restbohrmaß != 0"
    //Bleibt das Feld leer wird der Parameter aus dem wkz genommen
#define CIX_ABBLASEN "BFC"   //Gebläse für Reinigung von den Sägespänen
    // 0 = “NO”
    // 1 = “YES”
#define CIX_HAUBENPOS    "SHP"   //Haubenposition
    // Zulässige Werte von 0 bis 6
    #define CIX_HAUBENPOS_AUTO "0"//automatisch
    // 1 = ganz oben
    // 6 = ganz unten
#define CIX_ABWEISER    "UDT"
    //gibt die Verwendung des Späneleitblechs frei. Das markierte und deaktivierte
    //Kästchen zeigt an, dass eine Fräse mit eingebautem Späneleitblech programmiert wurde
#define CIX_KENNCODE_ARBEITSZENTRUM_MASCHINE    "CEN"
    //Kenncode des Arbeitszentrums der Maschine, das für die Bearbeitung verwendet werden soll
    //Die Zahl zwischen Anführungszeichen setzen
    //Beisp. “3” zur Kennung des Arbeitszentrums Nr. 3
#define CIX_KENNCODE_AGGREGAT   "AGG"   //Kenncode des Aggregats
//---------------------------------------------
#define CIX_WDH_TYP "RTY"    //Wiederholungstyp
    #define CIX_WDH_TYP_KEIN "rpNO"   //-1 = Wiederholungen deaktiviert
    // 0 = “rpX”
    // 1 = “rpY”
    // 2 = “rpXY”
    // 3 = “rpCIR”
    // 5 = “rpAL”
#define CIX_WDH_ABST_X   "DX"    //Wert des Achsenabstands in Richtung der Achse X
#define CIX_WDH_ABST_Y   "DY"    //Wert des Achsenabstands in Richtung der Achse Y
#define CIX_WDH_RAD      "R"     //Radius, um den die Wiederholungen ausgeführt werden
#define CIX_WDH_STARTWINKEL    "A" //Anfangswinkel der Wiederholungen
#define CIX_WDH_WINKEL   "DA"    //Winkelschritt zwischen den einzelnen Wiederholungen
#define CIX_WDH_DREHZENTRUM_X    "XRC"   //X-Position des Drehzentrums der Kreislinie, um das die Wiederholung ausgeführt wird
#define CIX_WDH_DREHZENTRUM_Y    "YRC"   //Y-Position des Drehzentrums der Kreislinie, um das die Wiederholung ausgeführt wird
#define CIX_WDH_GERADENWINKEL    "ARP"   //Abwinkelung der Geraden, entlang der die Wiederholungen durchgeführt werden
#define CIX_WDH_ABST     "LRP"   //Längenschritt/Abstand der Wiederholungen
#define CIX_WDH_RADIAL    "RDL"  //gibt die radiale Wiederholung frei

#define CIX_WDH_ANZAHL   "NRP"   //Anzahl der Wiederholungen

#define CIX_BEARB_OPTIMIEREN   "OPT"   //Optimierung der Bearbeitung
    // 0 = “NO”
    // 1 = “YES”
#define CIX_BEARB_DURCHGEHEND "THR"   //ist Durchgehende Bearbeitung
    //Durch Aktivierung dieser Option ändert sich der Maßbezug auf Unterseite WST (bei Bohrungen von oben)
    //1 = Durchgangsbearbeitung aktiviert.
    //0 = Durchgangsbearbeitung deaktiviert.
#define CIX_BEZUG_SIABST "TOS"   //Beeiflusst den Sicherheitsabstand
    #define CIX_BEZUG_SIABST_BEARBGRUND    "NO"  // 0 = bezieht sich auf den Grund der Bearbeitung
    #define CIX_BEZUG_SIABST_WSTOBSEI "YES" // 1 = bezieht sich auf WST-Oberseite
#define CIX_RADKOR  "CRC"   //Radiuskorrektur
    #define CIX_RADKOR_KEIN "0"
    #define CIX_RADKOR_LI   "1"
    #define CIX_RADKOR_RE   "2"
    #define CIX_RADKOR_INTERN   "5" //innerhalb des geschlossenen Profils
    #define CIX_RADKOR_EXTERN   "6" //außerhalb des geschlossenen Profils
    #define CIX_RADKOR_GEO      "7"
#define CIX_RESTBEARBTIEFE  "DVR"
    //Tiefe, die das Werkzeug bei Mehrfachdurchgängen während des letzten
    //Durchgangs erzielen muß
//-----------------------------------------------------Bohrungen:
#define CIX_BO_X    "X"     //X-Position
#define CIX_BO_Y    "Y"     //Y-Position
#define CIX_BO_Z    "Z"     //Z-Position
#define CIX_BO_BOTI "DP"    //Bohrtiefe
#define CIX_BO_DM   "DIA"   //Bohrdurchmesser


#define CIX_BO_WKZ_NEIGUNG  "AZ"    //Neigungswinkel des Werkzeugs
    //Neigungswinkel der Drehachse der Spindel im Vergleich zur Ebene X, Y
#define CIX_BO_WKZ_DREHWI   "AR"    //Drehwinkel des Werkzeugs
    //Drehwinkel der Spindelachse an der Ebene X, Y
#define CIX_BO_WKZ_DREHTYP  "CKA"   //aktiviert den Neigungstyp AR/AZ
    #define CIX_BO_WKZ_DREHTYP_KEIN "azrNO" // 0 = nicht gedreht/geneigt
    // 1 = “azrABS
    // 2 = “azrINC”
#define CIX_BO_REBOMA   "DDS"   //Restbohrmaß ab dem der Bohrer mit dem Abbremsen beginnen muss
    // 0 = Bohrer verlangsamt seine Geschwindigkeit nicht

#define CIX_BO_LAYER    "LAY"   //Kennstring des der Geometrie zugeordneten Layers.
    //Dieser String wird nicht unter den Programmierungszeilen angezeigt, sondern im
    //Dialogfenster Layer-Verwaltung
#define CIX_BO_PRESSVORRICHTUNG_AKTV    "PRS"   //aktiviert oder deaktiviert die Anwendung der Pressvorrichtung
    // 0 = “NO”
    // 1 = “YES”

//-----------------------------------------------------Nuten:
#define CIX_NUT_LAYER    "LAY"   //Kennstring des der Geometrie zugeordneten Layers.
    //Dieser String wird nicht unter den Programmierungszeilen angezeigt, sondern im
    //Dialogfenster Layer-Verwaltung
#define CIX_NUT_XS  "X"
#define CIX_NUT_YS  "Y"
#define CIX_NUT_ZS  "Z"
#define CIX_NUT_XE  "XE"
#define CIX_NUT_YE  "YE"
#define CIX_NUT_ZE  "ZE"
#define CIX_NUT_TI  "DP"    //Nuttiefe
#define CIX_NUT_BREITE "TTK"//Nutbreite
#define CIX_NUT_BREITENZUGABE   "OVM"
    //Wert der Materialzugabe, die bei der Bearbeitung des Profils belassen werden
    //soll. Der in diesem Feld eingegeben Wert ist an die Art der Korrektur gebunden
    //- Mit linker oder rechter Korrektur nimmt das Werkzeug bei Einstellung eines negativen Werts
    //  mehr Material weg, bei Einstellung eines positiven Werts, nimmt es weniger Material weg.
    //- Bei mittlerer Korrektur wird die Bearbeitung bei Eingabe eines negativen Werts rechterhand,
    //  bei Eingabe eines positiven Werts linkerhand der programmierten Bahn verschoben.
#define CIX_NUT_TYP "TYP"   //Nuttyp
    #define CIX_NUT_TYP_SP_EP    "cutXY"    //Startpunkt, Endpunkt
    #define CIX_NUT_TYP_SP_L_WI  "cutLA"    //Startpunkt, Länge, Winkel
    #define CIX_NUT_TYP_SP_XE_WI "cutXA"    //Startpunkt, X-Endepunkt, Winkel
    #define CIX_NUT_TYP_SP_YE_WI "cutYA"    //Startpunkt, Y-Endepunkt, Winkel
#define CIX_NUT_WI  "ANG"   //Nut-Winkel
#define CIX_NUT_ISO "ISO"   //ISO-Anweisung
#define CIX_NUT_REVERS  "RV" //kehrt die Richtung des programmierten geometrischen Profils um;
    //der Startpunkt der Geometrie wird somit zum Endpunkt
#define CIX_NUT_ANZ_TIZUST  "VTR"   //Anzahl der Tiefen-Zustellungen
    //Anzahl der Durchgänge, die sich auf die Tiefe der programmierten
    //Bearbeitung auswirken. Durch Eingabe der Zahl 2 wird die Bearbeitung
    //in 2 Teile aufgeteilt, bis die im Feld Tiefe angegebene Tiefe erreicht ist
#define CIX_NUT_TIEFENMASSBEZUG_ANGEPASST   "GIP"
    //"NO" == Tiefe bezieht sich auf Bezugsfläche (WST_Oberseite)
    //siehe Handbuch cix Seite 418
    //ermöglicht die Angabe bei welcher Tiefe das System das Profil P (GEO) berücksichtigen
    //muss, um die Bearbeitung zu nutzen. Das aktivierte Kästchen gibt an, dass der Ausgangspunkt
    //(Bez. A) des Profils auf der Oberfläche des Werkstücks ist (Bez. B); in diesem Fall zeigt die Quote
    //an, dass der Eingangspunkt des Werkzeugs in das entsprechende Werkstück mit dem
    //Ausgangspunkt des Profils A übereinstimmt.
    //Das deaktivierte Kästchen gibt an, dass der Ausgangspunkt des Profils (Bez. A) entlang der Z-
    //Achse (Bez. C) verschoben wurde, und dass man es daher nicht nur aus den X/Z Koordinaten
    //entnimmt, sondern aus den X/Z/Y Koordinaten, wobei die Angabe, die zu Z gehört, die Angabe für
    //die Tiefe der Bearbeitung ist (Bez. C). Wenn man bei diesem zweiten Fall die Bearbeitung mit dem
    //schräggestellten Werkzeug programmiert, stimmt die Quote, die die Eintrittsstelle (Bez. D) des
    //Werkzeugs in das Werkstück angibt, nicht mit dem Ausgangspunkt des Profils (Bez. A) überein.
#define CIX_NUT_AUSLAUF "BRC"
    //0 == kein Auslauf == Nutende bezieht sich auf Mitte Sägeblatt
    //1 == mit Auslauf == Nutende bezeiht WKZ-Radius mit ein = Bezug Schneidenspitzen
#define CIX_NUT_BIDIREKTIONAL "BDR"
    //autorisiert das Werkzeug zur Durchführung der folgenden
    //Durchgänge bei wechselnder Richtung. Das Werkzeug ändert seine Richtung bei jedem neuen
    //Durchgang. Zum Aktivieren dieser Funktion das Kästchen anklicken.
#define CIX_NUT_SCHNITTUMKEHR_VERHINDERN "PRV"
    //gibt den Wechsel der Vorschubrichtung des Sägeblatts frei. Wenn
    //die Richtung des programmierten Schnitts von rechts nach links verläuft,
    //die Default-Richtung des Sägeblatts aber von links nach rechts ist, sorgt
    //der CAM für die Umkehrung des Startpunkts des Sägeblatts, so daß es
    //genau unter Verfolgung seiner korrekten Vorschubrichtung schneidet. Es
    //empfiehlt sich dieses Feld zu aktivieren, um Fehler während der Optimierung des Programms zu
    //vermeiden, weil nicht immer die Richtung der programmierten Zeichnung mit der Defaul-Richtung
    //des Sägeblatts übereinstimmt
#define CIX_NUT_SCHNITTRICHTUNG_UMKEHREN "NRV"
#define CIX_NUT_VERLAENGERN_START "DIN" //Maßangabe zum Verlängern der Nut an Start
#define CIX_NUT_VERLAENGERN_ENDE "DOU" //Maßangabe zum Verlängern der Nut an Ende

//-----------------------------------------------------GEO und FKON:
#define CIX_X "X"
#define CIX_Y "Y"
#define CIX_Z "Z"
#define CIX_ZS "ZS"
#define CIX_XE "XE"
#define CIX_YE "YE"
#define CIX_ZE "ZE"
#define CIX_MIPU_X "XC"
#define CIX_MIPU_Y "YC"
#define CIX_LINIE_SCHARFE_KANNTE    "SC"
    //Eingabe der scharfen Kante. Ermöglicht zu definieren, dass der Schnittpunkt
    //zwischen der Linie und dem folgenden Element so bearbeitet werden muss, daß die scharfe Kante
    //erhalten bleibt
    #define CIX_LINIE_SCHARFE_KANNTE_AUS    "scOFF"
#define CIX_LINIE_VORSCHUB "FD"
#define CIX_LINIE_DREHZAHL "SP"
#define CIX_BOGEN_RICHTUNG "DIR"
    #define CIX_BOGEN_RICHTUNG_UZS "dirCW"
    #define CIX_BOGEN_RICHTUNG_GUZS "dirCCW"
#define CIX_FKON_TI "DP"    //Frästiefe
#define CIX_FKON_REVERS "RV" //kehrt die Richtung des programmierten geometrischen Profils um
    //der Startpunkt der Geometrie wird somit zum Endpunkt
#define CIX_FKON_GEO_ID  "GID"   //ID der Geometrie für die Fräskontur
#define CIX_FKON_EINTYP "TIN" //Eintauchtyp Siehe Handbuch cix Seite 408
#define CIX_FKON_AUSTYP "TOU" //Eintauchtyp Siehe Handbuch cix Seite 408
    #define CIX_FKON_EINTYP_KEIN  "0"  //kein
        //Werkzeug sinkt im rechten Winkel direkt auf den Startpunkt der Bearbeitung
    #define CIX_FKON_EINTYP_BOG   "1"  //Bogen
        //Werkzeug sinkt über eine im rechten Winkel zur Flanke stehende Linie, dringt ins
        //Werkstück ein und erreicht den Startpunkt der Bearbeitung über eine
        //kurze, bogenförmige Strecke, auf der es die Korrektur vornimmt. Durch Aktivierung des
        //Kästchens der Marker Korrekt. in der Luft korrigiert das Werkzeug seine Position bevor es
        //sinkt und erstellt somit eine kurze gerade Strecke, die parallel zur Flanke ist
    #define CIX_FKON_EINTYP_LINIE "2"  //Linie
        //Werkzeug sinkt über eine im rechten Winkel zur Flanke stehende Linie, dringt ins
        //Werkstück ein und erreicht den Startpunkt der Bearbeitung über eine
        //kurze, gerade Strecke, auf der es die Korrektur vornimmt. Durch Aktivierung des Kästchens
        //der Marker Korrekt. in der Luft korrigiert das Werkzeug seine Position bevor es sinkt und
        //erstellt somit eine kurze gerade Strecke, die parallel zur Flanke ist
    #define CIX_FKON_EINTYP_LIBOTG "3" //Linie-Bogen Tangential
        //Werkzeug sinkt über eine zur Flanke im rechten Winkel stehende Linie,
        //dringt ins Werkstück ein und erreicht den Startpunkt der Bearbeitung
        //über eine Linie und einen Bogen, die sich berühren und an denen es seine Position korrigiert
    #define CIX_FKON_EINTYP_SCHRAUB "5" //Schraubenlinie
        //Werkzeug erstellt in der Luft eine Parallele zur Flanke, entlang der es die
        //Korrektur vornimmt, sinkt über eine schraubenförmige Strecke und dringt ins Werkstück direkt
        //am Startpunkt der Bearbeitung ein
    #define CIX_FKON_EINTYP_LIBO3D  "6" //Linie-Bogen 3D
        //Werkzeug sinkt über eine schräge Linie, dringt ins Werkstück ein und
        //erreicht den Startpunkt der Bearbeitung
    #define CIX_FKON_EINTYP_LI3DKOR "7" //Linie 3D korrigiert
        //Werkzeug erstellt in der Luft eine Parallele zur Flanke, entlang der es
        //die Korrektur vornimmt, sinkt über eine schräge Linie und dringt ins Werkstück direkt am
        //Startpunkt der Bearbeitung ein
    #define CIX_FKON_EINTYP_BO3DKOR "8" //Bogen 3D korrigiert
        //Werkzeug erstellt in der Luft eine Parallele zur Flanke, entlang der es
        //die Korrektur vornimmt, sinkt über eine bogenförmige Strecke und dringt ins Werkstück direkt
        //am Startpunkt der Bearbeitung ein
    #define CIX_FKON_EINTYP_LIKOR   "9" //Linie korrigiert
        //Werkzeug erstellt in der Luft eine Parallele zur Flanke, entlang der es die
        //Korrektur vornimmt, sinkt über eine im rechten Winkel zur Ebene stehende Linie und dringt ins
        //Werkstück direkt am Startpunkt der Bearbeitung ein
    #define CIX_FKON_EINTYP_PROFIL3D "14" //Profil 3D
        //Werkzeug sinkt über eine schräge Linie und dringt ins Werkstück direkt am
        //Startpunkt der Bearbeitung ein. Die Verwendung dieses Eintritts ist
        //nur auf geschlossenen Profilen gewährt.
#define CIX_FKON_EINWI  "AIN"   //Eintrittswinkel des Werkzeugs
#define CIX_FKON_AUSWI  "AOU"   //Austrittswinkel des Werkzeugs
#define CIX_FKON_VERLAENGERN_START "DIN" //Maßangabe zum Verlängern der Nut an Start
#define CIX_FKON_VERLAENGERN_ENDE "DOU" //Maßangabe zum Verlängern der Nut an Ende
#define CIX_FKON_EINKOR "CIN" //Korrektug in der Luft fürs Eintauchen
#define CIX_FKON_AUSKOR "COU" //Korrektug in der Luft fürs Eintauchen
#define CIX_FKON_GIN "GIN"
    //Abstand in Millimetern vom Startpunkt der Bearbeitung zur Verschiebung des
    //Werkzeugs, so daß es leicht schräg sinkt. Dieser Wert kann nur mit Eintrittstyp Linie3D korrigiert
    //oder Typ Bogen3D korrigiert verwendet werden
#define CIX_FKON_GOU "GOU"
#define CIX_FKON_TBI "TBI"
    //Eingabe Tabbing; ermöglicht ein gerades Verschieben des Werkzeugs innerhalb des
    //Eintrittsstrecke, um eine kurze Stufe zu bilden, die an der Tiefe A  der programmierten
    //Bearbeitung berechnet werden kann (Abbildung 216). Dieser Wert kann nur mit dem
    //Ausgangstyp: Linie3D korrigiert
#define CIX_FKON_TBO "TBO"
#define CIX_FKON_EINAUSRADPROZENT "PRP"
    //Wert in Prozenten für die Veränderung des Radius der Ein- und Austritte
#define CIX_FKON_BREITENZUGABE   "OVM"
    //Wert der Materialzugabe, die bei der Bearbeitung des Profils belassen werden
    //soll. Der in diesem Feld eingegeben Wert ist an die Art der Korrektur gebunden
    //- Mit linker oder rechter Korrektur nimmt das Werkzeug bei Einstellung eines negativen Werts
    //  mehr Material weg, bei Einstellung eines positiven Werts, nimmt es weniger Material weg.
    //- Bei mittlerer Korrektur wird die Bearbeitung bei Eingabe eines negativen Werts rechterhand,
    //  bei Eingabe eines positiven Werts linkerhand der programmierten Bahn verschoben.
#define CIX_FKON_ANZ_TIZUST  "VTR"   //Anzahl der Tiefen-Zustellungen
    //Anzahl der Durchgänge, die sich auf die Tiefe der programmierten
    //Bearbeitung auswirken. Durch Eingabe der Zahl 2 wird die Bearbeitung
    //in 2 Teile aufgeteilt, bis die im Feld Tiefe angegebene Tiefe erreicht ist




#endif // DEF_CIX_H
