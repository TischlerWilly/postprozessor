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

#define FMC_KTA                 "[ZYKTFR40]"    //Kreistasche
#define FMC_KTA_X               "MPX"
#define FMC_KTA_Y               "MPY"
#define FMC_KTA_DM              "DM"
#define FMC_KTA_TI              "TI"
#define FMC_KTA_ZUST            "LGEZU"
#define FMC_KTA_AFB             "AFB"

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

#define FMC_NUT                 "[ZYSNUT40]"    //Nut
#define FMC_NUT_XS              "SPX"
#define FMC_NUT_XE              "EPX"
#define FMC_NUT_YS              "SPY"
#define FMC_NUT_YE              "EPY"
#define FMC_NUT_TI              "TI"
#define FMC_NUT_BR              "NB"
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

#define FMC_KOMMENTAR           "[SWKOMT40]"
#define FMC_KOMMENTAR_TEXT      "BEZB="

#define FMC_ENDE                "[PGENDE40]"












#endif // DEF_FMC_H
