#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef PROGRAMMVERSION
#define PROGRAMMVERSION "0.1"
#endif //PROGRAMMVERSION

#include <QMainWindow>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>

#include "Definitionen/dateinamen.h"
#include "Definitionen/werkzeug.h"

#include "eigeneFunktionen/text.h"
#include "allgemKlassen/text_zeilenweise.h"

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

private:
    Ui::MainWindow *ui;
    text_zeilenweise wkz_magazin_ganx;

    //Pfade:
    QString verzeichnis_quelle;
    QString verzeichnis_ziel;

    //Checkboxen:
    QString quelldateien_erhalten;  // "ja" | "nein"
    QString std_namen;              // "ja" | "nein"
    QString erzeuge_ganx;           // "ja" | "nein"

    //Radio Buttons:
    QString drehung_des_bauteils; // 0 | 90 | 180 | AUTO


    //Variablen:
    QString tz; //Trennzeichen für Pfade (Linux '/'  Windows '\')
    text_zeilenweise dateien_alle;
    //double bezugsmass;

    //Funktionen:
    void setup();
    void schreibe_ini();
    void dateien_erfassen();
    QString get_wkz_nummer(text_zeilenweise wkz_magazin, QString wkz_typ, double dm = 0, double bearbeitungstiefe = 0);
    QString get_wkz_dm(text_zeilenweise wkz_magazin, QString wkz_nr);
    QString get_wkz_vorschub(text_zeilenweise wkz_magazin, QString wkz_nr);



};

#endif // MAINWINDOW_H
