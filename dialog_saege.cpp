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

    emit sendData(wkz, wkz_ist_neu);
}
