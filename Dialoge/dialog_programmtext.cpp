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
    ui->listWidget_prgtext->addItem(pkopf.text());
    //Bearbeitungen ab 2. Zeile einfügen:
    for(uint i=1; i<=Wst.bearb().zeilenanzahl() ;i++)
    {
        ui->listWidget_prgtext->addItem(Wst.bearb().zeile(i));
    }
    this->show();
}
