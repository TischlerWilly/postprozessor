#include "dialog_programmtext.h"
#include "ui_dialog_programmtext.h"

Dialog_programmtext::Dialog_programmtext(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_programmtext)
{
    ui->setupUi(this);
}

Dialog_programmtext::~Dialog_programmtext()
{
    delete ui;
}

void Dialog_programmtext::resizeEvent(QResizeEvent *event)
{
    ui->listWidget_prgtext->move(5,5);
    ui->listWidget_prgtext->setFixedWidth(this->width()-10);
    ui->listWidget_prgtext->setFixedHeight(this->height()-10);
}

void Dialog_programmtext::slot_wst(werkstueck w_neu,\
                                   QString format, text_zeilenweise wkzmagazin, QString drehwinkel)
{
    Wst = w_neu;
    ui->listWidget_prgtext->clear();
    QString fenstertitel = "Programmtext von: ";
    fenstertitel += Wst.name();
    this->setWindowTitle(fenstertitel);
    double tmp_l = 0;
    double tmp_b = 0;
    text_zeilenweise tmp_bearb = Wst.bearb(format, wkzmagazin, drehwinkel, tmp_l, tmp_b);
    //Programmkopf als erste Zeile einfügen:
    text_zeilenweise pkopf;
    pkopf.set_trennzeichen(TRENNZ_BEARB_PARAM);
    QString param;
    param  = "L=";
    param += double_to_qstring(tmp_l);
    pkopf.zeile_anhaengen(param);
    param  = "B=";
    param += double_to_qstring(tmp_b);
    pkopf.zeile_anhaengen(param);
    param  = "D=";
    param += Wst.dicke_qstring();
    pkopf.zeile_anhaengen(param);
    param  = "Drehung ";
    param += drehwinkel;
    pkopf.zeile_anhaengen(param);
    param = format;
    pkopf.zeile_anhaengen(param);
    ui->listWidget_prgtext->addItem(pkopf.text());
    //Bearbeitungen ab 2. Zeile einfügen:
    for(uint i=1; i<=tmp_bearb.zeilenanzahl() ;i++)
    {
        ui->listWidget_prgtext->addItem(tmp_bearb.zeile(i));
    }
    ui->listWidget_prgtext->addItem("...");
    this->show();
}
void Dialog_programmtext::slot_zeilennummer(uint nr)
{
    if((int)nr < ui->listWidget_prgtext->count())
    {
        ui->listWidget_prgtext->item(nr-1)->setSelected(true);
    }
}

void Dialog_programmtext::on_listWidget_prgtext_currentRowChanged(int currentRow)
{
    emit signalIndexChange(currentRow+1);
}
