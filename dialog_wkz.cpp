#include "dialog_wkz.h"
#include "ui_dialog_wkz.h"


Dialog_WKZ::Dialog_WKZ(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_WKZ)
{
    ui->setupUi(this);
}

Dialog_WKZ::~Dialog_WKZ()
{
    delete ui;
}

void Dialog_WKZ::getDialogDataWKZ(QString fenstertitel, text_zeilenweise werkzeugmagazin)
{
    this->setWindowTitle(fenstertitel);
    for(uint i=1; i<=werkzeugmagazin.zeilenanzahl() ;i++)
    {
        ui->listWidget_wkz->addItem(werkzeugmagazin.zeile(i));
    }
    this->show();
}

void Dialog_WKZ::on_pushButton_abbrechen_clicked()
{
    clear();
    this->hide();
}

void Dialog_WKZ::clear()
{
    ui->listWidget_wkz->clear();
}

void Dialog_WKZ::on_pushButton_speichern_clicked()
{
    QMessageBox mb;
    mb.setText("Diese Funktion ist leider noch nicht fertig!");
    mb.exec();
}

void Dialog_WKZ::on_listWidget_wkz_itemDoubleClicked(QListWidgetItem *item)
{
    text_zeilenweise werkzeug;
    werkzeug.set_trennzeichen('\t');
    werkzeug.set_text(item->text());

    if(werkzeug.zeile(1) == WKZ_TYP_BOHRER)
    {
        QMessageBox mb;
        mb.setText("Das ist ein Bohrer");
        mb.exec();
    }else if(werkzeug.zeile(1) == WKZ_TYP_FRAESER)
    {
        QMessageBox mb;
        mb.setText("Das ist ein Fraeser");
        mb.exec();
    }if(werkzeug.zeile(1) == WKZ_TYP_SAEGE)
    {
        QMessageBox mb;
        mb.setText("Das ist eine Saege");
        mb.exec();
    }

}
