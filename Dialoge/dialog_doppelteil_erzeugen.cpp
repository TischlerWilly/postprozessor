#include "dialog_doppelteil_erzeugen.h"
#include "ui_dialog_doppelteil_erzeugen.h"

Dialog_doppelteil_erzeugen::Dialog_doppelteil_erzeugen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_doppelteil_erzeugen)
{
    ui->setupUi(this);
    ui->radioButton_vo->setChecked(true);
    ui->radioButton_drehen->setChecked(true);
    on_radioButton_vo_clicked(true);
    Wst_la = 0;
    Wst_br = 0;
    berechne_wst_groesse();
}

Dialog_doppelteil_erzeugen::~Dialog_doppelteil_erzeugen()
{
    delete ui;
}

void Dialog_doppelteil_erzeugen::on_pushButton_ok_clicked()
{
    //Prüfe auf Fehler:
    if(ui->radioButton_vo->isChecked())
    {
        bool hat_fehler = false;
        for(uint i=0; i<Bearb.count() ;i++)
        {
            text_zw zeile;
            zeile.set_text(Bearb.at(i),TRENNZ_BEARB_PARAM);
            int index_bezug = 1;
            QString bezug = zeile.at(index_bezug);
            if(bezug == WST_BEZUG_HI)
            {
                hat_fehler = true;
                break; //for
            }
        }
        if(hat_fehler == true)
        {
            QString msg;
            msg  = "Es dürfen keine Bearbeitungen in der ";
            msg += "hinteren";
            msg += " Kante des Bauteils sein um dieses Doppelteil zu erzeugen.";
            QMessageBox mb;
            mb.setWindowTitle("Fehlerhafte Einstellung in diesem Dialog!");
            mb.setText(msg);
            mb.exec();
            return;
        }
    }else if(ui->radioButton_hi->isChecked())
    {
        bool hat_fehler = false;
        for(uint i=0; i<Bearb.count() ;i++)
        {
            text_zw zeile;
            zeile.set_text(Bearb.at(i),TRENNZ_BEARB_PARAM);
            int index_bezug = 1;
            QString bezug = zeile.at(index_bezug);
            if(bezug == WST_BEZUG_VO)
            {
                hat_fehler = true;
                break; //for
            }
        }
        if(hat_fehler == true)
        {
            QString msg;
            msg  = "Es dürfen keine Bearbeitungen in der ";
            msg += "vorderen";
            msg += " Kante des Bauteils sein um dieses Doppelteil zu erzeugen.";
            QMessageBox mb;
            mb.setWindowTitle("Fehlerhafte Einstellung in diesem Dialog!");
            mb.setText(msg);
            mb.exec();
            return;
        }
    }else if(ui->radioButton_li->isChecked())
    {
        bool hat_fehler = false;
        for(uint i=0; i<Bearb.count() ;i++)
        {
            text_zw zeile;
            zeile.set_text(Bearb.at(i),TRENNZ_BEARB_PARAM);
            int index_bezug = 1;
            QString bezug = zeile.at(index_bezug);
            if(bezug == WST_BEZUG_RE)
            {
                hat_fehler = true;
                break; //for
            }
        }
        if(hat_fehler == true)
        {
            QString msg;
            msg  = "Es dürfen keine Bearbeitungen in der ";
            msg += "rechten";
            msg += " Kante des Bauteils sein um dieses Doppelteil zu erzeugen.";
            QMessageBox mb;
            mb.setWindowTitle("Fehlerhafte Einstellung in diesem Dialog!");
            mb.setText(msg);
            mb.exec();
            return;
        }
    }else //rechts
    {
        bool hat_fehler = false;
        for(uint i=0; i<Bearb.count() ;i++)
        {
            text_zw zeile;
            zeile.set_text(Bearb.at(i),TRENNZ_BEARB_PARAM);
            int index_bezug = 1;
            QString bezug = zeile.at(index_bezug);
            if(bezug == WST_BEZUG_LI)
            {
                hat_fehler = true;
                break; //for
            }
        }
        if(hat_fehler == true)
        {
            QString msg;
            msg  = "Es dürfen keine Bearbeitungen in der ";
            msg += "linken";
            msg += " Kante des Bauteils sein um dieses Doppelteil zu erzeugen.";
            QMessageBox mb;
            mb.setWindowTitle("Fehlerhafte Einstellung in diesem Dialog!");
            mb.setText(msg);
            mb.exec();
            return;
        }
    }
    //Es gab keine Fehler
    //Einstellungen an Parent rückmelden:
    QString bezug;
    if(ui->radioButton_vo->isChecked())
    {
        bezug = WST_BEZUG_VO;
    }else if(ui->radioButton_hi->isChecked())
    {
        bezug = WST_BEZUG_HI;
    }else if(ui->radioButton_li->isChecked())
    {
        bezug = WST_BEZUG_LI;
    }else //if(ui->radioButton_re->isChecked())
    {
        bezug = WST_BEZUG_RE;
    }
    double wst_l = ui->lineEdit_neu_la->text().toDouble();
    double wst_b = ui->lineEdit_neu_br->text().toDouble();
    bool spiegeln = ui->radioButton_spiegeln->isChecked();
    bool drehen = ui->radioButton_drehen->isChecked();

    emit send_dlg_einstellung(bezug, wst_l, wst_b, spiegeln, drehen);
    this->close();
}
void Dialog_doppelteil_erzeugen::on_pushButton_abbrechen_clicked()
{
    this->close();
}

