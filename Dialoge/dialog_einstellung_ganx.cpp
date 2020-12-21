#include "dialog_einstellung_ganx.h"
#include "ui_dialog_einstellung_ganx.h"

Dialog_einstellung_ganx::Dialog_einstellung_ganx(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_einstellung_ganx)
{
    ui->setupUi(this);
}

Dialog_einstellung_ganx::~Dialog_einstellung_ganx()
{
    delete ui;
}

void Dialog_einstellung_ganx::on_pushButton_ok_clicked()
{
    Einstellung.use_bezugsmass(ui->checkBox_bezugskantenmass->isChecked());
    Einstellung.set_bezugskantenmass(ui->doubleSpinBox_bezugskantenmass->value());
    this->close();
    emit send_einstellung(Einstellung);
}

void Dialog_einstellung_ganx::on_pushButton_abbrechen_clicked()
{
    this->close();
}

void Dialog_einstellung_ganx::slot_einstellung(einstellung_ganx e)
{
    Einstellung = e;
    ui->checkBox_bezugskantenmass->setChecked(Einstellung.bezugsmass_in_use());
    ui->doubleSpinBox_bezugskantenmass->setValue(Einstellung.bezugsmass());
    this->show();
}
einstellung_ganx Dialog_einstellung_ganx::einstellung()
{
    return Einstellung;
}
