#ifndef DEF_FMC_H
#define DEF_FMC_H

//FMC-Schnittstelle IMAWOP 4.0:

#define FMC_PRGKOPF             "[PGKOPF40]"    //Programmkpof
#define FMC_PRGKOPF_LAENGE      "FTL"
#define FMC_PRGKOPF_BREITE      "FTB"
#define FMC_PRGKOPF_DICKE       "FTD"

#define FMC_BOHR_DM             "[VBDMES40]"    //Bohren Durchmesser
#define FMC_BOHR_DM_AFB         "AFB"
#define FMC_BOHR_DM_DM          "DM"
#define FMC_BOHR_DM_TIEFE       "TI"
#define FMC_BOHR_DM_X           "X"
#define FMC_BOHR_DM_Y           "Y"

#define FMC_HBEXP               "[HBXPLU40]"    //HBE X plus
#define FMC_HBEXP_AFB           "AFB"
#define FMC_HBEXP_Y1            "Y1"
#define FMC_HBEXP_Y2            "Y2"
#define FMC_HBEXP_Y3            "Y3"
#define FMC_HBEXP_Y4            "Y4"
#define FMC_HBEXP_Y5            "Y5"
#define FMC_HBEXP_Y6            "Y6"
#define FMC_HBEXP_TI            "TI"
#define FMC_HBEXP_Z             "Z"             //Z-Position
#define FMC_HBEXP_DM            "DM"
#define FMC_HBEXP_KM            "KETTE"         //Kenntenmaß
#define FMC_HBEXP_X1            "X1"
#define FMC_HBEXP_X2            "X2"

#define FMC_HBEXM               "[HBXMIN40]"    //HBE X minus
#define FMC_HBEXM_AFB           "AFB"
#define FMC_HBEXM_Y1            "Y1"
#define FMC_HBEXM_Y2            "Y2"
#define FMC_HBEXM_Y3            "Y3"
#define FMC_HBEXM_Y4            "Y4"
#define FMC_HBEXM_Y5            "Y5"
#define FMC_HBEXM_Y6            "Y6"
#define FMC_HBEXM_TI            "TI"
#define FMC_HBEXM_Z             "Z"             //Z-Position
#define FMC_HBEXM_DM            "DM"
#define FMC_HBEXM_KM            "KETTE"         //Kenntenmaß
#define FMC_HBEXM_X1            "X1"
#define FMC_HBEXM_X2            "X2"

#define FMC_HBEYP               "[HBYPLU40]"    //HBE Y plus
#define FMC_HBEYP_AFB           "AFB"
#define FMC_HBEYP_X1            "X1"
#define FMC_HBEYP_X2            "X2"
#define FMC_HBEYP_X3            "X3"
#define FMC_HBEYP_X4            "X4"
#define FMC_HBEYP_X5            "X5"
#define FMC_HBEYP_X6            "X6"
#define FMC_HBEYP_TI            "TI"
#define FMC_HBEYP_Z             "Z"             //Z-Position
#define FMC_HBEYP_DM            "DM"
#define FMC_HBEYP_KM            "KETTE"         //Kenntenmaß
#define FMC_HBEYP_Y1            "Y1"
#define FMC_HBEYP_Y2            "Y2"

#define FMC_HBEYM               "[HBYMIN40]"    //HBE Y minus
#define FMC_HBEYM_AFB           "AFB"
#define FMC_HBEYM_X1            "X1"
#define FMC_HBEYM_X2            "X2"
#define FMC_HBEYM_X3            "X3"
#define FMC_HBEYM_X4            "X4"
#define FMC_HBEYM_X5            "X5"
#define FMC_HBEYM_X6            "X6"
#define FMC_HBEYM_TI            "TI"
#define FMC_HBEYM_Z             "Z"             //Z-Position
#define FMC_HBEYM_DM            "DM"
#define FMC_HBEYM_KM            "KETTE"         //Kenntenmaß
#define FMC_HBEYM_Y1            "Y1"
#define FMC_HBEYM_Y2            "Y2"

#define FMC_BOBIY               "[VBY_40]"
#define FMC_BOBIY_AFB           "AFB"
#define FMC_BOBIY_X1            "X"
#define FMC_BOBIY_X2            "X2"
#define FMC_BOBIY_Y1            "Y1"
#define FMC_BOBIY_Y2            "Y2"
#define FMC_BOBIY_Y3            "Y3"
#define FMC_BOBIY_Y4            "Y4"
#define FMC_BOBIY_Y5            "Y5"
#define FMC_BOBIY_Y6            "Y6"
#define FMC_BOBIY_TI            "TI"
#define FMC_BOBIY_DM            "DM"
#define FMC_BOBIY_KM            "KETTE"

