#include "dialog_fraeser.h"
#include "ui_dialog_fraeser.h"

Dialog_fraeser::Dialog_fraeser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_fraeser)
{
    ui->setupUi(this);
    setup();
}

Dialog_fraeser::~Dialog_fraeser()
{
    delete ui;
}

void Dialog_fraeser::getData(text_zeilenweise msg)
{
    clear();
    setup();
    wkz_ist_neu = false;
    ui->lineEdit_nr->setText(msg.zeile(2));
    ui->lineEdit_dm->setText(msg.zeile(3));
    ui->lineEdit_nutzl->setText(msg.zeile(4));
    ui->lineEdit_zustm->setText(msg.zeile(6));
    ui->lineEdit_voers->setText(msg.zeile(5));
    ui->lineEdit_alias->setText(msg.zeile(11));
    ui->lineEdit_zust_min->setText(msg.zeile(12));

    this->show();
}

void Dialog_fraeser::neuerFraeser()
{
    clear();
    setup();
    wkz_ist_neu = true;
    this->show();
}

void Dialog_fraeser::clear()
{
    ui->lineEdit_dm->clear();
    ui->lineEdit_nr->clear();
    ui->lineEdit_nutzl->clear();
    ui->lineEdit_voers->clear();
    ui->lineEdit_zustm->clear();
    ui->lineEdit_alias->clear();
    ui->lineEdit_zust_min->clear();
}

void Dialog_fraeser::setup()
{

}

void Dialog_fraeser::on_pushButton_abbrechen_clicked()
{
    this->hide();
}

void Dialog_fraeser::on_pushButton_ok_clicked()
{
    this->hide();
    text_zeilenweise wkz;
    wkz.set_trennzeichen('\t');

    wkz.zeile_anhaengen(WKZ_TYP_FRAESER);                       //1 : Werkzeigtyp
    wkz.zeile_anhaengen(ui->lineEdit_nr->text());               //2 : Nummer
    wkz.zeile_anhaengen(ui->lineEdit_dm->text());               //3 : Durchmesser des realen Werkzeuges
    wkz.zeile_anhaengen(ui->lineEdit_nutzl->text());            //4 : Nutzlänge
    wkz.zeile_anhaengen(ui->lineEdit_voers->text());            //5 : Vorschub
    wkz.zeile_anhaengen(ui->lineEdit_zustm->text());            //6 : Zustellmaß
    wkz.zeile_anhaengen(" ");                                   //7 : Durchmesser aus Import
    wkz.zeile_anhaengen(" ");                                   //8 : ist Durchgangsbohrer
    wkz.zeile_anhaengen(" ");                                   //9 : Sägeblattbreite
    wkz.zeile_anhaengen(WKZ_PARAMETER_LAGE_VERT);               //10: Lage
    wkz.zeile_anhaengen(ui->lineEdit_alias->text().toUpper());  //11: Alias-Name
                          //Beim Einlesen der FMC-Datei werden alle kleinen Buchstaben durch große ersetzt
    wkz.zeile_anhaengen(ui->lineEdit_zust_min->text());         //12: Mindest-Zustellmaß

    //deutsche Zahlen in englische Zahlen umwandeln:
    for(uint i=3; i<=wkz.zeilenanzahl() ;i++)
    {
        wkz.zeile_ersaetzen(i, wkz.zeile(i).replace(",","."));
    }
    emit sendData(wkz, wkz_ist_neu);
}
