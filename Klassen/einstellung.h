#ifndef EINSTELLUNG_H
#define EINSTELLUNG_H

#include <QString>
#include "text_zw.h"
#include "Funktionen/umwandeln.h"

class einstellung
{
public:
    einstellung();

    //set:
    void set_text(QString t);
    void set_entwicklermodus(bool ja);
    void set_entwicklermodus(QString jn);
    void set_eigenes_format_immer_mit_exportieren(bool ja);
    void set_eigenes_format_immer_mit_exportieren(QString jn);
    void set_verzeichnis_quelle(QString v);
    void set_verzeichnis_ziel_server(QString v);
    void set_verzeichnis_ziel_lokal(QString v);
    void set_verzeichnis_root_ganx(QString v);
    void set_verzeichnis_root_fmc(QString v);
    void set_verzeichnis_root_cix(QString v);
    void set_verzeichnis_ziel_auswahl(QString abc);
    void set_quelldateien_erhalten(bool erhalten);
    void set_quelldateien_erhalten(QString erhalten);
    void set_std_dateinamen_verwenden(bool jn);
    void set_std_dateinamen_verwenden(QString jn);
    bool set_drehung_wst(QString d);
    bool set_tiefeneinstellung_fkon(QString einst);
    void set_kurze_geraden_importieren(bool imp);
    void set_kurze_geraden_importieren(QString imp);
    bool set_geraden_schwellwert(double sw);
    void set_formartierungen_aufbrechen(bool aufb);
    void set_formartierungen_aufbrechen(QString aufb);
    void set_fkon_kantenschonend(bool ks);
    void set_fkon_kantenschonend(QString ks);
    bool set_gehrungen_zugabe(double zug);
    void set_wkz_fr_fmc(bool jn);
    void set_wkz_fr_fmc(QString jn);
    void set_wkz_fr_ganx(bool jn);
    void set_wkz_fr_ganx(QString jn);
    void set_wkz_fr_cix(bool jn);
    void set_wkz_fr_cix(QString jn);
    void set_wkz_fr_ggf(bool jn);
    void set_wkz_fr_ggf(QString jn);

    //get:    
    QString text();
    bool entwicklermodus();
    bool eigenes_format_immer_mit_exportieren();
    QString verzeichnis_quelle();
    QString verzeichnis_ziel_server();
    QString verzeichnis_ziel_lokal();
    QString verzeichnis_root_ganx();
    QString verzeichnis_root_fmc();
    QString verzeichnis_root_cix();
    QString verzeichnis_ziel_auswahl();
    bool quelldateien_erhalten();
    bool std_dateinamen_verwenden();
    QString drehung_wst();
    QString tiefeneinst_fkon();
    bool kurze_geraden_importieren();
    double geraden_schwellwert();
    bool formartierungen_aufbrechen();
    bool fkon_kantenschonend();
    double gehrungen_zugabe();
    bool wkz_fr_fmc();
    bool wkz_fr_ganx();
    bool wkz_fr_cix();
    bool wkz_fr_ggf();

private:
    bool Entwicklermodus;
    bool Eigenes_format_immer_mit_exportieren;
    QString Verzeichnis_quelle;
    QString Verzeichnis_ziel_server;
    QString Verzeichnis_ziel_lokal;
    QString Verzeichnis_root_ganx;
    QString Verzeichnis_root_fmc;
    QString Verzeichnis_root_cix;
    QString Verzeichnis_ziel_auswahl;
    bool Quelldateien_erhalten;
    bool Std_dateinamen_verwenden;
    QString Drehung_wst;
    QString Tiefeneinst_fkon;
    bool Kurze_geraden_importieren;
    double Geraden_schwellwert;
    bool Formartierungen_aufbrechen;
    bool Fkon_kantenschonend;
    double Gehrungen_zugabe;
    bool WKZ_fr_fmc;
    bool WKZ_fr_ganx;
    bool WKZ_fr_cix;
    bool WKZ_fr_ggf;

};

#endif // EINSTELLUNG_H
