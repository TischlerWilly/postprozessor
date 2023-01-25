#ifndef DIALOG_BEARB_BOHRUNG_H
#define DIALOG_BEARB_BOHRUNG_H

#include "Klassen/wst/bohrung.h"
#include "Klassen/wenndannsonst.h"
#include "Klassen/wst/werkstueck.h"
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
    void set_data(QString d, werkstueck *w);

private slots:
    void on_btn_ok_clicked();
    void on_btn_abbrechen_clicked();

signals:
    void signal_bo(bohrung bo);

private:
    Ui::Dialog_bearb_bohrung *ui;
    werkstueck *Wst;
    QString var_zu_wert(QString term);
};

#endif // DIALOG_BEARB_BOHRUNG_H
