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
    UnReDo.clear();
    UnReDo.neu(Wst->bearb());
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
        ui->listWidget_prgtext->setCurrentRow(nr-1);
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
        text_zeilenweise bearb_alt = Wst->bearb();
        text_zeilenweise bearb_neu;
        for (uint i = 1; i<=bearb_alt.zeilenanzahl() ; i++)
        {
            if(i==1)
            {
                bearb_neu.set_text(verschiebe_einen(bearb_alt.zeile(i), 0, 0, 0));
                //0,0,0 verschiebt die bearb auf die Wst-kanten
            }else
            {
                bearb_neu.zeile_anhaengen(verschiebe_einen(bearb_alt.zeile(i), 0, 0, 0));
                //0,0,0 verschiebt die bearb auf die Wst-kanten
            }
        }
        Wst->set_bearb(bearb_neu);
        update_listwidget();
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

void MainWin_wst_bearbeiten::zeile_aendern(int index, QString bearb)
{
    //index ist der indes des list-widgets
    //bearb ist eine Zeile der Bearbeitugen
    text_zeilenweise bearbeitungen = Wst->bearb();
    bearbeitungen.zeile_ersaetzen(index, bearb);
    Wst->bearb_ptr()->zeile_ersaetzen(index, bearbeitungen.zeile(index));
    update_listwidget();
    emit sendVorschauAktualisieren(*Wst, index+1);
}
void MainWin_wst_bearbeiten::slot_rta(rechtecktasche rta)
{
    int index = ui->listWidget_prgtext->currentRow();
    QString bearb = rta.text();
    ui->listWidget_prgtext->item(index)->setText(rta_zu_prgeile(bearb));
    zeile_aendern(index, bearb);
}
void MainWin_wst_bearbeiten::slot_bo(bohrung bo)
{
    int index = ui->listWidget_prgtext->currentRow();
    QString bearb = bo.text();
    ui->listWidget_prgtext->item(index)->setText(bohr_zu_prgeile(bearb));
    zeile_aendern(index, bearb);
}
void MainWin_wst_bearbeiten::slot_nut(nut nu)
{
    int index = ui->listWidget_prgtext->currentRow();
    QString bearb = nu.text();
    ui->listWidget_prgtext->item(index)->setText(nut_zu_prgeile(bearb));
    zeile_aendern(index, bearb);
}
void MainWin_wst_bearbeiten::slot_faufruf(fraueseraufruf fa)
{
    int index = ui->listWidget_prgtext->currentRow();
    QString bearb = fa.text();
    ui->listWidget_prgtext->item(index)->setText(fauf_zu_prgeile(bearb));
    zeile_aendern(index, bearb);
}
void MainWin_wst_bearbeiten::slot_fgerade(fraesergerade fg)
{
    int index = ui->listWidget_prgtext->currentRow();
    QString bearb = fg.text();
    ui->listWidget_prgtext->item(index)->setText(fgerade_zu_prgeile(bearb));
    zeile_aendern(index, bearb);
}
void MainWin_wst_bearbeiten::slot_fbogen(fraeserbogen fb)
{
    int index = ui->listWidget_prgtext->currentRow();
    QString bearb = fb.text();
    ui->listWidget_prgtext->item(index)->setText(fbogen_zu_prgeile(bearb));
    zeile_aendern(index, bearb);
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
    UnReDo.neu(Wst->bearb());
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
//----------------------------------Bearbeiten:
void MainWin_wst_bearbeiten::on_actionUndo_triggered()
{
    Wst->set_bearb(UnReDo.undo());
    update_listwidget();
    ui->listWidget_prgtext->setCurrentRow(ui->listWidget_prgtext->count()-1);
    sendVorschauAktualisieren(*Wst, 0);
}
void MainWin_wst_bearbeiten::on_actionRedo_triggered()
{
    Wst->set_bearb(UnReDo.redo());
    update_listwidget();
    ui->listWidget_prgtext->setCurrentRow(ui->listWidget_prgtext->count()-1);
    sendVorschauAktualisieren(*Wst, 0);
}
void MainWin_wst_bearbeiten::on_actionEntf_triggered()
{
    int index = ui->listWidget_prgtext->currentRow();
    if((ui->listWidget_prgtext->currentIndex().isValid())  &&  \
       (ui->listWidget_prgtext->currentItem()->isSelected())    )
    {
        QList<QListWidgetItem*> items = ui->listWidget_prgtext->selectedItems();
        int items_menge = items.count();
        int row_erstes = 0;//Nummer des ersten Elementes
        for(int i=0; i<ui->listWidget_prgtext->count() ;i++)
        {
            if(ui->listWidget_prgtext->item(i)->isSelected())
            {
                row_erstes = i;
                break;
            }
        }
        if(items_menge==1)
        {
            if(index > 0  &&  index+1 < ui->listWidget_prgtext->count())
            {
                Wst->bearb_ptr()->zeile_loeschen(index);
                update_listwidget();
                UnReDo.neu(Wst->bearb());
                ui->listWidget_prgtext->setCurrentRow(index-1);
                emit sendVorschauAktualisieren(*Wst, index);
            }
        }else
        {
            index = row_erstes;
            if(index == 0)
            {
                index = 1;
                items_menge = items_menge-1;
            }
            if(index+items_menge >= ui->listWidget_prgtext->count())
            {
                items_menge = ui->listWidget_prgtext->count()-index-1;
            }
            Wst->bearb_ptr()->zeilen_loeschen(index, items_menge);
            update_listwidget();
            UnReDo.neu(Wst->bearb());
            ui->listWidget_prgtext->setCurrentRow(index-1);
            emit sendVorschauAktualisieren(*Wst, index);
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
    int index = ui->listWidget_prgtext->currentRow();
    if((ui->listWidget_prgtext->currentIndex().isValid())  &&  \
       (ui->listWidget_prgtext->currentItem()->isSelected())    )
    {
        QList<QListWidgetItem*> items = ui->listWidget_prgtext->selectedItems();
        int items_menge = items.count();
        int row_erstes = 0;//Nummer des ersten Elementes
        for(int i=0; i<ui->listWidget_prgtext->count() ;i++)
        {
            if(ui->listWidget_prgtext->item(i)->isSelected())
            {
                row_erstes = i;
                break;
            }
        }
        if(items_menge==1)
        {
            if(index > 0  &&  index+1 < ui->listWidget_prgtext->count())
            {
                KopierterEintrag = Wst->bearb_ptr()->zeile(index);
            }
        }else
        {
            index = row_erstes;
            if(index == 0)
            {
                index = 1;
                items_menge = items_menge-1;
            }
            if(index+items_menge >= ui->listWidget_prgtext->count())
            {
                items_menge = ui->listWidget_prgtext->count()-index-1;
            }
            QString tmp = Wst->bearb_ptr()->zeilen(index, items_menge);
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
        int index = ui->listWidget_prgtext->currentRow();
        if(index == 0)
        {
            index = 1;
        }
        if(index == ui->listWidget_prgtext->count()-1)
        {
            Wst->bearb_ptr()->zeilen_anhaengen(KopierterEintrag);
        }else
        {
            Wst->bearb_ptr()->zeilen_einfuegen(index-1, KopierterEintrag);
        }
        update_listwidget();
        UnReDo.neu(Wst->bearb());
        ui->listWidget_prgtext->setCurrentRow(index);
        emit sendVorschauAktualisieren(*Wst, index+1);
    }
}
//----------------------------------Manipulation:
void MainWin_wst_bearbeiten::on_actionVerschieben_triggered()
{
    if((ui->listWidget_prgtext->currentIndex().isValid())  &&  \
       (ui->listWidget_prgtext->currentItem()->isSelected())    )
    {
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
    int index = ui->listWidget_prgtext->currentRow();
    //Die index-Prüfung erfolgt bereits in der Funktion on_actionVerschieben_triggered()

    QList<QListWidgetItem*> items = ui->listWidget_prgtext->selectedItems();
    int items_menge = items.count();
    int row_erstes = 0;//Nummer des ersten Elementes
    for(int i=0; i<ui->listWidget_prgtext->count() ;i++)
    {
        if(ui->listWidget_prgtext->item(i)->isSelected())
        {
            row_erstes = i;
            break;
        }
    }
    if(items_menge==1)
    {
        if(index > 0  &&  index+1 < ui->listWidget_prgtext->count())
        {
            QString bearb = Wst->bearb_ptr()->zeile(index);
            bearb = verschiebe_einen(bearb, p.x(), p.y(), p.z());
            zeile_aendern(index, bearb);
        }
    }else
    {
        index = row_erstes;
        if(index == 0)
        {
            index = 1;
            items_menge = items_menge-1;
        }
        if(index+items_menge >= ui->listWidget_prgtext->count())
        {
            items_menge = ui->listWidget_prgtext->count()-index-1;
        }
        for (int i=0 ; i<items_menge ; i++)
        {
            QString bearb = Wst->bearb_ptr()->zeile(index+i);
            bearb = verschiebe_einen(bearb, p.x(), p.y(), p.z());
            zeile_aendern(index+i, bearb);
        }
    }
}
QString MainWin_wst_bearbeiten::verschiebe_einen(QString bearb, double ax, double ay, double az)
{
    text_zeilenweise tz;
    tz.set_trennzeichen(TRENNZ_BEARB_PARAM);
    tz.set_text(bearb);
    if(tz.zeile(1) == BEARBART_BOHR)
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
            bo.set_x(0);
            bo.set_y(bo.y()+ay);
            bo.set_z(bo.z()+az);
        }else if(bo.bezug() == WST_BEZUG_RE)
        {
            bo.set_x(Wst->laenge());
            bo.set_y(bo.y()+ay);
            bo.set_z(bo.z()+az);
        }else if(bo.bezug() == WST_BEZUG_VO)
        {
            bo.set_x(bo.x()+ax);
            bo.set_y(0);
            bo.set_z(bo.z()+az);
        }else if(bo.bezug() == WST_BEZUG_HI)
        {
            bo.set_x(bo.x()+ax);
            bo.set_y(Wst->breite());
            bo.set_z(bo.z()+az);
        }
        bearb = bo.text();
    }else if(tz.zeile(1) == BEARBART_RTA)
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
    }if(tz.zeile(1) == BEARBART_NUT)
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
    }if(tz.zeile(1) == BEARBART_FRAESERAUFRUF)
    {
        fraueseraufruf fa;
        fa.set_text(bearb);
        fa.set_x(fa.x()+ax);
        fa.set_y(fa.y()+ay);
        bearb = fa.text();
    }if(tz.zeile(1) == BEARBART_FRAESERGERADE)
    {
        fraesergerade fg;
        fg.set_text(bearb);
        fg.set_xs(fg.xs()+ax);
        fg.set_xe(fg.xe()+ax);
        fg.set_ys(fg.ys()+ay);
        fg.set_ye(fg.ye()+ay);
        bearb = fg.text();
    }if(tz.zeile(1) == BEARBART_FRAESERBOGEN)
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
