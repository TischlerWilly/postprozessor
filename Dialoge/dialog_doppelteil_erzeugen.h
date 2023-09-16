#ifndef DIALOG_DOPPELTEIL_ERZEUGEN_H
#define DIALOG_DOPPELTEIL_ERZEUGEN_H

#include <QDialog>
#include <QMessageBox>
#include "Klassen/text_zw.h"
#include "Funktionen/umwandeln.h"
#include "Defines/def_bearbeitungen.h"

namespace Ui {
class Dialog_doppelteil_erzeugen;
}

class Dialog_doppelteil_erzeugen : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_doppelteil_erzeugen(QWidget *parent = nullptr);
    ~Dialog_doppelteil_erzeugen();
    void set_wst_laenge(double l);
    void set_wst_breite(double b);
    void set_bearb(text_zw bearb);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();
    void on_radioButton_vo_clicked(bool checked);
    void on_radioButton_hi_clicked(bool checked);
    void on_radioButton_li_clicked(bool checked);
    void on_radioButton_re_clicked(bool checked);

private:
    Ui::Dialog_doppelteil_erzeugen *ui;
    double Wst_la;
    double Wst_br;
    text_zw Bearb;

    void berechne_wst_groesse();

};

#endif // DIALOG_DOPPELTEIL_ERZEUGEN_H
