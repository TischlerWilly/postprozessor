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
    fb.set_xs(Formel(ui->lineEdit_xs->text()).bekomme_Ergebnis_als_String());
    fb.set_ys(Formel(ui->lineEdit_ys->text()).bekomme_Ergebnis_als_String());
    fb.set_zs(Formel(ui->lineEdit_zs->text()).bekomme_Ergebnis_als_String());
    fb.set_xe(Formel(ui->lineEdit_xe->text()).bekomme_Ergebnis_als_String());
    fb.set_ye(Formel(ui->lineEdit_ye->text()).bekomme_Ergebnis_als_String());
    fb.set_ze(Formel(ui->lineEdit_ze->text()).bekomme_Ergebnis_als_String());
    fb.set_rad(Formel(ui->lineEdit_rad->text()).bekomme_Ergebnis_als_String());
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