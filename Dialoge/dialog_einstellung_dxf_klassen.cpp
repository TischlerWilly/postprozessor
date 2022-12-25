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
    Einstellung_klassen.set_bohr_vert(ui->lineEdit_bohr_vert->text());
    Einstellung_klassen.set_bohr_hori(ui->lineEdit_bohr_hori->text());
    Einstellung_klassen.set_nut_vert(ui->lineEdit_nut_vert->text());
    Einstellung_klassen.set_kta(ui->lineEdit_kta->text());
    Einstellung_klassen.set_rta(ui->lineEdit_rta->text());
    Einstellung_klassen.set_fraes_vert(ui->lineEdit_fraes_vert->text());
    this->close();
    emit send_einstellung(Einstellung_klassen);
}

void Dialog_einstellung_dxf_klassen::slot_einstellung(einstellung_dxf eg, einstellung_dxf_klassen ek)
{
    Einstellung_allgem = eg;
    Einstellung_klassen = ek;
    ui->lineEdit_wst->clear();
    ui->lineEdit_wst->setText(Einstellung_klassen.wst());
    ui->lineEdit_bohr_vert->clear();
    ui->lineEdit_bohr_vert->setText(Einstellung_klassen.bohr_vert());
    ui->lineEdit_bohr_hori->clear();
    ui->lineEdit_bohr_hori->setText(Einstellung_klassen.bohr_hori());
    ui->lineEdit_nut_vert->clear();
    ui->lineEdit_nut_vert->setText(Einstellung_klassen.nut_vert());
    ui->lineEdit_kta->clear();
    ui->lineEdit_kta->setText(Einstellung_klassen.kta());
    ui->lineEdit_rta->clear();
    ui->lineEdit_rta->setText(Einstellung_klassen.rta());
    ui->lineEdit_fraes_vert->clear();
    ui->lineEdit_fraes_vert->setText(Einstellung_klassen.fraes_vert());
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
void Dialog_einstellung_dxf_klassen::on_lineEdit_bohr_vert_textChanged(const QString &arg1)
{
    QString beispiel = arg1;
    beispiel += "_14";
    beispiel += Einstellung_allgem.dezitren();
    beispiel += "2";
    ui->lineEdit_bohr_vert_beispiel->setText(beispiel);
}
void Dialog_einstellung_dxf_klassen::on_lineEdit_bohr_hori_textChanged(const QString &arg1)
{
    QString beispiel = arg1;
    beispiel += "_14";
    beispiel += Einstellung_allgem.dezitren();
    beispiel += "2";
    ui->lineEdit_bohr_hori_beispiel->setText(beispiel);
}
void Dialog_einstellung_dxf_klassen::on_lineEdit_nut_vert_textChanged(const QString &arg1)
{
    QString beispiel = arg1;
    beispiel += "_8";
    beispiel += Einstellung_allgem.dezitren();
    beispiel += "5";
    ui->lineEdit_nut_vert_beispiel->setText(beispiel);
}
void Dialog_einstellung_dxf_klassen::on_lineEdit_fraes_vert_textChanged(const QString &arg1)
{
    //Beispiel 1:
    QString beispiel = arg1;
    beispiel += "_-2";
    beispiel += Einstellung_allgem.kenWKZnr();
    beispiel += "601";
    beispiel += Einstellung_allgem.kenRadKorLi();
    ui->lineEdit_fraes_vert_beispiel1->setText(beispiel);
    //Beispiel 2:
    beispiel = arg1;
    if(Einstellung_allgem.bezugTiFkonObSei())
    {
        beispiel += "_5";
        beispiel += Einstellung_allgem.dezitren();
        beispiel += "0";
    }else
    {
        beispiel += "_14";
        beispiel += Einstellung_allgem.dezitren();
        beispiel += "0";
    }
    beispiel += Einstellung_allgem.kenWKZnr();
    beispiel += "601";
    beispiel += Einstellung_allgem.kenRadKorLi();
    ui->lineEdit_fraes_vert_beispiel2->setText(beispiel);
}
void Dialog_einstellung_dxf_klassen::on_lineEdit_kta_textChanged(const QString &arg1)
{
    //Beispiel 1:
    QString beispiel = arg1;
    beispiel += "_14";
    beispiel += Einstellung_allgem.dezitren();
    beispiel += "2";
    ui->lineEdit_kta_beispiel->setText(beispiel);
    //Beispiel 2:
    beispiel += Einstellung_allgem.kenWKZnr();
    beispiel += "601";
    ui->lineEdit_kta_beispiel2->setText(beispiel);
}
void Dialog_einstellung_dxf_klassen::on_lineEdit_rta_textChanged(const QString &arg1)
{
    //Beispiel 1:
    QString beispiel = arg1;
    beispiel += "_14";
    beispiel += Einstellung_allgem.dezitren();
    beispiel += "2";
    ui->lineEdit_rta_beispiel->setText(beispiel);
    //Beispiel 2:
    beispiel += Einstellung_allgem.kenWKZnr();
    beispiel += "601";
    ui->lineEdit_rta_beispiel2->setText(beispiel);
}
