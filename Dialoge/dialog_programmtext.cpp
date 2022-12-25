#include "dialog_programmtext.h"
#include "ui_dialog_programmtext.h"

Dialog_programmtext::Dialog_programmtext(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_programmtext)
{
    ui->setupUi(this);
    Wst = NULL;
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

void Dialog_programmtext::slot_wst(werkstueck* w)
{
    Wst = w;
    ui->listWidget_prgtext->clear();
    QString fenstertitel = "Programmtext von: ";
    fenstertitel += w->name();
    this->setWindowTitle(fenstertitel);
    //Programmkopf als erste Zeile einfügen:
    text_zeilenweise pkopf;
    pkopf.set_trennzeichen(TRENNZ_BEARB_PARAM);
    QString param;
    param  = "L=";
    param += double_to_qstring(w->zustand().l());
    pkopf.zeile_anhaengen(param);
    param  = "B=";
    param += double_to_qstring(w->zustand().b());
    pkopf.zeile_anhaengen(param);
    param  = "D=";
    param += w->dicke_qstring();
    pkopf.zeile_anhaengen(param);
    param  = "Drehung ";
    param += w->zustand().drehung();
    pkopf.zeile_anhaengen(param);
    param = w->zustand().format();
    pkopf.zeile_anhaengen(param);
    param = "KaVo=";
    param += w->zustand().kante_vo();
    pkopf.zeile_anhaengen(param);
    param = "KaHi=";
    param += w->zustand().kante_hi();
    pkopf.zeile_anhaengen(param);
    param = "KaLi=";
    param += w->zustand().kante_li();
    pkopf.zeile_anhaengen(param);
    param = "KaRe=";
    param += w->zustand().kante_re();
    pkopf.zeile_anhaengen(param);
    ui->listWidget_prgtext->addItem(pkopf.text());
    //Bearbeitungen ab 2. Zeile einfügen:
    text_zeilenweise tmp_bearb = w->zustand().bearb();
    for(uint i=1; i<=tmp_bearb.zeilenanzahl() ;i++)
    {
        QString bearb = tmp_bearb.zeile(i);
        text_zeilenweise zeile;
        zeile.set_trennzeichen(TRENNZ_BEARB_PARAM);
        zeile.set_text(bearb);
        if(zeile.zeile(1) == BEARBART_BOHR)
        {
            bearb = bohr_zu_prgeile(zeile.text());
        }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
        {
            bearb = bohrRaster_zu_prgeile(zeile.text());
        }else if(zeile.zeile(1) == BEARBART_NUT)
        {
            bearb = nut_zu_prgeile(zeile.text());
        }else if(zeile.zeile(1) == BEARBART_RTA)
        {
            bearb = rta_zu_prgeile(zeile.text());
        }else if(zeile.zeile(1) == BEARBART_FRAESERAUFRUF)
        {
            bearb = fauf_zu_prgeile(zeile.text());
        }else if(zeile.zeile(1) == BEARBART_FRAESERGERADE)
        {
            bearb = fgerade_zu_prgeile(zeile.text());
        }else if(zeile.zeile(1) == BEARBART_FRAESERBOGEN)
        {
            bearb = fbogen_zu_prgeile(zeile.text());
        }
        ui->listWidget_prgtext->addItem(bearb);
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

