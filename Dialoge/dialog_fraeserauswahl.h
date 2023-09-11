#ifndef DIALOG_FRAESERAUSWAHL_H
#define DIALOG_FRAESERAUSWAHL_H

#include <QDialog>
#include "Klassen/wkz/wkz_magazin.h"

namespace Ui {
class Dialog_fraeserauswahl;
}

class Dialog_fraeserauswahl : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_fraeserauswahl(QWidget *parent = nullptr);
    ~Dialog_fraeserauswahl();
    void set_wkzmag(text_zw wkzm);

signals:
    void send_wkz(QString w);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();

private:
    Ui::Dialog_fraeserauswahl *ui;
    text_zw Wkzmag;
};

#endif // DIALOG_FRAESERAUSWAHL_H
