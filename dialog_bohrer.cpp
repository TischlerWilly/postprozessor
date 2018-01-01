#include "dialog_bohrer.h"
#include "ui_dialog_bohrer.h"

Dialog_bohrer::Dialog_bohrer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bohrer)
{
    ui->setupUi(this);
    setup();
}

Dialog_bohrer::~Dialog_bohrer()
{
    delete ui;
}

void Dialog_bohrer::getData(text_zeilenweise msg)
{
    clear();
    setup();
    wkz_ist_neu = false;
    ui->lineEdit_nr->setText(msg.zeile(2));
    ui->lineEdit_dm_real->setText(msg.zeile(3));
    ui->lineEdit_dm_cad->setText(msg.zeile(7));
    ui->lineEdit__nutzlaenge->setText(msg.zeile(4));
    ui->lineEdit__zustmass->setText(msg.zeile(6));

    if(msg.zeile(8) == "1")
    {
        ui->comboBox_dubo->setCurrentIndex(0);  //ja
    }else
    {
        ui->comboBox_dubo->setCurrentIndex(1);  //nein
    }

    this->show();
}
void Dialog_bohrer::neuerBohrer()
{
    clear();
    setup();
    wkz_ist_neu = true;
    this->show();
}

void Dialog_bohrer::clear()
{
    ui->lineEdit_dm_cad->clear();
    ui->lineEdit_dm_real->clear();
    ui->lineEdit_nr->clear();
    ui->lineEdit__nutzlaenge->clear();
    ui->lineEdit__zustmass->clear();
    ui->comboBox_dubo->clear();
}
void Dialog_bohrer::setup()
{
    ui->comboBox_dubo->addItem("ja");
    ui->comboBox_dubo->addItem("nein");
}

void Dialog_bohrer::on_pushButton_abbrechen_clicked()
{
    this->hide();
}

void Dialog_bohrer::on_pushButton_ok_clicked()
{
    this->hide();
    text_zeilenweise wkz;
    wkz.set_trennzeichen('\t');

    wkz.zeile_anhaengen(WKZ_TYP_BOHRER);                    //1 : Werkzeigtyp
    wkz.zeile_anhaengen(ui->lineEdit_nr->text());           //2 : Nummer
    wkz.zeile_anhaengen(ui->lineEdit_dm_real->text());      //3 : Durchmesser des realen Werkzeuges
    wkz.zeile_anhaengen(ui->lineEdit__nutzlaenge->text());  //4 : Nutzlänge
    wkz.zeile_anhaengen(" ");                               //5 : Vorschub
    wkz.zeile_anhaengen(ui->lineEdit__zustmass->text());    //6 : Zustellmaß
    wkz.zeile_anhaengen(ui->lineEdit_dm_cad->text());       //7 : Durchmesser aus Import
    //8 : ist Durchgangsbohrer:
    if(ui->comboBox_dubo->currentIndex() == 0)//"ja"
    {
        wkz.zeile_anhaengen("1");
    }else
    {
        wkz.zeile_anhaengen("0");
    }

    emit sendData(wkz, wkz_ist_neu);
}
