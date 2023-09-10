#include "dialog_einstellung_wkz_pp.h"
#include "ui_dialog_einstellung_wkz_pp.h"

Dialog_einstellung_wkz_pp::Dialog_einstellung_wkz_pp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_einstellung_wkz_pp)
{
    ui->setupUi(this);
}

Dialog_einstellung_wkz_pp::~Dialog_einstellung_wkz_pp()
{
    delete ui;
}

void Dialog_einstellung_wkz_pp::set_einstellung(einstellung e)
{
    Einstellung = e;
    ui->checkBox_wkz_fr_fmc->setChecked(e.wkz_fr_fmc());
    ui->checkBox_wkz_fr_ganx->setChecked(e.wkz_fr_ganx());
    ui->checkBox_wkz_fr_cix->setChecked(e.wkz_fr_cix());
    ui->checkBox_wkz_fr_ggf->setChecked(e.wkz_fr_ggf());
    this->show();
}

void Dialog_einstellung_wkz_pp::on_pushButton_ok_clicked()
{
    Einstellung.set_wkz_fr_fmc(ui->checkBox_wkz_fr_fmc->isChecked());
    Einstellung.set_wkz_fr_ganx(ui->checkBox_wkz_fr_ganx->isChecked());
    Einstellung.set_wkz_fr_cix(ui->checkBox_wkz_fr_cix->isChecked());
    Einstellung.set_wkz_fr_ggf(ui->checkBox_wkz_fr_ggf->isChecked());
    emit send_einstellungen(Einstellung);
    this->close();
}
void Dialog_einstellung_wkz_pp::on_pushButton_abbrechen_clicked()
{
    this->close();
}
