#include "dialog_fraeser.h"
#include "ui_dialog_fraeser.h"

Dialog_fraeser::Dialog_fraeser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_fraeser)
{
    ui->setupUi(this);
}

Dialog_fraeser::~Dialog_fraeser()
{
    delete ui;
}

void Dialog_fraeser::set_Data(text_zw msg, bool ist_neues_wkz)
{
    clear();
    Wkz_ist_neu = ist_neues_wkz;
    wkz_fraeser wkz(msg);
    ui->lineEdit_nr->setText(wkz.wkznr());
    ui->lineEdit_dm->setText(double_to_qstring(wkz.dm()));
    ui->lineEdit_nutzl->setText(double_to_qstring(wkz.nutzl()));
    ui->lineEdit_zustmassvert->setText(double_to_qstring(wkz.zustmavert()));
    ui->lineEdit_zustmasshori->setText(double_to_qstring(wkz.zustmahori()));
    ui->lineEdit_voers->setText(double_to_qstring(wkz.vorschub()));
    ui->lineEdit_alias->setText(wkz.alias());
    ui->lineEdit_zust_min->setText(double_to_qstring(wkz.minzust()));
    ui->lineEdit_spiegel->setText(wkz.spiegelwkz());
    ui->checkBox_nur_direkt_zuweisbar->setChecked(wkz.nurdirektzuw());
    ui->checkBox_ist_aktiv->setChecked(wkz.istaktiv());
    ui->checkBox_ist_hori->setChecked(wkz.isthori());
    ui->checkBox_ist_veti->setChecked(wkz.istverti());
    this->show();
}

void Dialog_fraeser::neuerFraeser()
{
    clear();
    Wkz_ist_neu = true;
    this->show();
}

void Dialog_fraeser::clear()
{
    ui->lineEdit_dm->clear();
    ui->lineEdit_nr->clear();
    ui->lineEdit_nutzl->clear();
    ui->lineEdit_voers->clear();
    ui->lineEdit_zustmassvert->clear();
    ui->lineEdit_zustmasshori->clear();
    ui->lineEdit_alias->clear();
    ui->lineEdit_zust_min->clear();
    ui->lineEdit_spiegel->clear();
    ui->checkBox_nur_direkt_zuweisbar->setChecked(false);
    ui->checkBox_ist_aktiv->setChecked(true);
}

void Dialog_fraeser::on_pushButton_abbrechen_clicked()
{
    this->hide();
}

void Dialog_fraeser::on_pushButton_ok_clicked()
{
    this->hide();
    wkz_fraeser fraeser;
    fraeser.set_wkznr(ui->lineEdit_nr->text());
    fraeser.set_dm(berechnen(ui->lineEdit_dm->text()).toDouble());
    fraeser.set_nutzl(berechnen(ui->lineEdit_nutzl->text()).toDouble());
    fraeser.set_vorschub(berechnen(ui->lineEdit_voers->text()).toDouble());
    fraeser.set_zustmavert(berechnen(ui->lineEdit_zustmassvert->text()).toDouble());
    fraeser.set_zustmahori(berechnen(ui->lineEdit_zustmasshori->text()).toDouble());
    fraeser.set_istverti(ui->checkBox_ist_veti->isChecked());
    fraeser.set_isthori(ui->checkBox_ist_hori->isChecked());
    fraeser.set_alias(ui->lineEdit_alias->text().toUpper());
        //Beim Einlesen der FMC-Datei werden alle kleinen Buchstaben durch große ersetzt
    fraeser.set_minzust(berechnen(ui->lineEdit_zust_min->text()).toDouble());
    fraeser.set_spiegelwkz(ui->lineEdit_spiegel->text());
    fraeser.set_nurdirektzuw(ui->checkBox_nur_direkt_zuweisbar->isChecked());
    fraeser.set_istaktiv(ui->checkBox_ist_aktiv->isChecked());
    fraeser.set_isthori(ui->checkBox_ist_hori->isChecked());
    fraeser.set_istverti(ui->checkBox_ist_veti->isChecked());
    emit Data(fraeser.daten(), Wkz_ist_neu);
}
