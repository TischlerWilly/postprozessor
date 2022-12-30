#ifndef MAINWIN_WST_BEARBEITEN_H
#define MAINWIN_WST_BEARBEITEN_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "Klassen/geo/vorschau.h"
#include "Klassen/wst/werkstueck.h"
#include "Dialoge/dialog_bearb_pkopf.h"
#include "Dialoge/dialog_bearb_rta.h"
#include "Dialoge/dialog_bearb_bohrung.h"
#include "Dialoge/dialog_bearb_nut.h"
#include "Dialoge/dialog_bearb_faufruf.h"
#include "Dialoge/dialog_bearb_fgerade.h"
#include "Dialoge/dialog_bearb_fbogen.h"

#include "Funktionen/funktionen_prgtext.h"
#include "Klassen/undo_redo_tz.h"

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

private:
    Ui::MainWin_wst_bearbeiten *ui;
    vorschau vorschaufenster;
    werkstueck *Wst;
    undo_redo_tz UnReDo;

    void clear();
    void update_listwidget();
    void zeile_bearbeiten(int zeile);

signals:
    void sendVorschauAktualisieren(werkstueck w_neu, int aktive_zeile);
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

public slots:
    //Bearbeiten
    void slot_rta(rechtecktasche rta);
    void slot_bo(bohrung bo);    
    void slot_nut(nut nu);
    void slot_faufruf(fraueseraufruf fa);
    void slot_fgerade(fraesergerade fg);
    void slot_fbogen(fraeserbogen fb);
    //Erstellen/Make:
    void slot_make(QString bearb);
    void slot_make_bo(bohrung bo);
    void slot_make_rta(rechtecktasche rt);
    void slot_make_nut(nut nu);
};
#endif // MAINWIN_WST_BEARBEITEN_H
