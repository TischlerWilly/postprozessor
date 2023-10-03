#include "dialog_bearb_nut.h"
#include "ui_dialog_bearb_nut.h"

Dialog_bearb_nut::Dialog_bearb_nut(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bearb_nut)
{
    ui->setupUi(this);
    Wst = nullptr;
    this->setWindowTitle("Nut");
    ui->comboBox_bezug->addItem("Oberseite");   //0
    ui->comboBox_bezug->addItem("Unterseite");  //1
    ui->comboBox_bezug->addItem("Links");       //2
    ui->comboBox_bezug->addItem("Rechts");      //3
    ui->comboBox_bezug->addItem("Vorne");       //4
    ui->comboBox_bezug->addItem("Hinten");      //5
    ui->btn_ok->setFocus();
}

Dialog_bearb_nut::~Dialog_bearb_nut()
{
    delete ui;
}

void Dialog_bearb_nut::set_data(QString d, werkstueck *w)
{
    Wst = w;
    nut nu;
    nu.set_text(d);
    ui->lineEdit_b->setText(nu.breite_qstring());
    ui->lineEdit_ti->setText(nu.tiefe_qstring());
    ui->lineEdit_xs->setText(nu.xs_qstring());
    ui->lineEdit_ys->setText(nu.ys_qstring());
    ui->lineEdit_zs->setText(nu.zs_qstring());
    ui->lineEdit_xe->setText(nu.xe_qstring());
    ui->lineEdit_ye->setText(nu.ye_qstring());
    ui->lineEdit_ze->setText(nu.ze_qstring());
    //---------
    //Bezug:
    if(nu.bezug() == WST_BEZUG_OBSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(0);
    }else if(nu.bezug() == WST_BEZUG_UNSEI)
    {
        ui->comboBox_bezug->setCurrentIndex(1);
    }else if(nu.bezug() == WST_BEZUG_LI)
    {
        ui->comboBox_bezug->setCurrentIndex(2);
    }else if(nu.bezug() == WST_BEZUG_RE)
    {
        ui->comboBox_bezug->setCurrentIndex(3);
    }else if(nu.bezug() == WST_BEZUG_VO)
    {
        ui->comboBox_bezug->setCurrentIndex(4);
    }else if(nu.bezug() == WST_BEZUG_HI)
    {
        ui->comboBox_bezug->setCurrentIndex(5);
    }
    //---------
    ui->lineEdit_afb->setText(nu.afb());
}

QString Dialog_bearb_nut::var_zu_wert(QString term)
{
    if(Wst != nullptr)
    {
        term = term.toUpper();
        term.replace("L", Wst->laenge_qstring());
        term.replace("B", Wst->breite_qstring());
        term.replace("D", Wst->dicke_qstring());
        term = berechnen(term);
    }else
    {
        berechnen(term);
    }
    return term;
}

void Dialog_bearb_nut::on_btn_ok_clicked()
{
    nut nu;
    nu.set_breite(var_zu_wert(ui->lineEdit_b->text()));
    nu.set_tiefe(var_zu_wert(ui->lineEdit_ti->text()));
    nu.set_xs(var_zu_wert(ui->lineEdit_xs->text()));
    nu.set_ys(var_zu_wert(ui->lineEdit_ys->text()));
    nu.set_zs(var_zu_wert(ui->lineEdit_zs->text()));
    nu.set_xe(var_zu_wert(ui->lineEdit_xe->text()));
    nu.set_ye(var_zu_wert(ui->lineEdit_ye->text()));
    nu.set_ze(var_zu_wert(ui->lineEdit_ze->text()));
    QString bezug = ui->comboBox_bezug->currentText();
    if(bezug == "Oberseite")
    {
        nu.set_bezug(WST_BEZUG_OBSEI);
    }else if(bezug == "Unterseite")
    {
        nu.set_bezug(WST_BEZUG_UNSEI);
    }else if(bezug == "Links")
    {
        nu.set_bezug(WST_BEZUG_LI);
    }else if(bezug == "Rechts")
    {
        nu.set_bezug(WST_BEZUG_RE);
    }else if(bezug == "Vorne")
    {
        nu.set_bezug(WST_BEZUG_VO);
    }else if(bezug == "Hinten")
    {
        nu.set_bezug(WST_BEZUG_HI);
    }
    nu.set_afb(ui->lineEdit_afb->text());

    emit signal_nut(nu);
    this->close();
}

void Dialog_bearb_nut::on_btn_abbrechen_clicked()
{
    this->close();
}

void Dialog_bearb_nut::on_pushButton_ob_clicked()
{
    ui->comboBox_bezug->setCurrentIndex(0);
}
void Dialog_bearb_nut::on_pushButton_li_clicked()
{
    if(Wst != nullptr)
    {
        ui->comboBox_bezug->setCurrentIndex(2);
        ui->lineEdit_xs->setText("0");
        ui->lineEdit_ys->setText(Wst->breite_qstring());
        ui->lineEdit_xe->setText("0");
        ui->lineEdit_ye->setText("0");
    }
}
void Dialog_bearb_nut::on_pushButton_re_clicked()
{
    if(Wst != nullptr)
    {
        ui->comboBox_bezug->setCurrentIndex(3);
        ui->lineEdit_xs->setText(Wst->laenge_qstring());
        ui->lineEdit_ys->setText("0");
        ui->lineEdit_xe->setText(Wst->laenge_qstring());
        ui->lineEdit_ye->setText(Wst->breite_qstring());
    }
}
void Dialog_bearb_nut::on_pushButton_vo_clicked()
{
    if(Wst != nullptr)
    {
        ui->comboBox_bezug->setCurrentIndex(4);
        ui->lineEdit_xs->setText("0");
        ui->lineEdit_ys->setText("0");
        ui->lineEdit_xe->setText(Wst->laenge_qstring());
        ui->lineEdit_ye->setText("0");
    }
}
void Dialog_bearb_nut::on_pushButton_hi_clicked()
{
    if(Wst != nullptr)
    {
        ui->comboBox_bezug->setCurrentIndex(5);
        ui->lineEdit_xs->setText(Wst->laenge_qstring());
        ui->lineEdit_ys->setText(Wst->breite_qstring());
        ui->lineEdit_xe->setText("0");
        ui->lineEdit_ye->setText(Wst->breite_qstring());
    }
}
