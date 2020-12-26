#ifndef EINSTELLUNG_H
#define EINSTELLUNG_H

#include <QString>
#include "text_zeilenweise.h"
#include "Funktionen/umwandeln.h"

class einstellung
{
public:
    einstellung();

    //set:
    void set_text(QString t);
    void set_verzeichniss_quelle(QString v);
    void set_verzeichniss_ziel_a(QString v);
    void set_verzeichniss_ziel_b(QString v);
    bool set_verzeichniss_ziel_auswahl(QString abc);
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
    void set_export_ganx(bool jn);
    void set_export_ganx(QString jn);
    void set_export_fmc(bool jn);
    void set_export_fmc(QString jn);
    void set_export_ggf(bool jn);
    void set_export_ggf(QString jn);
    void set_export_eigen(bool jn);
    void set_export_eigen(QString jn);


    //get:
    QString text();
    QString verzeichniss_quelle();
    QString verzeichniss_ziel_a();
    QString verzeichniss_ziel_b();
    QString verzeichniss_ziel_auswahl();
    bool quelldateien_erhalten();
    bool std_dateinamen_verwenden();
    QString drehung_wst();
    QString tiefeneinst_fkon();
    bool kurze_geraden_importieren();
    double geraden_schwellwert();
    bool formartierungen_aufbrechen();
    bool fkon_kantenschonend();
    double gehrungen_zugabe();
    bool export_ganx();
    bool export_fmc();
    bool export_ggf();
    bool export_eigen();

private:
    QString Verzeichniss_quelle;
    QString Verzeichniss_ziel_a;
    QString Verzeichniss_ziel_b;
    QString Verzeichniss_ziel_auswahl;
    bool Quelldateien_erhalten;
    bool Std_dateinamen_verwenden;
    QString Drehung_wst;
    QString Tiefeneinst_fkon;
    bool Kurze_geraden_importieren;
    double Geraden_schwellwert;
    bool Formartierungen_aufbrechen;
    bool Fkon_kantenschonend;
    double Gehrungen_zugabe;
    bool Export_ganx;
    bool Export_fmc;
    bool Export_ggf;
    bool Export_eigen;

};

#endif // EINSTELLUNG_H
