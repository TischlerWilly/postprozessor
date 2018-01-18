#ifndef DIALOG_WKZ_H
#define DIALOG_WKZ_H

#include <QDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include "./allgemKlassen/text_zeilenweise.h"
#include "./Definitionen/werkzeug.h"
#include "dialog_bohrer.h"
#include "dialog_fraeser.h"
#include "dialog_saege.h"

namespace Ui {
class Dialog_WKZ;
}

class Dialog_WKZ : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_WKZ(QWidget *parent = 0);
    ~Dialog_WKZ();

private:
    Ui::Dialog_WKZ *ui;
    void clear();
    Dialog_bohrer dibo;
    Dialog_fraeser difr;
    Dialog_saege disae;

public slots:
    void getDialogDataWKZ(QString fenstertitel, text_zeilenweise werkzeugmagazin);
    void getParamaterWKZ(text_zeilenweise wkz, bool ist_neues_wkz);

private slots:
    void on_pushButton_abbrechen_clicked();
    void on_pushButton_speichern_clicked();
    void on_listWidget_wkz_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_neu_bohrer_clicked();
    void on_pushButton_entfernen_clicked();
    void on_pushButton_neu_fraeser_clicked();
    void on_pushButton_neu_saege_clicked();
    void on_pushButton_bearbeiten_clicked();

signals:
    void sendData_Bohrer(text_zeilenweise wkz);
    void sendData_Fraeser(text_zeilenweise wkz);
    void sendData_Saege(text_zeilenweise wkz);
    void neues_wkz_bohrer();
    void neues_wkz_fraeser();
    void neues_wkz_saege();
    void sendData_wkzmagazin(QString fenstertitel,text_zeilenweise werkzeugmagazin);

};

#endif // DIALOG_WKZ_H
