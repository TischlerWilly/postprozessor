#ifndef DIALOG_EINSTELLUNG_FMC_H
#define DIALOG_EINSTELLUNG_FMC_H

#include <QDialog>
#include "Klassen/einstellung_fmc.h"

namespace Ui {
class Dialog_einstellung_fmc;
}

class Dialog_einstellung_fmc : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_einstellung_fmc(QWidget *parent = nullptr);
    ~Dialog_einstellung_fmc();
    einstellung_fmc einstellung();

signals:
    void send_einstellung(einstellung_fmc e);

public slots:
    void slot_einstellung(einstellung_fmc e);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();

private:
    Ui::Dialog_einstellung_fmc *ui;
    einstellung_fmc Einstellung;
};

#endif // DIALOG_EINSTELLUNG_FMC_H
