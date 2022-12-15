#ifndef DIALOG_BEARB_RTA_H
#define DIALOG_BEARB_RTA_H

#include "Klassen/wst/rechtecktasche.h"
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
    void set_data(QString d);

private slots:
    void on_btn_abbrechen_clicked();
    void on_btn_ok_clicked();

private:
    Ui::Dialog_bearb_rta *ui;
    rechtecktasche Rta;
};

#endif // DIALOG_BEARB_RTA_H
