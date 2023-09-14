#include "dialog_bearb_faufruf.h"
#include "ui_dialog_bearb_faufruf.h"

Dialog_bearb_faufruf::Dialog_bearb_faufruf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bearb_faufruf)
{
    ui->setupUi(this);
    Wst = nullptr;
    this->setWindowTitle("Fräseraufruf");
    ui->comboBox_bezug->addItem("Oberseite");   //0
    ui->comboBox_bezug->addItem("Unterseite");  //1
    //---
    ui->comboBox_kor->addItem("Links");  //0
    ui->comboBox_kor->addItem("Keine");  //1
    ui->comboBox_kor->addItem("Rechts"); //2    
    connect(&dlg_wkzwahl, SIGNAL(send_wkz(QString)), this, SLOT(get_wkz(QString)));
}

Dialog_bearb_faufruf::~Dialog_bearb_faufruf()
{
    delete ui;
}

void Dialog_bearb_faufruf::set_data(QString d, werkstueck *w, text_zw wkzmag)
{
    Wst = w;
    Wkzmag = wkzmag;
    fraeseraufruf fa;
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

QString Dialog_bearb_faufruf::var_zu_wert(QString term)
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

void Dialog_bearb_faufruf::on_btn_ok_clicked()
{
    fraeseraufruf fa;
    fa.set_tiefe(var_zu_wert(ui->lineEdit_ti->text()));
    fa.set_x(var_zu_wert(ui->lineEdit_x->text()));
    fa.set_y(var_zu_wert(ui->lineEdit_y->text()));
    fa.set_z(var_zu_wert(ui->lineEdit_z->text()));
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

void Dialog_bearb_faufruf::on_pushButton_wkzwahl_clicked()
{
    dlg_wkzwahl.set_min_nutz(ui->lineEdit_ti->text().toDouble());
    dlg_wkzwahl.set_wkzmag(Wkzmag);
    dlg_wkzwahl.update_wkztabelle();
    dlg_wkzwahl.show();
}
void Dialog_bearb_faufruf::get_wkz(QString wkz)
{
    ui->lineEdit_wkz->setText(wkz);
}
