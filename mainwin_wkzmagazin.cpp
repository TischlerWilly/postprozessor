#include "mainwin_wkzmagazin.h"
#include "ui_mainwin_wkzmagazin.h"

mainwin_wkzmagazin::mainwin_wkzmagazin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwin_wkzmagazin)
{
    ui->setupUi(this);
    connect(&dlg_fraeser, SIGNAL(Data(text_zw,bool)),this, SLOT(set_Data(text_zw,bool)));
    connect(&dlg_bohrer, SIGNAL(Data(text_zw,bool)),this, SLOT(set_Data(text_zw,bool)));
    connect(&dlg_saege, SIGNAL(Data(text_zw,bool)),this, SLOT(set_Data(text_zw,bool)));
}

mainwin_wkzmagazin::~mainwin_wkzmagazin()
{
    delete ui;
}

//-------------------------------------set:

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
            wkz_bohrer bohrer(wkz);
            istaktiv = bohrer.istaktiv();
            zeile  = "Bohrer ";
            zeile += bohrer.wkznr();
            zeile += " / DM:";
            zeile += double_to_qstring(bohrer.dmexport());
        }else if(wkz.at(0) == WKZ_TYP_SAEGE)
        {
            wkz_saege saege(wkz);
            istaktiv = saege.istaktiv();
            zeile  = "Säge ";
            zeile += saege.wkznr();
            zeile += " / DM:";
            zeile += double_to_qstring(saege.dm());
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
    }else if(wkz.at(0) == WKZ_TYP_BOHRER)
    {
        wkz_bohrer b(wkz);
        info += "Name:\t";
        info += b.wkznr();
        info += "\n";
        info += "Import-DM:\t";
        info += double_to_qstring(b.dmimport());
        info += "\n";
        info += "Export-DM:\t";
        info += double_to_qstring(b.dmexport());
        info += "\n";
        info += "Nutzlänge:\t";
        info += double_to_qstring(b.nutzl());
        info += "\n";
        info += "Zustellmaß:\t";
        info += double_to_qstring(b.zustma());
        info += "\n";
        info += "Ist Durchgangsbohrer:\t";
        if(b.istdubo())
        {
            info += "ja";
        }else
        {
            info += "nein";
        }
        info += "\n";
        info += "Kann horizontal bohren:\t";
        if(b.isthori())
        {
            info += "ja";
        }else
        {
            info += "nein";
        }
        info += "\n";
        info += "Kann vertikal bohren:\t";
        if(b.istverti())
        {
            info += "ja";
        }else
        {
            info += "nein";
        }
    }else if(wkz.at(0) == WKZ_TYP_SAEGE)
    {
        wkz_saege s(wkz);
        info += "Name:\t";
        info += s.wkznr();
        info += "\n";
        info += "Durchmesser:\t";
        info += double_to_qstring(s.dm());
        info += "\n";
        info += "Zustellmaß:\t";
        info += double_to_qstring(s.zustma());
        info += "\n";
        info += "Schnittbreite:\t";
        info += double_to_qstring(s.sbreite());
        info += "\n";
        info += "Kann horizontal sägen:\t";
        if(s.isthori())
        {
            info += "ja";
        }else
        {
            info += "nein";
        }
        info += "\n";
        info += "Kann vertikal sägen:\t";
        if(s.istverti())
        {
            info += "ja";
        }else
        {
            info += "nein";
        }
    }
    ui->plainTextEdit->setPlainText(info);
}
void mainwin_wkzmagazin::edit(uint index)
{
    text_zw wkz;
    wkz.set_text(Magazin.magazin_ptr()->at(index), WKZ_TRENNZ);
    if(wkz.at(0) == WKZ_TYP_FRAESER)
    {
        dlg_fraeser.set_Data(wkz);
    }else if(wkz.at(0) == WKZ_TYP_BOHRER)
    {
        dlg_bohrer.set_Data(wkz);
    }else if(wkz.at(0) == WKZ_TYP_SAEGE)
    {
        dlg_saege.set_Data(wkz);
    }
}
//-------------------------------------public slots
void mainwin_wkzmagazin::set_Data(text_zw wkz, bool ist_neues_wkz)
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
void mainwin_wkzmagazin::set_wkzmag(QString fenstertitel, wkz_magazin wkzmag)
{
    this->setWindowTitle(fenstertitel);
    Magazin = wkzmag;
    UnReDo.neu(Magazin);
    liste_aktualisieren();
    this->show();
}
//-------------------------------------private slots:
void mainwin_wkzmagazin::on_actionFraeser_anlegen_triggered()
{
    dlg_fraeser.neuerFraeser();
}
void mainwin_wkzmagazin::on_actionBohrer_anlegen_triggered()
{
    dlg_bohrer.neuerBohrer();
}
void mainwin_wkzmagazin::on_actionSaege_anlegen_triggered()
{
    dlg_saege.neueSaege();
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
            dlg_fraeser.set_Data(wkz, true);
        }else if(wkz.at(0) == WKZ_TYP_BOHRER)
        {
            dlg_bohrer.set_Data(wkz, true);
        }else if(wkz.at(0) == WKZ_TYP_SAEGE)
        {
            dlg_saege.set_Data(wkz, true);
        }
    }
}
void mainwin_wkzmagazin::on_pushButton_abbrechen_clicked()
{
    this->hide();
}
void mainwin_wkzmagazin::on_pushButton_speichern_clicked()
{
    emit wkzmag(this->windowTitle(), Magazin);
    this->hide();
}
