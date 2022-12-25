#include "dialog_wst_bearbeiten.h"
#include "ui_dialog_wst_bearbeiten.h"

Dialog_wst_bearbeiten::Dialog_wst_bearbeiten(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_wst_bearbeiten)
{
    ui->setupUi(this);
    clear();

    connect(this, SIGNAL(sendVorschauAktualisieren(werkstueck,int)),\
            &vorschaufenster, SLOT(slot_aktualisieren_einzelwst(werkstueck,int)));
    connect(this, SIGNAL(signalIndexChange(int)),\
            &vorschaufenster, SLOT(slot_aktives_Element_einfaerben(int)));
    connect(&vorschaufenster, SIGNAL(sende_zeilennummer(uint)),\
            this, SLOT(slot_zeilennummer(uint)));
    connect(&vorschaufenster, SIGNAL(sende_maus_pos(QPoint)),\
            this, SLOT(getMausPosXY(QPoint)));
    this->setWindowFlags(Qt::Window);
    this->setWindowState(Qt::WindowMaximized);
}

Dialog_wst_bearbeiten::~Dialog_wst_bearbeiten()
{
    delete ui;
}

void Dialog_wst_bearbeiten::clear()
{
    Wst = nullptr;
    ui->listWidget_prgtext->clear();
}

void Dialog_wst_bearbeiten::resizeEvent(QResizeEvent *event)
{
    vorschaufenster.setParent(this);
    vorschaufenster.move(5,5);
    vorschaufenster.setFixedWidth(this->width()-400-15);
    vorschaufenster.setFixedHeight(this->height()-30);
    //----------------------
    ui->listWidget_prgtext->move(vorschaufenster.pos().x()+vorschaufenster.width()+5, 5);
    ui->listWidget_prgtext->setFixedWidth(400);
    ui->listWidget_prgtext->setFixedHeight(this->height()-30);
    //----------------------
    ui->label_xypos->move(ui->listWidget_prgtext->pos().x(),\
                          ui->listWidget_prgtext->pos().y() + ui->listWidget_prgtext->height()+2);
    ui->label_xypos->setFixedWidth(ui->listWidget_prgtext->width());
}

void Dialog_wst_bearbeiten::getMausPosXY(QPoint p)
{
    if(ui->listWidget_prgtext->selectedItems().count())
    {
        QString x = int_to_qstring(p.x());
        QString y = int_to_qstring(p.y());
        QString msg;
        msg  = "X: ";
        msg += x;
        msg += " / Y: ";
        msg += y;
        ui->label_xypos->setText(msg);
    }else
    {
        QString msg;
        msg  = "X: ";
        msg += "?";
        msg += " / Y: ";
        msg += "?";
        ui->label_xypos->setText(msg);
    }
}

void Dialog_wst_bearbeiten::set_wst(werkstueck *w)
{
    clear();
    Wst = w;
    update_listwidget();
    ui->listWidget_prgtext->setCurrentRow(ui->listWidget_prgtext->count()-1);
    sendVorschauAktualisieren(*Wst, 0);
}

void Dialog_wst_bearbeiten::update_listwidget()
{
    //Programmkopf als erste Zeile einfügen:
    text_zeilenweise pkopf;
    pkopf.set_trennzeichen(TRENNZ_BEARB_PARAM);
    QString param;
    param  = "L=";
    param += Wst->laenge_qstring();
    pkopf.zeile_anhaengen(param);
    param  = "B=";
    param += Wst->breite_qstring();
    pkopf.zeile_anhaengen(param);
    param  = "D=";
    param += Wst->dicke_qstring();
    pkopf.zeile_anhaengen(param);
    param = "KaVo=";
    param += Wst->kante_vo();
    pkopf.zeile_anhaengen(param);
    param = "KaHi=";
    param += Wst->kante_hi();
    pkopf.zeile_anhaengen(param);
    param = "KaLi=";
    param += Wst->kante_li();
    pkopf.zeile_anhaengen(param);
    param = "KaRe=";
    param += Wst->kante_re();
    pkopf.zeile_anhaengen(param);
    ui->listWidget_prgtext->addItem(pkopf.text());
    //Bearbeitungen ab 2. Zeile einfügen:
    text_zeilenweise tmp_bearb = Wst->bearb();
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
}

