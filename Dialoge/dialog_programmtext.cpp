#include "dialog_programmtext.h"
#include "ui_dialog_programmtext.h"

Dialog_programmtext::Dialog_programmtext(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_programmtext)
{
    ui->setupUi(this);
}

Dialog_programmtext::~Dialog_programmtext()
{
    delete ui;
}

void Dialog_programmtext::resizeEvent(QResizeEvent *event)
{
    ui->listWidget_prgtext->move(5,5);
    ui->listWidget_prgtext->setFixedWidth(this->width()-10);
    ui->listWidget_prgtext->setFixedHeight(this->height()-10);
}

void Dialog_programmtext::slot_wst(werkstueck* w)
{
    ui->listWidget_prgtext->clear();
    QString fenstertitel = "Programmtext von: ";
    fenstertitel += w->name();
    this->setWindowTitle(fenstertitel);
    //Programmkopf als erste Zeile einfügen:
    text_zeilenweise pkopf;
    pkopf.set_trennzeichen(TRENNZ_BEARB_PARAM);
    QString param;
    param  = "L=";
    param += double_to_qstring(w->zustand().l());
    pkopf.zeile_anhaengen(param);
    param  = "B=";
    param += double_to_qstring(w->zustand().b());
    pkopf.zeile_anhaengen(param);
    param  = "D=";
    param += w->dicke_qstring();
    pkopf.zeile_anhaengen(param);
    param  = "Drehung ";
    param += w->zustand().drehung();
    pkopf.zeile_anhaengen(param);
    param = w->zustand().format();
    pkopf.zeile_anhaengen(param);
    ui->listWidget_prgtext->addItem(pkopf.text());
    //Bearbeitungen ab 2. Zeile einfügen:
    text_zeilenweise tmp_bearb = w->zustand().bearb();
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
            QString msg = "RTA von ";
            rechtecktasche rt(zeile.text());
            msg += bezug(rt.bezug());
            msg += "\tL: ";
            msg += rt.laenge_qstring();
            msg += "\tB: ";
            msg += rt.breite_qstring();
            msg += "\tTi: ";
            msg += rt.tiefe_qstring();
            msg += "\tX: ";
            msg += rt.x_qstring();
            msg += "\tY: ";
            msg += rt.y_qstring();
            msg += "\tZ: ";
            msg += rt.z_qstring();
            msg += "\tZSM: ";
            msg += rt.zustellmass_qstring();
            msg += "\tWi: ";
            msg += rt.drewi_qstring();
            msg += "\tRAD: ";
            msg += rt.rad_qstring();
            msg += "\tausr: ";
            msg += rt.ausraeumen_qstring();
            msg += "\tAFB: ";
            msg += rt.afb();
            msg += "\tWKZ: ";
            msg += rt.wkznum();
            bearb = msg;
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
    this->show();
}

void Dialog_programmtext::slot_zeilennummer(uint nr)
{
    if((int)nr < ui->listWidget_prgtext->count())
    {
        ui->listWidget_prgtext->item(nr-1)->setSelected(true);
    }
}

void Dialog_programmtext::on_listWidget_prgtext_currentRowChanged(int currentRow)
{
    emit signalIndexChange(currentRow+1);
}

QString Dialog_programmtext::bezug(QString b)
{
    QString msg;
    if(b == WST_BEZUG_OBSEI)
    {
        msg += "ob";
    }else if(b == WST_BEZUG_UNSEI)
    {
        msg += "un";
    }else if(b == WST_BEZUG_LI)
    {
        msg += "li";
    }else if(b == WST_BEZUG_RE)
    {
        msg += "re";
    }else if(b == WST_BEZUG_VO)
    {
        msg += "vo";
    }else if(b == WST_BEZUG_HI)
    {
        msg += "hi";
    }
    return msg;
}



