#include "dialog_saege.h"
#include "ui_dialog_saege.h"

Dialog_saege::Dialog_saege(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_saege)
{
    ui->setupUi(this);
    setup();
}

Dialog_saege::~Dialog_saege()
{
    delete ui;
}

void Dialog_saege::getData(text_zeilenweise msg)
{
    clear();
    setup();
    wkz_ist_neu = false;
    ui->lineEdit_nr->setText(msg.zeile(2));
    ui->lineEdit_dm->setText(msg.zeile(3));
    ui->lineEdit_zustm->setText(msg.zeile(6));
    ui->lineEdit_breite->setText(msg.zeile(9));
    if(msg.zeile(15) == "1")
    {
        ui->checkBox_ist_aktiv->setChecked(true);
    }else
    {
        ui->checkBox_ist_aktiv->setChecked(false);
    }
    if(msg.zeile(16) == "1")
    {
        ui->checkBox_hori->setChecked(true);
    }else
    {
        ui->checkBox_hori->setChecked(false);
    }
    if(msg.zeile(17) == "1")
    {
        ui->checkBox_vert->setChecked(true);
    }else
    {
        ui->checkBox_vert->setChecked(false);
    }

    this->show();
}

void Dialog_saege::neueSaege()
{
    clear();
    setup();
    wkz_ist_neu = true;
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

void Dialog_saege::setup()
{

}

void Dialog_saege::on_pushButton_abbrechen_clicked()
{
    this->hide();
}

void Dialog_saege::on_pushButton_ok_clicked()
{
    this->hide();
    text_zeilenweise wkz;
    wkz.set_trennzeichen('\t');

    wkz.zeile_anhaengen(WKZ_TYP_SAEGE);                     //1 : Werkzeigtyp
    wkz.zeile_anhaengen(ui->lineEdit_nr->text());           //2 : Nummer
    wkz.zeile_anhaengen(ui->lineEdit_dm->text());           //3 : Durchmesser des realen Werkzeuges
    wkz.zeile_anhaengen(" ");                               //4 : Nutzlänge
    wkz.zeile_anhaengen(" ");                               //5 : Vorschub
    wkz.zeile_anhaengen(ui->lineEdit_zustm->text());        //6 : Zustellmaß
    wkz.zeile_anhaengen(" ");                               //7 : Durchmesser aus Import
    wkz.zeile_anhaengen(" ");                               //8 : ist Durchgangsbohrer
    wkz.zeile_anhaengen(ui->lineEdit_breite->text());       //9 : Sägeblattbreite
    wkz.zeile_anhaengen(WKZ_PARAMETER_LAGE_VERT);           //10: Lage
    wkz.zeile_anhaengen(" ");                               //11: Alias-Name
    wkz.zeile_anhaengen(" ");                               //12: Mindest Zustellmaß
    wkz.zeile_anhaengen(" ");                               //13: Spiegelwerkzeug
    wkz.zeile_anhaengen(" ");                               //14: nur direkt zuweisbar
    if(ui->checkBox_ist_aktiv->isChecked())
    {
        wkz.zeile_anhaengen("1");                           //15: ist aktiv
    }else
    {
        wkz.zeile_anhaengen("0");                           //15: ist nicht aktiv
    }
    if(ui->checkBox_hori->isChecked())
    {
        wkz.zeile_anhaengen("1");                           //16: ist horizontal verwendbar
    }else
    {
        wkz.zeile_anhaengen("0");                           //16: ist nicht horizontal verwendbar
    }
    if(ui->checkBox_vert->isChecked())
    {
        wkz.zeile_anhaengen("1");                           //17: ist vertikal verwendbar
    }else
    {
        wkz.zeile_anhaengen("0");                           //17: ist nicht vertikal verwendbar
    }

    //deutsche Zahlen in englische Zahlen umwandeln:
    for(uint i=3; i<=wkz.zeilenanzahl() ;i++)
    {
        wkz.zeile_ersaetzen(i, wkz.zeile(i).replace(",","."));
    }
    emit sendData(wkz, wkz_ist_neu);
}
