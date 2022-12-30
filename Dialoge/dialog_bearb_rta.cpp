#include "dialog_bearb_rta.h"
#include "ui_dialog_bearb_rta.h"

Dialog_bearb_rta::Dialog_bearb_rta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bearb_rta)
{
    ui->setupUi(this);
    this->setWindowTitle("Rechtecktasche");
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
    rechtecktasche rta;
    rta.set_text(d);
    ui->lineEdit_l->setText(rta.laenge_qstring());
    ui->lineEdit_b->setText(rta.breite_qstring());
    ui->lineEdit_ti->setText(rta.tiefe_qstring());
    ui->lineEdit_x->setText(rta.x_qstring());
    ui->lineEdit_y->setText(rta.y_qstring());
    ui->lineEdit_z->setText(rta.z_qstring());
    ui->lineEdit_wi->setText(rta.drewi_qstring());
    ui->lineEdit_rad->setText(rta.rad_qstring());
    ui->lineEdit_zust->setText(rta.zustellmass_qstring());
    if(rta.ausraeumen() == true)
    {
        ui->checkBox_raeumen->setChecked(true);
    }else
    {
        ui->checkBox_raeumen->setChecked(false);
    }
    //---------
    //Bezug:
    if(rta.bezug() == WST_BEZUG_OBSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(0);
    }else if(rta.bezug() == WST_BEZUG_UNSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(1);
    }else if(rta.bezug() == WST_BEZUG_LI)
    {
        ui->comboBox_bezug->setCurrentIndex(2);
    }else if(rta.bezug() == WST_BEZUG_RE)
    {
        ui->comboBox_bezug->setCurrentIndex(3);
    }else if(rta.bezug() == WST_BEZUG_VO)
    {
        ui->comboBox_bezug->setCurrentIndex(4);
    }else if(rta.bezug() == WST_BEZUG_HI)
    {
        ui->comboBox_bezug->setCurrentIndex(5);
    }
    //---------
    ui->lineEdit_afb->setText(rta.afb());
    ui->lineEdit_wkz->setText(rta.wkznum());
}

void Dialog_bearb_rta::on_btn_abbrechen_clicked()
{
    this->close();
}

void Dialog_bearb_rta::on_btn_ok_clicked()
{
    rechtecktasche rta;
    rta.set_laenge(berechnen(ui->lineEdit_l->text()));
    rta.set_breite(berechnen(ui->lineEdit_b->text()));
    rta.set_tiefe(berechnen(ui->lineEdit_ti->text()));
    rta.set_x(berechnen(ui->lineEdit_x->text()));
    rta.set_y(berechnen(ui->lineEdit_y->text()));
    rta.set_z(berechnen(ui->lineEdit_z->text()));
    rta.set_drewi(berechnen(ui->lineEdit_wi->text()));
    rta.set_rad(berechnen(ui->lineEdit_rad->text()));
    rta.set_zustellmass(berechnen(ui->lineEdit_zust->text()));
    rta.set_ausraeumen(ui->checkBox_raeumen->isChecked());
    QString bezug = ui->comboBox_bezug->currentText();
    if(bezug == "Oberseite")
    {
        rta.set_bezug(WST_BEZUG_OBSEI);
    }else if(bezug == "Unterseite")
    {
        rta.set_bezug(WST_BEZUG_UNSEI);
    }else if(bezug == "Links")
    {
        rta.set_bezug(WST_BEZUG_LI);
    }else if(bezug == "Rechts")
    {
        rta.set_bezug(WST_BEZUG_RE);
    }else if(bezug == "Vorne")
    {
        rta.set_bezug(WST_BEZUG_VO);
    }else if(bezug == "Hinten")
    {
        rta.set_bezug(WST_BEZUG_HI);
    }
    rta.set_afb(ui->lineEdit_afb->text());
    rta.set_wkznum(ui->lineEdit_wkz->text());

    emit signal_rta(rta);
    this->close();
}
