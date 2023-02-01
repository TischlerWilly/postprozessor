#include "dialog_saege.h"
#include "ui_dialog_saege.h"

Dialog_saege::Dialog_saege(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_saege)
{
    ui->setupUi(this);
}

Dialog_saege::~Dialog_saege()
{
    delete ui;
}

void Dialog_saege::set_Data(text_zw msg, bool ist_neues_wkz)
{
    clear();
    Wkz_ist_neu = ist_neues_wkz;
    wkz_saege wkz(msg);
    ui->lineEdit_nr->setText(wkz.wkznr());
    ui->lineEdit_dm->setText(double_to_qstring(wkz.dm()));
    ui->lineEdit_zustm->setText(double_to_qstring(wkz.zustma()));
    ui->lineEdit_breite->setText(double_to_qstring(wkz.sbreite()));
    ui->checkBox_hori->setChecked(wkz.isthori());
    ui->checkBox_vert->setChecked(wkz.istverti());
    ui->checkBox_ist_aktiv->setChecked(wkz.istaktiv());
    this->show();
}

void Dialog_saege::neueSaege()
{
    clear();
    Wkz_ist_neu = true;
    this->show();
}

void Dialog_saege::clear()
{
    ui->lineEdit_dm->clear();
    ui->lineEdit_nr->clear();
    ui->lineEdit_zustm->clear();
    ui->lineEdit_breite->clear();
    ui->checkBox_ist_aktiv->setChecked(true);
    ui->checkBox_hori->setChecked(false);
    ui->checkBox_vert->setChecked(false);
}

void Dialog_saege::on_pushButton_abbrechen_clicked()
{
    this->hide();
}

void Dialog_saege::on_pushButton_ok_clicked()
{
    this->hide();    
    wkz_saege saege;
    saege.set_wkznr(ui->lineEdit_nr->text());
    saege.set_istaktiv(ui->checkBox_ist_aktiv->isChecked());
    saege.set_dm(berechnen(ui->lineEdit_dm->text()).toDouble());
    saege.set_zustma(berechnen(ui->lineEdit_zustm->text()).toDouble());
    saege.set_sbreite(berechnen(ui->lineEdit_breite->text()).toDouble());
    saege.set_isthori(ui->checkBox_hori->isChecked());
    saege.set_istverti(ui->checkBox_vert->isChecked());
    emit Data(saege.daten(), Wkz_ist_neu);
}
