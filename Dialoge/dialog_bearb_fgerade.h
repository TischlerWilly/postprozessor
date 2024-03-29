#ifndef DIALOG_BEARB_FGERADE_H
#define DIALOG_BEARB_FGERADE_H

#include "Klassen/wst/fraesergerade.h"
#include "Klassen/formel.h"
#include "Klassen/wst/werkstueck.h"
#include <QDialog>

namespace Ui {
class Dialog_bearb_fgerade;
}

class Dialog_bearb_fgerade : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_bearb_fgerade(QWidget *parent = nullptr);
    ~Dialog_bearb_fgerade();
    void set_data(QString d, werkstueck *w);

private slots:
    void on_btn_ok_clicked();
    void on_btn_abbrechen_clicked();

signals:
    void signal_fgerade(fraesergerade fg);

private:
    Ui::Dialog_bearb_fgerade *ui;
    werkstueck *Wst;
    QString var_zu_wert(QString term);
};

#endif // DIALOG_BEARB_FGERADE_H
