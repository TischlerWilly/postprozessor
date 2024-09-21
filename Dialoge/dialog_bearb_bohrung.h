#ifndef DIALOG_BEARB_BOHRUNG_H
#define DIALOG_BEARB_BOHRUNG_H

#include "Klassen/wst/bohrung.h"
#include "Klassen/wenndannsonst.h"
#include "Klassen/wst/werkstueck.h"
#include "Dialoge/dialog_fraeserauswahl.h"
#include <QDialog>

namespace Ui {
class Dialog_bearb_bohrung;
}

class Dialog_bearb_bohrung : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_bearb_bohrung(QWidget *parent = nullptr);
    ~Dialog_bearb_bohrung();
    void set_data(QString d, werkstueck *w, text_zw wkzmag);

private slots:
    void on_btn_ok_clicked();
    void on_btn_abbrechen_clicked();
    void on_pushButton_invert_clicked();
    void on_pushButton_wkzwahl_clicked();

public slots:
    void get_wkz(QString wkz);

signals:
    void signal_bo(bohrung bo);

private:
    Ui::Dialog_bearb_bohrung *ui;
    werkstueck *Wst;
    text_zw Wkzmag;
    QString var_zu_wert(QString term);
    const int Bezug_ob = 0;
    const int Bezug_un = 1;
    const int Bezug_li = 2;
    const int Bezug_re = 3;
    const int Bezug_vo = 4;
    const int Bezug_hi = 5;

    Dialog_fraeserauswahl dlg_wkzwahl;
};

#endif // DIALOG_BEARB_BOHRUNG_H
