#ifndef DIALOG_BEARB_FAUFRUF_H
#define DIALOG_BEARB_FAUFRUF_H

#include "Klassen/wst/fraeseraufruf.h"
#include "Klassen/formel.h"
#include "Klassen/wst/werkstueck.h"
#include "Dialoge/dialog_fraeserauswahl.h"
#include <QDialog>

namespace Ui {
class Dialog_bearb_faufruf;
}

class Dialog_bearb_faufruf : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_bearb_faufruf(QWidget *parent = nullptr);
    ~Dialog_bearb_faufruf();
    void set_data(QString d, werkstueck *w, text_zw wkzmag);

private slots:
    void on_btn_ok_clicked();
    void on_btn_abbrechen_clicked();
    void on_pushButton_wkzwahl_clicked();

    void on_comboBox_kor_currentTextChanged(const QString &arg1);

    void on_comboBox_bezug_currentTextChanged(const QString &arg1);

public slots:
    void get_wkz(QString wkz);

signals:
    void signal_faufruf(fraeseraufruf fa);

private:
    Ui::Dialog_bearb_faufruf *ui;
    werkstueck *Wst;
    text_zw Wkzmag;
    QString var_zu_wert(QString term);

    Dialog_fraeserauswahl dlg_wkzwahl;
};

#endif // DIALOG_BEARB_FAUFRUF_H
