#ifndef DIALOG_SAEGE_H
#define DIALOG_SAEGE_H

#include <QDialog>

#include "Klassen/text_zw.h"
#include "Klassen/wkz/wkz_saege.h"
#include "Klassen/wenndannsonst.h"
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
    void clear();

private:
    Ui::Dialog_saege *ui;
    bool Wkz_ist_neu;

public slots:
    void set_Data(text_zeilenweise msg);
    void set_Data(text_zw msg, bool ist_neues_wkz = false);
    void neueSaege();

signals:
    void Data(text_zeilenweise wkz, bool ist_neues_wkz);
    void Data(text_zw wkz, bool ist_neues_wkz);

private slots:
    void on_pushButton_abbrechen_clicked();
    void on_pushButton_ok_clicked();
};

#endif // DIALOG_SAEGE_H
