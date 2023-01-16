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
    UnReDo.neu(Magazin);
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
        bool istaktiv = true;
        if(wkz.at(0) == WKZ_TYP_FRAESER)
        {
            wkz_fraeser fraeser(wkz);
            istaktiv = fraeser.istaktiv();
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
        if(!istaktiv)
        {
            ui->listWidget->item(ui->listWidget->count()-1)->setBackgroundColor(Qt::gray);
        }
    }
    ui->listWidget->addItem("...");
}
void mainwin_wkzmagazin::info_aktualisieren(uint index)
{
    text_zw wkz;
    wkz.set_text(Magazin.magazin_ptr()->at(index), WKZ_TRENNZ);
    QString info;
    if(wkz.at(0) == WKZ_TYP_FRAESER)
    {
        wkz_fraeser f(wkz);
        info += "Name:\t";
        info += f.wkznr();
        info += "\n";
        info += "Alias:\t";
        info += f.alias();
        info += "\n";
        info += "Spiegel-WKZ:\t";
        info += f.spiegelwkz();
        info += "\n";
        info += "Durchmesser:\t";
        info += double_to_qstring(f.dm());
        info += "\n";
        info += "Nutzlänge:\t";
        info += double_to_qstring(f.nutzl());
        info += "\n";
        info += "Zustellmaß:\t";
        info += double_to_qstring(f.zustma());
        info += "\n";
        info += "Mind-Zust.:\t";
        info += double_to_qstring(f.minzust());
        info += "\n";
        info += "Vorschub:\t";
        info += double_to_qstring(f.vorschub());
        info += "\n";
        info += "Nutzlänge:\t";
        info += double_to_qstring(f.nutzl());
    }else if(wkz.at(0) == WKZ_TYP_BOHRER)
    {

    }else if(wkz.at(0) == WKZ_TYP_SAEGE)
    {

    }
    ui->plainTextEdit->setPlainText(info);
}
void mainwin_wkzmagazin::edit(uint index)
{
    text_zw wkz;
    wkz.set_text(Magazin.magazin_ptr()->at(index), WKZ_TRENNZ);
    if(wkz.at(0) == WKZ_TYP_FRAESER)
    {
        dlg_fraeser.getData(wkz);
    }else if(wkz.at(0) == WKZ_TYP_BOHRER)
    {

    }else if(wkz.at(0) == WKZ_TYP_SAEGE)
    {

    }
}
//-------------------------------------public slots
void mainwin_wkzmagazin::getData(text_zw wkz, bool ist_neues_wkz)
{
    if(ist_neues_wkz)
    {
        Magazin.magazin_ptr()->add_hi(wkz.text());
        UnReDo.neu(Magazin);
        liste_aktualisieren();
    }else
    {
        int index = ui->listWidget->currentRow();
        Magazin.magazin_ptr()->edit(index, wkz.text());
        UnReDo.neu(Magazin);
        liste_aktualisieren();
        ui->listWidget->setCurrentRow(index);
    }
}
//-------------------------------------private slots:
void mainwin_wkzmagazin::on_actionFraeser_anlegen_triggered()
{
    dlg_fraeser.clear();
    dlg_fraeser.show();
}
void mainwin_wkzmagazin::on_actionBohrer_anlegen_triggered()
{

}
void mainwin_wkzmagazin::on_actionSaege_anlegen_triggered()
{

}
void mainwin_wkzmagazin::on_actionRunter_triggered()
{
    int index = ui->listWidget->currentRow();
    if((ui->listWidget->currentIndex().isValid())  &&  \
       (ui->listWidget->currentItem()->isSelected())    )
    {
        Magazin.item_down(index);
        UnReDo.neu(Magazin);
        liste_aktualisieren();
        if(index+2 < ui->listWidget->count())
        {
            ui->listWidget->setCurrentRow(index+1);
        }else
        {
            ui->listWidget->setCurrentRow(index);
        }
    }    
}
void mainwin_wkzmagazin::on_actionHoch_triggered()
{
    int index = ui->listWidget->currentRow();
    if((ui->listWidget->currentIndex().isValid())  &&  \
       (ui->listWidget->currentItem()->isSelected())    )
    {
        Magazin.item_up(index);
        UnReDo.neu(Magazin);
        liste_aktualisieren();
        if(index > 0)
        {
            ui->listWidget->setCurrentRow(index-1);
        }else
        {
            ui->listWidget->setCurrentRow(index);
        }
    }
}
void mainwin_wkzmagazin::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    int index = ui->listWidget->currentRow();
    edit(index);
}
void mainwin_wkzmagazin::on_listWidget_currentRowChanged(int currentRow)
{
    info_aktualisieren(currentRow);
}
void mainwin_wkzmagazin::on_actionL_schen_triggered()
{
    int index = ui->listWidget->currentRow();
    if((ui->listWidget->currentIndex().isValid())  &&  \
       (ui->listWidget->currentItem()->isSelected())    )
    {
        Magazin.entf(index);
        UnReDo.neu(Magazin);
        liste_aktualisieren();
    }
}
void mainwin_wkzmagazin::on_actionUndo_triggered()
{
    Magazin = UnReDo.undo();
    liste_aktualisieren();
}
void mainwin_wkzmagazin::on_actionRedo_triggered()
{
    Magazin = UnReDo.redo();
    liste_aktualisieren();
}
void mainwin_wkzmagazin::on_actionDuplizieren_triggered()
{
    int index = ui->listWidget->currentRow();
    if((ui->listWidget->currentIndex().isValid())  &&  \
       (ui->listWidget->currentItem()->isSelected())    )
    {
        text_zw wkz;
        wkz.set_text(Magazin.magazin_ptr()->at(index), WKZ_TRENNZ);
        if(wkz.at(0) == WKZ_TYP_FRAESER)
        {
            dlg_fraeser.getData(wkz, true);
        }else if(wkz.at(0) == WKZ_TYP_BOHRER)
        {

        }else if(wkz.at(0) == WKZ_TYP_SAEGE)
        {

        }
    }
}
