#ifndef DIALOG_FRAESER_H
#define DIALOG_FRAESER_H

#include <QDialog>

#include "Klassen/text_zeilenweise.h"
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

private:
    Ui::Dialog_fraeser *ui;
    void clear();
    void setup();
    bool wkz_ist_neu;

public slots:
    void getData(text_zeilenweise msg);
    void neuerFraeser();

signals:
    void sendData(text_zeilenweise wkz, bool ist_neues_wkz);


private slots:
    void on_pushButton_abbrechen_clicked();
    void on_pushButton_ok_clicked();
};

#endif // DIALOG_FRAESER_H