void Dialog_wst_bearbeiten::slot_zeilennummer(uint nr)
{
    if((int)nr < ui->listWidget_prgtext->count())
    {
        ui->listWidget_prgtext->item(nr-1)->setSelected(true);
    }
}

void Dialog_wst_bearbeiten::on_listWidget_prgtext_currentRowChanged(int currentRow)
{
    emit signalIndexChange(currentRow+1);
}

void Dialog_wst_bearbeiten::on_listWidget_prgtext_itemDoubleClicked(QListWidgetItem *item)
{
    int index = ui->listWidget_prgtext->currentRow();
    if(index == 0)
    {
        return;
    }
    //Zeile Auslesen:
    text_zeilenweise bearb;
    bearb.set_trennzeichen(TRENNZ_BEARB_PARAM);
    bearb.set_text(Wst->bearb_ptr()->zeile(index));
    //Dialogfenster aufrufen:
    if(bearb.zeile(1) == BEARBART_RTA)
    {
        Dialog_bearb_rta dlg;
        dlg.setModal(true);
        connect(&dlg, SIGNAL(signal_rta(rechtecktasche)), this, SLOT(slot_rta(rechtecktasche)));
        dlg.set_data(bearb.text());
        dlg.exec();
    }else if(bearb.zeile(1) == BEARBART_BOHR)
    {
        Dialog_bearb_bohrung dlg;
        dlg.setModal(true);
        connect(&dlg, SIGNAL(signal_bo(bohrung)), this, SLOT(slot_bo(bohrung)));
        dlg.set_data(bearb.text());
        dlg.exec();
    }else if(bearb.zeile(1) == BEARBART_NUT)
    {
        Dialog_bearb_nut dlg;
        dlg.setModal(true);
        connect(&dlg, SIGNAL(signal_nut(nut)), this, SLOT(slot_nut(nut)));
        dlg.set_data(bearb.text());
        dlg.exec();
    }
}

void Dialog_wst_bearbeiten::slot_rta(rechtecktasche rta)
{
    int index = ui->listWidget_prgtext->currentRow();
    //Werte zurück speichern:
    QString zeile;
    zeile = rta.text();
    ui->listWidget_prgtext->item(index)->setText(rta_zu_prgeile(zeile));

    text_zeilenweise bearbeitungen = Wst->bearb();
    bearbeitungen.zeile_ersaetzen(index, zeile);
    Wst->bearb_ptr()->zeile_ersaetzen(index, bearbeitungen.zeile(index));
    emit sendVorschauAktualisieren(*Wst, index);
}
void Dialog_wst_bearbeiten::slot_bo(bohrung bo)
{
    int index = ui->listWidget_prgtext->currentRow();
    //Werte zurück speichern:
    QString zeile;
    zeile = bo.text();
    ui->listWidget_prgtext->item(index)->setText(bohr_zu_prgeile(zeile));

    text_zeilenweise bearbeitungen = Wst->bearb();
    bearbeitungen.zeile_ersaetzen(index, zeile);
    Wst->bearb_ptr()->zeile_ersaetzen(index, bearbeitungen.zeile(index));
    emit sendVorschauAktualisieren(*Wst, index);
}
void Dialog_wst_bearbeiten::slot_nut(nut nu)
{
    int index = ui->listWidget_prgtext->currentRow();
    //Werte zurück speichern:
    QString zeile;
    zeile = nu.text();
    ui->listWidget_prgtext->item(index)->setText(nut_zu_prgeile(zeile));

    text_zeilenweise bearbeitungen = Wst->bearb();
    bearbeitungen.zeile_ersaetzen(index, zeile);
    Wst->bearb_ptr()->zeile_ersaetzen(index, bearbeitungen.zeile(index));
    emit sendVorschauAktualisieren(*Wst, index);
}
