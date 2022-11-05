#include "dialog_einstellung_dxf.h"
#include "ui_dialog_einstellung_dxf.h"

Dialog_einstellung_dxf::Dialog_einstellung_dxf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_einstellung_dxf)
{
    ui->setupUi(this);
    ui->comboBox_drehdypUnterseite->addItem("L");
    ui->comboBox_drehdypUnterseite->addItem("B");
}

Dialog_einstellung_dxf::~Dialog_einstellung_dxf()
{
    delete ui;
}

void Dialog_einstellung_dxf::on_pushButton_ok_clicked()
{
    QString tmp;

    tmp = ui->lineEdit_parametertrenner->text();
    if(tmp.isEmpty())
    {
        QString msg;
        msg = "Es wurde noch kein Parametertrenner angegeben!";
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
        return;
    }
    Einstellung.set_paramtren(tmp);

    tmp = ui->lineEdit_dezimaltrenner->text();
    if(tmp.isEmpty())
    {
        QString msg;
        msg = "Es wurde noch kein Dezimaltrenner angegeben!";
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
        return;
    }
    Einstellung.set_dezitren(tmp);

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

void Dialog_einstellung_dxf::on_pushButton_abbrechen_clicked()
{
    this->close();
}

void Dialog_einstellung_dxf::slot_einstellung(einstellung_dxf e)
{
    Einstellung = e;
    ui->lineEdit_parametertrenner->setText(Einstellung.paramtren());
    ui->lineEdit_dezimaltrenner->setText(Einstellung.dezitren());
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

einstellung_dxf Dialog_einstellung_dxf::einstellung()
{
    return Einstellung;
}
