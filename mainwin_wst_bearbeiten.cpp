#include "mainwin_wst_bearbeiten.h"
#include "ui_mainwin_wst_bearbeiten.h"

MainWin_wst_bearbeiten::MainWin_wst_bearbeiten(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin_wst_bearbeiten)
{
    ui->setupUi(this);
    clear();

    vorschaufenster.set_bearb_erlaubt(true);
    vorschaufenster.set_modus_einzel_wst(true);

    connect(this, SIGNAL(sendVorschauAktualisieren(werkstueck,int, wkz_magazin)),\
            &vorschaufenster, SLOT(slot_aktualisieren_einzelwst(werkstueck,int, wkz_magazin)));
    connect(this, SIGNAL(signalIndexChange(int)),\
            &vorschaufenster, SLOT(slot_aktives_Element_einfaerben(int)));
    connect(&vorschaufenster, SIGNAL(sende_zeilennummer(uint, bool)),\
            this, SLOT(slot_zeilennummer(uint, bool)));
    connect(&vorschaufenster, SIGNAL(sende_maus_pos(QPoint)),\
            this, SLOT(getMausPosXY(QPoint)));
    connect(&dlg_dt, SIGNAL(send_dlg_einstellung(QString,double,double,bool,bool)),\
            this, SLOT(slot_dt_erzeugen(QString,double,double,bool,bool)));

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
    Wkz_ptr = nullptr;
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
    ui->listWidget_prgtext->setFixedHeight(this->height()-70);
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
    unredo_clear();
    sendVorschauAktualisieren(*Wst, -1, Wkz_kopie);
    letzte_wst_l = Wst->laenge();
    letzte_wst_b = Wst->breite();
    letzte_wst_d = Wst->dicke();
    unredo_neu();
}
void MainWin_wst_bearbeiten::set_wkz(wkz_magazin *w)
{
    Wkz_ptr = w;
    Wkz_kopie = Wkz_ptr->magazin();
}

void MainWin_wst_bearbeiten::update_listwidget()
{
    int currentRow = ui->listWidget_prgtext->currentRow();
    ui->listWidget_prgtext->clear();
    //Programmkopf als erste Zeile einfügen:
    text_zw pkopf;
    pkopf.set_trenz(TRENNZ_BEARB_PARAM);
    QString param;
    param  = "L=";
    param += Wst->laenge_qstring();
    pkopf.add_hi(param);
    param  = "B=";
    param += Wst->breite_qstring();
    pkopf.add_hi(param);
    param  = "D=";
    param += Wst->dicke_qstring();
    pkopf.add_hi(param);
    param = "KaVo=";
    param += Wst->kante_vo();
    pkopf.add_hi(param);
    param = "KaHi=";
    param += Wst->kante_hi();
    pkopf.add_hi(param);
    param = "KaLi=";
    param += Wst->kante_li();
    pkopf.add_hi(param);
    param = "KaRe=";
    param += Wst->kante_re();
    pkopf.add_hi(param);
    ui->listWidget_prgtext->addItem(pkopf.text());
    //Bearbeitungen ab 2. Zeile einfügen:
    text_zw tmp_bearb = Wst->bearb();
    for(uint i=0; i<tmp_bearb.count() ;i++)
    {
        QString bearb = tmp_bearb.at(i);
        text_zw zeile;
        zeile.set_text(bearb,TRENNZ_BEARB_PARAM);
        QColor farbe;
        farbe.setRgb(255,255,255);
        int deckkraft = 160;
        QString bezug = zeile.at(1);
        if(zeile.at(0) == BEARBART_BOHR)
        {
            bearb = bohr_zu_prgzei(zeile.text());
            if(bezug == WST_BEZUG_OBSEI)
            {
                farbe.setRgb(0,240,240,deckkraft); //Hellblau
            }else if(bezug == WST_BEZUG_UNSEI)
            {
                farbe.setRgb(255,0,128,deckkraft);//Rose
            }else
            {
                farbe.setRgb(185,122,87,deckkraft);//braun
            }
        }else if(zeile.at(0) == BEARBART_BOHRRASTER)
        {
            bearb = bohrRaster_zu_prgzei(zeile.text());
        }else if(zeile.at(0) == BEARBART_NUT)
        {
            bearb = nut_zu_prgzei(zeile.text());
            farbe.setRgb(145,145,255,deckkraft);//helles lila
        }else if(zeile.at(0) == BEARBART_RTA)
        {
            bearb = rta_zu_prgzei(zeile.text());
            if(bezug == WST_BEZUG_OBSEI || bezug == WST_BEZUG_UNSEI)
            {
                farbe = Qt::darkGray;
                farbe.setAlpha(deckkraft);
            }else
            {
                farbe = Qt::green;
                farbe.setAlpha(deckkraft);
            }
        }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
        {
            bearb = fauf_zu_prgzei(zeile.text());
            farbe.setRgb(255,128,0,deckkraft);//orange
        }else if(zeile.at(0) == BEARBART_FRAESERGERADE)
        {
            bearb = fgerade_zu_prgzei(zeile.text());
            farbe.setRgb(255,155,106,deckkraft);//helles orange
        }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
        {
            bearb = fbogen_zu_prgzei(zeile.text());
            farbe.setRgb(255,155,106,deckkraft);//helles orange
        }else if(zeile.at(0) == BEARBART_GEHRUNG)
        {
            bearb = gehr_zu_prgzei(zeile.text());
        }
        ui->listWidget_prgtext->addItem(bearb);
        ui->listWidget_prgtext->item(i+1)->setBackgroundColor(farbe);
    }
    ui->listWidget_prgtext->addItem("...");
    if(currentRow < ui->listWidget_prgtext->count())
    {
        ui->listWidget_prgtext->setCurrentRow(currentRow);
    }
}
void MainWin_wst_bearbeiten::slot_zeilennummer(uint nr, bool bearbeiten)
{
    if((int)nr < ui->listWidget_prgtext->count())
    {
        ui->listWidget_prgtext->setCurrentRow(nr);
        if(bearbeiten == true)
        {
            zeile_bearbeiten(nr);
        }
    }
}
void MainWin_wst_bearbeiten::on_listWidget_prgtext_currentRowChanged(int currentRow)
{
    for(int i=0; i<ui->listWidget_prgtext->count();i++)
    {
        ui->listWidget_prgtext->item(i)->setTextColor(Qt::black);
        QFont font;
        font.setBold(false);
        //font.setPointSize(10);
        ui->listWidget_prgtext->item(i)->setFont(font);
    }
    if(currentRow >=0 && currentRow < ui->listWidget_prgtext->count())
    {
        ui->listWidget_prgtext->item(currentRow)->setTextColor(Qt::red);
        QFont font;
        font.setBold(true);
        //font.setPointSize(11);
        ui->listWidget_prgtext->item(currentRow)->setFont(font);
    }
    emit signalIndexChange(currentRow);
}
void MainWin_wst_bearbeiten::on_listWidget_prgtext_itemDoubleClicked(QListWidgetItem *item)
{
    int index = ui->listWidget_prgtext->currentRow();
    zeile_bearbeiten(index);
}
void MainWin_wst_bearbeiten::on_actionBearbeiten_triggered()
{
    int index = ui->listWidget_prgtext->currentRow();
    zeile_bearbeiten(index);
}
void MainWin_wst_bearbeiten::zeile_bearbeiten(int zeile)
{
    if(zeile == 0)
    {
        letzte_wst_l = Wst->laenge();
        letzte_wst_b = Wst->breite();
        letzte_wst_d = Wst->dicke();
        Dialog_bearb_pkopf dlg;
        dlg.setModal(true);
        dlg.set_data(Wst);
        dlg.exec();
        text_zw bearb_alt = Wst->bearb();
        text_zw bearb_neu;
        for (uint i = 0; i<bearb_alt.count() ; i++)
        {
            if(i==0)
            {
                bearb_neu.set_text(verschiebe_einen(bearb_alt.at(i), 0, 0, 0), bearb_alt.trennz());
                //0,0,0 verschiebt die bearb auf die Wst-kanten
            }else
            {
                bearb_neu.add_hi(verschiebe_einen(bearb_alt.at(i), 0, 0, 0));
                //0,0,0 verschiebt die bearb auf die Wst-kanten
            }
        }
        Wst->set_bearb(bearb_neu);
        unredo_neu();
        update_listwidget();        
        emit sendVorschauAktualisieren(*Wst, 0, Wkz_kopie);
        return;
    }
    //Zeile Auslesen:
    text_zw bearb;
    bearb.set_text(Wst->bearb_ptr()->at(zeile-1),TRENNZ_BEARB_PARAM);
    //Dialogfenster aufrufen:
    if(bearb.at(0) == BEARBART_RTA)
    {
        Dialog_bearb_rta dlg;
        dlg.setModal(true);
        connect(&dlg, SIGNAL(signal_rta(rechtecktasche)), this, SLOT(slot_rta(rechtecktasche)));
        dlg.set_data(bearb.text(), Wst, Wkz_kopie.magazin());
        dlg.exec();
    }else if(bearb.at(0) == BEARBART_BOHR)
    {
        Dialog_bearb_bohrung dlg;
        dlg.setModal(true);
        connect(&dlg, SIGNAL(signal_bo(bohrung)), this, SLOT(slot_bo(bohrung)));
        dlg.set_data(bearb.text(), Wst, Wkz_kopie.magazin());
        dlg.exec();
    }else if(bearb.at(0) == BEARBART_NUT)
    {
        Dialog_bearb_nut dlg;
        dlg.setModal(true);
        connect(&dlg, SIGNAL(signal_nut(nut)), this, SLOT(slot_nut(nut)));
        dlg.set_data(bearb.text(), Wst);
        dlg.exec();
    }else if(bearb.at(0) == BEARBART_FRAESERAUFRUF)
    {
        Dialog_bearb_faufruf dlg;
        dlg.setModal(true);
        connect(&dlg, SIGNAL(signal_faufruf(fraeseraufruf)), this, SLOT(slot_faufruf(fraeseraufruf)));
        dlg.set_data(bearb.text(), Wst, Wkz_kopie.magazin());
        dlg.exec();
    }else if(bearb.at(0) == BEARBART_FRAESERGERADE)
    {
        Dialog_bearb_fgerade dlg;
        dlg.setModal(true);
        connect(&dlg, SIGNAL(signal_fgerade(fraesergerade)), this, SLOT(slot_fgerade(fraesergerade)));
        dlg.set_data(bearb.text(), Wst);
        dlg.exec();
    }else if(bearb.at(0) == BEARBART_FRAESERBOGEN)
    {
        Dialog_bearb_fbogen dlg;
        dlg.setModal(true);
        connect(&dlg, SIGNAL(signal_fbogen(fraeserbogen)), this, SLOT(slot_fbogen(fraeserbogen)));
        dlg.set_data(bearb.text(), Wst);
        dlg.exec();
    }
}

