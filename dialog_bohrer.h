#ifndef DIALOG_BOHRER_H
#define DIALOG_BOHRER_H

#include <QDialog>

#include "./allgemKlassen/text_zeilenweise.h"
#include "./Definitionen/werkzeug.h"

namespace Ui {
class Dialog_bohrer;
}

class Dialog_bohrer : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_bohrer(QWidget *parent = 0);
    ~Dialog_bohrer();

private:
    Ui::Dialog_bohrer *ui;
    void clear();
    void setup();
    bool wkz_ist_neu;

public slots:
    void getData(text_zeilenweise msg);
    void neuerBohrer();


private slots:
    void on_pushButton_abbrechen_clicked();
    void on_pushButton_ok_clicked();

signals:
    void sendData(text_zeilenweise wkz, bool ist_neues_wkz);

};

#endif // DIALOG_BOHRER_H
