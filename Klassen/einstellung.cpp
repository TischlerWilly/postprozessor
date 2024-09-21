#include "einstellung.h"

einstellung::einstellung()
{
    Entwicklermodus             = false;
    Verzeichnis_quelle          = "./";
    Verzeichnis_ziel_server     = "./";
    Verzeichnis_ziel_lokal      = "./";
    Verzeichnis_root_ganx       = "P:\\CNC Ganner\\Programme";
    Verzeichnis_root_fmc        = "P:\\CNC";
    Verzeichnis_root_cix        = "P:\\CNC Biesse\\Programme";
    Verzeichnis_ziel_auswahl    = "server"; // | "lokal" | "AUTO"
    Quelldateien_erhalten       = true;
    Std_dateinamen_verwenden    = false;
    Drehung_wst                 = "0";// | "90" | "180" | "270" | "AUTO"
    Tiefeneinst_fkon            = "orgi"; // | "wkz"
    Kurze_geraden_importieren   = false;
    Geraden_schwellwert         = 1;
    Formartierungen_aufbrechen  = false;
    Fkon_kantenschonend         = false;
    Gehrungen_zugabe            = 20;
    WKZ_fr_fmc                  = false;
    WKZ_fr_ganx                 = false;
    WKZ_fr_cix                  = false;
    WKZ_fr_ggf                  = false;
}

