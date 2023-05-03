#include "dialog_stdnamen.h"
#include "ui_dialog_stdnamen.h"

Dialog_stdnamen::Dialog_stdnamen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_stdnamen)
{
    ui->setupUi(this);
    connect(this, SIGNAL(signalEditNane(QString,QString,int)),\
            &dlg_name, SLOT(slot_getData(QString,QString,int)));

    connect(&dlg_name, SIGNAL(signal_sendData(QString,QString,int)),\
            this, SLOT(slot_getName(QString,QString,int)));
}

Dialog_stdnamen::~Dialog_stdnamen()
{
    delete ui;
}

//--------------------------------------------------------------Buttons:

void Dialog_stdnamen::on_pushButton_neu_clicked()
{
    emit signalEditNane("vorher", "nachher", -1);
}

void Dialog_stdnamen::on_pushButton_edit_clicked()
{
    int row = ui->tableWidget->currentRow();
    if(row > 0)
    {
        emit signalEditNane(Vor_tz.at(row), Nach_tz.at(row), row);
    }else
    {
        QMessageBox mb;
        mb.setWindowTitle("Eintrag ändern");
        mb.setText("Bitte klicken Sie zuerst eine Zeile in der Tabelle an.");
        mb.exec();
    }
}

void Dialog_stdnamen::on_pushButton_entf_clicked()
{
    int row = ui->tableWidget->currentRow();
    if(row > 0)
    {
        Vor_tz.entf(row, 1);
        Nach_tz.entf(row, 1);
        update_tablewidget();
    }else
    {
        QMessageBox mb;
        mb.setWindowTitle("Eintrag entfernen");
        mb.setText("Bitte klicken Sie zuerst eine Zeile in der Tabelle an.");
        mb.exec();
    }
}

void Dialog_stdnamen::on_pushButton_ok_clicked()
{
    this->hide();
    emit signal_sendData(Vor_tz, Nach_tz);
}

void Dialog_stdnamen::on_pushButton_abbrechen_clicked()
{
    this->hide();
}

//--------------------------------------------------------------

void Dialog_stdnamen::slot_setup(text_zw namen_vor, text_zw namen_nach)
{
    Vor_tz = namen_vor;
    Nach_tz = namen_nach;
    update_tablewidget();
    this->show();
}

void Dialog_stdnamen::slot_getName(QString vor, QString nach, int zeile)
{
    if(vor == nach)
    {
        QString msg;
        msg  = "Quellname und Zielname sind identisch! \n";
        msg += "Name: \"";
        msg += vor;
        msg += "\"";
        QMessageBox mb;
        mb.setWindowTitle("Eingabefehler!");
        mb.setText(msg);        
        mb.exec();
    }else
    {
        if(zeile >= 0)
        {
            Vor_tz.edit(zeile, vor);
            Nach_tz.edit(zeile, nach);
        }else
        {
            Vor_tz.add_hi(vor);
            Nach_tz.add_hi(nach);

        }
        update_tablewidget();
    }
}

void Dialog_stdnamen::update_tablewidget()
{
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(Vor_tz.count());
    ui->tableWidget->setColumnCount(2);
    QStringList tabkopf;
    tabkopf << "Name original" << "Name neu";
    ui->tableWidget->setHorizontalHeaderLabels(tabkopf);
    ui->tableWidget->setColumnWidth(0,ui->tableWidget->width()/2-25);
    ui->tableWidget->setColumnWidth(1,ui->tableWidget->width()/2-25);
    for(uint i=1; i<Vor_tz.count() ;i++)//Ab zeile 2 weil zeile 1 der Tabellenkopf aus der Datei ist
    {
        ui->tableWidget->setItem(i,0, new QTableWidgetItem(Vor_tz.at(i)));
        ui->tableWidget->setItem(i,1, new QTableWidgetItem(Nach_tz.at(i)));
    }

}


void Dialog_stdnamen::on_pushButton_up_clicked()
{
    int row = ui->tableWidget->currentRow();
    if(row > 1)
    {
        QString vor = Vor_tz.at(row);
        QString nach = Nach_tz.at(row);
        Vor_tz.entf(row);
        Nach_tz.entf(row);
        Vor_tz.add_mi(row-2, vor);
        Nach_tz.add_mi(row-2, nach);
        update_tablewidget();
        ui->tableWidget->setCurrentCell(row-1, 0);
    }else if(row == 1)
    {
        //tu nix, weil ist bereits erster Eintrag
    }else
    {
        QMessageBox mb;
        mb.setWindowTitle("Eintrag verschieben");
        mb.setText("Bitte klicken Sie zuerst eine Zeile in der Tabelle an.");
        mb.exec();
    }
}

void Dialog_stdnamen::on_pushButton_down_clicked()
{
    int row = ui->tableWidget->currentRow();
    if(row > 0)
    {
        QString vor = Vor_tz.at(row);
        QString nach = Nach_tz.at(row);
        Vor_tz.entf(row);
        Nach_tz.entf(row);
        Vor_tz.add_mi(row, vor);
        Nach_tz.add_mi(row, nach);
        update_tablewidget();
        ui->tableWidget->setCurrentCell(row+1, 0);
    }else
    {
        QMessageBox mb;
        mb.setWindowTitle("Eintrag verschieben");
        mb.setText("Bitte klicken Sie zuerst eine Zeile in der Tabelle an.");
        mb.exec();
    }
}
