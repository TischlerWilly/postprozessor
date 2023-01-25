#ifndef DIALOG_BEARB_FAUFRUF_H
#define DIALOG_BEARB_FAUFRUF_H

#include "Klassen/wst/fraueseraufruf.h"
#include "Klassen/formel.h"
#include "Klassen/wst/werkstueck.h"
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
    void set_data(QString d, werkstueck *w);

private slots:
    void on_btn_ok_clicked();
    void on_btn_abbrechen_clicked();

signals:
    void signal_faufruf(fraueseraufruf fa);

private:
    Ui::Dialog_bearb_faufruf *ui;
    werkstueck *Wst;
    QString var_zu_wert(QString term);
};

#endif // DIALOG_BEARB_FAUFRUF_H
