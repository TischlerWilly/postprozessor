#ifndef DIALOG_WKZ_H
#define DIALOG_WKZ_H

#include <QDialog>
#include <QMessageBox>
#include <QListWidgetItem>
#include "./allgemKlassen/text_zeilenweise.h"
#include "./Definitionen/werkzeug.h"

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

public slots:
    void getDialogDataWKZ(QString fenstertitel, text_zeilenweise werkzeugmagazin);

private slots:
    void on_pushButton_abbrechen_clicked();
    void on_pushButton_speichern_clicked();
    void on_listWidget_wkz_itemDoubleClicked(QListWidgetItem *item);
};

#endif // DIALOG_WKZ_H
