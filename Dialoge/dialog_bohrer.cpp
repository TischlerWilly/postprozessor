#include "dialog_bohrer.h"
#include "ui_dialog_bohrer.h"

Dialog_bohrer::Dialog_bohrer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bohrer)
{
    ui->setupUi(this);
}

Dialog_bohrer::~Dialog_bohrer()
{
    delete ui;
}

void Dialog_bohrer::set_Data(text_zeilenweise msg)
{
    clear();
    Wkz_ist_neu = false;
    ui->lineEdit_nr->setText(msg.zeile(2));
    ui->lineEdit_dm_real->setText(msg.zeile(3));
    ui->lineEdit_dm_cad->setText(msg.zeile(7));
    ui->lineEdit_nutzlaenge->setText(msg.zeile(4));
    ui->lineEdit_zustmass->setText(msg.zeile(6));

    if(msg.zeile(8) == "1")
    {
        ui->checkBox_istdubo->setChecked(true);
    }else
    {
        ui->checkBox_istdubo->setChecked(false);
    }

    if(msg.zeile(10) == WKZ_PARAMETER_LAGE_VERT)
    {
        ui->checkBox_verti->setChecked(true);
        ui->checkBox_hori->setChecked(false);
    }else
    {
        ui->checkBox_verti->setChecked(false);
        ui->checkBox_hori->setChecked(true);
    }

    if(msg.zeile(15) == "1")
    {
        ui->checkBox_ist_aktiv->setChecked(true);
    }else
    {
        ui->checkBox_ist_aktiv->setChecked(false);
    }
    this->show();
}
void Dialog_bohrer::set_Data(text_zw msg, bool ist_neues_wkz)
{
    clear();
    Wkz_ist_neu = ist_neues_wkz;
    wkz_bohrer wkz(msg);
    ui->lineEdit_nr->setText(wkz.wkznr());
    ui->lineEdit_dm_real->setText(double_to_qstring(wkz.dmexport()));
    ui->lineEdit_dm_cad->setText(double_to_qstring(wkz.dmimport()));
    ui->lineEdit_nutzlaenge->setText(double_to_qstring(wkz.nutzl()));
    ui->lineEdit_zustmass->setText(double_to_qstring(wkz.zustma()));
    ui->checkBox_istdubo->setChecked(wkz.istdubo());
    ui->checkBox_hori->setChecked(wkz.isthori());
    ui->checkBox_verti->setChecked(wkz.istverti());
    ui->checkBox_ist_aktiv->setChecked(wkz.istaktiv());
    this->show();
}

void Dialog_bohrer::neuerBohrer()
{
    clear();
    Wkz_ist_neu = true;
    this->show();
}

void Dialog_bohrer::clear()
{
    ui->lineEdit_dm_cad->clear();
    ui->lineEdit_dm_real->clear();
    ui->lineEdit_nr->clear();
    ui->lineEdit_nutzlaenge->clear();
    ui->lineEdit_zustmass->clear();
    ui->checkBox_istdubo->setChecked(false);
    ui->checkBox_verti->setChecked(false);
    ui->checkBox_hori->setChecked(false);
    ui->checkBox_ist_aktiv->setChecked(true);
}

void Dialog_bohrer::on_pushButton_abbrechen_clicked()
{
    this->hide();
}

void Dialog_bohrer::on_pushButton_ok_clicked()
{
    this->hide();
    //-------------------------------------------------------------alt:
    text_zeilenweise wkz;
    wkz.set_trennzeichen('\t');

    wkz.zeile_anhaengen(WKZ_TYP_BOHRER);                    //1 : Werkzeigtyp
    wkz.zeile_anhaengen(ui->lineEdit_nr->text());           //2 : Nummer
    wkz.zeile_anhaengen(ui->lineEdit_dm_real->text());      //3 : Durchmesser des realen Werkzeuges
    wkz.zeile_anhaengen(ui->lineEdit_nutzlaenge->text());  //4 : Nutzlänge
    wkz.zeile_anhaengen(" ");                               //5 : Vorschub
    wkz.zeile_anhaengen(ui->lineEdit_zustmass->text());    //6 : Zustellmaß
    wkz.zeile_anhaengen(ui->lineEdit_dm_cad->text());       //7 : Durchmesser aus Import

    //8 : ist Durchgangsbohrer:
    if(ui->checkBox_istdubo->isChecked())
    {
        wkz.zeile_anhaengen("1");
    }else
    {
        wkz.zeile_anhaengen("0");
    }

    wkz.zeile_anhaengen(" ");                               //9 : Sägeblattbreite

    //10: Lage:
    if(ui->checkBox_verti->isChecked())
    {
        wkz.zeile_anhaengen(WKZ_PARAMETER_LAGE_VERT);
    }else
    {
        wkz.zeile_anhaengen(WKZ_PARAMETER_LAGE_HORI);
    }

    wkz.zeile_anhaengen(" ");                               //11: Alias-Name
    wkz.zeile_anhaengen(" ");                               //12: Mindest Zustellmaß
    wkz.zeile_anhaengen(" ");                               //13: Spiegelwerkzeug
    wkz.zeile_anhaengen(" ");                               //14: nur direkt zuweisbar

    //15: ist aktiv
    if(ui->checkBox_ist_aktiv->isChecked())
    {
        wkz.zeile_anhaengen("1");
    }else
    {
        wkz.zeile_anhaengen("0");
    }

    //deutsche Zahlen in englische Zahlen umwandeln:
    for(uint i=3; i<=wkz.zeilenanzahl() ;i++)
    {
        wkz.zeile_ersaetzen(i, wkz.zeile(i).replace(",","."));
    }
    emit Data(wkz, Wkz_ist_neu);
    //-------------------------------------------------------------neu:
    wkz_bohrer bohrer;
    bohrer.set_wkznr(ui->lineEdit_nr->text());
    bohrer.set_istaktiv(ui->checkBox_ist_aktiv->isChecked());
    bohrer.set_dmimport(berechnen(ui->lineEdit_dm_cad->text()).toDouble());
    bohrer.set_dmexport(berechnen(ui->lineEdit_dm_real->text()).toDouble());
    bohrer.set_nutzl(berechnen(ui->lineEdit_nutzlaenge->text()).toDouble());
    bohrer.set_zustma(berechnen(ui->lineEdit_zustmass->text()).toDouble());
    bohrer.set_istdubo(ui->checkBox_istdubo->isChecked());
    bohrer.set_isthori(ui->checkBox_hori->isChecked());
    bohrer.set_istverti(ui->checkBox_verti->isChecked());
    emit Data(bohrer.daten(), Wkz_ist_neu);
}
