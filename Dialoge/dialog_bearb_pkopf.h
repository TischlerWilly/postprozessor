#ifndef DIALOG_BEARB_PKOPF_H
#define DIALOG_BEARB_PKOPF_H

#include "Klassen/wst/werkstueck.h"
#include "Klassen/wenndannsonst.h"
#include <QDialog>

namespace Ui {
class Dialog_bearb_pkopf;
}

class Dialog_bearb_pkopf : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_bearb_pkopf(QWidget *parent = nullptr);
    ~Dialog_bearb_pkopf();
    void set_data(werkstueck *w);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();

private:
    Ui::Dialog_bearb_pkopf *ui;
    werkstueck *Wst;
};

#endif // DIALOG_BEARB_PKOPF_H
