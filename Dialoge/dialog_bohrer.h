#ifndef DIALOG_BOHRER_H
#define DIALOG_BOHRER_H

#include <QDialog>

#include "Klassen/text_zw.h"
#include "Klassen/wkz/wkz_bohrer.h"
#include "Klassen/wenndannsonst.h"
#include "Defines/werkzeug.h"

namespace Ui {
class Dialog_bohrer;
}

class Dialog_bohrer : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_bohrer(QWidget *parent = 0);
    ~Dialog_bohrer();
    void clear();

private:
    Ui::Dialog_bohrer *ui;
    bool Wkz_ist_neu;

public slots:
    void set_Data(text_zeilenweise msg);
    void set_Data(text_zw msg, bool ist_neues_wkz = false);
    void neuerBohrer();

signals:
    void Data(text_zeilenweise wkz, bool ist_neues_wkz);
    void Data(text_zw wkz, bool ist_neues_wkz);

private slots:
    void on_pushButton_abbrechen_clicked();
    void on_pushButton_ok_clicked();
};

#endif // DIALOG_BOHRER_H
