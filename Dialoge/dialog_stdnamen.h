#ifndef DIALOG_STDNAMEN_H
#define DIALOG_STDNAMEN_H

#include <QDialog>
#include "Klassen/text_zeilenweise.h"
#include "Defines/dateinamen.h"
#include "dialog_stdname.h"
#include "Funktionen/text.h"
#include "QMessageBox"

namespace Ui {
class Dialog_stdnamen;
}

class Dialog_stdnamen : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_stdnamen(QWidget *parent = 0);
    ~Dialog_stdnamen();

public slots:
    void slot_setup(text_zeilenweise namen_vor, text_zeilenweise namen_nach);
    void slot_getName(QString vor, QString nach);

private slots:
    void on_pushButton_neu_clicked();
    void on_pushButton_edit_clicked();
    void on_pushButton_entf_clicked();
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();

signals:
    void signalEditNane(QString vor, QString nach);
    void signal_sendData(text_zeilenweise namen_vor, text_zeilenweise namen_nach);

private:
    Ui::Dialog_stdnamen *ui;
    text_zeilenweise vor_tz;
    text_zeilenweise nach_tz;

    Dialog_stdname dlg_name;

    void update_listwidget();

};

#endif // DIALOG_STDNAMEN_H
