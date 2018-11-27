#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef PROGRAMMVERSION
#define PROGRAMMVERSION "1.18.11.27"
#endif //PROGRAMMVERSION

#include <QMainWindow>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>

#include "Definitionen/dateinamen.h"
#include "dialog_wkz.h"


#include "eigeneFunktionen/text.h"
#include "allgemKlassen/text_zeilenweise.h"
#include "KlassenWst/werkstuecke.h"
#include "werkzeugmagazin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_lineEdit_quelle_editingFinished();
    void on_lineEdit_ziel_editingFinished();
    void on_pushButton__quelle_clicked();
    void on_pushButton_ziel_clicked();
    void on_checkBox_quelldat_erhalt_stateChanged();
    void on_checkBox_std_namen_zuweisen_stateChanged();
    void on_checkBox_af_ganx_stateChanged();
    void on_radioButton_drehung_0_toggled(bool checked);
    void on_radioButton_drehung_90_toggled(bool checked);
    void on_radioButton_drehung_180_toggled(bool checked);
    void on_radioButton_drehung_270_toggled(bool checked);
    void on_radioButton_drehung_autom_toggled(bool checked);
    void on_actionWerkzeug_ganx_anzeigen_triggered();
    void on_actionInfo_triggered();
    void on_pushButton_dateien_auflisten_clicked();
    void on_pushButton_start_clicked();
    void on_checkBox_af_fmc_stateChanged();
    void on_actionWerkzeug_fmc_anzeigen_triggered();
    void on_checkBox_af_eigen_stateChanged();
    void on_actionStandard_Namen_anzeigen_triggered();
    void on_pushButton_zielordner_leeren_clicked();
    void on_radioButton_fkon_ti_quell_toggled(bool checked);
    void on_radioButton_fkon_ti_wkz_toggled(bool checked);
    void on_checkBox_geraden_stateChanged();
    void on_lineEdit_geraden_schwellenwert_editingFinished();

private:
    Ui::MainWindow *ui;
    text_zeilenweise wkz_magazin_ganx;
    text_zeilenweise wkz_magazin_fmc;

    //Pfade:
    QString verzeichnis_quelle;
    QString verzeichnis_ziel;

    //Checkboxen:
    QString quelldateien_erhalten;  // "ja" | "nein"
    QString std_namen;              // "ja" | "nein"
    QString erzeuge_ganx;           // "ja" | "nein"
    QString erzeuge_fmc;            // "ja" | "nein"
    QString erzeuge_eigenes_format; // "ja" | "nein"
    QString kurze_geraden_weglassen;// "ja" | "nein"

    //Radio Buttons:
    QString drehung_des_bauteils; // 0 | 90 | 180 | 270 | AUTO
    QString option_fkon_ti;
        //orgi = Tiefe gemäß Importdatei aus CAD
        //wkz  = Tiefe gemäß Zustellung aus dem WKZ-Magazin = evtl. mehrere Zustellungen


    //Variablen:
    QString tz; //Trennzeichen für Pfade (Linux '/'  Windows '\')
    text_zeilenweise dateien_alle;
    werkstuecke wste;
    text_zeilenweise namen_std_vor;         //Standard-Dateinamen von CAD
    text_zeilenweise namen_std_nach;        //Standard-Dateinamen eigen
    QString geraden_schwellenwert;          //Geraden ab dieser Lnge werden nicht importiert
    //double bezugsmass;

    //Funktionen:
    void setup();
    void schreibe_ini();
    void dateien_erfassen();

    //Dialoge:
    Dialog_WKZ dlg_wkz;

signals:
    void sendDialogDataWKZ(QString fenstertitel, text_zeilenweise werkzeugmagazin);

public slots:
    void getDialogDataWKZ(QString fenstertitel, text_zeilenweise werkzeugmagazin);

};

#endif // MAINWINDOW_H
