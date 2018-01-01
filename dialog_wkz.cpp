#include "dialog_wkz.h"
#include "ui_dialog_wkz.h"


Dialog_WKZ::Dialog_WKZ(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_WKZ)
{
    ui->setupUi(this);
    connect(this, SIGNAL(sendData_Bohrer(text_zeilenweise)), \
            &dibo, SLOT(getData(text_zeilenweise))        );
    connect(this, SIGNAL(sendData_Fraeser(text_zeilenweise)), \
            &difr, SLOT(getData(text_zeilenweise))        );
    connect(this, SIGNAL(sendData_Saege(text_zeilenweise)), \
            &disae, SLOT(getData(text_zeilenweise))        );

    connect(this, SIGNAL(neues_wkz_bohrer()), \
            &dibo, SLOT(neuerBohrer())     );
    connect(this, SIGNAL(neues_wkz_fraeser()), \
            &difr, SLOT(neuerFraeser())     );
    connect(this, SIGNAL(neues_wkz_saege()), \
            &disae, SLOT(neueSaege())     );

    connect(&dibo, SIGNAL(sendData(text_zeilenweise,bool)), \
            this, SLOT(getParamaterWKZ(text_zeilenweise,bool))     );
    connect(&difr, SIGNAL(sendData(text_zeilenweise,bool)), \
            this, SLOT(getParamaterWKZ(text_zeilenweise,bool))     );
    connect(&disae, SIGNAL(sendData(text_zeilenweise,bool)), \
            this, SLOT(getParamaterWKZ(text_zeilenweise,bool))     );

}

Dialog_WKZ::~Dialog_WKZ()
{
    delete ui;
}

void Dialog_WKZ::getDialogDataWKZ(QString fenstertitel, text_zeilenweise werkzeugmagazin)
{
    this->clear();
    this->setWindowTitle(fenstertitel);
    for(uint i=1; i<=werkzeugmagazin.zeilenanzahl() ;i++)
    {
        ui->listWidget_wkz->addItem(werkzeugmagazin.zeile(i));
    }
    this->show();
}

void Dialog_WKZ::on_pushButton_abbrechen_clicked()
{
    clear();
    this->hide();
}

void Dialog_WKZ::clear()
{
    ui->listWidget_wkz->clear();
}

void Dialog_WKZ::on_pushButton_speichern_clicked()
{
    text_zeilenweise tz;
    for(int i=0; i<ui->listWidget_wkz->count() ;i++)
    {
        tz.zeile_anhaengen(ui->listWidget_wkz->item(i)->text());
    }
    this->hide();
    emit sendData_wkzmagazin(this->windowTitle(), tz);
}

void Dialog_WKZ::on_listWidget_wkz_itemDoubleClicked(QListWidgetItem *item)
{
    text_zeilenweise werkzeug;
    werkzeug.set_trennzeichen('\t');
    werkzeug.set_text(item->text());

    if(werkzeug.zeile(1) == WKZ_TYP_BOHRER)
    {
        emit sendData_Bohrer(werkzeug);
    }else if(werkzeug.zeile(1) == WKZ_TYP_FRAESER)
    {
        emit sendData_Fraeser(werkzeug);
    }if(werkzeug.zeile(1) == WKZ_TYP_SAEGE)
    {
        emit sendData_Saege(werkzeug);
    }

}

void Dialog_WKZ::on_pushButton_neu_bohrer_clicked()
{
    emit neues_wkz_bohrer();
}

void Dialog_WKZ::getParamaterWKZ(text_zeilenweise wkz, bool ist_neues_wkz)
{
    if(ist_neues_wkz)
    {
        ui->listWidget_wkz->insertItem(ui->listWidget_wkz->count()-1, wkz.get_text());
    }else
    {
        ui->listWidget_wkz->currentItem()->setText(wkz.get_text());
    }
}

void Dialog_WKZ::on_pushButton_entfernen_clicked()
{
    if(ui->listWidget_wkz->currentRow() != 0  && \
       ui->listWidget_wkz->currentRow() != ui->listWidget_wkz->count()-1     )
    {//Tabellenkopf und die letzt (leere) Zeile muss erhalten beleiben!

        text_zeilenweise tz;
        for(int i = 0; i<ui->listWidget_wkz->count() ;i++)
        {
            if(i != ui->listWidget_wkz->currentRow())
            {
                tz.zeile_anhaengen(ui->listWidget_wkz->item(i)->text());
            }
        }
        ui->listWidget_wkz->clear();
        for(uint i=1; i<=tz.zeilenanzahl() ;i++)
        {
            ui->listWidget_wkz->addItem(tz.zeile(i));
        }
    }
}

void Dialog_WKZ::on_pushButton_neu_fraeser_clicked()
{
    emit neues_wkz_fraeser();
}

void Dialog_WKZ::on_pushButton_neu_saege_clicked()
{
    emit neues_wkz_saege();
}

void Dialog_WKZ::on_pushButton_bearbeiten_clicked()
{
    on_listWidget_wkz_itemDoubleClicked(ui->listWidget_wkz->currentItem());
}
