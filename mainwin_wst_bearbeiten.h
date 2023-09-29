#ifndef MAINWIN_WST_BEARBEITEN_H
#define MAINWIN_WST_BEARBEITEN_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "Klassen/geo/vorschau.h"
#include "Klassen/wst/werkstueck.h"
#include "Klassen/wkz/wkz_magazin.h"
#include "Dialoge/dialog_bearb_pkopf.h"
#include "Dialoge/dialog_bearb_rta.h"
#include "Dialoge/dialog_bearb_bohrung.h"
#include "Dialoge/dialog_bearb_nut.h"
#include "Dialoge/dialog_bearb_faufruf.h"
#include "Dialoge/dialog_bearb_fgerade.h"
#include "Dialoge/dialog_bearb_fbogen.h"
#include "Dialoge/dialog_bearb_verschieben.h"
#include "Dialoge/dialog_doppelteil_erzeugen.h"

#include "Funktionen/funktionen_prgtext.h"
#include "Klassen/undo_redo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWin_wst_bearbeiten; }
QT_END_NAMESPACE

class MainWin_wst_bearbeiten : public QMainWindow
{
    Q_OBJECT

public:
    MainWin_wst_bearbeiten(QWidget *parent = nullptr);
    ~MainWin_wst_bearbeiten();
    void set_wst(werkstueck *w);
    void set_wkz(wkz_magazin *w);

private:
    Ui::MainWin_wst_bearbeiten *ui;
    vorschau vorschaufenster;
    werkstueck *Wst;
    wkz_magazin *Wkz_ptr;
    wkz_magazin Wkz_kopie;
    undo_redo<text_zw> UnReDo;
    undo_redo<double> UnReDo_L;
    undo_redo<double> UnReDo_B;
    undo_redo<double> UnReDo_D;
    QString KopierterEintrag;
    double letzte_wst_l;
    double letzte_wst_b;
    double letzte_wst_d;
    Dialog_doppelteil_erzeugen dlg_dt;

    void clear();
    void update_listwidget();
    void zeile_bearbeiten(int zeile);
    QString verschiebe_einen(QString bearb, double ax, double ay, double az);
    int auswahl_erster();
    int auswahl_letzter();
    int auswahl_menge();
    void unredo_neu();
    void unredo_clear();

signals:
    void sendVorschauAktualisieren(werkstueck w_neu, int aktive_zeile, wkz_magazin wkzm);
    void signalIndexChange(int index);

private slots:
    void resizeEvent(QResizeEvent *event);
    void getMausPosXY(QPoint p);
    void slot_zeilennummer(uint nr, bool bearbeiten);
    void on_listWidget_prgtext_currentRowChanged(int currentRow);
    void on_listWidget_prgtext_itemDoubleClicked(QListWidgetItem *item);
    void on_actionMakeBohrung_triggered();
    void on_actionMakeRTA_triggered();
    void on_actionMakeNut_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionEntf_triggered();
    void on_actionKopieren_triggered();
    void on_actionEinfuegen_triggered();
    void on_actionVerschieben_triggered();
    void on_actionBearbeiten_triggered();
    void on_actionDoppelteil_erzeugen_triggered();
    void on_actionFormartierungen_aufbrechen_triggered();

public slots:
    //Bearbeiten
    void zeile_aendern(int index, QString bearb, bool unredor_verwenden);
    void slot_rta(rechtecktasche rta);
    void slot_bo(bohrung bo);
    void slot_nut(nut nu);
    void slot_faufruf(fraeseraufruf fa);
    void slot_fgerade(fraesergerade fg);
    void slot_fbogen(fraeserbogen fb);
    //Erstellen/Make:
    void slot_make(QString bearb, bool unredor_verwenden);
    void slot_make_bo(bohrung bo);
    void slot_make_rta(rechtecktasche rt);
    void slot_make_nut(nut nu);
    //Manipulation:
    void slot_verschieben(punkt3d p);
    void slot_dt_erzeugen(QString bezug, double wst_l, double wst_b, bool spiegeln, bool drehen);
};
#endif // MAINWIN_WST_BEARBEITEN_H
