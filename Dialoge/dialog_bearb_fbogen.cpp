#include "dialog_bearb_fbogen.h"
#include "ui_dialog_bearb_fbogen.h"

Dialog_bearb_fbogen::Dialog_bearb_fbogen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bearb_fbogen)
{
    ui->setupUi(this);
    this->setWindowTitle("Bogenfräsung");
    ui->comboBox_bezug->addItem("Oberseite");   //0
    ui->comboBox_bezug->addItem("Unterseite");  //1
    //---
    ui->comboBox_uzs->addItem("UZS");   //0
    ui->comboBox_uzs->addItem("GUZS");  //1
}

Dialog_bearb_fbogen::~Dialog_bearb_fbogen()
{
    delete ui;
}

void Dialog_bearb_fbogen::set_data(QString d)
{
    fraeserbogen fb;
    fb.set_text(d);
    ui->lineEdit_xs->setText(fb.xs_qstring());
    ui->lineEdit_ys->setText(fb.ys_qstring());
    ui->lineEdit_zs->setText(fb.zs_qstring());
    ui->lineEdit_xe->setText(fb.xe_qstring());
    ui->lineEdit_ye->setText(fb.ye_qstring());
    ui->lineEdit_ze->setText(fb.ze_qstring());
    ui->lineEdit_rad->setText(fb.rad_qstring());
    //---------
    //UZS:
    if(fb.uzs() == true)
    {
        ui->comboBox_uzs->setCurrentIndex(0);
    }else
    {
        ui->comboBox_uzs->setCurrentIndex(1);
    }
    //---------
    //Bezug:
    if(fb.bezug() == WST_BEZUG_OBSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(0);
    }else if(fb.bezug() == WST_BEZUG_UNSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(1);
    }
    //---------
    ui->lineEdit_afb->setText(fb.afb());
}

void Dialog_bearb_fbogen::on_btn_ok_clicked()
{
    fraeserbogen fb;
    fb.set_xs(berechnen(ui->lineEdit_xs->text()));
    fb.set_ys(berechnen(ui->lineEdit_ys->text()));
    fb.set_zs(berechnen(ui->lineEdit_zs->text()));
    fb.set_xe(berechnen(ui->lineEdit_xe->text()));
    fb.set_ye(berechnen(ui->lineEdit_ye->text()));
    fb.set_ze(berechnen(ui->lineEdit_ze->text()));
    fb.set_rad(berechnen(ui->lineEdit_rad->text()));
    QString uzs = ui->comboBox_uzs->currentText();
    if(uzs == "UZS")
    {
        fb.set_uzs(true);
    }else
    {
        fb.set_uzs(false);
    }
    QString bezug = ui->comboBox_bezug->currentText();
    if(bezug == "Oberseite")
    {
        fb.set_bezug(WST_BEZUG_OBSEI);
    }else if(bezug == "Unterseite")
    {
        fb.set_bezug(WST_BEZUG_UNSEI);
    }
    fb.set_afb(ui->lineEdit_afb->text());

    emit signal_fbogen(fb);
    this->close();
}

void Dialog_bearb_fbogen::on_btn_abbrechen_clicked()
{
    this->close();
}
