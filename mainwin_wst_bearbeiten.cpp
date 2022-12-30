#include "mainwin_wst_bearbeiten.h"
#include "ui_mainwin_wst_bearbeiten.h"

MainWin_wst_bearbeiten::MainWin_wst_bearbeiten(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin_wst_bearbeiten)
{
    ui->setupUi(this);
    clear();

    vorschaufenster.set_bearb_erlaubt(true);

    connect(this, SIGNAL(sendVorschauAktualisieren(werkstueck,int)),\
            &vorschaufenster, SLOT(slot_aktualisieren_einzelwst(werkstueck,int)));
    connect(this, SIGNAL(signalIndexChange(int)),\
            &vorschaufenster, SLOT(slot_aktives_Element_einfaerben(int)));
    connect(&vorschaufenster, SIGNAL(sende_zeilennummer(uint, bool)),\
            this, SLOT(slot_zeilennummer(uint, bool)));
    connect(&vorschaufenster, SIGNAL(sende_maus_pos(QPoint)),\
            this, SLOT(getMausPosXY(QPoint)));
    this->setWindowFlags(Qt::Window);
    this->setWindowState(Qt::WindowMaximized);
}

MainWin_wst_bearbeiten::~MainWin_wst_bearbeiten()
{
    delete ui;
}

void MainWin_wst_bearbeiten::clear()
{
    Wst = nullptr;
    ui->listWidget_prgtext->clear();
}

void MainWin_wst_bearbeiten::resizeEvent(QResizeEvent *event)
{
    vorschaufenster.setParent(this);
    vorschaufenster.move(5,25);
    vorschaufenster.setFixedWidth(this->width()-400-25);
    vorschaufenster.setFixedHeight(this->height()-50);
    //----------------------
    ui->listWidget_prgtext->move(vorschaufenster.pos().x()+vorschaufenster.width()+5, 5);
    ui->listWidget_prgtext->setFixedWidth(400);
    ui->listWidget_prgtext->setFixedHeight(this->height());
    //----------------------
    ui->label_xypos->move(ui->listWidget_prgtext->pos().x(),\
                          ui->listWidget_prgtext->pos().y() + ui->listWidget_prgtext->height()+2);
    ui->label_xypos->setFixedWidth(ui->listWidget_prgtext->width());
}

void MainWin_wst_bearbeiten::getMausPosXY(QPoint p)
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

void MainWin_wst_bearbeiten::set_wst(werkstueck *w)
{
    clear();
    Wst = w;
    update_listwidget();
    ui->listWidget_prgtext->setCurrentRow(ui->listWidget_prgtext->count()-1);
    sendVorschauAktualisieren(*Wst, 0);
}

void MainWin_wst_bearbeiten::update_listwidget()
{
    ui->listWidget_prgtext->clear();
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

void MainWin_wst_bearbeiten::slot_zeilennummer(uint nr, bool bearbeiten)
{
    if((int)nr < ui->listWidget_prgtext->count())
    {
        ui->listWidget_prgtext->item(nr-1)->setSelected(true);
        if(bearbeiten == true)
        {
            zeile_bearbeiten(nr-1);
        }
    }
}

void MainWin_wst_bearbeiten::on_listWidget_prgtext_currentRowChanged(int currentRow)
{
    emit signalIndexChange(currentRow+1);
}

void MainWin_wst_bearbeiten::on_listWidget_prgtext_itemDoubleClicked(QListWidgetItem *item)
{
    int index = ui->listWidget_prgtext->currentRow();
    zeile_bearbeiten(index);
}

void MainWin_wst_bearbeiten::zeile_bearbeiten(int zeile)
{
    if(zeile == 0)
    {
        Dialog_bearb_pkopf dlg;
        dlg.setModal(true);
        dlg.set_data(Wst);
        dlg.exec();
        emit sendVorschauAktualisieren(*Wst, 0);
        return;
    }
    //Zeile Auslesen:
    text_zeilenweise bearb;
    bearb.set_trennzeichen(TRENNZ_BEARB_PARAM);
    bearb.set_text(Wst->bearb_ptr()->zeile(zeile));
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
    }else if(bearb.zeile(1) == BEARBART_FRAESERAUFRUF)
    {
        Dialog_bearb_faufruf dlg;
        dlg.setModal(true);
        connect(&dlg, SIGNAL(signal_faufruf(fraueseraufruf)), this, SLOT(slot_faufruf(fraueseraufruf)));
        dlg.set_data(bearb.text());
        dlg.exec();
    }else if(bearb.zeile(1) == BEARBART_FRAESERGERADE)
    {
        Dialog_bearb_fgerade dlg;
        dlg.setModal(true);
        connect(&dlg, SIGNAL(signal_fgerade(fraesergerade)), this, SLOT(slot_fgerade(fraesergerade)));
        dlg.set_data(bearb.text());
        dlg.exec();
    }else if(bearb.zeile(1) == BEARBART_FRAESERBOGEN)
    {
        Dialog_bearb_fbogen dlg;
        dlg.setModal(true);
        connect(&dlg, SIGNAL(signal_fbogen(fraeserbogen)), this, SLOT(slot_fbogen(fraeserbogen)));
        dlg.set_data(bearb.text());
        dlg.exec();
    }
}

