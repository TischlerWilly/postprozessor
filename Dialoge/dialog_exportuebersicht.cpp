#include "dialog_exportuebersicht.h"
#include "ui_dialog_exportuebersicht.h"

Dialog_ExportUebersicht::Dialog_ExportUebersicht(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_ExportUebersicht)
{
    ui->setupUi(this);
    spalte_namen    = -1;
    spalte_fmc      = -1;
    spalte_ganx     = -1;
    spalte_ggf      = -1;
    spalte_eigen    = -1;
}

Dialog_ExportUebersicht::~Dialog_ExportUebersicht()
{
    delete ui;
}

void Dialog_ExportUebersicht::resizeEvent(QResizeEvent *event)
{
    ui->tableWidget_exporte->move(5,5);
    ui->tableWidget_exporte->setFixedWidth(this->width()-10);
    ui->tableWidget_exporte->setFixedHeight(this->height()-10);
}

void Dialog_ExportUebersicht::slot_wstnamen(text_zeilenweise namen)
{
    int anz_spalten = 5;
    spalte_namen    = 0;
    spalte_fmc      = 1;
    spalte_ganx     = 2;
    spalte_ggf      = 3;
    spalte_eigen    = 4;
    ui->tableWidget_exporte->clear();
    ui->tableWidget_exporte->setRowCount(namen.zeilenanzahl());
    ui->tableWidget_exporte->setColumnCount(anz_spalten);
    QStringList tabkopf;
    tabkopf << "Name" << "fmc" << "ganx" << "ggf" << "eigen";
    ui->tableWidget_exporte->setHorizontalHeaderLabels(tabkopf);
    ui->tableWidget_exporte->setColumnWidth(0,150);
    for(uint i=1; i<=namen.zeilenanzahl() ;i++)
    {
        for(int ii=0; ii<anz_spalten;ii++)
        {
            if(ii==0)
            {
                ui->tableWidget_exporte->setItem(i-1,ii, new QTableWidgetItem(namen.zeile(i)));
            }else
            {
                ui->tableWidget_exporte->setItem(i-1,ii, new QTableWidgetItem("-"));
                ui->tableWidget_exporte->item(i-1,ii)->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

void Dialog_ExportUebersicht::slot_wstexport(QString name, QString format, bool exportiert)
{
    if(name.contains(".fmc"))
    {
        name = text_links(name, ".fmc");
    }else if(name.contains(".ganx"))
    {
        name = text_links(name, ".ganx");
    }else if(name.contains(".ggf"))
    {
        name = text_links(name, ".ggf");
    }else if(name.contains(".ppf"))
    {
        name = text_links(name, ".ppf");
    }
    int zeile = -1;
    if(ui->tableWidget_exporte->rowCount())
    {
        for(int i=0; i<=ui->tableWidget_exporte->rowCount() ;i++)
        {
            if(ui->tableWidget_exporte->item(i, spalte_namen)->text() == name)
            {
                zeile = i;
                break;
            }
        }
    }
    if(zeile >= 0)
    {
        int spalte = -1;
        if(format == "fmc")
        {
            spalte = spalte_fmc;
        }else if(format == "ganx")
        {
            spalte = spalte_ganx;
        }else if(format == "ggf")
        {
            spalte = spalte_ggf;
        }else if(format == "eigen")
        {
            spalte = spalte_eigen;
        }
        if(spalte >= 0 && ui->tableWidget_exporte->colorCount())
        {
            if(exportiert == true)
            {
                ui->tableWidget_exporte->item(zeile, spalte)->setText("X");
            }else
            {
                ui->tableWidget_exporte->item(zeile, spalte)->setText("-");
            }
        }
    }
}

void Dialog_ExportUebersicht::slot_wst_umbenennen(QString name_vor, QString name_nach)
{
    int zeile = -1;
    for(int i=0; i<=ui->tableWidget_exporte->rowCount() ;i++)
    {
        if(ui->tableWidget_exporte->item(i, spalte_namen)->text() == name_vor)
        {
            zeile = i;
            break;
        }
    }
    if(zeile >= 0)
    {
        ui->tableWidget_exporte->item(zeile, spalte_namen)->setText(name_nach);
    }
}












