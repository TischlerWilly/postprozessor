#ifndef DIALOG_BEARB_RTA_H
#define DIALOG_BEARB_RTA_H

#include "Klassen/wst/rechtecktasche.h"
#include "Klassen/formel.h"
#include "Klassen/wst/werkstueck.h"
#include "Dialoge/dialog_fraeserauswahl.h"
#include <QDialog>

namespace Ui {
class Dialog_bearb_rta;
}

class Dialog_bearb_rta : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_bearb_rta(QWidget *parent = nullptr);
    ~Dialog_bearb_rta();
    void set_data(QString d, werkstueck *w, text_zw wkzmag);

private slots:
    void on_btn_abbrechen_clicked();
    void on_btn_ok_clicked();
    void on_pushButton_wkzwahl_clicked();

public slots:
    void get_wkz(QString wkz);

signals:
    void signal_rta(rechtecktasche rta);

private:
    Ui::Dialog_bearb_rta *ui;
    werkstueck *Wst;
    text_zw Wkzmag;
    QString var_zu_wert(QString term);

    Dialog_fraeserauswahl dlg_wkzwahl;

};

#endif // DIALOG_BEARB_RTA_H