void MainWin_wst_bearbeiten::zeile_aendern(int index, QString bearb, bool unredor_verwenden)
{
    //index ist der index der Bearbeitung
    //bearb ist eine Zeile der Bearbeitugen
    text_zw bearbeitungen = Wst->bearb();
    bearbeitungen.edit(index, bearb);
    Wst->bearb_ptr()->edit(index, bearbeitungen.at(index));
    if(unredor_verwenden == true)
    {
        unredo_neu();
    }
    update_listwidget();
    emit sendVorschauAktualisieren(*Wst, index+1, Wkz_kopie);
}
void MainWin_wst_bearbeiten::slot_rta(rechtecktasche rta)
{
    int index = ui->listWidget_prgtext->currentRow()-1;//Index-1 weil 1. Zeile WST-Maße sind
    QString bearb = rta.text();
    ui->listWidget_prgtext->item(index)->setText(rta_zu_prgzei(bearb));
    zeile_aendern(index, bearb, true);
}
void MainWin_wst_bearbeiten::slot_bo(bohrung bo)
{
    int index = ui->listWidget_prgtext->currentRow()-1;//Index-1 weil 1. Zeile WST-Maße sind
    QString bearb = bo.text();
    ui->listWidget_prgtext->item(index)->setText(bohr_zu_prgzei(bearb));
    zeile_aendern(index, bearb, true);
}
void MainWin_wst_bearbeiten::slot_nut(nut nu)
{
    int index = ui->listWidget_prgtext->currentRow()-1;//Index-1 weil 1. Zeile WST-Maße sind
    QString bearb = nu.text();
    ui->listWidget_prgtext->item(index)->setText(nut_zu_prgzei(bearb));
    zeile_aendern(index, bearb, true);
}
void MainWin_wst_bearbeiten::slot_faufruf(fraeseraufruf fa)
{
    int index = ui->listWidget_prgtext->currentRow()-1;//Index-1 weil 1. Zeile WST-Maße sind
    QString bearb = fa.text();
    ui->listWidget_prgtext->item(index)->setText(fauf_zu_prgzei(bearb));
    text_zw bearbeitungen = Wst->bearb();
    //Folgezeile mit ändern?:
    if(index+1 < bearbeitungen.count())
    {
        text_zw bearb_nach;
        bearb_nach.set_text(bearbeitungen.at(index+1),TRENNZ_BEARB_PARAM);
        if(bearb_nach.at(0) == BEARBART_FRAESERGERADE)
        {
            fraesergerade fg_nach(bearb_nach.text());
            fg_nach.set_startpunkt(fa.pos());
            zeile_aendern(index+1, fg_nach.text(), false);
        }else if(bearb_nach.at(0) == BEARBART_FRAESERBOGEN)
        {
            fraeserbogen fb_nach(bearb_nach.text());
            fb_nach.set_startpunkt(fa.pos());
            zeile_aendern(index+1, fb_nach.text(), false);
        }
    }
    //Bezug mit ändern?:
    fraeseraufruf fa_alt;
    fa_alt.set_text(bearbeitungen.at(index));
    if(fa_alt.bezug() != fa.bezug())
    {
        for(uint i=index+1; i<bearbeitungen.count() ;i++)
        {
            text_zw bearb_ff;
            bearb_ff.set_text(bearbeitungen.at(i),TRENNZ_BEARB_PARAM);
            if(bearb_ff.at(0) == BEARBART_FRAESERGERADE)
            {
                fraesergerade fg(bearb_ff.text());
                fg.set_bezug(fa.bezug());
                zeile_aendern(i, fg.text(), false);
            }else if(bearb_ff.at(0) == BEARBART_FRAESERBOGEN)
            {
                fraeserbogen fb(bearb_ff.text());
                fb.set_uzs(!fb.uzs());
                fb.set_bezug(fa.bezug());
                zeile_aendern(i, fb.text(), false);
            }else
            {
                break;//for
            }
        }
    }
    zeile_aendern(index, bearb, true);
}
void MainWin_wst_bearbeiten::slot_fgerade(fraesergerade fg)
{
    int index = ui->listWidget_prgtext->currentRow()-1;//Index-1 weil 1. Zeile WST-Maße sind
    QString bearb = fg.text();
    ui->listWidget_prgtext->item(index)->setText(fgerade_zu_prgzei(bearb));
    text_zw bearbeitungen = Wst->bearb();
    //Zeile davor mit ändern?:
    if(index-1 >=0)
    {
        text_zw bearb_vor;
        bearb_vor.set_text(bearbeitungen.at(index-1),TRENNZ_BEARB_PARAM);
        if(bearb_vor.at(0) == BEARBART_FRAESERAUFRUF)
        {
            fraeseraufruf fa_vor(bearb_vor.text());
            fa_vor.set_pos(fg.sp());
            zeile_aendern(index-1, fa_vor.text(), false);
        }else if(bearb_vor.at(0) == BEARBART_FRAESERGERADE)
        {
            fraesergerade fg_vor(bearb_vor.text());
            fg_vor.set_endpunkt(fg.sp());
            zeile_aendern(index-1, fg_vor.text(), false);
        }else if(bearb_vor.at(0) == BEARBART_FRAESERBOGEN)
        {
            fraeserbogen fb_vor(bearb_vor.text());
            fb_vor.set_endpunkt(fg.sp());
            zeile_aendern(index-1, fb_vor.text(), false);
        }
    }
    //Folgezeile mit ändern?:
    if(index+1 < bearbeitungen.count())
    {
        text_zw bearb_nach;
        bearb_nach.set_text(bearbeitungen.at(index+1),TRENNZ_BEARB_PARAM);
        if(bearb_nach.at(0) == BEARBART_FRAESERGERADE)
        {
            fraesergerade fg_nach(bearb_nach.text());
            fg_nach.set_startpunkt(fg.ep());
            zeile_aendern(index+1, fg_nach.text(), false);
        }else if(bearb_nach.at(0) == BEARBART_FRAESERBOGEN)
        {
            fraeserbogen fb_nach(bearb_nach.text());
            fb_nach.set_startpunkt(fg.ep());
            zeile_aendern(index+1, fb_nach.text(), false);
        }
    }
    zeile_aendern(index, bearb, true);
}
void MainWin_wst_bearbeiten::slot_fbogen(fraeserbogen fb)
{
    int index = ui->listWidget_prgtext->currentRow()-1;//Index-1 weil 1. Zeile WST-Maße sind
    QString bearb = fb.text();
    ui->listWidget_prgtext->item(index)->setText(fbogen_zu_prgzei(bearb));
    text_zw bearbeitungen = Wst->bearb();
    //Zeile davor mit ändern?:
    if(index-1 >=0)
    {
        text_zw bearb_vor;
        bearb_vor.set_text(bearbeitungen.at(index-1),TRENNZ_BEARB_PARAM);
        if(bearb_vor.at(0) == BEARBART_FRAESERAUFRUF)
        {
            fraeseraufruf fa_vor(bearb_vor.text());
            fa_vor.set_pos(fb.sp());
            zeile_aendern(index-1, fa_vor.text(), false);
        }else if(bearb_vor.at(0) == BEARBART_FRAESERGERADE)
        {
            fraesergerade fg_vor(bearb_vor.text());
            fg_vor.set_endpunkt(fb.sp());
            zeile_aendern(index-1, fg_vor.text(), false);
        }else if(bearb_vor.at(0) == BEARBART_FRAESERBOGEN)
        {
            fraeserbogen fb_vor(bearb_vor.text());
            fb_vor.set_endpunkt(fb.sp());
            zeile_aendern(index-1, fb_vor.text(), false);
        }
    }
    //Folgezeile mit ändern?:
    if(index+1 < bearbeitungen.count())
    {
        text_zw bearb_nach;
        bearb_nach.set_text(bearbeitungen.at(index+1),TRENNZ_BEARB_PARAM);
        if(bearb_nach.at(0) == BEARBART_FRAESERGERADE)
        {
            fraesergerade fg_nach(bearb_nach.text());
            fg_nach.set_startpunkt(fb.ep());
            zeile_aendern(index+1, fg_nach.text(), false);
        }else if(bearb_nach.at(0) == BEARBART_FRAESERBOGEN)
        {
            fraeserbogen fb_nach(bearb_nach.text());
            fb_nach.set_startpunkt(fb.ep());
            zeile_aendern(index+1, fb_nach.text(), false);
        }
    }
    zeile_aendern(index, bearb, true);
}

