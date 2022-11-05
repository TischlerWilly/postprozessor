#include "dialog_einstellung_dxf_klassen.h"
#include "ui_dialog_einstellung_dxf_klassen.h"

Dialog_einstellung_dxf_klassen::Dialog_einstellung_dxf_klassen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_einstellung_dxf_klassen)
{
    ui->setupUi(this);
}

Dialog_einstellung_dxf_klassen::~Dialog_einstellung_dxf_klassen()
{
    delete ui;
}

void Dialog_einstellung_dxf_klassen::on_pushButton_abbrechen_clicked()
{
    this->close();
}

void Dialog_einstellung_dxf_klassen::on_pushButton_speichern_clicked()
{
    Einstellung_klassen.set_wst(ui->lineEdit_wst->text());
    this->close();
    emit send_einstellung(Einstellung_klassen);
}

void Dialog_einstellung_dxf_klassen::slot_einstellung(einstellung_dxf eg, einstellung_dxf_klassen ek)
{
    Einstellung_allgem = eg;
    Einstellung_klassen = ek;
    ui->lineEdit_wst->clear();
    ui->lineEdit_wst->setText(Einstellung_klassen.wst());
    this->show();
}

einstellung_dxf_klassen Dialog_einstellung_dxf_klassen::einstellung()
{
    return Einstellung_klassen;
}

void Dialog_einstellung_dxf_klassen::on_lineEdit_wst_textChanged(const QString &arg1)
{
    QString beispiel = arg1;
    beispiel += "_19";
    beispiel += Einstellung_allgem.dezitren();
    beispiel += "6";
    ui->lineEdit_wst_beispiel->setText(beispiel);
}
