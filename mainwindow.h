#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QClipboard>
#include <QDateTime>

#include "Klassen/prgpfade.h"
#include "Defines/dateinamen.h"
#include "Dialoge/dialog_wkz.h"
#include "mainwin_wkzmagazin.h"
#include "Dialoge/dialog_stdnamen.h"
#include "Dialoge/dialog_einstellung_pfade.h"
#include "Dialoge/dialog_einstellung_ganx.h"
#include "Dialoge/dialog_einstellung_dxf.h"
#include "Dialoge/dialog_einstellung_dxf_klassen.h"
#include "Dialoge/dialog_programmtext.h"
#include "Dialoge/dialog_exportuebersicht.h"

#include "mainwin_wst_bearbeiten.h"

#include "Funktionen/text.h"
#include "Klassen/text_zeilenweise.h"
#include "Klassen/text_zw.h"
#include "Klassen/wst/werkstuecke.h"
#include "Klassen/werkzeugmagazin.h"
#include "Klassen/einstellung.h"
#include "Klassen/einstellung_ganx.h"
#include "Klassen/geo/vorschau.h"
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
    void resizeEvent(QResizeEvent *event);
    void on_checkBox_quelldat_erhalt_stateChanged();
    void on_checkBox_std_namen_zuweisen_stateChanged();
    void on_radioButton_drehung_0_toggled(bool checked);
    void on_radioButton_drehung_90_toggled(bool checked);
    void on_radioButton_drehung_180_toggled(bool checked);
    void on_radioButton_drehung_270_toggled(bool checked);
    void on_radioButton_drehung_autom_toggled(bool checked);
    void on_actionWerkzeug_ganx_anzeigen_triggered();
    void on_actionInfo_triggered();
    void on_pushButton_dateien_auflisten_clicked();
    void on_actionWerkzeug_fmc_anzeigen_triggered();
    void on_actionStandard_Namen_anzeigen_triggered();
    void zielordner_leeren();
    void on_radioButton_fkon_ti_quell_toggled(bool checked);
    void on_radioButton_fkon_ti_wkz_toggled(bool checked);
    void on_checkBox_geraden_stateChanged();
    void on_lineEdit_geraden_schwellenwert_editingFinished();
    void on_checkBox_formatierung_aufbrechen_stateChanged();
    void on_checkBox_fkon_kantenschonend_stateChanged();
    void on_actionWerkzeug_ggf_anzeigen_triggered();
    void on_lineEdit_zugabe_gehr_editingFinished();
    void on_actionEinstellung_ganx_triggered();
    void on_actionEinstellung_pfade_triggered();
    void on_pushButton_import_clicked();
    void on_listWidget_wste_currentRowChanged(int currentRow);
    void on_radioButton_vorschau_eigen_clicked(bool checked);
    void on_radioButton_vorschau_ganx_clicked(bool checked);
    void on_radioButton_vorschau_fmc_clicked(bool checked);
    void on_radioButton_vorschau_ggf_clicked(bool checked);
    void on_listWidget_wste_itemDoubleClicked();
    void on_lineEdit_projekt_editingFinished();
    void on_lineEdit_pos_editingFinished();
    void on_lineEdit_baugruppe_editingFinished();
    void on_listWidget_wste_itemSelectionChanged();
    void on_pushButton_einzelexport_clicked();
    void on_pushButton_umbenennen_clicked();
    void on_actionExportUebersicht_triggered();
    void on_actionWST_ausblenden_triggered();
    void on_actionEinstellung_dxf_klassen_triggered();
    void on_actionEinstellung_dxf_triggered();
    void on_actionWST_bearbeiten_triggered();
    void on_listWidget_wste_itemClicked(QListWidgetItem *item);

    void on_actionEntwicklermodus_triggered(bool checked);

    void on_actionTestfunktion_triggered();

private:
    Ui::MainWindow *ui;
    text_zeilenweise wkz_magazin_ganx;//alt
    text_zeilenweise wkz_magazin_fmc;//alt
    text_zeilenweise wkz_magazin_ggf;//alt
    wkz_magazin wkz_mag_ganx;//neu
    wkz_magazin wkz_mag_fmc;//neu
    wkz_magazin wkz_mag_ggf;//neu
    prgpfade pf;

    //Variablen:
    QString tz; //Trennzeichen für Pfade (Linux '/'  Windows '\')
    text_zeilenweise dateien_alle;
    werkstuecke wste;
    text_zeilenweise namen_std_vor;         //Standard-Dateinamen von CAD
    text_zeilenweise namen_std_nach;        //Standard-Dateinamen eigen
    einstellung Einstellung;
    einstellung_ganx Einstellung_ganx;
    einstellung_dxf Einstellung_dxf;
    einstellung_dxf_klassen Einstellung_dxf_klassen;
    vorschau vorschaufenster;
    QString Projektposition;
    bool Projektpfad_stimmt;
    QString Pfad_mit_dateinamen;

    //Funktionen:
    void setup();
    void schreibe_ini();
    void dateien_erfassen();
    QString verzeichnis_ziel();
    void import();
    void closeEvent(QCloseEvent *ce);
    void set_projektpfad();
    void speichere_ausgabepfad(QString pfad);
    void speichere_ausgabepfad_fmc(QString pfad);
    void schreibe_in_zwischenablage(QString s);
    QString fenstertitel_exportuebersicht();
    void set_prginfo();

    //Dialoge:
    Dialog_WKZ dlg_wkz;
    Dialog_stdnamen dlg_stdnamen;
    Dialog_Einstellung_pfade dlg_Einstellung_pfade;
    Dialog_einstellung_ganx dlg_einstellung_ganx;
    Dialog_einstellung_dxf dlg_einstellung_dxf;
    Dialog_einstellung_dxf_klassen dlg_einstellung_dxf_klassen;
    Dialog_programmtext dlg_prgtext;
    Dialog_ExportUebersicht dlg_exporte;
    MainWin_wst_bearbeiten dlg_wst_bearbeiten;
    mainwin_wkzmagazin dlg_wkzmag;

signals:
    void sendDialogDataWKZ(QString fenstertitel, text_zeilenweise werkzeugmagazin);
    void sendStdNamen(text_zeilenweise namen_vor, text_zeilenweise namen_nach);
    void sendEinstellungPfade(einstellung e);
    void sendEinstellungGANX(einstellung_ganx e);
    void sendEinstellungDxf(einstellung_dxf e);
    void sendEinstellungDxfKlassen(einstellung_dxf eg, einstellung_dxf_klassen ek);
    void sendVorschauAktualisieren(werkstueck w_neu, int aktive_zeile);
    void sendProgrammtext(werkstueck* w);
    void signal_exporte(text_zeilenweise daten);
    void signal_wstexport(QString name, QString format, bool exportiert);
    void signal_wst_umbenennen(QString name_vor, QString name_nach);
    void signal_wst_ausblenden(QString name, bool ausblenden);

public slots:
    void getDialogDataWKZ(QString fenstertitel, text_zeilenweise werkzeugmagazin);
    void getStdNamen(text_zeilenweise namen_vor, text_zeilenweise namen_nach);
    void getEinstellungGANX(einstellung_ganx e);
    void getEinstellungDxf(einstellung_dxf e);
    void getEinstellungDxfKlassen(einstellung_dxf_klassen e);
    void getEinstellung(einstellung e);
    void getMausPosXY(QPoint p);
    void getCADFehler(QString w);
    void getWarnungen(QString w);
    void getWSTMas(double l, double b, double d);
    void getDrewi(QString w);
    void slotWstChanged(werkstueck *w, int index);

};

#endif // MAINWINDOW_H
