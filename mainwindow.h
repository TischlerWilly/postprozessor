#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>

#include "Klassen/prgpfade.h"
#include "Defines/dateinamen.h"
#include "Dialoge/dialog_wkz.h"
#include "Dialoge/dialog_stdnamen.h"
#include "Dialoge/dialog_einstellung_pfade.h"
#include "Dialoge/dialog_einstellung_ganx.h"

#include "Funktionen/text.h"
#include "Klassen/text_zeilenweise.h"
#include "Klassen/wst/werkstuecke.h"
#include "Klassen/werkzeugmagazin.h"
#include "Klassen/einstellung.h"
#include "Klassen/einstellung_ganx.h"
#include "ToDo.h"


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
    void zielordner_leeren();
    void on_radioButton_fkon_ti_quell_toggled(bool checked);
    void on_radioButton_fkon_ti_wkz_toggled(bool checked);
    void on_checkBox_geraden_stateChanged();
    void on_lineEdit_geraden_schwellenwert_editingFinished();
    void on_checkBox_formatierung_aufbrechen_stateChanged();
    void on_checkBox_fkon_kantenschonend_stateChanged();
    void on_checkBox_af_ggf_stateChanged();
    void on_actionWerkzeug_ggf_anzeigen_triggered();
    void on_lineEdit_zugabe_gehr_editingFinished();
    void on_actionEinstellung_ganx_triggered();
    void on_actionEinstellung_pfade_triggered();

private:
    Ui::MainWindow *ui;
    text_zeilenweise wkz_magazin_ganx;
    text_zeilenweise wkz_magazin_fmc;
    text_zeilenweise wkz_magazin_ggf;
    prgpfade pf;

    //Radio Buttons:
    //QString drehung_des_bauteils; // 0 | 90 | 180 | 270 | AUTO
    //QString option_fkon_ti;
        //orgi = Tiefe gemäß Importdatei aus CAD
        //wkz  = Tiefe gemäß Zustellung aus dem WKZ-Magazin = evtl. mehrere Zustellungen


    //Variablen:
    QString tz; //Trennzeichen für Pfade (Linux '/'  Windows '\')
    text_zeilenweise dateien_alle;
    werkstuecke wste;
    text_zeilenweise namen_std_vor;         //Standard-Dateinamen von CAD
    text_zeilenweise namen_std_nach;        //Standard-Dateinamen eigen
    //QString geraden_schwellenwert;          //Geraden ab dieser Lnge werden nicht importiert
    //QString zugabe_gehrungen;               //Maßangabe wie viel Zugabe bei Gehrungen gewünscht ist
    einstellung Einstellung;
    einstellung_ganx Einstellung_ganx;

    //Funktionen:
    void setup();
    void schreibe_ini();
    void dateien_erfassen();
    QString verzeichnis_ziel();

    //Dialoge:
    Dialog_WKZ dlg_wkz;
    Dialog_stdnamen dlg_stdnamen;
    Dialog_Einstellung_pfade dlg_Einstellung_pfade;
    Dialog_einstellung_ganx dlg_einstellung_ganx;


signals:
    void sendDialogDataWKZ(QString fenstertitel, text_zeilenweise werkzeugmagazin);
    void sendStdNamen(text_zeilenweise namen_vor, text_zeilenweise namen_nach);
    void sendEinstellungPfade(einstellung e);
    void sendEinstellungGANX(einstellung_ganx e);

public slots:
    void getDialogDataWKZ(QString fenstertitel, text_zeilenweise werkzeugmagazin);
    void getStdNamen(text_zeilenweise namen_vor, text_zeilenweise namen_nach);
    void getEinstellungGANX(einstellung_ganx e);
    void getEinstellung(einstellung e);

};

#endif // MAINWINDOW_H