#define FMC_BOBIX               "[VBX_40]"      //Bohrbild in X
#define FMC_BOBIX_AFB           "AFB"
#define FMC_BOBIX_Y1            "Y"
#define FMC_BOBIX_Y2            "Y2"
#define FMC_BOBIX_X1            "X1"
#define FMC_BOBIX_X2            "X2"
#define FMC_BOBIX_X3            "X3"
#define FMC_BOBIX_X4            "X4"
#define FMC_BOBIX_X5            "X5"
#define FMC_BOBIX_X6            "X6"
#define FMC_BOBIX_TI            "TI"
#define FMC_BOBIX_DM            "DM"
#define FMC_BOBIX_KM            "KETTE"

#define FMC_KTA                 "[ZYKTFR40]"    //Kreistasche
#define FMC_KTA_X               "MPX"
#define FMC_KTA_Y               "MPY"
#define FMC_KTA_DM              "DM"
#define FMC_KTA_TI              "TI"
#define FMC_KTA_ZUST            "LGEZU"
#define FMC_KTA_AFB             "AFB"
#define FMC_KTA_WKZ             "WKZID"

#define FMC_RTA                 "[ZYRTFR40]"    //Rechtecktasche
#define FMC_RTA_X               "MPX"
#define FMC_RTA_Y               "MPY"
#define FMC_RTA_L               "LGET1"
#define FMC_RTA_B               "LGET2"
#define FMC_RTA_TI              "TI"
#define FMC_RTA_RAD             "R"
#define FMC_RTA_ZUST            "LGEZU"
#define FMC_RTA_WI              "WKL"
#define FMC_RTA_RAEUM           "RAEUMEN"
#define FMC_RTA_AFB             "AFB"
#define FMC_RTA_WKZ             "WKZID"

#define FMC_NUT                 "[ZYSNUT40]"    //Nut
#define FMC_NUT_XS              "SPX"
#define FMC_NUT_XE              "EPX"
#define FMC_NUT_YS              "SPY"
#define FMC_NUT_YE              "EPY"
#define FMC_NUT_TI              "TI"
#define FMC_NUT_BR              "NB"
#define FMC_NUT_KOR             "TRKOR"
#define FMC_NUT_AFB             "AFB"

#define FMC_LORAE               "[VBLAEN40]"    //Lochreihe Anfang Ende
#define FMC_LORAE_XS            "SPX"
#define FMC_LORAE_XE            "EPX"
#define FMC_LORAE_Y1            "Y1"
#define FMC_LORAE_Y2            "Y2"
#define FMC_LORAE_RASTER        "RASTER"
#define FMC_LORAE_TI            "TI"
#define FMC_LORAE_DM            "DM"
#define FMC_LORAE_DM_           "D"
#define FMC_LORAE_AFB           "AFB"
#define FMC_LORAE_BEZ           "BEZB"

#define FMC_LORAM               "[VBLMIT40]"    //Lochreihe Anfang Mitte
#define FMC_LORAM_XM            "MPX"
#define FMC_LORAM_XS            "SPX"
#define FMC_LORAM_Y1            "Y1"
#define FMC_LORAM_Y2            "Y2"
#define FMC_LORAM_RASTER        "RASTER"
#define FMC_LORAM_RASTER_       "LR"
#define FMC_LORAM_TI            "TI"
#define FMC_LORAM_TI_           "BT"
#define FMC_LORAM_DM            "DM"
#define FMC_LORAM_DM_           "D"
#define FMC_LORAM_AFB           "AFB"

#define FMC_KOMMENTAR           "[SWKOMT40]"    //Kommentar
#define FMC_KOMMENTAR_TEXT      "BEZB"

#define FMC_ENDE                "[PGENDE40]"
#define FMC_HALT                "[SNHALT40]"

#define FMC_FKON                "[KAFRAE40]"    //Aufruf Fräser
#define FMC_FKON_WKZ            "WKZID"
#define FMC_FKON_X              "X"
#define FMC_FKON_Y              "Y"
#define FMC_FKON_Z              "Z"
#define FMC_FKON_RAD            "EBG"
#define FMC_FKON_KADI           "KD"
#define FMC_FKON_KOR            "TRKOR"
#define FMC_FKON_BEZ            "BEZB"
#define FMC_FKON_AFB            "AFB"
#define FMC_FKON_ANTYP          "TYPAN"
#define FMC_FKON_ABTYP          "TYPAB"

#define FMC_FKONG               "[G1]"
#define FMC_FKONG_XE            "X"
#define FMC_FKONG_YE            "Y"
#define FMC_FKONG_ZE            "Z"
#define FMC_FKONG_AFB           "AFB"

#define FMC_FKONBOGUZS          "[G2]"
#define FMC_FKONBOGGUZS         "[G3]"
#define FMC_FKONBOG_XE          "X"
#define FMC_FKONBOG_YE          "Y"
#define FMC_FKONBOG_ZE          "Z"
#define FMC_FKONBOG_RAD         "RAD"
#define FMC_FKONBOG_AFB         "AFB"

