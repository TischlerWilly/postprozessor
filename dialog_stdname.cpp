#include "dialog_stdname.h"
#include "ui_dialog_stdname.h"

Dialog_stdname::Dialog_stdname(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_stdname)
{
    ui->setupUi(this);
}

Dialog_stdname::~Dialog_stdname()
{
    delete ui;
}

void Dialog_stdname::on_pushButton_ok_clicked()
{
    QString vor = ui->lineEdit_vor->text();
    QString nach = ui->lineEdit_nach->text();

    vor.replace("\t", "");
    nach.replace("\t", "");

    this->hide();
    emit signal_sendData(vor, nach);
}

void Dialog_stdname::on_pushButton_abbrechen_clicked()
{
    this->hide();
}

void Dialog_stdname::slot_getData(QString vor, QString nach)
{
    ui->lineEdit_vor->setText(vor);
    ui->lineEdit_nach->setText(nach);
    this->show();
}
