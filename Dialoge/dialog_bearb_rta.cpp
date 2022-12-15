#include "dialog_bearb_rta.h"
#include "ui_dialog_bearb_rta.h"

Dialog_bearb_rta::Dialog_bearb_rta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bearb_rta)
{
    ui->setupUi(this);
    ui->comboBox_bezug->addItem("Oberseite");   //0
    ui->comboBox_bezug->addItem("Unterseite");  //1
    ui->comboBox_bezug->addItem("Links");       //2
    ui->comboBox_bezug->addItem("Rechts");      //3
    ui->comboBox_bezug->addItem("Vorne");       //4
    ui->comboBox_bezug->addItem("Hinten");      //5
}

Dialog_bearb_rta::~Dialog_bearb_rta()
{
    delete ui;
}

void Dialog_bearb_rta::set_data(QString d)
{
    Rta.set_text(d);
    ui->lineEdit_l->setText(Rta.laenge_qstring());
    ui->lineEdit_b->setText(Rta.breite_qstring());
    ui->lineEdit_ti->setText(Rta.tiefe_qstring());
    ui->lineEdit_x->setText(Rta.x_qstring());
    ui->lineEdit_y->setText(Rta.y_qstring());
    ui->lineEdit_z->setText(Rta.z_qstring());
    ui->lineEdit_wi->setText(Rta.drewi_qstring());
    ui->lineEdit_zust->setText(Rta.zustellmass_qstring());
    ui->lineEdit_raeumen->setText(Rta.ausraeumen_qstring());
    //---------
    //Bezug:
    if(Rta.bezug() == WST_BEZUG_OBSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(0);
    }else if(Rta.bezug() == WST_BEZUG_UNSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(1);
    }else if(Rta.bezug() == WST_BEZUG_LI)
    {
        ui->comboBox_bezug->setCurrentIndex(2);
    }else if(Rta.bezug() == WST_BEZUG_RE)
    {
        ui->comboBox_bezug->setCurrentIndex(3);
    }else if(Rta.bezug() == WST_BEZUG_VO)
    {
        ui->comboBox_bezug->setCurrentIndex(4);
    }else if(Rta.bezug() == WST_BEZUG_HI)
    {
        ui->comboBox_bezug->setCurrentIndex(5);
    }
    //---------
    ui->lineEdit_afb->setText(Rta.afb());
    ui->lineEdit_wkz->setText(Rta.wkznum());
}

void Dialog_bearb_rta::on_btn_abbrechen_clicked()
{
    this->close();
}

void Dialog_bearb_rta::on_btn_ok_clicked()
{

}
