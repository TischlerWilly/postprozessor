#include "dialog_fraeserauswahl.h"
#include "ui_dialog_fraeserauswahl.h"

Dialog_fraeserauswahl::Dialog_fraeserauswahl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_fraeserauswahl)
{
    ui->setupUi(this);
}

Dialog_fraeserauswahl::~Dialog_fraeserauswahl()
{
    delete ui;
}

void Dialog_fraeserauswahl::on_pushButton_ok_clicked()
{
    int i = ui->tableWidget->currentRow();
    text_zw zeile(Wkzmag.at(i), WKZ_TRENNZ);
    wkz_fraeser fr(zeile);
    emit send_wkz(fr.alias());
    this->close();
}

void Dialog_fraeserauswahl::on_pushButton_abbrechen_clicked()
{
    this->close();
}

void Dialog_fraeserauswahl::set_wkzmag(text_zw wkzm)
{
    Wkzmag = wkzm;
    ui->tableWidget->clear();
    int anz_spalten = 4;
    ui->tableWidget->setRowCount(wkzm.count());
    ui->tableWidget->setColumnCount(anz_spalten);
    QStringList tabkopf;
    tabkopf << "Werkzeug-Nr." << "Alias" << "DM" << "Nutzlänge";
    ui->tableWidget->setHorizontalHeaderLabels(tabkopf);
    ui->tableWidget->setColumnWidth(0,250);
    ui->tableWidget->setColumnWidth(1,250);
    for(uint i=0; i<Wkzmag.count();i++)
    {
        text_zw zeile(Wkzmag.at(i), WKZ_TRENNZ);
        wkz_fraeser fr(zeile);
        QMessageBox mb;
        mb.setText(Wkzmag.at(i));
        //mb.exec();
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(fr.wkznr()));
        ui->tableWidget->setItem(i,1, new QTableWidgetItem(fr.alias()));
        ui->tableWidget->setItem(i,2, new QTableWidgetItem(double_to_qstring(fr.dm())));
        ui->tableWidget->setItem(i,3, new QTableWidgetItem(double_to_qstring(fr.nutzl())));
        ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignCenter);
    }
    this->show();
}
