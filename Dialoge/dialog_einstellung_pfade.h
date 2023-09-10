#ifndef DIALOG_EINSTELLUNG_PFADE_H
#define DIALOG_EINSTELLUNG_PFADE_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "Klassen/einstellung.h"

namespace Ui {
class Dialog_Einstellung_pfade;
}

class Dialog_Einstellung_pfade : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Einstellung_pfade(QWidget *parent = nullptr);
    ~Dialog_Einstellung_pfade();

public slots:
    void slot_einstellungen(einstellung e);

signals:
    void send_einstellungen(einstellung e);

private slots:
    void on_pushButton_abbrechen_clicked();
    void on_pushButton_ok_clicked();
    void on_pushButton_quelle_clicked();
    void on_pushButton_ziel_server_clicked();
    void on_pushButton_ziel_lokal_clicked();
    void on_pushButton_root_ganx_clicked();
    void on_pushButton_root_fmc_clicked();
    void on_pushButton_root_cix_clicked();
    void on_lineEdit_quelle_editingFinished();
    void on_lineEdit_ziel_server_editingFinished();
    void on_lineEdit_ziel_lokal_editingFinished();
    void on_lineEdit_root_ganx_editingFinished();
    void on_lineEdit_root_fmc_editingFinished();
    void on_lineEdit_root_cix_editingFinished();

private:
    Ui::Dialog_Einstellung_pfade *ui;
    einstellung Einstellung;
};

#endif // DIALOG_EINSTELLUNG_PFADE_H
