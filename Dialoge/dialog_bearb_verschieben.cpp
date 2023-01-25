#include "dialog_bearb_verschieben.h"
#include "ui_dialog_bearb_verschieben.h"

Dialog_bearb_verschieben::Dialog_bearb_verschieben(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_bearb_verschieben)
{
    ui->setupUi(this);
    ui->lineEdit_ax->setText("0");
    ui->lineEdit_ay->setText("0");
    ui->lineEdit_az->setText("0");
}

Dialog_bearb_verschieben::~Dialog_bearb_verschieben()
{
    delete ui;
}

void Dialog_bearb_verschieben::on_pushButton_ok_clicked()
{
    punkt3d p;
    p.set_x(berechnen(ui->lineEdit_ax->text()));
    p.set_y(berechnen(ui->lineEdit_ay->text()));
    p.set_z(berechnen(ui->lineEdit_az->text()));
    emit signal_punkt(p);
    this->close();
}

void Dialog_bearb_verschieben::on_pushButton_abbrechen_clicked()
{
    this->close();
}
