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
    zeile_aendern(index, bearb, true);
}
void MainWin_wst_bearbeiten::slot_fgerade(fraesergerade fg)
{
    int index = ui->listWidget_prgtext->currentRow()-1;//Index-1 weil 1. Zeile WST-Maße sind
    QString bearb = fg.text();
    ui->listWidget_prgtext->item(index)->setText(fgerade_zu_prgzei(bearb));
    zeile_aendern(index, bearb, true);
}
void MainWin_wst_bearbeiten::slot_fbogen(fraeserbogen fb)
{
    int index = ui->listWidget_prgtext->currentRow()-1;//Index-1 weil 1. Zeile WST-Maße sind
    QString bearb = fb.text();
    ui->listWidget_prgtext->item(index)->setText(fbogen_zu_prgzei(bearb));
    zeile_aendern(index, bearb, true);
}

//----------------------------------Make:
void MainWin_wst_bearbeiten::on_actionMakeBohrung_triggered()
{
    Dialog_bearb_bohrung dlg;
    dlg.setModal(true);
    bohrung bo;//Default-Daten
    dlg.set_data(bo.text(), Wst, Wkz_ptr->magazin());
    connect(&dlg, SIGNAL(signal_bo(bohrung)), this, SLOT(slot_make_bo(bohrung)));
    dlg.exec();
}
void MainWin_wst_bearbeiten::on_actionMakeRTA_triggered()
{
    Dialog_bearb_rta dlg;
    dlg.setModal(true);
    rechtecktasche rt;//Default-Daten
    dlg.set_data(rt.text(), Wst, Wkz_ptr->magazin());
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
void MainWin_wst_bearbeiten::on_actionDoppelteil_erzeugen_triggered()
{
    dlg_dt.set_wst_laenge(Wst->laenge());
    dlg_dt.set_wst_breite(Wst->breite());
    dlg_dt.set_bearb(Wst->bearb());
    dlg_dt.exec();
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
                    }else //WST_BEZUG_VO,     WST_BEZUG_HI ist hier nicht möglich
                    {
                        bo.set_y(wst_b-bo.y());
                        bo.set_bezug(WST_BEZUG_HI);
                    }
                    slot_make(bo.text(), false);
                }
            }else //if(drehen == true)
            {
                //...
            }
        }
    }else if(bezug == WST_BEZUG_HI)
    {//Wst wird nach vorne hin breiter
        //vorhandene Bearbeitung nach hinten verschieben:
        for(uint i=0; i<Wst->bearb().count() ;i++)
        {
            zeile_aendern(i, verschiebe_einen(Wst->bearb().at(i),ax,ay,0), false);
        }
        //...
        //...
    }else if(bezug == WST_BEZUG_LI)
    {//Wst wird nach rechts hin breiter
        //vorhandene Bearbeitung muss nicht verschoben werden
        //...
        //...
    }else //if(bezug == WST_BEZUG_RE)
    {//Wst wird nach links hin breiter
        //vorhandene Bearbeitung nach rechts verschieben:
        for(uint i=0; i<Wst->bearb().count() ;i++)
        {
            zeile_aendern(i, verschiebe_einen(Wst->bearb().at(i),ax,ay,0), false);
        }
        //...
        //...
    }
    unredo_neu();
}





























