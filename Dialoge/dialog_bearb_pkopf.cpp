#include "dialog_bearb_pkopf.h"
#include "ui_dialog_bearb_pkopf.h"

Dialog_bearb_pkopf::Dialog_bearb_pkopf(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bearb_pkopf)
{
    ui->setupUi(this);
    this->setWindowTitle("Programmkopf");
    Wst = nullptr;
}

Dialog_bearb_pkopf::~Dialog_bearb_pkopf()
{
    delete ui;
}

void Dialog_bearb_pkopf::set_data(werkstueck *w)
{
    Wst = w;
    ui->lineEdit_l->setText(Wst->laenge_qstring());
    ui->lineEdit_b->setText(Wst->breite_qstring());
    ui->lineEdit_d->setText(Wst->dicke_qstring());
    ui->lineEdit_kvo->setText(Wst->kante_vo());
    ui->lineEdit_khi->setText(Wst->kante_hi());
    ui->lineEdit_kli->setText(Wst->kante_li());
    ui->lineEdit_kre->setText(Wst->kante_re());
}

void Dialog_bearb_pkopf::on_pushButton_ok_clicked()
{
    Wst->set_laenge(Formel(ui->lineEdit_l->text()).bekomme_Ergebnis_als_String());
    Wst->set_breite(Formel(ui->lineEdit_b->text()).bekomme_Ergebnis_als_String());
    Wst->set_dicke(Formel(ui->lineEdit_d->text()).bekomme_Ergebnis_als_String());
    Wst->set_kante_vo(ui->lineEdit_kvo->text());
    Wst->set_kante_hi(ui->lineEdit_khi->text());
    Wst->set_kante_li(ui->lineEdit_kli->text());
    Wst->set_kante_re(ui->lineEdit_kre->text());
    this->close();
}

void Dialog_bearb_pkopf::on_pushButton_abbrechen_clicked()
{
    this->close();
}
