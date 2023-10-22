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
    void update_wkztabelle();
    void set_wkzmag(text_zw wkzm);
    void set_max_dm(double dm);
    void set_min_nutz(double nutzl);

signals:
    void send_wkz(QString w);

private slots:
    void resizeEvent(QResizeEvent *event);
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();

private:
    Ui::Dialog_fraeserauswahl *ui;
    text_zw Wkzmag;
    double Max_dm;
    double Min_nutzl;

    void set_fenstertitel();

};

#endif // DIALOG_FRAESERAUSWAHL_H