//----------------------------------------set:
void einstellung::set_text(QString t)
{
    text_zw tz;
    tz.set_text(t,'\n');
    for(uint i=0; i<tz.count() ;i++)
    {
        text_zw spalten;
        spalten.set_text(tz.at(i),'\t');
        if(spalten.at(0) == "Entwicklermodus:")
        {
            set_entwicklermodus(spalten.at(1));
        }else if(spalten.at(0) == "Eigenes Format immer mit exportieren:")
        {
            set_eigenes_format_immer_mit_exportieren(spalten.at(1));
        }else if(spalten.at(0) == "verzeichnis_quelle:")
        {
            set_verzeichnis_quelle(spalten.at(1));
        }else if(spalten.at(0) == "verzeichnis_ziel_server:")
        {
            set_verzeichnis_ziel_server(spalten.at(1));
        }else if(spalten.at(0) == "verzeichnis_ziel_lokal:")
        {
            set_verzeichnis_ziel_lokal(spalten.at(1));
        }else if(spalten.at(0) == "verzeichnis_root_ganx:")
        {
            set_verzeichnis_root_ganx(spalten.at(1));
        }else if(spalten.at(0) == "verzeichnis_root_fmc:")
        {
            set_verzeichnis_root_fmc(spalten.at(1));
        }else if(spalten.at(0) == "verzeichnis_root_cix:")
        {
            set_verzeichnis_root_cix(spalten.at(1));
        }else if(spalten.at(0) == "verzeichnis_zielABC:")
        {
            set_verzeichnis_ziel_auswahl(spalten.at(1));
        }else if(spalten.at(0) == "quelldateien_erhalten:")
        {
            set_quelldateien_erhalten(spalten.at(1));
        }else if(spalten.at(0) == "stdandard_dateinamen:")
        {
            set_std_dateinamen_verwenden(spalten.at(1));
        }else if(spalten.at(0) == "drehung_des_bauteils:")
        {
            set_drehung_wst(spalten.at(1));
        }else if(spalten.at(0) == "tiefenzustellung_fkon:")
        {
            set_tiefeneinstellung_fkon(spalten.at(1));
        }else if(spalten.at(0) == "kurze_geraden_import:")
        {
            set_kurze_geraden_importieren(spalten.at(1));
        }else if(spalten.at(0) == "geraden_schwellenwert:")
        {
            set_geraden_schwellwert(spalten.at(1).toDouble());
        }else if(spalten.at(0) == "formartierungen_aufbr:")
        {
            set_formartierungen_aufbrechen(spalten.at(1));
        }else if(spalten.at(0) == "fkon_kantenschonend:")
        {
            set_fkon_kantenschonend(spalten.at(1));
        }else if(spalten.at(0) == "zugabemass_gehrungen:")
        {
            set_gehrungen_zugabe(spalten.at(1).toDouble());
        }else if(spalten.at(0) == "wkz_fr_fmc:")
        {
            set_wkz_fr_fmc(spalten.at(1));
        }else if(spalten.at(0) == "wkz_fr_ganx:")
        {
            set_wkz_fr_ganx(spalten.at(1));
        }else if(spalten.at(0) == "wkz_fr_cix:")
        {
            set_wkz_fr_cix(spalten.at(1));
        }else if(spalten.at(0) == "wkz_fr_ggf:")
        {
            set_wkz_fr_ggf(spalten.at(1));
        }
    }
}
void einstellung::set_entwicklermodus(bool ja)
{
    Entwicklermodus = ja;
}
void einstellung::set_entwicklermodus(QString jn)
{
    if(jn == "ja")
    {
        set_entwicklermodus(true);
    }else
    {
        set_entwicklermodus(false);
    }
}
void einstellung::set_eigenes_format_immer_mit_exportieren(bool ja)
{
    Eigenes_format_immer_mit_exportieren = ja;
}
void einstellung::set_eigenes_format_immer_mit_exportieren(QString jn)
{
    if(jn == "ja")
    {
        set_eigenes_format_immer_mit_exportieren(true);
    }else
    {
        set_eigenes_format_immer_mit_exportieren(false);
    }
}
void einstellung::set_verzeichnis_quelle(QString v)
{
    Verzeichnis_quelle = v;
}
void einstellung::set_verzeichnis_ziel_server(QString v)
{
    Verzeichnis_ziel_server = v;
}
void einstellung::set_verzeichnis_ziel_lokal(QString v)
{
    Verzeichnis_ziel_lokal = v;
}
void einstellung::set_verzeichnis_root_ganx(QString v)
{
    Verzeichnis_root_ganx = v;
}
void einstellung::set_verzeichnis_root_fmc(QString v)
{
    Verzeichnis_root_fmc = v;
}
void einstellung::set_verzeichnis_root_cix(QString v)
{
    Verzeichnis_root_cix = v;
}
void einstellung::set_verzeichnis_ziel_auswahl(QString abc)
{
    Verzeichnis_ziel_auswahl = abc;
}
void einstellung::set_quelldateien_erhalten(bool erhalten)
{
    Quelldateien_erhalten = erhalten;
}
void einstellung::set_quelldateien_erhalten(QString erhalten)
{
    if(erhalten == "nein")
    {
        set_quelldateien_erhalten(false);
    }else
    {
        set_quelldateien_erhalten(true);
    }
}
void einstellung::set_std_dateinamen_verwenden(bool jn)
{
    Std_dateinamen_verwenden = jn;
}
void einstellung::set_std_dateinamen_verwenden(QString jn)
{
    if(jn == "ja")
    {
        set_std_dateinamen_verwenden(true);
    }else
    {
        set_std_dateinamen_verwenden(false);
    }
}
bool einstellung::set_drehung_wst(QString d)
{
    if(d =="0" || d =="90" || d=="180" || d=="270" || d=="AUTO")
    {
        Drehung_wst = d;
        return true;//Erfolg
    }else
    {
        return false;//Fehlschlag
    }
}
bool einstellung::set_tiefeneinstellung_fkon(QString einst)
{
    if(einst == "orgi" || einst == "wkz")
    {
        Tiefeneinst_fkon = einst;
        return true;//Erfolg
    }else
    {
        return false;//Fehlschlag
    }
}
void einstellung::set_kurze_geraden_importieren(bool imp)
{
    Kurze_geraden_importieren = imp;
}
void einstellung::set_kurze_geraden_importieren(QString imp)
{
    if(imp == "nein")
    {
        set_kurze_geraden_importieren(false);
    }else
    {
        set_kurze_geraden_importieren(true);
    }
}
bool einstellung::set_geraden_schwellwert(double sw)
{
    if(sw > 0)
    {
        Geraden_schwellwert = sw;
        return true;//Erfolg
    }else
    {
        return false;//Fehlschlag
    }
}
void einstellung::set_formartierungen_aufbrechen(bool aufb)
{
    Formartierungen_aufbrechen = aufb;
}
void einstellung::set_formartierungen_aufbrechen(QString aufb)
{
    if(aufb == "ja")
    {
        set_formartierungen_aufbrechen(true);
    }else
    {
        set_formartierungen_aufbrechen(false);
    }
}
void einstellung::set_fkon_kantenschonend(bool ks)
{
    Fkon_kantenschonend = ks;
}
void einstellung::set_fkon_kantenschonend(QString ks)
{
    if(ks == "ja")
    {
        set_fkon_kantenschonend(true);
    }else
    {
        set_fkon_kantenschonend(false);
    }
}
bool einstellung::set_gehrungen_zugabe(double zug)
{
    if(zug >= 0)
    {
        Gehrungen_zugabe = zug;
        return true;//Erfolg
    }else
    {
        return false;//Fehlschlag
    }
}
void einstellung::set_wkz_fr_fmc(bool jn)
{
    WKZ_fr_fmc = jn;
}
void einstellung::set_wkz_fr_fmc(QString jn)
{
    if(jn == "ja")
    {
        set_wkz_fr_fmc(true);
    }else
    {
        set_wkz_fr_fmc(false);
    }
}
void einstellung::set_wkz_fr_ganx(bool jn)
{
    WKZ_fr_ganx = jn;
}
void einstellung::set_wkz_fr_ganx(QString jn)
{
    if(jn == "ja")
    {
        set_wkz_fr_ganx(true);
    }else
    {
        set_wkz_fr_ganx(false);
    }
}
void einstellung::set_wkz_fr_cix(bool jn)
{
    WKZ_fr_cix = jn;
}
void einstellung::set_wkz_fr_cix(QString jn)
{
    if(jn == "ja")
    {
        set_wkz_fr_cix(true);
    }else
    {
        set_wkz_fr_cix(false);
    }
}
void einstellung::set_wkz_fr_ggf(bool jn)
{
    WKZ_fr_ggf = jn;
}
void einstellung::set_wkz_fr_ggf(QString jn)
{
    if(jn == "ja")
    {
        set_wkz_fr_ggf(true);
    }else
    {
        set_wkz_fr_ggf(false);
    }
}