//----------------------------------Make:
void MainWin_wst_bearbeiten::on_actionMakeBohrung_triggered()
{
    Dialog_bearb_bohrung dlg;
    dlg.setModal(true);
    bohrung bo;//Default-Daten
    dlg.set_data(bo.text(), Wst, Wkz_kopie.magazin());
    connect(&dlg, SIGNAL(signal_bo(bohrung)), this, SLOT(slot_make_bo(bohrung)));
    dlg.exec();
}
void MainWin_wst_bearbeiten::on_actionMakeRTA_triggered()
{
    Dialog_bearb_rta dlg;
    dlg.setModal(true);
    rechtecktasche rt;//Default-Daten
    dlg.set_data(rt.text(), Wst, Wkz_kopie.magazin());
    connect(&dlg, SIGNAL(signal_rta(rechtecktasche)), this, SLOT(slot_make_rta(rechtecktasche)));
    dlg.exec();
}
void MainWin_wst_bearbeiten::on_actionMakeNut_triggered()
{
    Dialog_bearb_nut dlg;
    dlg.setModal(true);
    nut nu;//Default-Daten
    dlg.set_data(nu.text(), Wst);
    connect(&dlg, SIGNAL(signal_nut(nut)), this, SLOT(slot_make_nut(nut)));
    dlg.exec();
}
//----------------------------------Slot_Make:
void MainWin_wst_bearbeiten::slot_make(QString bearb, bool unredor_verwenden)
{
    int index = ui->listWidget_prgtext->currentRow();
    //Werte zurück speichern:
    if(index == 0)
    {
        Wst->bearb_ptr()->add_vo(bearb);
    }else if(index+1 < ui->listWidget_prgtext->count())
    {
        Wst->bearb_ptr()->add_mi(index, bearb);
    }else
    {
        Wst->bearb_ptr()->add_hi(bearb);
    }
    update_listwidget();
    if(unredor_verwenden == true)
    {
        unredo_neu();
    }
    emit sendVorschauAktualisieren(*Wst, index, Wkz_kopie);
}
void MainWin_wst_bearbeiten::slot_make_bo(bohrung bo)
{
    slot_make(bo.text(), true);
}
void MainWin_wst_bearbeiten::slot_make_rta(rechtecktasche rt)
{
    slot_make(rt.text(), true);
}
void MainWin_wst_bearbeiten::slot_make_nut(nut nu)
{
    slot_make(nu.text(), true);
}
//----------------------------------Bearbeiten:
void MainWin_wst_bearbeiten::on_actionUndo_triggered()
{
    Wst->set_laenge(UnReDo_L.undo());
    Wst->set_breite(UnReDo_B.undo());
    Wst->set_dicke(UnReDo_D.undo());
    Wst->set_bearb(UnReDo.undo());
    update_listwidget();
    ui->listWidget_prgtext->setCurrentRow(ui->listWidget_prgtext->count()-1);
    sendVorschauAktualisieren(*Wst, ui->listWidget_prgtext->count()-1, Wkz_kopie);
}
void MainWin_wst_bearbeiten::on_actionRedo_triggered()
{
    Wst->set_laenge(UnReDo_L.redo());
    Wst->set_breite(UnReDo_B.redo());
    Wst->set_dicke(UnReDo_D.redo());
    Wst->set_bearb(UnReDo.redo());
    update_listwidget();
    ui->listWidget_prgtext->setCurrentRow(ui->listWidget_prgtext->count()-1);
    sendVorschauAktualisieren(*Wst, 0, Wkz_kopie);
}
void MainWin_wst_bearbeiten::on_actionEntf_triggered()
{
    int index_liwid = ui->listWidget_prgtext->currentRow();
    int index_bearb = index_liwid-1;
    if((ui->listWidget_prgtext->currentIndex().isValid())  &&  \
       (ui->listWidget_prgtext->currentItem()->isSelected())    )
    {        
        QList<QListWidgetItem*> items = ui->listWidget_prgtext->selectedItems();
        int items_menge = items.count();
        int row_erstes_liwid = 0;//Nummer des ersten Elementes
        for(int i=0; i<ui->listWidget_prgtext->count() ;i++)
        {
            if(ui->listWidget_prgtext->item(i)->isSelected())
            {
                row_erstes_liwid = i;
                break;
            }
        }
        int row_erstes_bearb = row_erstes_liwid-1;
        if(items_menge==1)
        {
            if(index_liwid > 0  &&  index_liwid+1 < ui->listWidget_prgtext->count())
            {
                if(index_bearb > 0)
                {
                    text_zw zeile;
                    zeile.set_text(Wst->bearb().at(index_bearb),TRENNZ_BEARB_PARAM);
                    text_zw zeile_vor;
                    zeile_vor.set_text(Wst->bearb().at(index_bearb-1),TRENNZ_BEARB_PARAM);
                    if(zeile_vor.at(0) == BEARBART_FRAESERAUFRUF)
                    {
                        fraeseraufruf fa(zeile_vor.text());
                        if(zeile.at(0) == BEARBART_FRAESERGERADE)
                        {
                            fraesergerade fg(zeile.text());
                            fa.set_pos(fg.ep());
                            Wst->bearb_ptr()->edit(index_bearb-1, fa.text());
                            fraeseraufruf fa(zeile_vor.text());
                        }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
                        {
                            fraeserbogen fb(zeile.text());
                            fa.set_pos(fb.ep());
                            Wst->bearb_ptr()->edit(index_bearb-1, fa.text());
                        }
                    }
                }
                Wst->bearb_ptr()->entf(index_bearb);
                update_listwidget();
                unredo_neu();
                ui->listWidget_prgtext->setCurrentRow(index_liwid);
                emit sendVorschauAktualisieren(*Wst, index_liwid, Wkz_kopie);
            }
        }else
        {
            if(row_erstes_liwid == 0)//Programmkopf
            {
                row_erstes_liwid = 1;
                row_erstes_bearb = row_erstes_liwid-1;
                items_menge = items_menge-1;
            }
            if(row_erstes_liwid+items_menge >= ui->listWidget_prgtext->count())
            {
                items_menge = ui->listWidget_prgtext->count()-row_erstes_liwid-1;
            }
            Wst->bearb_ptr()->entf(row_erstes_bearb, items_menge);
            update_listwidget();
            unredo_neu();
            ui->listWidget_prgtext->setCurrentRow(row_erstes_liwid);
            emit sendVorschauAktualisieren(*Wst, row_erstes_liwid, Wkz_kopie);
        }
    } else
    {
        QMessageBox mb;
        mb.setText("Sie haben noch nichts ausgewaelt was entfernt werden kann!");
        mb.exec();
    }
}
void MainWin_wst_bearbeiten::on_actionKopieren_triggered()
{
    int index_liwid = ui->listWidget_prgtext->currentRow();
    int index_bearb = index_liwid-1;
    if((ui->listWidget_prgtext->currentIndex().isValid())  &&  \
       (ui->listWidget_prgtext->currentItem()->isSelected())    )
    {
        QList<QListWidgetItem*> items = ui->listWidget_prgtext->selectedItems();
        int items_menge = items.count();
        int row_erstes_liwid = 0;//Nummer des ersten Elementes
        for(int i=0; i<ui->listWidget_prgtext->count() ;i++)
        {
            if(ui->listWidget_prgtext->item(i)->isSelected())
            {
                row_erstes_liwid = i;
                break;
            }
        }
        int row_erstes_bearb = row_erstes_liwid-1;
        if(items_menge==1)
        {
            if(index_liwid > 0  &&  index_liwid+1 < ui->listWidget_prgtext->count())
            {
                KopierterEintrag = Wst->bearb_ptr()->at(index_bearb);
            }
        }else
        {
            if(row_erstes_liwid == 0)//Programmkopf
            {
                row_erstes_liwid = 1;
                row_erstes_bearb = row_erstes_liwid-1;
                items_menge = items_menge-1;
            }
            if(row_erstes_liwid+items_menge >= ui->listWidget_prgtext->count())
            {
                items_menge = ui->listWidget_prgtext->count()-row_erstes_liwid-1;
            }
            QString tmp = Wst->bearb_ptr()->at(row_erstes_bearb, items_menge);
            KopierterEintrag = tmp;
        }
    }else
    {
        QMessageBox mb;
        mb.setText("Sie haben noch nichts ausgewaelt was kopiert werden kann!");
        mb.exec();
    }
}
void MainWin_wst_bearbeiten::on_actionEinfuegen_triggered()
{
    if(!KopierterEintrag.isEmpty())
    {
        int index_liwid = ui->listWidget_prgtext->currentRow();
        if(index_liwid == 0)//Programmkopf
        {
            index_liwid = 1;
        }
        if(index_liwid == 1)
        {
            Wst->bearb_ptr()->add_vo(KopierterEintrag);
        }else if(index_liwid == ui->listWidget_prgtext->count()-1)
        {
            Wst->bearb_ptr()->add_hi(KopierterEintrag);
        }else
        {
            Wst->bearb_ptr()->add_mi(index_liwid-2, KopierterEintrag);
        }
        update_listwidget();
        unredo_neu();
        ui->listWidget_prgtext->setCurrentRow(index_liwid);
        emit sendVorschauAktualisieren(*Wst, index_liwid, Wkz_kopie);
    }
}
void MainWin_wst_bearbeiten::unredo_neu()
{
    UnReDo_L.neu((Wst->laenge()));
    UnReDo_B.neu(Wst->breite());
    UnReDo_D.neu(Wst->dicke());
    UnReDo.neu(Wst->bearb());
}
void MainWin_wst_bearbeiten::unredo_clear()
{
    UnReDo_L.clear();
    UnReDo_B.clear();
    UnReDo_D.clear();
    UnReDo.clear();
}
//----------------------------------Manipulation:
int MainWin_wst_bearbeiten::auswahl_erster()
{
    QList<QListWidgetItem*> items = ui->listWidget_prgtext->selectedItems();
    int row_erstes = 0;//Nummer des ersten Elementes
    for(int i=0; i<ui->listWidget_prgtext->count() ;i++)
    {
        if(ui->listWidget_prgtext->item(i)->isSelected())
        {
            row_erstes = i;
            break;
        }
    }
    return row_erstes;
}
int MainWin_wst_bearbeiten::auswahl_letzter()
{
    int erster = auswahl_erster();
    int menge = auswahl_menge();
    return erster+menge-1;
}
int MainWin_wst_bearbeiten::auswahl_menge()
{
    QList<QListWidgetItem*> items = ui->listWidget_prgtext->selectedItems();
    return items.count();
}
void MainWin_wst_bearbeiten::on_actionVerschieben_triggered()
{
    if((ui->listWidget_prgtext->currentIndex().isValid())  &&  \
       (ui->listWidget_prgtext->currentItem()->isSelected())    )
    {
        //Prüfen ob Fräsbahnen durch das Verschieben geteilt werden:
        bool gesund = true;
        //--Prüfen ob eine Fräsbahn nach der Auswahl weiter geht:
        if(auswahl_letzter() < ui->listWidget_prgtext->count())
        {
            int zeile_dannach = auswahl_letzter();//index von QListwidget
            text_zw bearb;
            bearb.set_text(Wst->bearb_ptr()->at(zeile_dannach),TRENNZ_BEARB_PARAM);
            if(bearb.at(0) == BEARBART_FRAESERGERADE  || \
               bearb.at(0) == BEARBART_FRAESERBOGEN)
            {
                gesund = false;
            }
        }
        //---Prüfen ob eine Fräsbahn vor der Auswahl beginnt:
        if(auswahl_erster() >= 2)
        {
            int zeile_davor = auswahl_erster()-1;//index von QListwidget
            text_zw bearb;
            bearb.set_text(Wst->bearb_ptr()->at(zeile_davor),TRENNZ_BEARB_PARAM);
            text_zw bearb_erster;
            bearb_erster.set_text(Wst->bearb_ptr()->at(auswahl_erster()-1),TRENNZ_BEARB_PARAM);
            if(bearb_erster.at(0) != BEARBART_FRAESERAUFRUF)
            {
                if(bearb.at(0) == BEARBART_FRAESERAUFRUF  || \
                   bearb.at(0) == BEARBART_FRAESERGERADE  || \
                   bearb.at(0) == BEARBART_FRAESERBOGEN)
                {
                    gesund = false;
                }
            }
        }
        //---
        if(gesund == false)
        {
            QMessageBox mb;
            mb.setText("Das Verschieben dieser Zeilenauswahl ist nicht möglich weil eine Fräsbahn nur vollständig verschoben werden kann!");
            mb.exec();
            return;
        }
        //---
        Dialog_bearb_verschieben dlg;
        dlg.setModal(true);
        connect(&dlg, SIGNAL(signal_punkt(punkt3d)), this, SLOT(slot_verschieben(punkt3d)));
        dlg.exec();
    }else
    {
        QMessageBox mb;
        mb.setText("Sie haben noch nichts ausgewaelt was verschoben werden kann!");
        mb.exec();
    }
}
void MainWin_wst_bearbeiten::on_actionDoppelteil_erzeugen_triggered()
{
    dlg_dt.set_wst_laenge(Wst->laenge());
    dlg_dt.set_wst_breite(Wst->breite());
    dlg_dt.set_bearb(Wst->bearb());
    dlg_dt.exec();
}
void MainWin_wst_bearbeiten::on_actionFormartierungen_aufbrechen_triggered()
{
    text_zw bearb = Wst->bearb();
    double tmp_l = Wst->laenge();
    double tmp_b = Wst->breite();

    //Diese Funktion soll die vom VW ausgegebenen Poligonförmigen Formartierungen entdecken.
    //Diese werden generiert, wenn die Grundfläche eines 3D-Bauteils kein Rechteck ist
    //Die Bestandteile der Fräskontur, die deckungsgleich auf der Kante liegen werden nicht benötigt
    //Und werden durch diese Funktion heraus genommen

    //Prüfen ob wst eine umlaufende Formartierung enthällt:
    for(uint i=0; i< bearb.count() ;i++)
    {
        text_zw param;
        param.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
        if(param.at(0) == BEARBART_FRAESERAUFRUF)
        {
            uint zeibeg = i;
            uint zeiend = i;
            fraeseraufruf fa(param.text());
            double xbeg = fa.x();
            double ybeg = fa.y();
            double zbeg = fa.tiefe();
            double xend = xbeg;
            double yend = ybeg;
            double zend = zbeg;
            double xmin = xbeg;
            double xmax = xbeg;
            double ymin = ybeg;
            double ymax = ybeg;
            if(i< bearb.count())
            {
                i++;
                for(; i< bearb.count() ;i++)
                {
                    param.set_text(bearb.at(i), TRENNZ_BEARB_PARAM);
                    if(param.at(0) == BEARBART_FRAESERGERADE)
                    {
                        fraesergerade fg(param.text());
                        xend = fg.xe();
                        yend = fg.ye();
                        zend = fg.ze();
                        zeiend = i;
                        if(xend > xmax)
                        {
                            xmax = xend;
                        }
                        if(xend < xmin)
                        {
                            xmin = xend;
                        }
                        if(yend > ymax)
                        {
                            ymax = yend;
                        }
                        if(yend < ymin)
                        {
                            ymin = yend;
                        }
                    }else if(param.at(0) == BEARBART_FRAESERBOGEN)
                    {
                        fraeserbogen fb(param.text());
                        xend = fb.xe();
                        yend = fb.ye();
                        zend = fb.ze();
                        zeiend = i;
                        if(xend > xmax)
                        {
                            xmax = xend;
                        }
                        if(xend < xmin)
                        {
                            xmin = xend;
                        }
                        if(yend > ymax)
                        {
                            ymax = yend;
                        }
                        if(yend < ymin)
                        {
                            ymin = yend;
                        }
                    }else
                    {
                        break;
                    }
                }
            }
            if(zeibeg != zeiend)
            {
                //Prüfen ob Start- und Endpunkt gleich sind:
                if(xbeg == xend && ybeg == yend && zbeg == zend)//evtl. ist hier cagleich nötig!!
                {
                    //Prüfen ob fkon Formartierung ist:
                    if(xmin <= 0        &&\
                                        xmax >= tmp_l    &&\
                              ymin <= 0        &&\
                              ymax >= tmp_b)
                    {
                        //Die Teile aus der Bearbeitung löschen die Deckungsgleich auf der WST-Kante liegen
                        text_zw bearb_neu;
                        bearb_neu.set_text(fa.text(), '\n');

                        for(uint ii=zeibeg+1; ii<=zeiend ;ii++)
                        {
                            text_zw param;
                            param.set_text(bearb.at(ii), TRENNZ_BEARB_PARAM);

                            if(param.at(0) == BEARBART_FRAESERGERADE)
                            {
                                fraesergerade fg(param.text());
                                bool loeschen = false;
                                if((fg.xs() == fg.xe()) && (fg.ys() != fg.ye()))
                                {
                                    //Gerade ist senkrecht
                                    if((fg.xs() == 0) || (fg.xs()== tmp_l))
                                    {
                                        //Gerade liegt auf der WST-Kante
                                        loeschen = true;
                                    }
                                }else if((fg.xs() != fg.xe()) && (fg.ys() == fg.ye()))
                                {
                                    //Gerade ist wagerecht
                                    if((fg.ys() == 0) || (fg.ys()== tmp_b))
                                    {
                                        //Gerade liegt auf der WST-Kante
                                        loeschen = true;
                                    }
                                }
                                if(loeschen == true)
                                {
                                    QString vorzeile = bearb_neu.at(bearb_neu.count()-1);
                                    text_zw vorparam;
                                    vorparam.set_text(vorzeile, TRENNZ_BEARB_PARAM);
                                    if(vorparam.at(0) == BEARBART_FRAESERAUFRUF)
                                    {
                                        fraeseraufruf tmpfa(vorparam.text());
                                        tmpfa.set_x(fg.xe());
                                        tmpfa.set_y(fg.ye());
                                        bearb_neu.edit(bearb_neu.count()-1, tmpfa.text());
                                    }else
                                    {
                                        fa.set_x(fg.xe());
                                        fa.set_y(fg.ye());
                                        bearb_neu.add_hi(fa.text());
                                    }
                                }else
                                {
                                    bearb_neu.add_hi(bearb.at(ii));
                                }
                            }else
                            {
                                bearb_neu.add_hi(bearb.at(ii));
                            }
                        }
                        //prüfen ob letzte Zeile von bearb_neu fa ist und ggf löschen:
                        text_zw endparam;
                        endparam.set_text(bearb_neu.at(bearb_neu.count()-1), TRENNZ_BEARB_PARAM);
                        if(endparam.at(0) == BEARBART_FRAESERAUFRUF)
                        {
                            bearb_neu.entf(bearb_neu.count()-1);
                        }
                        //bearb.zeile(zeibeg bis zeiend) gegen bearb_neu austauschen:
                        if(zeiend+1 < bearb.count())
                        {
                            bearb.entf(zeibeg, zeiend-zeibeg+1);
                            bearb.add_mi(zeibeg, bearb_neu.text());
                            i = zeibeg+bearb_neu.count()-1;
                        }else
                        {
                            bearb.entf(zeibeg, zeiend-zeibeg+1);
                            bearb.add_hi(bearb_neu.text());
                            i = bearb.count()-1;
                        }
                    }
                }
            }
        }
    }
    Wst->set_bearb(bearb);
    sendVorschauAktualisieren(*Wst, -1, Wkz_kopie);
    update_listwidget();
    unredo_neu();
}
void MainWin_wst_bearbeiten::on_actionFraesrichtung_umkehren_triggered()
{
    if(auswahl_menge() == 0)
    {
        QMessageBox mb;
        mb.setText("Bitte eine Zeile auswählen");
        mb.setWindowTitle("Fräsrichtung umkehren");
        mb.exec();
        return;
    }
    if(auswahl_menge() > 1)
    {
        QMessageBox mb;
        mb.setText("Bitte nur eine Zeile auswählen");
        mb.setWindowTitle("Fräsrichtung umkehren");
        mb.exec();
        return;
    }
    uint index_auswahl_listwidget = auswahl_erster();
    uint index_auswahl_bearb = index_auswahl_listwidget-1;//1. Zeile ist Prgrammkopf
    text_zw bearb = Wst->bearb();
    text_zw zeile;
    zeile.set_text(bearb.at(index_auswahl_bearb),TRENNZ_BEARB_PARAM);
    if(zeile.at(0) != BEARBART_FRAESERAUFRUF)
    {
        QMessageBox mb;
        mb.setText("Die ausgewählte Ziele muss einen Fräseraufruf enthalten");
        mb.setWindowTitle("Fräsrichtung umkehren");
        mb.exec();
        return;
    }
    fraeseraufruf fa(zeile.text());
    text_zw bearb_fkon_gedreht;
    punkt3d sp_fkon;
    for(uint i=index_auswahl_bearb+1; i<bearb.count() ;i++)
    {
        text_zw folgezeile;
        folgezeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
        if(folgezeile.at(0) == BEARBART_FRAESERGERADE)
        {
            fraesergerade fg(folgezeile.text());
            punkt3d sp = fg.sp();
            punkt3d ep = fg.ep();
            fg.set_startpunkt(ep);
            fg.set_endpunkt(sp);
            bearb_fkon_gedreht.add_vo(fg.text());
            sp_fkon = ep;
        }else if(folgezeile.at(0) == BEARBART_FRAESERBOGEN)
        {
            fraeserbogen fb(folgezeile.text());
            punkt3d sp = fb.sp();
            punkt3d ep = fb.ep();
            fb.set_startpunkt(ep);
            fb.set_endpunkt(sp);
            fb.set_uzs(!fb.uzs());
            bearb_fkon_gedreht.add_vo(fb.text());
            sp_fkon = ep;
        }else
        {
            break;//for
        }
    }
    if(bearb_fkon_gedreht.count() > 0)
    {
        fa.set_pos(sp_fkon);
        if(fa.radkor() == FRKOR_L)
        {
            fa.set_radkor(FRKOR_R);
        }else if(fa.radkor() == FRKOR_R)
        {
            fa.set_radkor(FRKOR_L);
        }
        QString wkznr = fa.wkznum();
        QString spiegelwkz = Wkz_kopie.spiegelwkz(wkznr);
        if(!spiegelwkz.isEmpty())
        {
            fa.set_wkznum(spiegelwkz);
        }
        bearb_fkon_gedreht.add_vo(fa.text());
        for(uint i=0; i<bearb_fkon_gedreht.count() ;i++)
        {
            uint index_bearb_akt = index_auswahl_bearb + i;
            Wst->bearb_ptr()->edit(index_bearb_akt, bearb_fkon_gedreht.at(i));
        }
        update_listwidget();
        unredo_neu();
        ui->listWidget_prgtext->setCurrentRow(index_auswahl_listwidget);
        emit sendVorschauAktualisieren(*Wst, index_auswahl_listwidget, Wkz_kopie);
    }
}
void MainWin_wst_bearbeiten::on_actionFraesbahn_teilen_in_aktueller_Zeile_triggered()
{
    if(auswahl_menge() == 0)
    {
        QMessageBox mb;
        mb.setText("Bitte eine Zeile auswählen");
        mb.setWindowTitle("Fräsbahn in aktueller Zeile teilen");
        mb.exec();
        return;
    }
    if(auswahl_menge() > 1)
    {
        QMessageBox mb;
        mb.setText("Bitte nur eine Zeile auswählen");
        mb.setWindowTitle("Fräsbahn in aktueller Zeile teilen");
        mb.exec();
        return;
    }
    uint index_auswahl_listwidget = auswahl_erster();
    uint index_auswahl_bearb = index_auswahl_listwidget-1;//1. Zeile ist Prgrammkopf
    text_zw bearb = Wst->bearb();
    if(index_auswahl_bearb >= bearb.count())
    {
        return;
    }
    text_zw zeile;
    zeile.set_text(bearb.at(index_auswahl_bearb),TRENNZ_BEARB_PARAM);
    if(zeile.at(0) != BEARBART_FRAESERGERADE && zeile.at(0) != BEARBART_FRAESERBOGEN)
    {
       QMessageBox mb;
       mb.setText("Die ausgewählte Ziele muss einen gerade oder gebogene Fräsbahn enthalten");
       mb.setWindowTitle("Fräsbahn in aktueller Zeile teilen");
       mb.exec();
       return;
    }
    punkt3d trennpunkt;
    fraeseraufruf fa;
    for(int i=index_auswahl_bearb; i>=0 ;i--)
    {
        text_zw vorherigezeile;
        vorherigezeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
        if(vorherigezeile.at(0) == BEARBART_FRAESERAUFRUF)
        {
            fa.set_text(vorherigezeile.text());
            break;//for
        }
    }
    if(zeile.at(0) == BEARBART_FRAESERGERADE)
    {
        fraesergerade fg(zeile.text());
        trennpunkt = fg.strecke_().mipu();
        fraesergerade fg_ende = fg;
        fg_ende.set_endpunkt(trennpunkt);
        fraesergerade fg_start = fg;
        fg_start.set_startpunkt(trennpunkt);
        fa.set_pos(trennpunkt);
        Wst->bearb_ptr()->edit(index_auswahl_bearb, fg_ende.text());
        Wst->bearb_ptr()->add_mi(index_auswahl_bearb,fg_start.text());
        Wst->bearb_ptr()->add_mi(index_auswahl_bearb, fa.text());
    }else //if(zeile.at(0) == BEARBART_FRAESERBOGEN)
    {
        fraeserbogen fb(zeile.text());
        double bowi = winkel(fb.stapu(), fb.bog().mitte(), fb.endpu());
        if(bowi < 0)
        {
            bowi = bowi * -1;
        }
        punkt3d bomipu;
        strecke sehne;
        sehne.set_stapu(fb.bog().start());
        sehne.set_endpu(fb.bog().ende());
        strecke strahl;
        strahl.set_stapu(fb.bog().mitte());
        strahl.set_endpu(sehne.mipu2d());
        strahl.set_laenge_2d(fb.bog().rad(), strecke_bezugspunkt_start);
        trennpunkt.set_x(strahl.endpu().x());
        trennpunkt.set_y(strahl.endpu().y());
        if(fa.bezug() == WST_BEZUG_UNSEI)
        {
            trennpunkt = drehen(sehne.mipu(), trennpunkt, (double)180, true);
        }
        double pos_z = (fb.stapu().z()+fb.endpu().z())/2;
        trennpunkt.set_z(pos_z);
        fraeserbogen fb_ende = fb;
        fb_ende.set_endpunkt(trennpunkt);
        fraeserbogen fb_start = fb;
        fb_start.set_startpunkt(trennpunkt);
        fa.set_pos(trennpunkt);
        Wst->bearb_ptr()->edit(index_auswahl_bearb, fb_ende.text());
        Wst->bearb_ptr()->add_mi(index_auswahl_bearb,fb_start.text());
        Wst->bearb_ptr()->add_mi(index_auswahl_bearb, fa.text());
    }
    update_listwidget();
    unredo_neu();
    ui->listWidget_prgtext->setCurrentRow(index_auswahl_listwidget);
    emit sendVorschauAktualisieren(*Wst, index_auswahl_listwidget, Wkz_kopie);
}
void MainWin_wst_bearbeiten::on_actionVerlaengern_triggered()
{
    if(auswahl_menge() == 0)
    {
        QMessageBox mb;
        mb.setText("Sie haben noch nichts ausgewählt was verlängert werden soll!");
        mb.setWindowTitle("Verlängern um");
        mb.exec();
        return;
    }
    if(auswahl_menge() > 1)
    {
        QMessageBox mb;
        mb.setText("Bitte nur eine Zeile auswählen!");
        mb.setWindowTitle("Verlängern um");
        mb.exec();
        return;
    }
    uint index_auswahl_listwidget = auswahl_erster();
    uint index_auswahl_bearb = index_auswahl_listwidget-1;//1. Zeile ist Prgrammkopf
    text_zw bearb = Wst->bearb();
    if(index_auswahl_bearb >= bearb.count())
    {
        return;
    }
    text_zw zeile;
    zeile.set_text(bearb.at(index_auswahl_bearb),TRENNZ_BEARB_PARAM);
    if(zeile.at(0) == BEARBART_FRAESERGERADE)
    {
        bool gesund = false;
        if(index_auswahl_bearb == bearb.count())
        {
            gesund = true;
            Ist_verlaengerung_am_anfang = false;
        }
        if(index_auswahl_bearb+1 <= bearb.count())
        {
            text_zw folgezeile;
            folgezeile.set_text(bearb.at(index_auswahl_bearb+1),TRENNZ_BEARB_PARAM);
            if(folgezeile.at(0) != BEARBART_FRAESERGERADE  &&  folgezeile.at(0) != BEARBART_FRAESERBOGEN)
            {
                gesund = true;
                Ist_verlaengerung_am_anfang = false;
            }
        }
        if(gesund == false && index_auswahl_bearb > 0)
        {
            text_zw vorzeile;
            vorzeile.set_text(bearb.at(index_auswahl_bearb-1),TRENNZ_BEARB_PARAM);
            if(vorzeile.at(0) != BEARBART_FRAESERGERADE  &&  vorzeile.at(0) != BEARBART_FRAESERBOGEN)
            {
                gesund = true;
                Ist_verlaengerung_am_anfang = true;
            }
        }
        if(gesund == true)
        {
            Dialog_userinput dlg_verlaengern;
            dlg_verlaengern.setWindowTitle("gerade Fräsbahn verlängern um");
            dlg_verlaengern.set_default("10");
            connect(&dlg_verlaengern, SIGNAL(send_input(QString)), this, SLOT(slot_verlaengern_fgerade(QString)));
            dlg_verlaengern.exec();
        }
    }
}
//----------------------------------Slot_Manipulation:
void MainWin_wst_bearbeiten::slot_verschieben(punkt3d p)
{
    int index = ui->listWidget_prgtext->currentRow()-1;//index der Bearbeitung, nicht vom listwidget
    //Die index-Prüfung erfolgt bereits in der Funktion on_actionVerschieben_triggered()
    int row_erstes = auswahl_erster()-1;//-1 weil index der Bearbeitung, nicht vom listwidget
    int items_menge = auswahl_menge();
    if(items_menge==1)
    {
        if(index >= 0  &&  index+1 < ui->listWidget_prgtext->count())
        {
            QString bearb = Wst->bearb_ptr()->at(index);
            bearb = verschiebe_einen(bearb, p.x(), p.y(), p.z());
            zeile_aendern(index, bearb, true);
        }
    }else
    {
        index = row_erstes;
        if(index < 0)
        {
            index = 0;
            items_menge = items_menge-1;
        }
        if(index+items_menge >= ui->listWidget_prgtext->count())
        {
            items_menge = ui->listWidget_prgtext->count()-index-1;
        }
        for (int i=0 ; i<items_menge ; i++)
        {
            QString bearb = Wst->bearb_ptr()->at(index+i);
            bearb = verschiebe_einen(bearb, p.x(), p.y(), p.z());
            zeile_aendern(index+i, bearb, false);
        }
        unredo_neu();
    }
}
QString MainWin_wst_bearbeiten::verschiebe_einen(QString bearb, double ax, double ay, double az)
{
    text_zw tz;
    tz.set_text(bearb, TRENNZ_BEARB_PARAM);
    if(tz.at(0) == BEARBART_BOHR)
    {
        bohrung bo;
        bo.set_text(bearb);
        //bo.set_x(bo.x()+ax);
        //bo.set_y(bo.y()+ay);
        //bo.set_z(bo.z()+az);
        if(bo.bezug() == WST_BEZUG_OBSEI || bo.bezug() == WST_BEZUG_UNSEI)
        {
            bo.set_x(bo.x()+ax);
            bo.set_y(bo.y()+ay);
        }else if(bo.bezug() == WST_BEZUG_LI)
        {
            if(bo.x() != 0)
            {
                bo.set_x(bo.x()+ax);
            }
            bo.set_y(bo.y()+ay);
            bo.set_z(bo.z()+az);
        }else if(bo.bezug() == WST_BEZUG_RE)
        {
            if(bo.x() == letzte_wst_l)
            {
                bo.set_x(Wst->laenge());
            }else
            {
                bo.set_x(bo.x()+ax);
            }
            bo.set_y(bo.y()+ay);
            bo.set_z(bo.z()+az);
        }else if(bo.bezug() == WST_BEZUG_VO)
        {
            bo.set_x(bo.x()+ax);
            if(bo.y() != 0)
            {
                bo.set_y(bo.y()+ay);
            }
            bo.set_z(bo.z()+az);
        }else if(bo.bezug() == WST_BEZUG_HI)
        {
            bo.set_x(bo.x()+ax);
            if(bo.y() == letzte_wst_b)
            {
                bo.set_y(Wst->breite());
            }else
            {
                bo.set_y(bo.y()+ay);
            }
            bo.set_z(bo.z()+az);
        }
        bearb = bo.text();
    }else if(tz.at(0) == BEARBART_RTA)
    {
        rechtecktasche rt;
        rt.set_text(bearb);
        if(rt.bezug() == WST_BEZUG_OBSEI || rt.bezug() == WST_BEZUG_UNSEI)
        {
            rt.set_x(rt.x()+ax);
            rt.set_y(rt.y()+ay);
        }else if(rt.bezug() == WST_BEZUG_LI)
        {
            rt.set_x(0);
            rt.set_y(rt.y()+ay);
            rt.set_z(rt.z()+az);
        }else if(rt.bezug() == WST_BEZUG_RE)
        {
            rt.set_x(Wst->laenge());
            rt.set_y(rt.y()+ay);
            rt.set_z(rt.z()+az);
        }else if(rt.bezug() == WST_BEZUG_VO)
        {
            rt.set_x(rt.x()+ax);
            rt.set_y(0);
            rt.set_z(rt.z()+az);
        }else if(rt.bezug() == WST_BEZUG_HI)
        {
            rt.set_x(rt.x()+ax);
            rt.set_y(Wst->breite());
            rt.set_z(rt.z()+az);
        }
        bearb = rt.text();
    }if(tz.at(0) == BEARBART_NUT)
    {
        nut nu;
        nu.set_text(bearb);
        if(nu.bezug() == WST_BEZUG_OBSEI || nu.bezug() == WST_BEZUG_UNSEI)
        {
            nu.set_xs(nu.xs()+ax);
            nu.set_xe(nu.xe()+ax);
            nu.set_ys(nu.ys()+ay);
            nu.set_ye(nu.ye()+ay);
        }else if(nu.bezug() == WST_BEZUG_LI)
        {
            nu.set_xs(0);
            nu.set_xe(0);
            nu.set_ys(nu.ys()+ay);
            nu.set_ye(nu.ye()+ay);
            nu.set_zs(nu.zs()+az);
            nu.set_ze(nu.ze()+az);
        }else if(nu.bezug() == WST_BEZUG_RE)
        {
            nu.set_xs(Wst->laenge());
            nu.set_xe(Wst->laenge());
            nu.set_ys(nu.ys()+ay);
            nu.set_ye(nu.ye()+ay);
            nu.set_zs(nu.zs()+az);
            nu.set_ze(nu.ze()+az);
        }else if(nu.bezug() == WST_BEZUG_VO)
        {
            nu.set_xs(nu.xs()+ax);
            nu.set_xe(nu.xe()+ax);
            nu.set_ys(0);
            nu.set_ye(0);
            nu.set_zs(nu.zs()+az);
            nu.set_ze(nu.ze()+az);
        }else if(nu.bezug() == WST_BEZUG_HI)
        {
            nu.set_xs(nu.xs()+ax);
            nu.set_xe(nu.xe()+ax);
            nu.set_ys(Wst->breite());
            nu.set_ye(Wst->breite());
            nu.set_zs(nu.zs()+az);
            nu.set_ze(nu.ze()+az);
        }
        bearb = nu.text();
    }if(tz.at(0) == BEARBART_FRAESERAUFRUF)
    {
        fraeseraufruf fa;
        fa.set_text(bearb);
        fa.set_x(fa.x()+ax);
        fa.set_y(fa.y()+ay);
        bearb = fa.text();
    }if(tz.at(0) == BEARBART_FRAESERGERADE)
    {
        fraesergerade fg;
        fg.set_text(bearb);
        fg.set_xs(fg.xs()+ax);
        fg.set_xe(fg.xe()+ax);
        fg.set_ys(fg.ys()+ay);
        fg.set_ye(fg.ye()+ay);
        bearb = fg.text();
    }if(tz.at(0) == BEARBART_FRAESERBOGEN)
    {
        fraeserbogen fb;
        fb.set_text(bearb);
        fb.set_xs(fb.xs()+ax);
        fb.set_xe(fb.xe()+ax);
        fb.set_ys(fb.ys()+ay);
        fb.set_ye(fb.ye()+ay);
        bearb = fb.text();
    }
    return bearb;
}
void MainWin_wst_bearbeiten::slot_dt_erzeugen(QString bezug, double wst_l, double wst_b, bool spiegeln, bool drehen)
{
    double ax = wst_l - Wst->laenge();//Abstand der Verschiebung der Bearbeitung in X-Richtung
    double ay = wst_b - Wst->breite();//Abstand der Verschiebung der Bearbeitung in Y-Richtung
    Wst->set_laenge(wst_l);
    Wst->set_breite(wst_b);
    sendVorschauAktualisieren(*Wst, -1, Wkz_kopie);
    letzte_wst_l = Wst->laenge();
    letzte_wst_b = Wst->breite();
    letzte_wst_d = Wst->dicke();
    if(bezug == WST_BEZUG_VO)
    {//Wst wird nach hinten hin breiter
        //vorhandene Bearbeitung muss nicht verschoben werden
        //Bearbeitung für DT einfügen:
        text_zw bearb = Wst->bearb();
        text_zw bearb_neu;
        bearb_neu.set_trenz(bearb.trennz());
        for(uint i=0; i<bearb.count() ;i++)
        {
            text_zw zeile;
            zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
            if(spiegeln == true)
            {
                if(zeile.at(0) == BEARBART_BOHR)
                {
                    bohrung bo(zeile.text());
                    if(bo.bezug() == WST_BEZUG_OBSEI || bo.bezug() == WST_BEZUG_UNSEI)
                    {
                        bo.set_y(wst_b-bo.y());
                    }else if(bo.bezug() == WST_BEZUG_LI || bo.bezug() == WST_BEZUG_RE)
                    {
                        bo.set_y(wst_b-bo.y());
                    }else //WST_BEZUG_VO,     WST_BEZUG_HI ist hier nicht möglich
                    {
                        bo.set_y(wst_b-bo.y());
                        bo.set_bezug(WST_BEZUG_HI);
                    }
                    bearb_neu.add_hi(bo.text());
                    //slot_make(bo.text(), false);
                }else if(zeile.at(0) == BEARBART_NUT)
                {
                    nut nu(zeile.text());
                    punkt3d sp_alt = nu.stapu();
                    punkt3d ep_alt = nu.endpu();
                    punkt3d sp_neu = sp_alt;
                    punkt3d ep_neu = ep_alt;
                    if(nu.bezug() == WST_BEZUG_OBSEI || nu.bezug() == WST_BEZUG_UNSEI)
                    {
                        sp_neu.set_y(wst_b-sp_alt.y());
                        ep_neu.set_y(wst_b-ep_alt.y());
                        nu.set_stapu(sp_neu);
                        nu.set_endpu(ep_neu);
                        bearb_neu.add_hi(nu.text());
                        //slot_make(nu.text(), false);
                    }else if(nu.bezug() == WST_BEZUG_LI || nu.bezug() == WST_BEZUG_RE)
                    {
                        //überspringen
                    }else //WST_BEZUG_VO,     WST_BEZUG_HI ist hier nicht möglich
                    {
                        //überspringen
                    }
                }else if(zeile.at(0) == BEARBART_RTA)
                {
                    rechtecktasche rt(zeile.text());
                    if(rt.bezug() == WST_BEZUG_OBSEI || rt.bezug() == WST_BEZUG_UNSEI)
                    {
                        rt.set_y(wst_b-rt.y());
                        rt.set_drewi(360-rt.drewi());
                    }else if(rt.bezug() == WST_BEZUG_LI || rt.bezug() == WST_BEZUG_RE)
                    {
                        rt.set_y(wst_b-rt.y());
                    }else //WST_BEZUG_VO,     WST_BEZUG_HI ist hier nicht möglich
                    {
                        rt.set_y(wst_b-rt.y());
                        rt.set_bezug(WST_BEZUG_HI);
                    }
                    bearb_neu.add_hi(rt.text());
                    //slot_make(rt.text(), false);
                }
            }else //if(drehen == true)
            {
                if(zeile.at(0) == BEARBART_BOHR)
                {
                    bohrung bo(zeile.text());
                    if(bo.bezug() == WST_BEZUG_OBSEI || bo.bezug() == WST_BEZUG_UNSEI)
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                    }else if(bo.bezug() == WST_BEZUG_LI)
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                        bo.set_bezug(WST_BEZUG_RE);
                    }else if(bo.bezug() == WST_BEZUG_RE)
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                        bo.set_bezug(WST_BEZUG_LI);
                    }else //WST_BEZUG_VO,     WST_BEZUG_HI ist hier nicht möglich
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                        bo.set_bezug(WST_BEZUG_HI);
                    }
                    bearb_neu.add_hi(bo.text());
                    //slot_make(bo.text(), false);
                }else if(zeile.at(0) == BEARBART_NUT)
                {
                    nut nu(zeile.text());
                    punkt3d sp_alt = nu.stapu();
                    punkt3d ep_alt = nu.endpu();
                    punkt3d sp_neu = sp_alt;
                    punkt3d ep_neu = ep_alt;
                    if(nu.bezug() == WST_BEZUG_OBSEI || nu.bezug() == WST_BEZUG_UNSEI)
                    {
                        sp_neu.set_x(wst_l-sp_alt.x());
                        ep_neu.set_x(wst_l-ep_alt.x());
                        sp_neu.set_y(wst_b-sp_alt.y());
                        ep_neu.set_y(wst_b-ep_alt.y());
                        nu.set_stapu(sp_neu);
                        nu.set_endpu(ep_neu);
                        bearb_neu.add_hi(nu.text());
                        //slot_make(nu.text(), false);
                    }else if(nu.bezug() == WST_BEZUG_LI)
                    {
                        //überspringen
                    }else if(nu.bezug() == WST_BEZUG_RE)
                    {
                        //überspringen
                    }else //WST_BEZUG_VO,     WST_BEZUG_HI ist hier nicht möglich
                    {
                        //überspringen
                    }
                }else if(zeile.at(0) == BEARBART_RTA)
                {
                    rechtecktasche rt(zeile.text());
                    if(rt.bezug() == WST_BEZUG_OBSEI || rt.bezug() == WST_BEZUG_UNSEI)
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                    }else if(rt.bezug() == WST_BEZUG_LI)
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                        rt.set_bezug(WST_BEZUG_RE);
                    }else if(rt.bezug() == WST_BEZUG_RE)
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                        rt.set_bezug(WST_BEZUG_LI);
                    }else //WST_BEZUG_VO,     WST_BEZUG_HI ist hier nicht möglich
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                        rt.set_bezug(WST_BEZUG_HI);
                    }
                    bearb_neu.add_hi(rt.text());
                    //slot_make(rt.text(), false);
                }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
                {
                    fraeseraufruf fa(zeile.text());
                    if(fa.bezug() == WST_BEZUG_OBSEI || fa.bezug() == WST_BEZUG_UNSEI)
                    {
                        fa.set_x(wst_l-fa.x());
                        fa.set_y(wst_b-fa.y());
                        bearb_neu.add_hi(fa.text());
                        //slot_make(fa.text(), false);
                    }
                }else if(zeile.at(0) == BEARBART_FRAESERGERADE)
                {
                    fraesergerade fg(zeile.text());
                    if(fg.bezug() == WST_BEZUG_OBSEI || fg.bezug() == WST_BEZUG_UNSEI)
                    {
                        fg.set_xs(wst_l-fg.xs());
                        fg.set_xe(wst_l-fg.xe());
                        fg.set_ys(wst_b-fg.ys());
                        fg.set_ye(wst_b-fg.ye());
                        bearb_neu.add_hi(fg.text());
                        //slot_make(fg.text(), false);
                    }
                }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
                {
                    fraeserbogen fb(zeile.text());
                    if(fb.bezug() == WST_BEZUG_OBSEI || fb.bezug() == WST_BEZUG_UNSEI)
                    {
                        fb.set_xs(wst_l-fb.xs());
                        fb.set_xe(wst_l-fb.xe());
                        fb.set_ys(wst_b-fb.ys());
                        fb.set_ye(wst_b-fb.ye());
                        bearb_neu.add_hi(fb.text());
                        //slot_make(fb.text(), false);
                    }
                }
            }
        }
        for(uint i=0; i<bearb_neu.count();i++)
        {
            Wst->bearb_ptr()->add_hi(bearb_neu.at(i));
        }
        update_listwidget();
        unredo_neu();
        int index = ui->listWidget_prgtext->currentRow();
        emit sendVorschauAktualisieren(*Wst, index, Wkz_kopie);
    }else if(bezug == WST_BEZUG_HI)
    {//Wst wird nach vorne hin breiter
        //vorhandene Bearbeitung nach hinten verschieben:
        for(uint i=0; i<Wst->bearb().count() ;i++)
        {
            zeile_aendern(i, verschiebe_einen(Wst->bearb().at(i),ax,ay,0), false);
        }
        //Bearbeitung für DT einfügen:
        text_zw bearb = Wst->bearb();
        for(uint i=0; i<bearb.count() ;i++)
        {
            text_zw zeile;
            zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
            if(spiegeln == true)
            {
                if(zeile.at(0) == BEARBART_BOHR)
                {
                    bohrung bo(zeile.text());
                    if(bo.bezug() == WST_BEZUG_OBSEI || bo.bezug() == WST_BEZUG_UNSEI)
                    {
                        bo.set_y(wst_b-bo.y());
                    }else if(bo.bezug() == WST_BEZUG_LI || bo.bezug() == WST_BEZUG_RE)
                    {
                        bo.set_y(wst_b-bo.y());
                    }else //WST_BEZUG_HI,     WST_BEZUG_VO ist hier nicht möglich
                    {
                        bo.set_y(wst_b-bo.y());
                        bo.set_bezug(WST_BEZUG_VO);
                    }
                    slot_make(bo.text(), false);
                }else if(zeile.at(0) == BEARBART_NUT)
                {
                    nut nu(zeile.text());
                    punkt3d sp_alt = nu.stapu();
                    punkt3d ep_alt = nu.endpu();
                    punkt3d sp_neu = sp_alt;
                    punkt3d ep_neu = ep_alt;
                    if(nu.bezug() == WST_BEZUG_OBSEI || nu.bezug() == WST_BEZUG_UNSEI)
                    {
                        sp_neu.set_y(wst_b-sp_alt.y());
                        ep_neu.set_y(wst_b-ep_alt.y());
                        nu.set_stapu(sp_neu);
                        nu.set_endpu(ep_neu);
                        slot_make(nu.text(), false);
                    }else if(nu.bezug() == WST_BEZUG_LI || nu.bezug() == WST_BEZUG_RE)
                    {
                        //überspringen
                    }else //WST_BEZUG_HI,     WST_BEZUG_VO ist hier nicht möglich
                    {
                        //überspringen
                    }
                }else if(zeile.at(0) == BEARBART_RTA)
                {
                    rechtecktasche rt(zeile.text());
                    if(rt.bezug() == WST_BEZUG_OBSEI || rt.bezug() == WST_BEZUG_UNSEI)
                    {
                        rt.set_y(wst_b-rt.y());
                        rt.set_drewi(360-rt.drewi());
                    }else if(rt.bezug() == WST_BEZUG_LI || rt.bezug() == WST_BEZUG_RE)
                    {
                        rt.set_y(wst_b-rt.y());
                    }else //WST_BEZUG_HI,     WST_BEZUG_VO ist hier nicht möglich
                    {
                        rt.set_y(wst_b-rt.y());
                        rt.set_bezug(WST_BEZUG_VO);
                    }
                    slot_make(rt.text(), false);
                }
            }else //if(drehen == true)
            {
                if(zeile.at(0) == BEARBART_BOHR)
                {
                    bohrung bo(zeile.text());
                    if(bo.bezug() == WST_BEZUG_OBSEI || bo.bezug() == WST_BEZUG_UNSEI)
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                    }else if(bo.bezug() == WST_BEZUG_LI)
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                        bo.set_bezug(WST_BEZUG_RE);
                    }else if(bo.bezug() == WST_BEZUG_RE)
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                        bo.set_bezug(WST_BEZUG_LI);
                    }else //WST_BEZUG_HI,     WST_BEZUG_VO ist hier nicht möglich
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                        bo.set_bezug(WST_BEZUG_VO);
                    }
                    slot_make(bo.text(), false);
                }else if(zeile.at(0) == BEARBART_NUT)
                {
                    nut nu(zeile.text());
                    punkt3d sp_alt = nu.stapu();
                    punkt3d ep_alt = nu.endpu();
                    punkt3d sp_neu = sp_alt;
                    punkt3d ep_neu = ep_alt;
                    if(nu.bezug() == WST_BEZUG_OBSEI || nu.bezug() == WST_BEZUG_UNSEI)
                    {
                        sp_neu.set_x(wst_l-sp_alt.x());
                        ep_neu.set_x(wst_l-ep_alt.x());
                        sp_neu.set_y(wst_b-sp_alt.y());
                        ep_neu.set_y(wst_b-ep_alt.y());
                        nu.set_stapu(sp_neu);
                        nu.set_endpu(ep_neu);
                        slot_make(nu.text(), false);
                    }else if(nu.bezug() == WST_BEZUG_LI)
                    {
                        //überspringen
                    }else if(nu.bezug() == WST_BEZUG_RE)
                    {
                        //überspringen
                    }else //WST_BEZUG_HI,     WST_BEZUG_VO ist hier nicht möglich
                    {
                        //überspringen
                    }
                }else if(zeile.at(0) == BEARBART_RTA)
                {
                    rechtecktasche rt(zeile.text());
                    if(rt.bezug() == WST_BEZUG_OBSEI || rt.bezug() == WST_BEZUG_UNSEI)
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                    }else if(rt.bezug() == WST_BEZUG_LI)
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                        rt.set_bezug(WST_BEZUG_RE);
                    }else if(rt.bezug() == WST_BEZUG_RE)
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                        rt.set_bezug(WST_BEZUG_LI);
                    }else //WST_BEZUG_HI,     WST_BEZUG_VO ist hier nicht möglich
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                        rt.set_bezug(WST_BEZUG_VO);
                    }
                    slot_make(rt.text(), false);
                }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
                {
                    fraeseraufruf fa(zeile.text());
                    if(fa.bezug() == WST_BEZUG_OBSEI || fa.bezug() == WST_BEZUG_UNSEI)
                    {
                        fa.set_x(wst_l-fa.x());
                        fa.set_y(wst_b-fa.y());
                        slot_make(fa.text(), false);
                    }
                }else if(zeile.at(0) == BEARBART_FRAESERGERADE)
                {
                    fraesergerade fg(zeile.text());
                    if(fg.bezug() == WST_BEZUG_OBSEI || fg.bezug() == WST_BEZUG_UNSEI)
                    {
                        fg.set_xs(wst_l-fg.xs());
                        fg.set_xe(wst_l-fg.xe());
                        fg.set_ys(wst_b-fg.ys());
                        fg.set_ye(wst_b-fg.ye());
                        slot_make(fg.text(), false);
                    }
                }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
                {
                    fraeserbogen fb(zeile.text());
                    if(fb.bezug() == WST_BEZUG_OBSEI || fb.bezug() == WST_BEZUG_UNSEI)
                    {
                        fb.set_xs(wst_l-fb.xs());
                        fb.set_xe(wst_l-fb.xe());
                        fb.set_ys(wst_b-fb.ys());
                        fb.set_ye(wst_b-fb.ye());
                        slot_make(fb.text(), false);
                    }
                }
            }
        }
    }else if(bezug == WST_BEZUG_LI)
    {//Wst wird nach rechts hin breiter
        //vorhandene Bearbeitung muss nicht verschoben werden
        //Bearbeitung für DT einfügen:
        text_zw bearb = Wst->bearb();
        for(uint i=0; i<bearb.count() ;i++)
        {
            text_zw zeile;
            zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
            if(spiegeln == true)
            {
                if(zeile.at(0) == BEARBART_BOHR)
                {
                    bohrung bo(zeile.text());
                    if(bo.bezug() == WST_BEZUG_OBSEI || bo.bezug() == WST_BEZUG_UNSEI)
                    {
                        bo.set_x(wst_l-bo.x());
                    }else if(bo.bezug() == WST_BEZUG_VO || bo.bezug() == WST_BEZUG_HI)
                    {
                        bo.set_x(wst_l-bo.x());
                    }else //WST_BEZUG_LI,     WST_BEZUG_RE ist hier nicht möglich
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_bezug(WST_BEZUG_RE);
                    }
                    slot_make(bo.text(), false);
                }else if(zeile.at(0) == BEARBART_NUT)
                {
                    nut nu(zeile.text());
                    punkt3d sp_alt = nu.stapu();
                    punkt3d ep_alt = nu.endpu();
                    punkt3d sp_neu = sp_alt;
                    punkt3d ep_neu = ep_alt;
                    if(nu.bezug() == WST_BEZUG_OBSEI || nu.bezug() == WST_BEZUG_UNSEI)
                    {
                        sp_neu.set_x(wst_l-sp_alt.x());
                        ep_neu.set_x(wst_l-ep_alt.x());
                        nu.set_stapu(sp_neu);
                        nu.set_endpu(ep_neu);
                        slot_make(nu.text(), false);
                    }else if(nu.bezug() == WST_BEZUG_VO || nu.bezug() == WST_BEZUG_HI)
                    {
                        //überspringen
                    }else //WST_BEZUG_LI,     WST_BEZUG_RE ist hier nicht möglich
                    {
                        //überspringen
                    }
                }else if(zeile.at(0) == BEARBART_RTA)
                {
                    rechtecktasche rt(zeile.text());
                    if(rt.bezug() == WST_BEZUG_OBSEI || rt.bezug() == WST_BEZUG_UNSEI)
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_drewi(360-rt.drewi());
                    }else if(rt.bezug() == WST_BEZUG_VO || rt.bezug() == WST_BEZUG_HI)
                    {
                        rt.set_x(wst_l-rt.x());
                    }else //WST_BEZUG_LI,     WST_BEZUG_RE ist hier nicht möglich
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_bezug(WST_BEZUG_RE);
                    }
                    slot_make(rt.text(), false);
                }
            }else //if(drehen == true)
            {
                if(zeile.at(0) == BEARBART_BOHR)
                {
                    bohrung bo(zeile.text());
                    if(bo.bezug() == WST_BEZUG_OBSEI || bo.bezug() == WST_BEZUG_UNSEI)
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                    }else if(bo.bezug() == WST_BEZUG_VO)
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                        bo.set_bezug(WST_BEZUG_HI);
                    }else if(bo.bezug() == WST_BEZUG_HI)
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                        bo.set_bezug(WST_BEZUG_VO);
                    }else //WST_BEZUG_LI,     WST_BEZUG_RE ist hier nicht möglich
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                        bo.set_bezug(WST_BEZUG_RE);
                    }
                    slot_make(bo.text(), false);
                }else if(zeile.at(0) == BEARBART_NUT)
                {
                    nut nu(zeile.text());
                    punkt3d sp_alt = nu.stapu();
                    punkt3d ep_alt = nu.endpu();
                    punkt3d sp_neu = sp_alt;
                    punkt3d ep_neu = ep_alt;
                    if(nu.bezug() == WST_BEZUG_OBSEI || nu.bezug() == WST_BEZUG_UNSEI)
                    {
                        sp_neu.set_x(wst_l-sp_alt.x());
                        ep_neu.set_x(wst_l-ep_alt.x());
                        sp_neu.set_y(wst_b-sp_alt.y());
                        ep_neu.set_y(wst_b-ep_alt.y());
                        nu.set_stapu(sp_neu);
                        nu.set_endpu(ep_neu);
                        slot_make(nu.text(), false);
                    }else if(nu.bezug() == WST_BEZUG_VO)
                    {
                        //überspringen
                    }else if(nu.bezug() == WST_BEZUG_HI)
                    {
                        //überspringen
                    }else //WST_BEZUG_LI,     WST_BEZUG_RE ist hier nicht möglich
                    {
                        //überspringen
                    }
                }else if(zeile.at(0) == BEARBART_RTA)
                {
                    rechtecktasche rt(zeile.text());
                    if(rt.bezug() == WST_BEZUG_OBSEI || rt.bezug() == WST_BEZUG_UNSEI)
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                    }else if(rt.bezug() == WST_BEZUG_VO)
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                        rt.set_bezug(WST_BEZUG_HI);
                    }else if(rt.bezug() == WST_BEZUG_HI)
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                        rt.set_bezug(WST_BEZUG_VO);
                    }else //WST_BEZUG_LI,     WST_BEZUG_RE ist hier nicht möglich
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                        rt.set_bezug(WST_BEZUG_RE);
                    }
                    slot_make(rt.text(), false);
                }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
                {
                    fraeseraufruf fa(zeile.text());
                    if(fa.bezug() == WST_BEZUG_OBSEI || fa.bezug() == WST_BEZUG_UNSEI)
                    {
                        fa.set_x(wst_l-fa.x());
                        fa.set_y(wst_b-fa.y());
                        slot_make(fa.text(), false);
                    }
                }else if(zeile.at(0) == BEARBART_FRAESERGERADE)
                {
                    fraesergerade fg(zeile.text());
                    if(fg.bezug() == WST_BEZUG_OBSEI || fg.bezug() == WST_BEZUG_UNSEI)
                    {
                        fg.set_xs(wst_l-fg.xs());
                        fg.set_xe(wst_l-fg.xe());
                        fg.set_ys(wst_b-fg.ys());
                        fg.set_ye(wst_b-fg.ye());
                        slot_make(fg.text(), false);
                    }
                }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
                {
                    fraeserbogen fb(zeile.text());
                    if(fb.bezug() == WST_BEZUG_OBSEI || fb.bezug() == WST_BEZUG_UNSEI)
                    {
                        fb.set_xs(wst_l-fb.xs());
                        fb.set_xe(wst_l-fb.xe());
                        fb.set_ys(wst_b-fb.ys());
                        fb.set_ye(wst_b-fb.ye());
                        slot_make(fb.text(), false);
                    }
                }
            }
        }
    }else //if(bezug == WST_BEZUG_RE)
    {//Wst wird nach links hin breiter
        //vorhandene Bearbeitung nach rechts verschieben:
        for(uint i=0; i<Wst->bearb().count() ;i++)
        {
            zeile_aendern(i, verschiebe_einen(Wst->bearb().at(i),ax,ay,0), false);
        }
        //Bearbeitung für DT einfügen:
        text_zw bearb = Wst->bearb();
        for(uint i=0; i<bearb.count() ;i++)
        {
            text_zw zeile;
            zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
            if(spiegeln == true)
            {
                if(zeile.at(0) == BEARBART_BOHR)
                {
                    bohrung bo(zeile.text());
                    if(bo.bezug() == WST_BEZUG_OBSEI || bo.bezug() == WST_BEZUG_UNSEI)
                    {
                        bo.set_x(wst_l-bo.x());
                    }else if(bo.bezug() == WST_BEZUG_VO || bo.bezug() == WST_BEZUG_HI)
                    {
                        bo.set_x(wst_l-bo.x());
                    }else //WST_BEZUG_RE,     WST_BEZUG_LI ist hier nicht möglich
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_bezug(WST_BEZUG_LI);
                    }
                    slot_make(bo.text(), false);
                }else if(zeile.at(0) == BEARBART_NUT)
                {
                    nut nu(zeile.text());
                    punkt3d sp_alt = nu.stapu();
                    punkt3d ep_alt = nu.endpu();
                    punkt3d sp_neu = sp_alt;
                    punkt3d ep_neu = ep_alt;
                    if(nu.bezug() == WST_BEZUG_OBSEI || nu.bezug() == WST_BEZUG_UNSEI)
                    {
                        sp_neu.set_x(wst_l-sp_alt.x());
                        ep_neu.set_x(wst_l-ep_alt.x());
                        nu.set_stapu(sp_neu);
                        nu.set_endpu(ep_neu);
                        slot_make(nu.text(), false);
                    }else if(nu.bezug() == WST_BEZUG_VO || nu.bezug() == WST_BEZUG_HI)
                    {
                        //überspringen
                    }else //WST_BEZUG_RE,     WST_BEZUG_LI ist hier nicht möglich
                    {
                        //überspringen
                    }
                }else if(zeile.at(0) == BEARBART_RTA)
                {
                    rechtecktasche rt(zeile.text());
                    if(rt.bezug() == WST_BEZUG_OBSEI || rt.bezug() == WST_BEZUG_UNSEI)
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_drewi(360-rt.drewi());
                    }else if(rt.bezug() == WST_BEZUG_VO || rt.bezug() == WST_BEZUG_HI)
                    {
                        rt.set_x(wst_l-rt.x());
                    }else //WST_BEZUG_RE,     WST_BEZUG_LI ist hier nicht möglich
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_bezug(WST_BEZUG_LI);
                    }
                    slot_make(rt.text(), false);
                }
            }else //if(drehen == true)
            {
                if(zeile.at(0) == BEARBART_BOHR)
                {
                    bohrung bo(zeile.text());
                    if(bo.bezug() == WST_BEZUG_OBSEI || bo.bezug() == WST_BEZUG_UNSEI)
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                    }else if(bo.bezug() == WST_BEZUG_VO)
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                        bo.set_bezug(WST_BEZUG_HI);
                    }else if(bo.bezug() == WST_BEZUG_HI)
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                        bo.set_bezug(WST_BEZUG_VO);
                    }else //WST_BEZUG_RE,     WST_BEZUG_LI ist hier nicht möglich
                    {
                        bo.set_x(wst_l-bo.x());
                        bo.set_y(wst_b-bo.y());
                        bo.set_bezug(WST_BEZUG_LI);
                    }
                    slot_make(bo.text(), false);
                }else if(zeile.at(0) == BEARBART_NUT)
                {
                    nut nu(zeile.text());
                    punkt3d sp_alt = nu.stapu();
                    punkt3d ep_alt = nu.endpu();
                    punkt3d sp_neu = sp_alt;
                    punkt3d ep_neu = ep_alt;
                    if(nu.bezug() == WST_BEZUG_OBSEI || nu.bezug() == WST_BEZUG_UNSEI)
                    {
                        sp_neu.set_x(wst_l-sp_alt.x());
                        ep_neu.set_x(wst_l-ep_alt.x());
                        sp_neu.set_y(wst_b-sp_alt.y());
                        ep_neu.set_y(wst_b-ep_alt.y());
                        nu.set_stapu(sp_neu);
                        nu.set_endpu(ep_neu);
                        slot_make(nu.text(), false);
                    }else if(nu.bezug() == WST_BEZUG_VO)
                    {
                        //überspringen
                    }else if(nu.bezug() == WST_BEZUG_HI)
                    {
                        //überspringen
                    }else //WST_BEZUG_RE,     WST_BEZUG_LI ist hier nicht möglich
                    {
                        //überspringen
                    }
                }else if(zeile.at(0) == BEARBART_RTA)
                {
                    rechtecktasche rt(zeile.text());
                    if(rt.bezug() == WST_BEZUG_OBSEI || rt.bezug() == WST_BEZUG_UNSEI)
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                    }else if(rt.bezug() == WST_BEZUG_VO)
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                        rt.set_bezug(WST_BEZUG_HI);
                    }else if(rt.bezug() == WST_BEZUG_HI)
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                        rt.set_bezug(WST_BEZUG_VO);
                    }else //WST_BEZUG_RE,     WST_BEZUG_LI ist hier nicht möglich
                    {
                        rt.set_x(wst_l-rt.x());
                        rt.set_y(wst_b-rt.y());
                        rt.set_bezug(WST_BEZUG_LI);
                    }
                    slot_make(rt.text(), false);
                }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
                {
                    fraeseraufruf fa(zeile.text());
                    if(fa.bezug() == WST_BEZUG_OBSEI || fa.bezug() == WST_BEZUG_UNSEI)
                    {
                        fa.set_x(wst_l-fa.x());
                        fa.set_y(wst_b-fa.y());
                        slot_make(fa.text(), false);
                    }
                }else if(zeile.at(0) == BEARBART_FRAESERGERADE)
                {
                    fraesergerade fg(zeile.text());
                    if(fg.bezug() == WST_BEZUG_OBSEI || fg.bezug() == WST_BEZUG_UNSEI)
                    {
                        fg.set_xs(wst_l-fg.xs());
                        fg.set_xe(wst_l-fg.xe());
                        fg.set_ys(wst_b-fg.ys());
                        fg.set_ye(wst_b-fg.ye());
                        slot_make(fg.text(), false);
                    }
                }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
                {
                    fraeserbogen fb(zeile.text());
                    if(fb.bezug() == WST_BEZUG_OBSEI || fb.bezug() == WST_BEZUG_UNSEI)
                    {
                        fb.set_xs(wst_l-fb.xs());
                        fb.set_xe(wst_l-fb.xe());
                        fb.set_ys(wst_b-fb.ys());
                        fb.set_ye(wst_b-fb.ye());
                        slot_make(fb.text(), false);
                    }
                }
            }
        }
    }
    unredo_neu();
}
void MainWin_wst_bearbeiten::slot_verlaengern_fgerade(QString input)
{
    uint index_auswahl_listwidget = auswahl_erster();
    uint index_auswahl_bearb = index_auswahl_listwidget-1;//1. Zeile ist Prgrammkopf
    text_zw bearb = Wst->bearb();
    text_zw zeile;
    zeile.set_text(bearb.at(index_auswahl_bearb),TRENNZ_BEARB_PARAM);
    double verlaengerungsmass = ausdruck_auswerten(input).toDouble();
    if(zeile.at(0) == BEARBART_FRAESERGERADE)
    {
        fraesergerade fg(zeile.text());
        strecke s = fg.strecke_();
        if(Ist_verlaengerung_am_anfang == true)
        {
            s.set_laenge_2d(s.laenge2d()+verlaengerungsmass, strecke_bezugspunkt_ende);
            fg.set_startpunkt(s.stapu());
            if(index_auswahl_bearb > 0)
            {
                text_zw vorzeile;
                vorzeile.set_text(bearb.at(index_auswahl_bearb-1),TRENNZ_BEARB_PARAM);
                if(vorzeile.at(0) == BEARBART_FRAESERAUFRUF)
                {
                    fraeseraufruf fa(vorzeile.text());
                    fa.set_pos(s.stapu());
                    Wst->bearb_ptr()->edit(index_auswahl_bearb-1, fa.text());
                }
            }
        }else
        {
            s.set_laenge_2d(s.laenge2d()+verlaengerungsmass, strecke_bezugspunkt_start);
            fg.set_endpunkt(s.endpu());
        }
        Wst->bearb_ptr()->edit(index_auswahl_bearb, fg.text());
        update_listwidget();
        unredo_neu();
        ui->listWidget_prgtext->setCurrentRow(index_auswahl_listwidget);
        emit sendVorschauAktualisieren(*Wst, index_auswahl_listwidget, Wkz_kopie);
    }
}











































