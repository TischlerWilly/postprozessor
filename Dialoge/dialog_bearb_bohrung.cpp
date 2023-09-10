#include "dialog_bearb_bohrung.h"
#include "ui_dialog_bearb_bohrung.h"

Dialog_bearb_bohrung::Dialog_bearb_bohrung(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bearb_bohrung)
{
    ui->setupUi(this);
    Wst = nullptr;
    this->setWindowTitle("Bohrung/Kreistasche");
    ui->comboBox_bezug->addItem("Oberseite");   //0
    ui->comboBox_bezug->addItem("Unterseite");  //1
    ui->comboBox_bezug->addItem("Links");       //2
    ui->comboBox_bezug->addItem("Rechts");      //3
    ui->comboBox_bezug->addItem("Vorne");       //4
    ui->comboBox_bezug->addItem("Hinten");      //5
    ui->pushButton_invert->setText("HBE\ninvertieren");
}

Dialog_bearb_bohrung::~Dialog_bearb_bohrung()
{
    delete ui;
}

void Dialog_bearb_bohrung::set_data(QString d, werkstueck *w)
{
    Wst = w;
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

QString Dialog_bearb_bohrung::var_zu_wert(QString term)
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

void Dialog_bearb_bohrung::on_btn_ok_clicked()
{
    bohrung bo;
    bo.set_dm(var_zu_wert(ui->lineEdit_dm->text()));
    bo.set_tiefe(var_zu_wert(ui->lineEdit_ti->text()));
    bo.set_x(var_zu_wert(ui->lineEdit_x->text()));
    bo.set_y(var_zu_wert(ui->lineEdit_y->text()));
    bo.set_z(var_zu_wert(ui->lineEdit_z->text()));
    bo.set_zustellmass(var_zu_wert(ui->lineEdit_zust->text()));
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

void Dialog_bearb_bohrung::on_pushButton_invert_clicked()
{
    int bezug = ui->comboBox_bezug->currentIndex();
    if(bezug == Bezug_li)
    {
        ui->comboBox_bezug->setCurrentIndex(Bezug_re);
        double x = var_zu_wert(ui->lineEdit_x->text()).toDouble();
        x = Wst->laenge() - x;
        ui->lineEdit_x->setText(double_to_qstring(x));
    }else if(bezug == Bezug_re)
    {
        ui->comboBox_bezug->setCurrentIndex(Bezug_li);
        double x = var_zu_wert(ui->lineEdit_x->text()).toDouble();
        x = Wst->laenge() - x;
        ui->lineEdit_x->setText(double_to_qstring(x));
    }else if(bezug == Bezug_vo)
    {
        ui->comboBox_bezug->setCurrentIndex(Bezug_hi);
        double y = var_zu_wert(ui->lineEdit_y->text()).toDouble();
        y = Wst->breite() - y;
        ui->lineEdit_y->setText(double_to_qstring(y));
    }else if(bezug == Bezug_hi)
    {
        ui->comboBox_bezug->setCurrentIndex(Bezug_vo);
        double y = var_zu_wert(ui->lineEdit_y->text()).toDouble();
        y = Wst->breite() - y;
        ui->lineEdit_y->setText(double_to_qstring(y));
    }
}
