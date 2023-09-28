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
    text_zw pkopf;
    pkopf.set_trenz(TRENNZ_BEARB_PARAM);
    QString param;
    param  = "L=";
    param += double_to_qstring(w->zustand().l());
    pkopf.add_hi(param);
    param  = "B=";
    param += double_to_qstring(w->zustand().b());
    pkopf.add_hi(param);
    param  = "D=";
    param += w->dicke_qstring();
    pkopf.add_hi(param);
    param  = "Drehung ";
    param += w->zustand().drehung();
    pkopf.add_hi(param);
    param = w->zustand().format();
    pkopf.add_hi(param);
    param = "KaVo=";
    param += w->zustand().kante_vo();
    pkopf.add_hi(param);
    param = "KaHi=";
    param += w->zustand().kante_hi();
    pkopf.add_hi(param);
    param = "KaLi=";
    param += w->zustand().kante_li();
    pkopf.add_hi(param);
    param = "KaRe=";
    param += w->zustand().kante_re();
    pkopf.add_hi(param);
    param = "Use_ax=";
    if(w->use_ax() == true)
    {
        param += "ja";
    }else
    {
        param += "nein";
    }
    pkopf.add_hi(param);
    param = "Use_ay=";
    if(w->use_ay() == true)
    {
        param += "ja";
    }else
    {
        param += "nein";
    }
    pkopf.add_hi(param);
    ui->listWidget_prgtext->addItem(pkopf.text());
    //Bearbeitungen ab 2. Zeile einfügen:
    text_zw tmp_bearb = w->zustand().bearb();
    for(uint i=0; i<tmp_bearb.count() ;i++)
    {
        QString bearb = tmp_bearb.at(i);
        text_zw zeile;
        zeile.set_text(bearb,TRENNZ_BEARB_PARAM);
        if(zeile.at(0) == BEARBART_BOHR)
        {
            bearb = bohr_zu_prgzei(zeile.text());
        }else if(zeile.at(0) == BEARBART_BOHRRASTER)
        {
            bearb = bohrRaster_zu_prgzei(zeile.text());
        }else if(zeile.at(0) == BEARBART_NUT)
        {
            bearb = nut_zu_prgzei(zeile.text());
        }else if(zeile.at(0) == BEARBART_RTA)
        {
            bearb = rta_zu_prgzei(zeile.text());
        }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
        {
            bearb = fauf_zu_prgzei(zeile.text());
        }else if(zeile.at(0) == BEARBART_FRAESERGERADE)
        {
            bearb = fgerade_zu_prgzei(zeile.text());
        }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
        {
            bearb = fbogen_zu_prgzei(zeile.text());
        }else if(zeile.at(0) == BEARBART_GEHRUNG)
        {
            bearb = gehr_zu_prgzei(zeile.text());
        }
        ui->listWidget_prgtext->addItem(bearb);
    }
    ui->listWidget_prgtext->addItem("...");
    this->show();
}

void Dialog_programmtext::slot_zeilennummer(uint nr, bool bearbeiten)
{
    if((int)nr < ui->listWidget_prgtext->count())
    {
        ui->listWidget_prgtext->item(nr+1)->setSelected(true);
    }
}

void Dialog_programmtext::on_listWidget_prgtext_currentRowChanged(int currentRow)
{
    emit signalIndexChange(currentRow);
}

