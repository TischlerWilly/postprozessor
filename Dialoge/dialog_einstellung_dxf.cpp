#include "dialog_einstellung_dxf.h"
#include "ui_dialog_einstellung_dxf.h"

Dialog_einstellung_dxf::Dialog_einstellung_dxf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_einstellung_dxf)
{
    ui->setupUi(this);
    ui->comboBox_drehdypUnterseite->addItem("L");
    ui->comboBox_drehdypUnterseite->addItem("B");
    ui->comboBox_bezugTiFkon->addItem("Unterseite Bauteil");
    ui->comboBox_bezugTiFkon->addItem("Oberseite Bauteil");
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

    tmp = ui->lineEdit_KennungWKZnr->text();
    if(tmp.isEmpty())
    {
        QString msg;
        msg = "Es wurde noch kein Kennung für die Werkzeugnummer angegeben!";
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
        return;
    }
    Einstellung.set_kenWKZnr(tmp);

    tmp = ui->lineEdit_KennungRadKorLi->text();
    if(tmp.isEmpty())
    {
        QString msg;
        msg = "Es wurde noch kein Kennung für die Radiuskorrektur links angegeben!";
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
        return;
    }
    Einstellung.set_kenRadKorLi(tmp);

    tmp = ui->lineEdit_KennungRadKorMi->text();
    if(tmp.isEmpty())
    {
        QString msg;
        msg = "Es wurde noch kein Kennung für die Radiuskorrektur mitte angegeben!";
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
        return;
    }
    Einstellung.set_kenRadKorMi(tmp);

    tmp = ui->lineEdit_KennungRadKorRe->text();
    if(tmp.isEmpty())
    {
        QString msg;
        msg = "Es wurde noch kein Kennung für die Radiuskorrektur rechts angegeben!";
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
        return;
    }
    Einstellung.set_kenRadKorRe(tmp);

    tmp = ui->comboBox_bezugTiFkon->currentText();
    Einstellung.set_bezugTiFkon(tmp);

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
    ui->lineEdit_KennungWKZnr->setText(Einstellung.kenWKZnr());
    ui->lineEdit_KennungRadKorLi->setText(Einstellung.kenRadKorLi());
    ui->lineEdit_KennungRadKorMi->setText(Einstellung.kenRadKorMi());
    ui->lineEdit_KennungRadKorRe->setText(Einstellung.kenRadKorRe());
    if(Einstellung.bezugTiFkonUnSei())
    {
        ui->comboBox_bezugTiFkon->setCurrentIndex(0);
    }else
    {
        ui->comboBox_bezugTiFkon->setCurrentIndex(1);
    }
    this->show();
}

einstellung_dxf Dialog_einstellung_dxf::einstellung()
{
    return Einstellung;
}