void MainWin_wst_bearbeiten::slot_rta(rechtecktasche rta)
{
    int index = ui->listWidget_prgtext->currentRow();
    //Werte zurück speichern:
    QString zeile;
    zeile = rta.text();
    ui->listWidget_prgtext->item(index)->setText(rta_zu_prgeile(zeile));

    text_zeilenweise bearbeitungen = Wst->bearb();
    bearbeitungen.zeile_ersaetzen(index, zeile);
    Wst->bearb_ptr()->zeile_ersaetzen(index, bearbeitungen.zeile(index));
    emit sendVorschauAktualisieren(*Wst, index+1);
}
void MainWin_wst_bearbeiten::slot_bo(bohrung bo)
{
    int index = ui->listWidget_prgtext->currentRow();
    //Werte zurück speichern:
    QString zeile;
    zeile = bo.text();
    ui->listWidget_prgtext->item(index)->setText(bohr_zu_prgeile(zeile));

    text_zeilenweise bearbeitungen = Wst->bearb();
    bearbeitungen.zeile_ersaetzen(index, zeile);
    Wst->bearb_ptr()->zeile_ersaetzen(index, bearbeitungen.zeile(index));
    emit sendVorschauAktualisieren(*Wst, index+1);
}
void MainWin_wst_bearbeiten::slot_nut(nut nu)
{
    int index = ui->listWidget_prgtext->currentRow();
    //Werte zurück speichern:
    QString zeile;
    zeile = nu.text();
    ui->listWidget_prgtext->item(index)->setText(nut_zu_prgeile(zeile));

    text_zeilenweise bearbeitungen = Wst->bearb();
    bearbeitungen.zeile_ersaetzen(index, zeile);
    Wst->bearb_ptr()->zeile_ersaetzen(index, bearbeitungen.zeile(index));
    emit sendVorschauAktualisieren(*Wst, index+1);
}
void MainWin_wst_bearbeiten::slot_faufruf(fraueseraufruf fa)
{
    int index = ui->listWidget_prgtext->currentRow();
    //Werte zurück speichern:
    QString zeile;
    zeile = fa.text();
    ui->listWidget_prgtext->item(index)->setText(fauf_zu_prgeile(zeile));

    text_zeilenweise bearbeitungen = Wst->bearb();
    bearbeitungen.zeile_ersaetzen(index, zeile);
    Wst->bearb_ptr()->zeile_ersaetzen(index, bearbeitungen.zeile(index));
    emit sendVorschauAktualisieren(*Wst, index+1);
}
void MainWin_wst_bearbeiten::slot_fgerade(fraesergerade fg)
{
    int index = ui->listWidget_prgtext->currentRow();
    //Werte zurück speichern:
    QString zeile;
    zeile = fg.text();
    ui->listWidget_prgtext->item(index)->setText(fgerade_zu_prgeile(zeile));

    text_zeilenweise bearbeitungen = Wst->bearb();
    bearbeitungen.zeile_ersaetzen(index, zeile);
    Wst->bearb_ptr()->zeile_ersaetzen(index, bearbeitungen.zeile(index));
    emit sendVorschauAktualisieren(*Wst, index+1);
}
void MainWin_wst_bearbeiten::slot_fbogen(fraeserbogen fb)
{
    int index = ui->listWidget_prgtext->currentRow();
    //Werte zurück speichern:
    QString zeile;
    zeile = fb.text();
    ui->listWidget_prgtext->item(index)->setText(fbogen_zu_prgeile(zeile));

    text_zeilenweise bearbeitungen = Wst->bearb();
    bearbeitungen.zeile_ersaetzen(index, zeile);
    Wst->bearb_ptr()->zeile_ersaetzen(index, bearbeitungen.zeile(index));
    emit sendVorschauAktualisieren(*Wst, index+1);
}

//----------------------------------Make:
void MainWin_wst_bearbeiten::on_actionMakeBohrung_triggered()
{
    Dialog_bearb_bohrung dlg;
    dlg.setModal(true);
    bohrung bo;//Default-Daten
    dlg.set_data(bo.text());
    connect(&dlg, SIGNAL(signal_bo(bohrung)), this, SLOT(slot_make_bo(bohrung)));
    dlg.exec();
}
void MainWin_wst_bearbeiten::on_actionMakeRTA_triggered()
{
    Dialog_bearb_rta dlg;
    dlg.setModal(true);
    rechtecktasche rt;//Default-Daten
    dlg.set_data(rt.text());
    connect(&dlg, SIGNAL(signal_rta(rechtecktasche)), this, SLOT(slot_make_rta(rechtecktasche)));
    dlg.exec();
}
void MainWin_wst_bearbeiten::on_actionMakeNut_triggered()
{
    Dialog_bearb_nut dlg;
    dlg.setModal(true);
    nut nu;//Default-Daten
    dlg.set_data(nu.text());
    connect(&dlg, SIGNAL(signal_nut(nut)), this, SLOT(slot_make_nut(nut)));
    dlg.exec();
}
//----------------------------------Slot_Make:
void MainWin_wst_bearbeiten::slot_make(QString bearb)
{
    int index = ui->listWidget_prgtext->currentRow();
    //Werte zurück speichern:
    if(index == 0)
    {
        Wst->bearb_ptr()->zeile_vorwegsetzen(bearb);
    }else if(index+1 < ui->listWidget_prgtext->count())
    {
        Wst->bearb_ptr()->zeile_einfuegen(index-1, bearb);
    }else
    {
        Wst->bearb_ptr()->zeile_anhaengen(bearb);
    }
    update_listwidget();
    emit sendVorschauAktualisieren(*Wst, index);
}
void MainWin_wst_bearbeiten::slot_make_bo(bohrung bo)
{
    slot_make(bo.text());
}
void MainWin_wst_bearbeiten::slot_make_rta(rechtecktasche rt)
{
    slot_make(rt.text());
}
void MainWin_wst_bearbeiten::slot_make_nut(nut nu)
{
    slot_make(nu.text());
}
//----------------------------------




