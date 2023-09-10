#ifndef DIALOG_FRAESER_H
#define DIALOG_FRAESER_H

#include <QDialog>

#include "Klassen/text_zw.h"
#include "Klassen/wkz/wkz_fraeser.h"
#include "Klassen/wenndannsonst.h"
#include "Defines/werkzeug.h"

namespace Ui {
class Dialog_fraeser;
}

class Dialog_fraeser : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_fraeser(QWidget *parent = 0);
    ~Dialog_fraeser();
    void clear();

private:
    Ui::Dialog_fraeser *ui;    
    bool Wkz_ist_neu;

public slots:
    void set_Data(text_zw msg, bool ist_neues_wkz = false);
    void neuerFraeser();

signals:
    void Data(text_zw wkz, bool ist_neues_wkz);

private slots:
    void on_pushButton_abbrechen_clicked();
    void on_pushButton_ok_clicked();
};

#endif // DIALOG_FRAESER_H
