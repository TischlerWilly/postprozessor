#include "dialog_stdnamen.h"
#include "ui_dialog_stdnamen.h"

Dialog_stdnamen::Dialog_stdnamen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_stdnamen)
{
    ui->setupUi(this);
    connect(this, SIGNAL(signalEditNane(QString,QString)),\
            &dlg_name, SLOT(slot_getData(QString,QString)));

    connect(&dlg_name, SIGNAL(signal_sendData(QString,QString)),\
            this, SLOT(slot_getName(QString,QString)));
}

Dialog_stdnamen::~Dialog_stdnamen()
{
    delete ui;
}

//--------------------------------------------------------------Buttons:

void Dialog_stdnamen::on_pushButton_neu_clicked()
{
    QString vor = "neu";
    QString nach = "neu";
    QString zeile;
    zeile  = vor;
    zeile += NAMEN_STD_INI_TZ_;
    zeile += nach;
    vor_tz.zeile_anhaengen(vor);
    nach_tz.zeile_anhaengen(nach);
    update_listwidget();
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
    emit signalEditNane(vor, nach);
}

void Dialog_stdnamen::on_pushButton_edit_clicked()
{
    if(ui->listWidget->count() > 0)
    {
        QString vor = vor_tz.zeile(ui->listWidget->currentRow()+2);
        QString nach = nach_tz.zeile(ui->listWidget->currentRow()+2);
        emit signalEditNane(vor, nach);
    }
}

void Dialog_stdnamen::on_pushButton_entf_clicked()
{
    if(ui->listWidget->count() > 0)
    {
        vor_tz.zeile_loeschen(ui->listWidget->currentRow()+2);
        nach_tz.zeile_loeschen(ui->listWidget->currentRow()+2);
        update_listwidget();
    }
}

void Dialog_stdnamen::on_pushButton_ok_clicked()
{
    this->hide();
    emit signal_sendData(vor_tz, nach_tz);
}

void Dialog_stdnamen::on_pushButton_abbrechen_clicked()
{
    this->hide();
}

//--------------------------------------------------------------

void Dialog_stdnamen::slot_setup(text_zeilenweise namen_vor, text_zeilenweise namen_nach)
{
    vor_tz = namen_vor;
    nach_tz = namen_nach;
    update_listwidget();
    this->show();
}

void Dialog_stdnamen::slot_getName(QString vor, QString nach)
{
    if(vor == nach)
    {
        QString msg;
        msg  = "Quellname und Zielname sind identisch! \n";
        msg += "Eintrag wird entfernt.\n";
        msg += "Name: \"";
        msg += vor;
        msg += "\"";

        QMessageBox mb;
        mb.setText(msg);
        mb.setWindowTitle("Eingabefehler!");
        mb.exec();
        on_pushButton_entf_clicked();
    }else
    {
        int row = ui->listWidget->currentRow();
        vor_tz.zeile_ersaetzen(row+2, vor);
        nach_tz.zeile_ersaetzen(row+2, nach);
        update_listwidget();
        ui->listWidget->setCurrentRow(row);
    }

}

void Dialog_stdnamen::update_listwidget()
{
    ui->listWidget->clear();
    for(uint i=2; i<=vor_tz.zeilenanzahl() ;i++)//Ab zeile 2 weil zeile 1 der Tabellenkopf aus der Datei ist
    {
        QString zeile;
        zeile  = vor_tz.zeile(i);
        zeile += NAMEN_STD_INI_TZ_;
        zeile += nach_tz.zeile(i);
        ui->listWidget->addItem(zeile);
    }
    if(ui->listWidget->count() > 0)
    {
        ui->listWidget->setCurrentRow(0);
    }
}



