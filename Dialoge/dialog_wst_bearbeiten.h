#ifndef DIALOG_WST_BEARBEITEN_H
#define DIALOG_WST_BEARBEITEN_H

#include <QDialog>
#include <QListWidgetItem>
#include "Klassen/geo/vorschau.h"
#include "Klassen/wst/werkstueck.h"
#include "Dialoge/dialog_bearb_rta.h"
#include "Dialoge/dialog_bearb_bohrung.h"
#include "Funktionen/funktionen_prgtext.h"

namespace Ui {
class Dialog_wst_bearbeiten;
}

class Dialog_wst_bearbeiten : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_wst_bearbeiten(QWidget *parent = nullptr);
    ~Dialog_wst_bearbeiten();
    void set_wst(werkstueck *w);

private:
    Ui::Dialog_wst_bearbeiten *ui;
    vorschau vorschaufenster;
    werkstueck *Wst;

    void clear();
    void update_listwidget();

signals:
    void sendVorschauAktualisieren(werkstueck w_neu, int aktive_zeile);
    void signalIndexChange(int index);

private slots:
    void resizeEvent(QResizeEvent *event);
    void getMausPosXY(QPoint p);
    void slot_zeilennummer(uint nr);
    void on_listWidget_prgtext_currentRowChanged(int currentRow);    
    void on_listWidget_prgtext_itemDoubleClicked(QListWidgetItem *item);

public slots:
    void slot_rta(rechtecktasche rta);
    void slot_bo(bohrung bo);
};

#endif // DIALOG_WST_BEARBEITEN_H
