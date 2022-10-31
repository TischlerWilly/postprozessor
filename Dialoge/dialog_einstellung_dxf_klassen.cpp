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
    Einstellung.set_wst(ui->lineEdit_wst->text());
    this->close();
    emit send_einstellung(Einstellung);
}

void Dialog_einstellung_dxf_klassen::slot_einstellung(einstellung_dxf_klassen e)
{
    Einstellung = e;
    ui->lineEdit_wst->setText(Einstellung.wst());
    this->show();
}

einstellung_dxf_klassen Dialog_einstellung_dxf_klassen::einstellung()
{
    return Einstellung;
}

void Dialog_einstellung_dxf_klassen::on_lineEdit_wst_textChanged(const QString &arg1)
{
    QString beispiel = arg1;
    beispiel += "_19_6";
    ui->lineEdit_wst_beispiel->setText(beispiel);
}
