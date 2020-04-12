#ifndef DIALOG_SAEGE_H
#define DIALOG_SAEGE_H

#include <QDialog>

#include "Klassen/text_zeilenweise.h"
#include "Defines/werkzeug.h"

namespace Ui {
class Dialog_saege;
}

class Dialog_saege : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_saege(QWidget *parent = 0);
    ~Dialog_saege();

private slots:
    void on_pushButton_abbrechen_clicked();
    void on_pushButton_ok_clicked();

private:
    Ui::Dialog_saege *ui;
    void clear();
    void setup();
    bool wkz_ist_neu;

public slots:
    void getData(text_zeilenweise msg);
    void neueSaege();

signals:
    void sendData(text_zeilenweise wkz, bool ist_neues_wkz);



};

#endif // DIALOG_SAEGE_H
