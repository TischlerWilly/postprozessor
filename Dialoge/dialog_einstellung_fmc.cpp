#include "dialog_einstellung_fmc.h"
#include "ui_dialog_einstellung_fmc.h"

Dialog_einstellung_fmc::Dialog_einstellung_fmc(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_einstellung_fmc)
{
    ui->setupUi(this);
    ui->comboBox_drehdypUnterseite->addItem("L");
    ui->comboBox_drehdypUnterseite->addItem("B");
}

Dialog_einstellung_fmc::~Dialog_einstellung_fmc()
{
    delete ui;
}

void Dialog_einstellung_fmc::on_pushButton_ok_clicked()
{
    QString tmp;

    tmp = ui->lineEdit_KennungOberseite->text();
    if(tmp.isEmpty())
    {
        QString msg;
        msg = "Es wurde noch kein Kennung für die Oberseite angegeben!";
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
        return;
    }
    Einstellung.set_kenObsei(tmp);

    tmp = ui->lineEdit_KennungUnterseite->text();
    if(tmp.isEmpty())
    {
        QString msg;
        msg = "Es wurde noch kein Kennung für die Unterseite angegeben!";
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
        return;
    }
    Einstellung.set_kenUnsei(tmp);

    tmp = ui->comboBox_drehdypUnterseite->currentText();
    Einstellung.set_dretypUnsei(tmp);

    this->close();
    emit send_einstellung(Einstellung);
}

void Dialog_einstellung_fmc::on_pushButton_abbrechen_clicked()
{
    this->close();
}

void Dialog_einstellung_fmc::slot_einstellung(einstellung_fmc e)
{
    Einstellung = e;
    ui->lineEdit_KennungOberseite->setText(Einstellung.kenObsei());
    ui->lineEdit_KennungUnterseite->setText(Einstellung.kenUnsei());
    if(Einstellung.drehtypUnsei() == "L")
    {
        ui->comboBox_drehdypUnterseite->setCurrentIndex(0);
    }else
    {
        ui->comboBox_drehdypUnterseite->setCurrentIndex(1);
    }
    this->show();
}

einstellung_fmc Dialog_einstellung_fmc::einstellung()
{
    return Einstellung;
}
