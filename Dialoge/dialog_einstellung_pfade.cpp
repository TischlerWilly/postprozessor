#include "dialog_einstellung_pfade.h"
#include "ui_dialog_einstellung_pfade.h"

Dialog_Einstellung_pfade::Dialog_Einstellung_pfade(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_Einstellung_pfade)
{
    ui->setupUi(this);
}

Dialog_Einstellung_pfade::~Dialog_Einstellung_pfade()
{
    delete ui;
}

void Dialog_Einstellung_pfade::on_pushButton_abbrechen_clicked()
{
    this->close();
}

void Dialog_Einstellung_pfade::on_pushButton_ok_clicked()
{
    this->close();
    emit send_einstellungen(Einstellung);
}
void Dialog_Einstellung_pfade::slot_einstellungen(einstellung e)
{
    Einstellung = e;
    ui->lineEdit_quelle->setText(Einstellung.verzeichnis_quelle());
    ui->lineEdit_ziel_server->setText(Einstellung.verzeichnis_ziel_server());
    ui->lineEdit_ziel_lokal->setText(Einstellung.verzeichnis_ziel_lokal());
    ui->lineEdit_root_ganx->setText(Einstellung.verzeichnis_root_ganx());
    ui->lineEdit_root_fmc->setText(Einstellung.verzeichnis_root_fmc());
    this->show();
}

void Dialog_Einstellung_pfade::on_pushButton_quelle_clicked()
{
    if(Einstellung.verzeichnis_quelle().isEmpty())
    {
        Einstellung.set_verzeichnis_quelle("./");
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Quellverzeichniss"), Einstellung.verzeichnis_quelle());
    if(!tmp.isEmpty())
    {
        Einstellung.set_verzeichnis_quelle(tmp);
        ui->lineEdit_quelle->setText(tmp);
    }
}
void Dialog_Einstellung_pfade::on_pushButton_ziel_server_clicked()
{
    if(Einstellung.verzeichnis_ziel_server().isEmpty())
    {
        Einstellung.set_verzeichnis_ziel_server("./");
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Zielverzeichniss Server"), Einstellung.verzeichnis_ziel_server());
    if(!tmp.isEmpty())
    {
        Einstellung.set_verzeichnis_ziel_server(tmp);
        ui->lineEdit_ziel_server->setText(tmp);
    }
}
void Dialog_Einstellung_pfade::on_pushButton_ziel_lokal_clicked()
{
    if(Einstellung.verzeichnis_ziel_lokal().isEmpty())
    {
        Einstellung.set_verzeichnis_ziel_lokal("./");
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Zielverzeichniss lokal"), Einstellung.verzeichnis_ziel_lokal());
    if(!tmp.isEmpty())
    {
        Einstellung.set_verzeichnis_ziel_lokal(tmp);
        ui->lineEdit_ziel_lokal->setText(tmp);
    }
}
void Dialog_Einstellung_pfade::on_pushButton_root_ganx_clicked()
{
    if(Einstellung.verzeichnis_root_ganx().isEmpty())
    {
        Einstellung.set_verzeichnis_root_ganx("./");
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Wurzelverzeichnis ganx"), Einstellung.verzeichnis_root_ganx());
    if(!tmp.isEmpty())
    {
        Einstellung.set_verzeichnis_root_ganx(tmp);
        ui->lineEdit_root_ganx->setText(tmp);
    }
}
void Dialog_Einstellung_pfade::on_pushButton_root_fmc_clicked()
{
    if(Einstellung.verzeichnis_root_fmc().isEmpty())
    {
        Einstellung.set_verzeichnis_root_fmc("./");
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Wurzelverzeichnis fmc"), Einstellung.verzeichnis_root_fmc());
    if(!tmp.isEmpty())
    {
        Einstellung.set_verzeichnis_root_fmc(tmp);
        ui->lineEdit_root_fmc->setText(tmp);
    }
}

void Dialog_Einstellung_pfade::on_lineEdit_quelle_editingFinished()
{
    QString eingabe = ui->lineEdit_quelle->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_quelle->setText(Einstellung.verzeichnis_quelle());
    }else
    {
        Einstellung.set_verzeichnis_quelle(eingabe);
    }
}
void Dialog_Einstellung_pfade::on_lineEdit_ziel_server_editingFinished()
{
    QString eingabe = ui->lineEdit_ziel_server->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_ziel_server->setText(Einstellung.verzeichnis_ziel_server());
    }else
    {
        Einstellung.set_verzeichnis_ziel_server(eingabe);
    }
}
void Dialog_Einstellung_pfade::on_lineEdit_ziel_lokal_editingFinished()
{
    QString eingabe = ui->lineEdit_ziel_lokal->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_ziel_lokal->setText(Einstellung.verzeichnis_ziel_lokal());
    }else
    {
        Einstellung.set_verzeichnis_ziel_lokal(eingabe);
    }
}
void Dialog_Einstellung_pfade::on_lineEdit_root_ganx_editingFinished()
{
    QString eingabe = ui->lineEdit_root_ganx->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_root_ganx->setText(Einstellung.verzeichnis_root_ganx());
    }else
    {
        Einstellung.set_verzeichnis_root_ganx(eingabe);
    }
}
void Dialog_Einstellung_pfade::on_lineEdit_root_fmc_editingFinished()
{
    QString eingabe = ui->lineEdit_root_fmc->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_root_fmc->setText(Einstellung.verzeichnis_root_fmc());
    }else
    {
        Einstellung.set_verzeichnis_root_fmc(eingabe);
    }
}