void Dialog_doppelteil_erzeugen::set_wst_laenge(double l)
{
    Wst_la = l;
    ui->lineEdit_alt_la->setText(double_to_qstring(l));
    berechne_wst_groesse();
}
void Dialog_doppelteil_erzeugen::set_wst_breite(double b)
{
    Wst_br = b;
    ui->lineEdit_alt_br->setText(double_to_qstring(b));
    berechne_wst_groesse();
}
void Dialog_doppelteil_erzeugen::set_bearb(text_zw bearb)
{
    Bearb = bearb;
}
void Dialog_doppelteil_erzeugen::berechne_wst_groesse()
{
    double zugabe = 20;
    if(ui->radioButton_vo->isChecked() || ui->radioButton_hi->isChecked())
    {
        ui->lineEdit_neu_la->setText(double_to_qstring(Wst_la));
        ui->lineEdit_neu_br->setText(double_to_qstring(Wst_br*2+zugabe));
    }else //links oder rechts:
    {
        ui->lineEdit_neu_la->setText(double_to_qstring(Wst_la*2+zugabe));
        ui->lineEdit_neu_br->setText(double_to_qstring(Wst_br));
    }
}

void Dialog_doppelteil_erzeugen::on_radioButton_vo_clicked(bool checked)
{
    if(checked)
    {
        ui->lineEdit_neu_la->setEnabled(false);
        ui->lineEdit_neu_br->setEnabled(true);
        berechne_wst_groesse();
    }
}
void Dialog_doppelteil_erzeugen::on_radioButton_hi_clicked(bool checked)
{
    if(checked)
    {
        ui->lineEdit_neu_la->setEnabled(false);
        ui->lineEdit_neu_br->setEnabled(true);
        berechne_wst_groesse();
    }
}
void Dialog_doppelteil_erzeugen::on_radioButton_li_clicked(bool checked)
{
    if(checked)
    {
        ui->lineEdit_neu_la->setEnabled(true);
        ui->lineEdit_neu_br->setEnabled(false);
        berechne_wst_groesse();
    }
}
void Dialog_doppelteil_erzeugen::on_radioButton_re_clicked(bool checked)
{
    if(checked)
    {
        ui->lineEdit_neu_la->setEnabled(true);
        ui->lineEdit_neu_br->setEnabled(false);
        berechne_wst_groesse();
    }
}
