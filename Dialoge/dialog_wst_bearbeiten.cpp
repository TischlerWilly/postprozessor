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
            QString msg = "Bohr von ";
            bohrung bo(zeile.text());
            msg += bezug(bo.bezug());
            msg += "\tØ: ";
            msg += bo.dm_qstring();
            msg += "\tTi: ";
            msg += bo.tiefe_qstring();
            msg += "\tX: ";
            msg += bo.x_qstring();
            msg += "\tY: ";
            msg += bo.y_qstring();
            msg += "\tZ: ";
            msg += bo.z_qstring();
            msg += "\tZSM: ";
            msg += bo.zustellmass_qstring();
            msg += "\tAFB: ";
            msg += bo.afb();
            msg += "\tWKZ: ";
            msg += bo.wkznum();
            bearb = msg;
        }else if(zeile.zeile(1) == BEARBART_BOHRRASTER)
        {
            QString msg = "BoRa von ";
            bohrraster bo(zeile.text());
            msg += bezug(bo.bezug());
            msg += "\tØ: ";
            msg += bo.dm_qstring();
            msg += "\tTi: ";
            msg += bo.tiefe_qstring();
            msg += "\tX: ";
            msg += bo.x_qstring();
            msg += "\tY: ";
            msg += bo.y_qstring();
            msg += "\tZ: ";
            msg += bo.z_qstring();
            msg += "\tZSM: ";
            msg += bo.zustellmass_qstring();
            msg += "\tAFB: ";
            msg += bo.afb();
            msg += "\tWKZ: ";
            msg += bo.wkznum();
            msg += "\tAnz X: ";
            msg += bo.anz_x_qstring();
            msg += "\tAbst X: ";
            msg += bo.raster_x_qstring();
            msg += "\tAnz Y: ";
            msg += bo.anz_y_qstring();
            msg += "\tAbst Y: ";
            msg += bo.raster_y_qstring();
            msg += "\tAnz Z: ";
            msg += bo.anz_z_qstring();
            msg += "\tAbst Z: ";
            msg += bo.raster_z_qstring();

            bearb = msg;
        }else if(zeile.zeile(1) == BEARBART_NUT)
        {
            QString msg = "Nut von ";
            nut nu(zeile.text());
            msg += bezug(nu.bezug());
            msg += "\tTi: ";
            msg += nu.tiefe_qstring();
            msg += "\tB: ";
            msg += nu.breite_qstring();
            msg += "\tXS: ";
            msg += nu.xs_qstring();
            msg += "\tYS: ";
            msg += nu.ys_qstring();
            msg += "\tXE: ";
            msg += nu.xe_qstring();
            msg += "\tYE: ";
            msg += nu.ye_qstring();
            msg += "\tAFB: ";
            msg += nu.afb();
            bearb = msg;
        }else if(zeile.zeile(1) == BEARBART_RTA)
        {
            bearb = rta_zu_prgeile(zeile.text());
        }else if(zeile.zeile(1) == BEARBART_FRAESERAUFRUF)
        {
            QString msg = "Fräser von ";
            fraueseraufruf fa(zeile.text());
            msg += bezug(fa.bezug());
            msg += "\tX: ";
            msg += fa.x_qstring();
            msg += "\tY: ";
            msg += fa.y_qstring();
            msg += "\tZ: ";
            msg += fa.z_qstring();
            msg += "\tTi: ";
            msg += fa.tiefe_qstring();
            msg += "\tAFB: ";
            msg += fa.afb();
            msg += "\tKor: ";
            msg += fa.radkor();
            msg += "\tWKZ: ";
            msg += fa.wkznum();
            bearb = msg;
        }else if(zeile.zeile(1) == BEARBART_FRAESERGERADE)
        {
            QString msg = "Gerade von ";
            fraesergerade fg(zeile.text());
            msg += bezug(fg.bezug());
            msg += "\tXS: ";
            msg += fg.xs_qstring();
            msg += "\tYS: ";
            msg += fg.ys_qstring();
            msg += "\tZS: ";
            msg += fg.zs_qstring();
            msg += "\tXE: ";
            msg += fg.xe_qstring();
            msg += "\tYE: ";
            msg += fg.ye_qstring();
            msg += "\tZE: ";
            msg += fg.ze_qstring();
            msg += "\tAFB: ";
            msg += fg.afb();
            bearb = msg;
        }else if(zeile.zeile(1) == BEARBART_FRAESERBOGEN)
        {
            QString msg = "Bogen von ";
            fraeserbogen fb(zeile.text());
            msg += bezug(fb.bezug());
            msg += "\tXS: ";
            msg += fb.xs_qstring();
            msg += "\tYS: ";
            msg += fb.ys_qstring();
            msg += "\tZS: ";
            msg += fb.zs_qstring();
            msg += "\tXE: ";
            msg += fb.xe_qstring();
            msg += "\tYE: ";
            msg += fb.ye_qstring();
            msg += "\tZE: ";
            msg += fb.ze_qstring();
            msg += "\tRAD: ";
            msg += fb.rad_qstring();
            msg += "\tUZS: ";
            msg += fb.uzs_qstring();
            msg += "\tAFB: ";
            msg += fb.afb();
            bearb = msg;
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
        Dialog_bearb_rta dlg_rta;
        dlg_rta.setModal(true);
        connect(&dlg_rta, SIGNAL(signal_rta(rechtecktasche)), this, SLOT(slot_rta(rechtecktasche)));
        dlg_rta.set_data(bearb.text());
        dlg_rta.exec();
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
