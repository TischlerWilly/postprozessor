#include "mainwin_wkzmagazin.h"
#include "ui_mainwin_wkzmagazin.h"

mainwin_wkzmagazin::mainwin_wkzmagazin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwin_wkzmagazin)
{
    ui->setupUi(this);
    connect(&dlg_fraeser, SIGNAL(sendData(text_zw,bool)),this, SLOT(getData(text_zw,bool)));
}

mainwin_wkzmagazin::~mainwin_wkzmagazin()
{
    delete ui;
}

//-------------------------------------set:
void mainwin_wkzmagazin::set_wkzmag(wkz_magazin w)
{
    Magazin = w;
    liste_aktualisieren();
}
//-------------------------------------get:

//-------------------------------------private Funktionen:
void mainwin_wkzmagazin::liste_aktualisieren()
{
    ui->listWidget->clear();
    for(uint i=0; i<Magazin.magazin_ptr()->count();i++)
    {
        QString zeile = Magazin.magazin_ptr()->at(i);
        text_zw wkz(zeile, WKZ_TRENNZ);
        if(wkz.at(0) == WKZ_TYP_FRAESER)
        {
            wkz_fraeser fraeser(wkz);
            zeile  = "Fräser ";
            zeile += fraeser.wkznr();
            zeile += " / DM:";
            zeile += double_to_qstring(fraeser.dm());
        }else if(wkz.at(0) == WKZ_TYP_BOHRER)
        {
            //..
        }else if(wkz.at(0) == WKZ_TYP_SAEGE)
        {
            //..
        }
        ui->listWidget->addItem(zeile);
    }
    ui->listWidget->addItem("...");
}
//-------------------------------------public slots
void mainwin_wkzmagazin::getData(text_zw wkz, bool ist_neues_wkz)
{
    if(ist_neues_wkz)
    {
        Magazin.magazin_ptr()->add_hi(wkz.text());//später noch an markierter Stelle einfügen und nicht immer am Ende
        liste_aktualisieren();
    }else
    {
        //...
    }
}
//-------------------------------------private slots:
void mainwin_wkzmagazin::on_actionFraeser_anlegen_triggered()
{
    dlg_fraeser.show();
}
void mainwin_wkzmagazin::on_actionBohrer_anlegen_triggered()
{

}
void mainwin_wkzmagazin::on_actionSaege_anlegen_triggered()
{

}
