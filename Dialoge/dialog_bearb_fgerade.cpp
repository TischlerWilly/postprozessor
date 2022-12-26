#include "dialog_bearb_fgerade.h"
#include "ui_dialog_bearb_fgerade.h"

Dialog_bearb_fgerade::Dialog_bearb_fgerade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bearb_fgerade)
{
    ui->setupUi(this);
    this->setWindowTitle("Gerade Fräsen");
    ui->comboBox_bezug->addItem("Oberseite");   //0
    ui->comboBox_bezug->addItem("Unterseite");  //1
}

Dialog_bearb_fgerade::~Dialog_bearb_fgerade()
{
    delete ui;
}

void Dialog_bearb_fgerade::set_data(QString d)
{
    fraesergerade fg;
    fg.set_text(d);
    ui->lineEdit_xs->setText(fg.xs_qstring());
    ui->lineEdit_ys->setText(fg.ys_qstring());
    ui->lineEdit_zs->setText(fg.zs_qstring());
    ui->lineEdit_xe->setText(fg.xe_qstring());
    ui->lineEdit_ye->setText(fg.ye_qstring());
    ui->lineEdit_ze->setText(fg.ze_qstring());
    //---------
    //Bezug:
    if(fg.bezug() == WST_BEZUG_OBSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(0);
    }else if(fg.bezug() == WST_BEZUG_UNSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(1);
    }
    //---------
    ui->lineEdit_afb->setText(fg.afb());
}

void Dialog_bearb_fgerade::on_btn_ok_clicked()
{
    fraesergerade fg;
    fg.set_xs(ui->lineEdit_xs->text());
    fg.set_ys(ui->lineEdit_ys->text());
    fg.set_zs(ui->lineEdit_zs->text());
    fg.set_xe(ui->lineEdit_xe->text());
    fg.set_ye(ui->lineEdit_ye->text());
    fg.set_ze(ui->lineEdit_ze->text());
    QString bezug = ui->comboBox_bezug->currentText();
    if(bezug == "Oberseite")
    {
        fg.set_bezug(WST_BEZUG_OBSEI);
    }else if(bezug == "Unterseite")
    {
        fg.set_bezug(WST_BEZUG_UNSEI);
    }
    fg.set_afb(ui->lineEdit_afb->text());

    emit signal_fgerade(fg);
    this->close();
}

void Dialog_bearb_fgerade::on_btn_abbrechen_clicked()
{
    this->close();
}
