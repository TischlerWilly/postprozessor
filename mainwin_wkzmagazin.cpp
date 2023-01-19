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
            zeile  = "Fräser           ";
            zeile += fraeser.wkznr();
            zeile += "\t";
            zeile += double_to_qstring(fraeser.dm());
            zeile += "mm";
        }else if(wkz.at(0) == WKZ_TYP_BOHRER)
        {
            wkz_bohrer bohrer(wkz);
            istaktiv = bohrer.istaktiv();
            zeile  = "Bohrer         ";
            zeile += bohrer.wkznr();
            zeile += "\t";
            zeile += double_to_qstring(bohrer.dmexport());
            zeile += "mm";
        }else if(wkz.at(0) == WKZ_TYP_SAEGE)
        {
            wkz_saege saege(wkz);
            istaktiv = saege.istaktiv();
            zeile  = "Säge           ";
            zeile += saege.wkznr();
            zeile += "\t";
            zeile += double_to_qstring(saege.dm());
            zeile += "mm";
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
    ui->tableWidget_info->clear();
    ui->tableWidget_info->setColumnCount(2);
    ui->tableWidget_info->setColumnWidth(0, ui->tableWidget_info->width()/2-1);
    ui->tableWidget_info->setColumnWidth(1, ui->tableWidget_info->width()/2-1);
    if(wkz.at(0) == WKZ_TYP_FRAESER)
    {
        wkz_fraeser f(wkz);
        text_zw kopf, rumpf;
        kopf.add_hi("Name/Nummer");
        rumpf.add_hi(f.wkznr());
        kopf.add_hi("Alias");
        rumpf.add_hi(f.alias());
        kopf.add_hi("Spiegelwerkzeug");
        rumpf.add_hi(f.spiegelwkz());
        kopf.add_hi("Durchmesser");
        rumpf.add_hi(double_to_qstring(f.dm()));
        kopf.add_hi("Nutzlänge");
        rumpf.add_hi(double_to_qstring(f.nutzl()));
        kopf.add_hi("Zustellmaß");
        rumpf.add_hi(double_to_qstring(f.zustma()));
        kopf.add_hi("Mindestzustellung");
        rumpf.add_hi(double_to_qstring(f.minzust()));
        kopf.add_hi("Vorschub");
        rumpf.add_hi(double_to_qstring(f.vorschub()));
        kopf.add_hi("Zuweisbar");
        if(f.nurdirektzuw())
        {
            rumpf.add_hi("nur direkt");
        }else
        {
            rumpf.add_hi("nicht nur direkt");
        }
        kopf.add_hi("Vertikal fräsen");
        if(f.istverti())
        {
            rumpf.add_hi("ja");
        }else
        {
            rumpf.add_hi("nein");
        }
        kopf.add_hi("Horizontal fräsen");
        if(f.isthori())
        {
            rumpf.add_hi("ja");
        }else
        {
            rumpf.add_hi("nein");
        }
        ui->tableWidget_info->setRowCount(kopf.count());
        for(uint i=0;i<kopf.count();i++)
        {
            ui->tableWidget_info->setItem(i,0, new QTableWidgetItem(kopf.at(i)));
        }
        for(uint i=0;i<rumpf.count();i++)
        {
            ui->tableWidget_info->setItem(i,1, new QTableWidgetItem(rumpf.at(i)));
        }
    }else if(wkz.at(0) == WKZ_TYP_BOHRER)
    {
        wkz_bohrer b(wkz);
        text_zw kopf, rumpf;
        kopf.add_hi("Name/Nummer");
        rumpf.add_hi(b.wkznr());
        kopf.add_hi("Import-DM");
        rumpf.add_hi(double_to_qstring(b.dmimport()));
        kopf.add_hi("Export-DM");
        rumpf.add_hi(double_to_qstring(b.dmexport()));
        kopf.add_hi("Nutzlänge");
        rumpf.add_hi(double_to_qstring(b.nutzl()));
        kopf.add_hi("Zustellmaß");
        rumpf.add_hi(double_to_qstring(b.zustma()));
        kopf.add_hi("Ist Durchgangsbohrer");
        if(b.istdubo())
        {
            rumpf.add_hi("ja");
        }else
        {
            rumpf.add_hi("nein");
        }
        kopf.add_hi("Vertikal bohren");
        if(b.istverti())
        {
            rumpf.add_hi("ja");
        }else
        {
            rumpf.add_hi("nein");
        }
        kopf.add_hi("Horizontal bohren");
        if(b.isthori())
        {
            rumpf.add_hi("ja");
        }else
        {
            rumpf.add_hi("nein");
        }
        ui->tableWidget_info->setRowCount(kopf.count());
        for(uint i=0;i<kopf.count();i++)
        {
            ui->tableWidget_info->setItem(i,0, new QTableWidgetItem(kopf.at(i)));
        }
        for(uint i=0;i<rumpf.count();i++)
        {
            ui->tableWidget_info->setItem(i,1, new QTableWidgetItem(rumpf.at(i)));
        }
    }else if(wkz.at(0) == WKZ_TYP_SAEGE)
    {
        wkz_saege s(wkz);
        text_zw kopf, rumpf;
        kopf.add_hi("Name/Nummer");
        rumpf.add_hi(s.wkznr());
        kopf.add_hi("Durchmesser");
        rumpf.add_hi(double_to_qstring(s.dm()));
        kopf.add_hi("Zustellmaß");
        rumpf.add_hi(double_to_qstring(s.zustma()));
        kopf.add_hi("Schnittbreite");
        rumpf.add_hi(double_to_qstring(s.sbreite()));
        kopf.add_hi("Vertikal Sägen");
        if(s.istverti())
        {
            rumpf.add_hi("ja");
        }else
        {
            rumpf.add_hi("nein");
        }
        kopf.add_hi("Horizontal Sägen");
        if(s.isthori())
        {
            rumpf.add_hi("ja");
        }else
        {
            rumpf.add_hi("nein");
        }
        ui->tableWidget_info->setRowCount(kopf.count());
        for(uint i=0;i<kopf.count();i++)
        {
            ui->tableWidget_info->setItem(i,0, new QTableWidgetItem(kopf.at(i)));
        }
        for(uint i=0;i<rumpf.count();i++)
        {
            ui->tableWidget_info->setItem(i,1, new QTableWidgetItem(rumpf.at(i)));
        }
    }else
    {
        ui->tableWidget_info->clear();
        ui->tableWidget_info->setColumnCount(0);
        ui->tableWidget_info->setRowCount(0);
    }
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
void mainwin_wkzmagazin::resizeEvent(QResizeEvent *event)
{
    ui->listWidget->setFixedWidth(250);
    ui->listWidget->setFixedHeight(this->height()-100);
    ui->listWidget->move(5,5);
    //----------------------
    int abst_unten = 30;
    ui->tableWidget_info->setFixedWidth(this->width()-ui->listWidget->width()-5*3);
    ui->tableWidget_info->setFixedHeight(ui->listWidget->height()-abst_unten);
    ui->tableWidget_info->move(ui->listWidget->pos().x()+ui->listWidget->width()+5,\
                            ui->listWidget->pos().y());
    //----------------------
    int breite_un = ui->tableWidget_info->width()\
                   -ui->pushButton_speichern->width()\
                   -ui->pushButton_abbrechen->width()\
                   -5;
    ui->pushButton_speichern->move(ui->tableWidget_info->pos().x()+breite_un/2,\
                                   ui->tableWidget_info->pos().y()+ui->tableWidget_info->height()+5);
    ui->pushButton_abbrechen->move(ui->pushButton_speichern->pos().x()+ui->pushButton_speichern->width()+5,\
                                   ui->pushButton_speichern->pos().y());
}

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
