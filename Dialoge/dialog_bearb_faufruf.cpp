#include "dialog_bearb_faufruf.h"
#include "ui_dialog_bearb_faufruf.h"

Dialog_bearb_faufruf::Dialog_bearb_faufruf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bearb_faufruf)
{
    ui->setupUi(this);
    this->setWindowTitle("Fräseraufruf");
    ui->comboBox_bezug->addItem("Oberseite");   //0
    ui->comboBox_bezug->addItem("Unterseite");  //1
    //---
    ui->comboBox_kor->addItem("Links");  //0
    ui->comboBox_kor->addItem("Keine");  //1
    ui->comboBox_kor->addItem("Rechts"); //2
}

Dialog_bearb_faufruf::~Dialog_bearb_faufruf()
{
    delete ui;
}

void Dialog_bearb_faufruf::set_data(QString d)
{
    fraueseraufruf fa;
    fa.set_text(d);
    ui->lineEdit_ti->setText(fa.tiefe_qstring());
    ui->lineEdit_x->setText(fa.x_qstring());
    ui->lineEdit_y->setText(fa.y_qstring());
    ui->lineEdit_z->setText(fa.z_qstring());
    //---------
    //Radiuskorrektur:
    if(fa.radkor() == FRKOR_L)
    {
        ui->comboBox_kor->setCurrentIndex(0);
    }else if(fa.radkor() == FRKOR_M)
    {
        ui->comboBox_kor->setCurrentIndex(1);
    }else //if(fa.radkor() == FRKOR_R)
    {
        ui->comboBox_kor->setCurrentIndex(2);
    }
    //---------
    //Bezug:
    if(fa.bezug() == WST_BEZUG_OBSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(0);
    }else if(fa.bezug() == WST_BEZUG_UNSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(1);
    }
    //---------
    ui->lineEdit_afb->setText(fa.afb());
    ui->lineEdit_wkz->setText(fa.wkznum());
}

void Dialog_bearb_faufruf::on_btn_ok_clicked()
{
    fraueseraufruf fa;
    fa.set_tiefe(berechnen(ui->lineEdit_ti->text()));
    fa.set_x(berechnen(ui->lineEdit_x->text()));
    fa.set_y(berechnen(ui->lineEdit_y->text()));
    fa.set_z(berechnen(ui->lineEdit_z->text()));
    QString kor = ui->comboBox_kor->currentText();
    if(kor == "Links")
    {
        fa.set_radkor(FRKOR_L);
    }else if(kor == "Keine")
    {
        fa.set_radkor(FRKOR_M);
    }else //if(kor == "Rechts")
    {
        fa.set_radkor(FRKOR_R);
    }
    QString bezug = ui->comboBox_bezug->currentText();
    if(bezug == "Oberseite")
    {
        fa.set_bezug(WST_BEZUG_OBSEI);
    }else if(bezug == "Unterseite")
    {
        fa.set_bezug(WST_BEZUG_UNSEI);
    }
    fa.set_afb(ui->lineEdit_afb->text());
    fa.set_wkznum(ui->lineEdit_wkz->text());

    emit signal_faufruf(fa);
    this->close();
}

void Dialog_bearb_faufruf::on_btn_abbrechen_clicked()
{
    this->close();
}