//----------------------------------------get:
QString einstellung::text()
{
    QString text;

    text += "Entwicklermodus:";
    text += "\t";
    if(entwicklermodus() == true)
    {
        text += "ja";
    }else
    {
        text += "nein";
    }
    text += "\n";

    text += "Eigenes Format immer mit exportieren:";
    text += "\t";
    if(eigenes_format_immer_mit_exportieren() == true)
    {
        text += "ja";
    }else
    {
        text += "nein";
    }
    text += "\n";

    text += "verzeichnis_quelle:";
    text += "\t";
    text += verzeichnis_quelle();
    text += "\n";

    text += "verzeichnis_ziel_server:";
    text += "\t";
    text += verzeichnis_ziel_server();
    text += "\n";

    text += "verzeichnis_ziel_lokal:";
    text += "\t";
    text += verzeichnis_ziel_lokal();
    text += "\n";

    text += "verzeichnis_root_ganx:";
    text += "\t";
    text += verzeichnis_root_ganx();
    text += "\n";

    text += "verzeichnis_root_fmc:";
    text += "\t";
    text += verzeichnis_root_fmc();
    text += "\n";

    text += "verzeichnis_zielABC:";
    text += "\t";
    text += verzeichnis_ziel_auswahl();
    text += "\n";

    text += "quelldateien_erhalten:";
    text += "\t";
    if(quelldateien_erhalten() == true)
    {
        text += "ja";
    }else
    {
        text += "nein";
    }
    text += "\n";

    text += "stdandard_dateinamen:";
    text += "\t";
    if(std_dateinamen_verwenden() == true)
    {
        text += "ja";
    }else
    {
        text += "nein";
    }
    text += "\n";

    text += "drehung_des_bauteils:";
    text += "\t";
    text += drehung_wst();
    text += "\n";

    text += "tiefenzustellung_fkon:";
    text += "\t";
    text += tiefeneinst_fkon();
    text += "\n";

    text += "kurze_geraden_import:";
    text += "\t";
    if(kurze_geraden_importieren() == true)
    {
        text += "ja";
    }else
    {
        text += "nein";
    }
    text += "\n";

    text += "geraden_schwellenwert:";
    text += "\t";
    text += double_to_qstring(geraden_schwellwert());
    text += "\n";

    text += "formartierungen_aufbr:";
    text += "\t";
    if(formartierungen_aufbrechen() == true)
    {
        text += "ja";
    }else
    {
        text += "nein";
    }
    text += "\n";

    text += "fkon_kantenschonend:";
    text += "\t";
    if(fkon_kantenschonend() == true)
    {
        text += "ja";
    }else
    {
        text += "nein";
    }
    text += "\n";

    text += "zugabemass_gehrungen:";
    text += "\t";
    text += double_to_qstring(gehrungen_zugabe());
    text += "\n";

    text += "wkz_fr_fmc:";
    text += "\t";
    if(wkz_fr_fmc() == true)
    {
        text += "ja";
    }else
    {
        text += "nein";
    }
    text += "\n";

    text += "wkz_fr_ganx:";
    text += "\t";
    if(wkz_fr_ganx() == true)
    {
        text += "ja";
    }else
    {
        text += "nein";
    }
    text += "\n";

    text += "wkz_fr_cix:";
    text += "\t";
    if(wkz_fr_cix() == true)
    {
        text += "ja";
    }else
    {
        text += "nein";
    }
    text += "\n";

    text += "wkz_fr_ggf:";
    text += "\t";
    if(wkz_fr_ggf() == true)
    {
        text += "ja";
    }else
    {
        text += "nein";
    }
    text += "\n";

    return text;
}
bool einstellung::entwicklermodus()
{
    return Entwicklermodus;
}
bool einstellung::eigenes_format_immer_mit_exportieren()
{
    return Eigenes_format_immer_mit_exportieren;
}
QString einstellung::verzeichnis_quelle()
{
    return Verzeichnis_quelle;
}
QString einstellung::verzeichnis_ziel_server()
{
    return Verzeichnis_ziel_server;
}
QString einstellung::verzeichnis_ziel_lokal()
{
    return Verzeichnis_ziel_lokal;
}
QString einstellung::verzeichnis_root_ganx()
{
    return Verzeichnis_root_ganx;
}
QString einstellung::verzeichnis_root_fmc()
{
    return Verzeichnis_root_fmc;
}
QString einstellung::verzeichnis_root_cix()
{
    return Verzeichnis_root_cix;
}
QString einstellung::verzeichnis_ziel_auswahl()
{
    return Verzeichnis_ziel_auswahl;
}
bool einstellung::quelldateien_erhalten()
{
    return Quelldateien_erhalten;
}
bool einstellung::std_dateinamen_verwenden()
{
    return Std_dateinamen_verwenden;
}
QString einstellung::drehung_wst()
{
    return Drehung_wst;
}
QString einstellung::tiefeneinst_fkon()
{
    return Tiefeneinst_fkon;
}
bool einstellung::kurze_geraden_importieren()
{
    return Kurze_geraden_importieren;
}
double einstellung::geraden_schwellwert()
{
    return Geraden_schwellwert;
}
bool einstellung::formartierungen_aufbrechen()
{
    return Formartierungen_aufbrechen;
}
bool einstellung::fkon_kantenschonend()
{
    return Fkon_kantenschonend;
}
double einstellung::gehrungen_zugabe()
{
    return Gehrungen_zugabe;
}
bool einstellung::wkz_fr_fmc()
{
    return WKZ_fr_fmc;
}
bool einstellung::wkz_fr_ganx()
{
    return WKZ_fr_ganx;
}
bool einstellung::wkz_fr_cix()
{
    return WKZ_fr_cix;
}
bool einstellung::wkz_fr_ggf()
{
    return WKZ_fr_ggf;
}


