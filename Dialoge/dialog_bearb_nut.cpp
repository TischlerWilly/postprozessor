#include "dialog_bearb_nut.h"
#include "ui_dialog_bearb_nut.h"

Dialog_bearb_nut::Dialog_bearb_nut(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bearb_nut)
{
    ui->setupUi(this);
    this->setWindowTitle("Nut");
    ui->comboBox_bezug->addItem("Oberseite");   //0
    ui->comboBox_bezug->addItem("Unterseite");  //1
}

Dialog_bearb_nut::~Dialog_bearb_nut()
{
    delete ui;
}

void Dialog_bearb_nut::set_data(QString d)
{
    nut nu;
    nu.set_text(d);
    ui->lineEdit_b->setText(nu.breite_qstring());
    ui->lineEdit_ti->setText(nu.tiefe_qstring());
    ui->lineEdit_xs->setText(nu.xs_qstring());
    ui->lineEdit_ys->setText(nu.ys_qstring());
    ui->lineEdit_xe->setText(nu.xe_qstring());
    ui->lineEdit_ye->setText(nu.ye_qstring());
    //---------
    //Bezug:
    if(nu.bezug() == WST_BEZUG_OBSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(0);
    }else if(nu.bezug() == WST_BEZUG_UNSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(1);
    }
    //---------
    ui->lineEdit_afb->setText(nu.afb());
}

void Dialog_bearb_nut::on_btn_ok_clicked()
{
    nut nu;
    nu.set_breite(Formel(ui->lineEdit_b->text()).bekomme_Ergebnis_als_String());
    nu.set_tiefe(Formel(ui->lineEdit_ti->text()).bekomme_Ergebnis_als_String());
    nu.set_xs(Formel(ui->lineEdit_xs->text()).bekomme_Ergebnis_als_String());
    nu.set_ys(Formel(ui->lineEdit_ys->text()).bekomme_Ergebnis_als_String());
    nu.set_xe(Formel(ui->lineEdit_xe->text()).bekomme_Ergebnis_als_String());
    nu.set_ye(Formel(ui->lineEdit_ye->text()).bekomme_Ergebnis_als_String());
    QString bezug = ui->comboBox_bezug->currentText();
    if(bezug == "Oberseite")
    {
        nu.set_bezug(WST_BEZUG_OBSEI);
    }else if(bezug == "Unterseite")
    {
        nu.set_bezug(WST_BEZUG_UNSEI);
    }
    nu.set_afb(ui->lineEdit_afb->text());

    emit signal_nut(nu);
    this->close();
}

void Dialog_bearb_nut::on_btn_abbrechen_clicked()
{
    this->close();
}