#define FMC_FALZ                "[ZYFALZ40]"        //Falz
#define FMC_FALZ_XS             "SPX"
#define FMC_FALZ_XE             "EPX"
#define FMC_FALZ_YS             "SPY"
#define FMC_FALZ_YE             "EPY"
#define FMC_FALZ_Z              "TI"
#define FMC_FALZ_KADI           "KD"
#define FMC_FALZ_KOR            "TRKOR"
#define FMC_FALZ_WKZ            "WKZID"
#define FMC_FALZ_BEZ            "BEZB"
#define FMC_FALZ_AFB            "AFB"

#define FMC_TOPF                "[VBTOPF41]"        //Bohrung Topfband
#define FMC_TOPF_ABST           "ABSTTPF"           //Topfabstand = MAß von WST-Kante bis mitte Topf
#define FMC_TOPF_A1             "ABST1"             //Maß von WST-Kante bis zum ersten Topf
#define FMC_TOPF_A2             "ABST2"
#define FMC_TOPF_A3             "ABST3"
#define FMC_TOPF_A4             "ABST4"
#define FMC_TOPF_A5             "ABST5"
#define FMC_TOPF_MA             "ABSTA"             //Abstand der beiden Tübellöche zueinander
#define FMC_TOPF_MB             "ABSTB"             //Abstnd zwischen dem Topf und den Dübellöchern
#define FMC_TOPF_KM             "KETTE"
#define FMC_TOPF_SEITE          "BRICHT"
#define FMC_TOPF_DDM            "DMDUEB"            //Dübeldurchmesser
#define FMC_TOPF_TODM           "DMTPF"             //Topfdurchmesser
#define FMC_TOPF_DTI            "TIDUEB"            //Dübeltiefe
#define FMC_TOPF_TOTI           "TITPF"             //Topftiefe
#define FMC_TOPF_TOWKZ          "TNR"               //Werkzeugnummer für Topf
#define FMC_TOPF_AFB            "AFB"

#define FMC_GEHR                "[ZYSCHN40]"
#define FMC_GEHR_SPX            "SPX" //Startpunkt X-Wert
#define FMC_GEHR_SPY            "SPY" //Startpunkt Y-Wert
#define FMC_GEHR_EPX            "EPX" //Endpunkt X-Wert
#define FMC_GEHR_EPY            "EPY" //Endpunkt Y-Wert
#define FMC_GEHR_TIRITZEN       "LGEAN" //Einritztiefe (Vorritztiefe)
#define FMC_GEHR_TISCHNITT      "TI" //gesamte Schnitttiefe
#define FMC_GEHR_KOR            "TRKOR" //Bahnkorrektur (1 == linkg / 0 == keine / 2 == rechts)
#define FMC_GEHR_GEGENLAUF      "GEGENL" //Gegenlauf
#define FMC_GEHR_KADI           "KD" //Kantendicke
#define FMC_GEHR_WI             "TWKL" //Neigungswinkel (0° == Blatt steht senkrecht)
#define FMC_GEHR_BEZUG          "TYPN" //Bezugsfläche (1 == Spitze auf Unterseite / 2 == Spitze auf Oberseite)
#define FMC_GEHR_WKZNR          "WKZID"
#define FMC_GEHR_AFB            "AFB"

#define FMC_STULP               "[ZYSTUL40]"    //Stulp
#define FMC_STULP_WKZ           "WKZID"
#define FMC_STULP_WKZAKT        "WKZAKTUELL"
#define FMC_STULP_X             "MPX"           //Mittelpunkt in X
#define FMC_STULP_Y             "MPY"           //Mittelpunkt in Y
#define FMC_STULP_Z             "MPZ"           //Mittelpunkt in Z
#define FMC_STULP_L             "LGET1"         //Länge
#define FMC_STULP_B             "LGET2"         //Breite
#define FMC_STULP_TI            "TI"            //Tiefe
#define FMC_STULP_RAD           "R"             //Radius
#define FMC_STULP_VERSATZ       "FB"            //Falz-Versatz
#define FMC_STULP_ZUST          "LGEZU"         //Zustellmaß
#define FMC_STULP_GEGENL        "GEGENL"        //Gegenlauf
#define FMC_STULP_SEITE         "BRICHT"        //Seite von der Eingetaucht wird
#define FMC_STULP_FEIN          "FAN"           //Eintauchvorschub
#define FMC_STULP_F             "F"             //Vorschub
#define FMC_STULP_N             "N"             //Drahzahl
#define FMC_STULP_BEZ           "BEZB"          //Beichnung
#define FMC_STULP_AFB           "AFB"           //Ausführbedingung

#endif // DEF_FMC_H
