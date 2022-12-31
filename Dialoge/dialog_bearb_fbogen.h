#ifndef DIALOG_BEARB_FBOGEN_H
#define DIALOG_BEARB_FBOGEN_H

#include "Klassen/wst/fraeserbogen.h"
#include "Klassen/formel.h"
#include "Klassen/wst/werkstueck.h"
#include <QDialog>

namespace Ui {
class Dialog_bearb_fbogen;
}

class Dialog_bearb_fbogen : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_bearb_fbogen(QWidget *parent = nullptr);
    ~Dialog_bearb_fbogen();
    void set_data(QString d, werkstueck *w);

private slots:
    void on_btn_ok_clicked();
    void on_btn_abbrechen_clicked();

signals:
    void signal_fbogen(fraeserbogen fb);

private:
    Ui::Dialog_bearb_fbogen *ui;
    werkstueck *Wst;
    QString var_zu_wert(QString term);
};

#endif // DIALOG_BEARB_FBOGEN_H
