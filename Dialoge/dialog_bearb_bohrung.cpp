#include "dialog_bearb_bohrung.h"
#include "ui_dialog_bearb_bohrung.h"

Dialog_bearb_bohrung::Dialog_bearb_bohrung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bearb_bohrung)
{
    ui->setupUi(this);
    this->setWindowTitle("Bohrung/Kreistasche");
    ui->comboBox_bezug->addItem("Oberseite");   //0
    ui->comboBox_bezug->addItem("Unterseite");  //1
    ui->comboBox_bezug->addItem("Links");       //2
    ui->comboBox_bezug->addItem("Rechts");      //3
    ui->comboBox_bezug->addItem("Vorne");       //4
    ui->comboBox_bezug->addItem("Hinten");      //5
}

Dialog_bearb_bohrung::~Dialog_bearb_bohrung()
{
    delete ui;
}

void Dialog_bearb_bohrung::set_data(QString d)
{
    bohrung bo;
    bo.set_text(d);
    ui->lineEdit_dm->setText(bo.dm_qstring());
    ui->lineEdit_ti->setText(bo.tiefe_qstring());
    ui->lineEdit_x->setText(bo.x_qstring());
    ui->lineEdit_y->setText(bo.y_qstring());
    ui->lineEdit_z->setText(bo.z_qstring());
    ui->lineEdit_zust->setText(bo.zustellmass_qstring());
    //---------
    //Bezug:
    if(bo.bezug() == WST_BEZUG_OBSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(0);
    }else if(bo.bezug() == WST_BEZUG_UNSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(1);
    }else if(bo.bezug() == WST_BEZUG_LI)
    {
        ui->comboBox_bezug->setCurrentIndex(2);
    }else if(bo.bezug() == WST_BEZUG_RE)
    {
        ui->comboBox_bezug->setCurrentIndex(3);
    }else if(bo.bezug() == WST_BEZUG_VO)
    {
        ui->comboBox_bezug->setCurrentIndex(4);
    }else if(bo.bezug() == WST_BEZUG_HI)
    {
        ui->comboBox_bezug->setCurrentIndex(5);
    }
    //---------
    ui->lineEdit_afb->setText(bo.afb());
    ui->lineEdit_wkz->setText(bo.wkznum());
}

void Dialog_bearb_bohrung::on_btn_ok_clicked()
{
    bohrung bo;
    bo.set_dm(ui->lineEdit_dm->text());
    bo.set_tiefe(ui->lineEdit_ti->text());
    bo.set_x(ui->lineEdit_x->text());
    bo.set_y(ui->lineEdit_y->text());
    bo.set_z(ui->lineEdit_z->text());
    bo.set_zustellmass(ui->lineEdit_zust->text());
    QString bezug = ui->comboBox_bezug->currentText();
    if(bezug == "Oberseite")
    {
        bo.set_bezug(WST_BEZUG_OBSEI);
    }else if(bezug == "Unterseite")
    {
        bo.set_bezug(WST_BEZUG_UNSEI);
    }else if(bezug == "Links")
    {
        bo.set_bezug(WST_BEZUG_LI);
    }else if(bezug == "Rechts")
    {
        bo.set_bezug(WST_BEZUG_RE);
    }else if(bezug == "Vorne")
    {
        bo.set_bezug(WST_BEZUG_VO);
    }else if(bezug == "Hinten")
    {
        bo.set_bezug(WST_BEZUG_HI);
    }
    bo.set_afb(ui->lineEdit_afb->text());
    bo.set_wkznum(ui->lineEdit_wkz->text());

    emit signal_bo(bo);
    this->close();
}

void Dialog_bearb_bohrung::on_btn_abbrechen_clicked()
{
    this->close();
}
