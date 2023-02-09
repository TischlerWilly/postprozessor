#include "vorschau.h"

vorschau::vorschau(QWidget *parent) :
    QWidget(parent)
{
    this->resize(500, 500);
    this->setWindowTitle("Vorschau");
    Wstd.set_bezugspunkt(MITTE);
    Wstd.set_einfuegepunkt(width()/2 , height()/2);
    this->setMouseTracking(true);
    Zf = 1;
    Npv.x = 0;
    Npv.y = 0;
    Mrg = false;
    Bearb_erlaubt = false;
    this->setCursor(Qt::CrossCursor);
}

void vorschau::set_bearb_erlaubt(bool erlaubt)
{
    Bearb_erlaubt = erlaubt;
}

void vorschau::update_cad()
{
    werkstueck_darstellung_berechnen();
    QPainter painter(this);

    //Hintergrund:
    painter.setBrush( Qt::white);
    painter.setPen(Qt::black);
    painter.drawRect(0, 0, width(), height());

    //Bearbeitungen darstellen:
    text_zw geotext = Geotext;
    for(uint i=0;i<geotext.count();i++)
    {
        text_zw spalten;
        spalten.set_text(geotext.at(i),TRZ_EL_);

        for(uint ii=0;ii<spalten.count();ii++)
        {
            zeichneGeotext(spalten.at(ii), i);
        }
    }
    this->update();
}

void vorschau::paintEvent(QPaintEvent *)
{
    update_cad();
}

void vorschau::zeichneGeotext(QString geometrieElement, uint i)
{
    QPainter painter(this);
    painter.setBrush( Qt::white);
    painter.setPen(Qt::black);

    text_zw element;
    element.set_text(geometrieElement,TRZ_PA_);

    if(element.text().contains(PUNKT))
    {
        punkt2d p2;
        p2.set_x(element.at(1).toDouble()*Sf*Zf);
        p2.set_y(element.at(2).toDouble()*Sf*Zf);
        QPen pen, pen_alt;
        pen_alt = painter.pen();
        pen.setWidth(element.at(5).toInt());
        if(i==Aktuelle_zeilennummer)
        {
            pen.setColor(Qt::red);
            pen.setWidth(pen.width()*2);
        }else
        {
            pen.setColor(set_farbe(element.at(4)));
        }
        pen.setCapStyle(Qt::RoundCap);
        painter.setPen(pen);
        painter.drawPoint(N.x-Npv.x+p2.x(), \
                          N.y-Npv.y-p2.y());
        painter.setPen(pen_alt);
    }else if(element.text().contains(STRECKE))
    {
        punkt2d startpunkt, endpunkt;
        startpunkt.set_x(element.at(1).toDouble()*Sf*Zf);
        startpunkt.set_y(element.at(2).toDouble()*Sf*Zf);
        endpunkt.set_x(element.at(4).toDouble()*Sf*Zf);
        endpunkt.set_y(element.at(5).toDouble()*Sf*Zf);

        QPen pen, pen_alt;
        pen_alt = painter.pen();
        pen.setWidth(element.at(8).toInt());
        pen.setStyle(set_linienstil(element.at(9)));
        if(i==Aktuelle_zeilennummer)
        {
            pen.setColor(Qt::red);
            pen.setWidth(pen.width()*2);
        }else
        {
            pen.setColor(set_farbe(element.at(7)));
        }
        pen.setCapStyle(Qt::RoundCap);
        painter.setPen(pen);

        painter.drawLine(N.x-Npv.x+startpunkt.x(), \
                         N.y-Npv.y-startpunkt.y(), \
                         N.x-Npv.x+endpunkt.x(), \
                         N.y-Npv.y-endpunkt.y());

        painter.setPen(pen_alt);
    }else if(element.text().contains(BOGEN))
    {
        double rad = element.at(7).toDouble()*Sf*Zf;
        punkt2d mipu;
        mipu.set_x(element.at(9).toDouble()*Sf*Zf);//Mittelpunkt in X
        mipu.set_y(element.at(10).toDouble()*Sf*Zf);//Mittelpunkt in Y
        punkt2d obli;
        obli.set_x(mipu.x()-rad);
        obli.set_y(mipu.y()+rad);

        punkt2d mp;
        mp.set_x(element.at(9).toDouble());//Mittelpunkt in X
        mp.set_y(element.at(10).toDouble());//Mittelpunkt in Y
        punkt2d sp;
        sp.set_x(element.at(1).toDouble());//Start in X
        sp.set_y(element.at(2).toDouble());//Start in Y
        punkt2d ep;
        ep.set_x(element.at(4).toDouble());//Ende in X
        ep.set_y(element.at(5).toDouble());//Ende in Y
        double stawi=0, bogwi=0;

        if(element.at(8) == "nein")//Bogen gegen den Uhrzeigersinn
        {
            stawi = winkel(sp.x(),   \
                           sp.y(),   \
                           mp.x(),   \
                           mp.y());
            bogwi = winkel(sp.x(),   \
                           sp.y(),   \
                           mp.x(),   \
                           mp.y(),   \
                           ep.x(),   \
                           ep.y());
        }else//Bogen im Uhrzeigersinn
        {
            stawi = winkel(ep.x(),   \
                           ep.y(),   \
                           mp.x(),   \
                           mp.y());
            bogwi = winkel(ep.x(),   \
                           ep.y(),   \
                           mp.x(),   \
                           mp.y(),   \
                           sp.x(),   \
                           sp.y());
        }
        if(bogwi<0)
        {
            bogwi = 360+bogwi;
        }

        QPen pen, pen_alt;
        pen_alt = painter.pen();
        pen.setWidth(element.at(12).toInt());
        pen.setStyle(set_linienstil(element.at(13)));
        if(i==Aktuelle_zeilennummer)
        {
            pen.setColor(Qt::red);
            pen.setWidth(pen.width()*2);
        }else
        {
            pen.setColor(set_farbe(element.at(11)));
        }
        pen.setCapStyle(Qt::RoundCap);
        painter.setPen(pen);

        painter.drawArc(N.x-Npv.x+obli.x(),\
                        N.y-Npv.y-obli.y(),\
                        rad*2,\
                        rad*2,\
                        stawi*16,\
                        bogwi*16);

        painter.setPen(pen_alt);
    }else if(element.text().contains(KREIS))
    {
        double rad = element.at(4).toDouble()*Sf*Zf;
        QPen pen, pen_alt;
        pen_alt = painter.pen();
        pen.setWidth(element.at(7).toInt());
        pen.setStyle(set_linienstil(element.at(8)));
        if(i==Aktuelle_zeilennummer)
        {
            pen.setColor(Qt::red);
            pen.setWidth(pen.width()*2);
        }else
        {
            pen.setColor(set_farbe(element.at(5)));
        }
        pen.setCapStyle(Qt::RoundCap);
        painter.setPen(pen);

        QBrush brush = painter.brush();
        QBrush brush_alt = painter.brush();
        brush.setColor(set_farbe(element.at(6)));
        painter.setBrush(brush);

        painter.drawEllipse(N.x-Npv.x+(element.at(1).toDouble()*Sf*Zf)-rad,\
                            N.y-Npv.y-(element.at(2).toDouble()*Sf*Zf)-rad,\
                            rad*2,\
                            rad*2);

        painter.setPen(pen_alt);
        painter.setBrush(brush_alt);
    }else if(element.text().contains(ZYLINDER))
    {
        double rad = element.at(4).toDouble()*Sf*Zf;
        QPen pen, pen_alt;
        pen_alt = painter.pen();
        pen.setWidth(element.at(8).toInt());
        pen.setStyle(set_linienstil(element.at(9)));
        if(i==Aktuelle_zeilennummer)
        {
            pen.setColor(Qt::red);
            pen.setWidth(pen.width()*2);
        }else
        {
            pen.setColor(set_farbe(element.at(6)));
        }
        pen.setCapStyle(Qt::RoundCap);
        painter.setPen(pen);

        QBrush brush = painter.brush();
        QBrush brush_alt = painter.brush();
        brush.setColor(set_farbe(element.at(7)));
        painter.setBrush(brush);

        painter.drawEllipse(N.x-Npv.x+(element.at(1).toDouble()*Sf*Zf)-rad,\
                            N.y-Npv.y-(element.at(2).toDouble()*Sf*Zf)-rad,\
                            rad*2,\
                            rad*2);

        painter.setPen(pen_alt);
        painter.setBrush(brush_alt);
    }else if(element.text().contains(RECHTECK3D))
    {
        rechteck3d r;
        int bezpunkt = element.at(1).toInt();
        if(bezpunkt == UNTEN_LINKS)
        {
            bezpunkt = OBEN_LINKS;
        }else if(bezpunkt == UNTEN)
        {
            bezpunkt = OBEN;
        }else if(bezpunkt == UNTEN_RECHTS)
        {
            bezpunkt = OBEN_RECHTS;
        }else if(bezpunkt == OBEN_LINKS)
        {
            bezpunkt = UNTEN_LINKS;
        }else if(bezpunkt == OBEN)
        {
            bezpunkt = UNTEN;
        }else if(bezpunkt == OBEN_RECHTS)
        {
            bezpunkt = UNTEN_RECHTS;
        }
        r.set_bezugspunkt(bezpunkt);
        r.set_einfuegepunkt(N.x-Npv.x+element.at(2).toDouble()*Sf*Zf,\
                            N.y-Npv.y-element.at(3).toDouble()*Sf*Zf,\
                            element.at(4).toDouble()*Sf*Zf);
        r.set_laenge(element.at(5).toDouble()*Sf*Zf);
        r.set_breite(element.at(6).toDouble()*Sf*Zf);
        r.set_rad(element.at(7).toDouble()*Sf*Zf);
        r.set_drewi(element.at(8).toDouble());

        QPen pen, pen_alt;
        pen_alt = painter.pen();
        pen.setWidth(element.at(11).toInt());
        pen.setStyle(set_linienstil(element.at(12)));
        pen.setCapStyle(Qt::RoundCap);
        if(i==Aktuelle_zeilennummer)
        {
            pen.setColor(Qt::red);
            pen.setWidth(pen.width()*2);
        }else
        {
            pen.setColor(set_farbe(element.at(9)));
        }
        painter.setPen(pen);

        QBrush brush = painter.brush();
        QBrush brush_alt = painter.brush();
        brush.setColor(set_farbe(element.at(10)));
        painter.setBrush(brush);

        if(r.rad()==0)
        {
            //Rechteck mit eckigen Ecken:
            QPainterPath pp;
            pp.moveTo(r.unl(false).x(),\
                      r.unl(false).y());
            pp.lineTo(r.unr(false).x(),\
                      r.unr(false).y());
            pp.lineTo(r.obr(false).x(),\
                      r.obr(false).y());
            pp.lineTo(r.obl(false).x(),\
                      r.obl(false).y());
            pp.closeSubpath();
            painter.drawPath(pp);

        }else
        {
            //Rechteck runden Ecken:
            punkt2d mitpu = r.mi();
            //mitpu.set_y(mitpu.y()-r.b());
            QPainterPath pp;

            punkt2d p2;
            //Startpunkt:
            p2.set_x(r.unl().x());
            p2.set_y((r.mi().y()+r.b()/2)-r.rad());
            p2 = drehen(mitpu,\
                        p2,\
                        r.drewi(),\
                        true);
            pp.moveTo(p2.x(), p2.y());
            //Rundung links unten:
            p2.set_x(r.unl().x());
            p2.set_y((r.mi().y()+r.b()/2)-r.rad()*2);
            p2 = drehen_arcTo(p2,\
                        r.rad()*2,\
                        r.rad()*2,\
                        r.drewi(),\
                        mitpu);
            pp.arcTo(p2.x(), p2.y(), r.rad()*2, r.rad()*2, 180+r.drewi(), 90);
            //Linie nach rechts unten:
            p2.set_x(r.unr().x()-r.rad());
            p2.set_y((r.mi().y()+r.b()/2));
            p2 = drehen(mitpu,\
                        p2,\
                        r.drewi(),\
                        true);
            pp.lineTo(p2.x(),p2.y());
            //Rundung rechts unten:
            p2.set_x(r.unr().x()-r.rad()*2);
            p2.set_y((r.mi().y()+r.b()/2)-r.rad()*2);
            p2 = drehen_arcTo(p2,\
                        r.rad()*2,\
                        r.rad()*2,\
                        r.drewi(),\
                        mitpu);
            pp.arcTo(p2.x(), p2.y(), r.rad()*2, r.rad()*2, 270+r.drewi(), 90);
            //Linie nach rechts oben:
            p2.set_x(r.obr().x());
            p2.set_y((r.mi().y()-r.b()/2)+r.rad());
            p2 = drehen(mitpu,\
                        p2,\
                        r.drewi(),\
                        true);
            pp.lineTo(p2.x(),p2.y());
            //Rundung rechts oben
            p2.set_x(r.unr().x()-r.rad()*2);
            p2.set_y((r.mi().y()-r.b()/2));
            p2 = drehen_arcTo(p2,\
                        r.rad()*2,\
                        r.rad()*2,\
                        r.drewi(),\
                        mitpu);
            pp.arcTo(p2.x(), p2.y(), r.rad()*2, r.rad()*2, 0+r.drewi(), 90);
            //Linie nach links oben:
            p2.set_x(r.obl().x()+r.rad());
            p2.set_y((r.mi().y()-r.b()/2));
            p2 = drehen(mitpu,\
                        p2,\
                        r.drewi(),\
                        true);
            pp.lineTo(p2.x(),p2.y());
            //Rundung links oben
            p2.set_x(r.obl().x());
            p2.set_y((r.mi().y()-r.b()/2));
            p2 = drehen_arcTo(p2,\
                        r.rad()*2,\
                        r.rad()*2,\
                        r.drewi(),\
                        mitpu);
            pp.arcTo(p2.x(), p2.y(), r.rad()*2, r.rad()*2, 90+r.drewi(), 90);

            pp.closeSubpath();
            painter.drawPath(pp);
        }

        painter.setPen(pen_alt);
        painter.setBrush(brush_alt);
    }else if(element.text().contains(WUERFEL))
    {
        rechteck3d r;
        int bezpunkt = element.at(1).toInt();
        if(bezpunkt == UNTEN_LINKS)
        {
            bezpunkt = OBEN_LINKS;
        }else if(bezpunkt == UNTEN)
        {
            bezpunkt = OBEN;
        }else if(bezpunkt == UNTEN_RECHTS)
        {
            bezpunkt = OBEN_RECHTS;
        }else if(bezpunkt == OBEN_LINKS)
        {
            bezpunkt = UNTEN_LINKS;
        }else if(bezpunkt == OBEN)
        {
            bezpunkt = UNTEN;
        }else if(bezpunkt == OBEN_RECHTS)
        {
            bezpunkt = UNTEN_RECHTS;
        }
        r.set_bezugspunkt(bezpunkt);
        r.set_einfuegepunkt(N.x-Npv.x+element.at(2).toDouble()*Sf*Zf,\
                            N.y-Npv.y-element.at(3).toDouble()*Sf*Zf,\
                            element.at(4).toDouble()*Sf*Zf);
        r.set_laenge(element.at(5).toDouble()*Sf*Zf);
        r.set_breite(element.at(6).toDouble()*Sf*Zf);
        r.set_rad(element.at(7).toDouble()*Sf*Zf);
        r.set_drewi(element.at(8).toDouble());

        QPen pen, pen_alt;
        pen_alt = painter.pen();
        pen.setWidth(element.at(12).toInt());
        pen.setStyle(set_linienstil(element.at(13)));
        pen.setCapStyle(Qt::RoundCap);
        if(i==Aktuelle_zeilennummer)
        {
            pen.setColor(Qt::red);
            pen.setWidth(pen.width()*2);
        }else
        {
            pen.setColor(set_farbe(element.at(10)));
        }
        painter.setPen(pen);

        QBrush brush = painter.brush();
        QBrush brush_alt = painter.brush();
        brush.setColor(set_farbe(element.at(11)));
        painter.setBrush(brush);

        if(r.rad()==0)
        {
            //Rechteck mit eckigen Ecken:
            QPainterPath pp;
            pp.moveTo(r.unl(false).x(),\
                      r.unl(false).y());
            pp.lineTo(r.unr(false).x(),\
                      r.unr(false).y());
            pp.lineTo(r.obr(false).x(),\
                      r.obr(false).y());
            pp.lineTo(r.obl(false).x(),\
                      r.obl(false).y());
            pp.closeSubpath();
            painter.drawPath(pp);

        }else
        {
            //Rechteck runden Ecken:
            punkt2d mitpu = r.mi();
            //mitpu.set_y(mitpu.y()-r.b());
            QPainterPath pp;

            punkt2d p2;
            //Startpunkt:
            p2.set_x(r.unl().x());
            p2.set_y((r.mi().y()+r.b()/2)-r.rad());
            p2 = drehen(mitpu,\
                        p2,\
                        r.drewi(),\
                        true);
            pp.moveTo(p2.x(), p2.y());
            //Rundung links unten:
            p2.set_x(r.unl().x());
            p2.set_y((r.mi().y()+r.b()/2)-r.rad()*2);
            p2 = drehen_arcTo(p2,\
                        r.rad()*2,\
                        r.rad()*2,\
                        r.drewi(),\
                        mitpu);
            pp.arcTo(p2.x(), p2.y(), r.rad()*2, r.rad()*2, 180+r.drewi(), 90);
            //Linie nach rechts unten:
            p2.set_x(r.unr().x()-r.rad());
            p2.set_y((r.mi().y()+r.b()/2));
            p2 = drehen(mitpu,\
                        p2,\
                        r.drewi(),\
                        true);
            pp.lineTo(p2.x(),p2.y());
            //Rundung rechts unten:
            p2.set_x(r.unr().x()-r.rad()*2);
            p2.set_y((r.mi().y()+r.b()/2)-r.rad()*2);
            p2 = drehen_arcTo(p2,\
                        r.rad()*2,\
                        r.rad()*2,\
                        r.drewi(),\
                        mitpu);
            pp.arcTo(p2.x(), p2.y(), r.rad()*2, r.rad()*2, 270+r.drewi(), 90);
            //Linie nach rechts oben:
            p2.set_x(r.obr().x());
            p2.set_y((r.mi().y()-r.b()/2)+r.rad());
            p2 = drehen(mitpu,\
                        p2,\
                        r.drewi(),\
                        true);
            pp.lineTo(p2.x(),p2.y());
            //Rundung rechts oben
            p2.set_x(r.unr().x()-r.rad()*2);
            p2.set_y((r.mi().y()-r.b()/2));
            p2 = drehen_arcTo(p2,\
                        r.rad()*2,\
                        r.rad()*2,\
                        r.drewi(),\
                        mitpu);
            pp.arcTo(p2.x(), p2.y(), r.rad()*2, r.rad()*2, 0+r.drewi(), 90);
            //Linie nach links oben:
            p2.set_x(r.obl().x()+r.rad());
            p2.set_y((r.mi().y()-r.b()/2));
            p2 = drehen(mitpu,\
                        p2,\
                        r.drewi(),\
                        true);
            pp.lineTo(p2.x(),p2.y());
            //Rundung links oben
            p2.set_x(r.obl().x());
            p2.set_y((r.mi().y()-r.b()/2));
            p2 = drehen_arcTo(p2,\
                        r.rad()*2,\
                        r.rad()*2,\
                        r.drewi(),\
                        mitpu);
            pp.arcTo(p2.x(), p2.y(), r.rad()*2, r.rad()*2, 90+r.drewi(), 90);

            pp.closeSubpath();
            painter.drawPath(pp);
        }

        painter.setPen(pen_alt);
        painter.setBrush(brush_alt);
    }

}

void vorschau::zeichneFkon(QString geometrieElement, uint i)
{
    QPainter painter(this);
    painter.setBrush( Qt::white);
    painter.setPen(Qt::black);

    text_zw element;
    element.set_text(geometrieElement,TRZ_PA_);

    if(element.text().contains(STRECKE))
    {
        punkt2d startpunkt, endpunkt;
        startpunkt.set_x(element.at(1).toDouble()*Sf*Zf);
        startpunkt.set_y(element.at(2).toDouble()*Sf*Zf);
        endpunkt.set_x(element.at(4).toDouble()*Sf*Zf);
        endpunkt.set_y(element.at(5).toDouble()*Sf*Zf);

        QPen pen, pen_alt;
        pen_alt = painter.pen();
        pen.setWidth(element.at(8).toInt());
        pen.setStyle(set_linienstil(element.at(9)));
        if(i==Aktuelle_zeilennummer)
        {
            pen.setColor(Qt::red);
            pen.setWidth(pen.width()*2);
        }else
        {
            pen.setColor(set_farbe(element.at(7)));
        }
        pen.setCapStyle(Qt::RoundCap);
        painter.setPen(pen);

        painter.drawLine(N.x-Npv.x+startpunkt.x(), \
                         N.y-Npv.y-startpunkt.y(), \
                         N.x-Npv.x+endpunkt.x(), \
                         N.y-Npv.y-endpunkt.y());

        painter.setPen(pen_alt);
    }else if(element.text().contains(BOGEN))
    {
        double rad = element.at(7).toDouble()*Sf*Zf;
        punkt2d mipu;
        mipu.set_x(element.at(9).toDouble()*Sf*Zf);//Mittelpunkt in X
        mipu.set_y(element.at(10).toDouble()*Sf*Zf);//Mittelpunkt in Y
        punkt2d obli;
        obli.set_x(mipu.x()-rad);
        obli.set_y(mipu.y()+rad);

        punkt2d mp;
        mp.set_x(element.at(9).toDouble());//Mittelpunkt in X
        mp.set_y(element.at(10).toDouble());//Mittelpunkt in Y
        punkt2d sp;
        sp.set_x(element.at(1).toDouble());//Start in X
        sp.set_y(element.at(2).toDouble());//Start in Y
        punkt2d ep;
        ep.set_x(element.at(4).toDouble());//Ende in X
        ep.set_y(element.at(5).toDouble());//Ende in Y
        double stawi=0, bogwi=0;

        if(element.at(8) == "nein")//Bogen gegen den Uhrzeigersinn
        {
            stawi = winkel(sp.x(),   \
                           sp.y(),   \
                           mp.x(),   \
                           mp.y());
            bogwi = winkel(sp.x(),   \
                           sp.y(),   \
                           mp.x(),   \
                           mp.y(),   \
                           ep.x(),   \
                           ep.y());
        }else//Bogen im Uhrzeigersinn
        {
            stawi = winkel(ep.x(),   \
                           ep.y(),   \
                           mp.x(),   \
                           mp.y());
            bogwi = winkel(ep.x(),   \
                           ep.y(),   \
                           mp.x(),   \
                           mp.y(),   \
                           sp.x(),   \
                           sp.y());
        }
        if(bogwi<0)
        {
            bogwi = 360+bogwi;
        }

        QPen pen, pen_alt;
        pen_alt = painter.pen();
        pen.setWidth(element.at(12).toInt());
        pen.setStyle(set_linienstil(element.at(13)));
        if(i==Aktuelle_zeilennummer)
        {
            pen.setColor(Qt::red);
            pen.setWidth(pen.width()*2);
        }else
        {
            pen.setColor(set_farbe(element.at(11)));
        }
        pen.setCapStyle(Qt::RoundCap);
        painter.setPen(pen);

        painter.drawArc(N.x-Npv.x+obli.x(),\
                        N.y-Npv.y-obli.y(),\
                        rad*2,\
                        rad*2,\
                        stawi*16,\
                        bogwi*16);

        painter.setPen(pen_alt);
    }
}

void vorschau::werkstueck_darstellung_berechnen()
{
    QString format = W.zustand().format();
    int randabstand = 10;
    float maximallaenge = W.max_x() - W.min_x();
    float maximalbreite = W.max_y() - W.min_y();

    float bildlaenge = width()-randabstand*2;
    float bildbreite = height()-randabstand*2;

    float faktor_laenge = bildlaenge/maximallaenge;
    float faktor_breite = bildbreite/maximalbreite;

    if(faktor_laenge < faktor_breite)
    {
        set_sf(faktor_laenge);
    }else
    {
        set_sf(faktor_breite);
    }

    float laenge = Wst.l() * sf() * Zf;
    float breite = Wst.b() * sf() * Zf;

    Wstd.set_laenge(laenge);
    Wstd.set_breite(breite);

    punkt basispunkt;
    basispunkt.x = randabstand;
    basispunkt.y = height()-randabstand;

    N.x = basispunkt.x - W.min_x(format)*Sf * Zf;
    N.y = basispunkt.y + W.min_y(format)*Sf * Zf;

    sende_wstmas(W.zustand().l(), W.zustand().b(), W.dicke());
}

void vorschau::slot_aktualisieren(werkstueck w_neu, int aktive_zeile)
{
    W = w_neu;
    Geotext = W.zustand().geo().text_zwei();
    Wst.set_laenge(w_neu.zustand().l());
    Wst.set_breite(w_neu.zustand().b());
    Aktuelle_zeilennummer = aktive_zeile;
    werkstueck_darstellung_berechnen();
    this->update();
}

void vorschau::slot_aktualisieren_einzelwst(werkstueck w_neu, int aktive_zeile)
{
    W = w_neu;
    Geotext = W.geo().text_zwei();
    Wst.set_laenge(w_neu.laenge());
    Wst.set_breite(w_neu.breite());
    Aktuelle_zeilennummer = aktive_zeile;
    werkstueck_darstellung_berechnen();
    this->update();
}

void vorschau::slot_aktives_Element_einfaerben(int zeilennummer)
{
    //Element aus dieser Zeile farbig markieren
    Aktuelle_zeilennummer = zeilennummer;
    werkstueck_darstellung_berechnen();
    this->update();
}

punkt vorschau::drehen_arcTo(punkt oben_links, float laenge, float breite, \
                             float drehwinkel, punkt drehzentrum)
{
    punkt mittelpunkt;
    mittelpunkt.x = oben_links.x + laenge/2;
    mittelpunkt.y = oben_links.y + breite/2;

    mittelpunkt = drehen(drehzentrum, mittelpunkt, drehwinkel, true);

    punkt p;
    p.x = mittelpunkt.x - laenge/2;
    p.y = mittelpunkt.y - breite/2;

    return p;
}

punkt2d vorschau::drehen_arcTo(punkt2d oben_links, double laenge, double breite, \
                               double drehwinkel, punkt2d drehzentrum)
{
    punkt2d mittelpunkt;
    mittelpunkt.set_x(oben_links.x() + laenge/2);
    mittelpunkt.set_y(oben_links.y() + breite/2);

    mittelpunkt = drehen(drehzentrum, mittelpunkt, drehwinkel, true);

    punkt2d p2;
    p2.set_x(mittelpunkt.x() - laenge/2);
    p2.set_y(mittelpunkt.y() - breite/2);

    return p2;
}

//-------------------------------------------------------------
float vorschau::sf()
{
    return Sf;
}

//-------------------------------------------------------------
void vorschau::set_sf(float neuer_faktor)
{
    Sf = neuer_faktor;
}

void vorschau::zoom(bool dichter)
{
    if(dichter == true)
    {
        Zf = Zf + Zf/25;
    }else
    {
        if(Zf > 1)
        {
            Zf = Zf - Zf/25;
        }else
        {
            //Npv.x = 0;
            //Npv.y = 0;
        }
    }

}

punkt2d vorschau::mauspos_npanschlag()
{
    QPoint p = this->mapFromGlobal(QCursor::pos());
    int abst_nullp_x = p.x() - N.x + Npv.x;
    int abst_nullp_y = p.y() - N.y + Npv.y;

    punkt2d p2d;
    p2d.set_x(abst_nullp_x/Sf/Zf);
    p2d.set_y(abst_nullp_y/Sf*-1/Zf);
    return p2d;
}

punkt2d vorschau::mauspos_npwst()
{
    punkt2d p;
    p = mauspos_npanschlag();
    p.set_x(p.x()-0);
    p.set_y(p.y()-W.zustand().ay());
    return p;
}

uint vorschau::zeile_von_Mauspos()
{
    uint zeile = 0;
    double abst = 9999999999;
    strecke s; //nehmen wir für Längenberechnung/Abstandsberechnung
    s.set_stapu(mauspos_npanschlag());
    text_zw geotext = Geotext;

    for(uint i=0;i<geotext.count();i++)
    {
        text_zw spalten;
        spalten.set_text(geotext.at(i),TRZ_EL_);

        for(uint ii=0;ii<spalten.count();ii++)
        {
            text_zw element;
            element.set_text(spalten.at(ii),TRZ_PA_);

            if(element.text().contains(PUNKT))
            {
                punkt3d ep;
                ep.set_text(element.text());
                s.set_endpu(ep);
                double l = s.laenge2d();
                if(l < abst)
                {
                    abst = l;
                    zeile = i;
                }
            }else if(element.text().contains(STRECKE))
            {
                strecke s2;
                s2.set_text(element.text());
                double l = s2.abst(mauspos_npanschlag());
                if(l < abst)
                {
                    abst = l;
                    zeile = i;
                }
            }else if(element.text().contains(BOGEN))
            {
                bogen b;
                b.set_text(element.text());
                punkt3d sp, ep, mipu;
                sp = b.start();
                ep = b.ende();
                mipu.set_x(b.mitte().x());
                mipu.set_y(b.mitte().y());
                strecke s1, s2, s3;
                s1.set_stapu(mipu);
                s2.set_stapu(mipu);
                s3.set_stapu(mipu);
                s1.set_endpu(sp);
                s2.set_endpu(ep);
                s3.set_endpu(mauspos_npanschlag());
                double w1, w2, w3;
                w1 = s1.wink();
                w2 = s2.wink();
                w3 = s3.wink();
                if(w1 > w2)
                {
                    double tmp;
                    tmp = w1;
                    w1 = w2;
                    w2 = tmp;
                }
                if(  (w1 <= w3)  &&  (w3 <= w2)  )
                {
                    //Abstandsberechnung ähnlich wie beim Kreis:
                    s.set_endpu(mipu);
                    double l = s.laenge2d();
                    double rad = b.rad();
                    if(l > rad)
                    {
                        //Punkt auf bOgen-Außenseite
                        l = l - rad;
                    }else
                    {
                        //Punkt auf Bogen-Innenseite
                        l = rad - l;
                    }
                    if(l < abst)
                    {
                        abst = l;
                        zeile = i;
                    }
                }else
                {
                    strecke s1, s2;
                    s1.set_stapu(sp);
                    s2.set_stapu(ep);
                    s1.set_endpu(mauspos_npanschlag());
                    s2.set_endpu(mauspos_npanschlag());
                    double abst_sp, abst_ep, l;
                    abst_sp = s1.laenge2d();
                    abst_ep = s2.laenge2d();
                    if(abst_sp < abst_ep)
                    {
                        l = abst_sp;
                    }else
                    {
                        l = abst_ep;
                    }
                    if(l < abst)
                    {
                        abst = l;
                        zeile = i;
                    }
                }
            }else if(  element.text().contains(KREIS)  ||  element.text().contains(ZYLINDER)  )
            {
                punkt2d ep;
                ep.set_x(element.at(1).toDouble());
                ep.set_y(element.at(2).toDouble());
                s.set_endpu(ep);
                double l = s.laenge2d();
                double rad = element.at(4).toDouble();
                if(l > rad)
                {
                    l = l - rad;
                }else
                {
                    double abst_mipu = l;
                    double abst_umkreis = rad - l;
                    double abst_min;
                    if(abst_mipu < abst_umkreis)
                    {
                        abst_min = abst_mipu;
                    }else
                    {
                        abst_min = abst_umkreis;
                    }
                    l = abst_min;
                }
                if(l < abst)
                {
                    abst = l;
                    zeile = i;
                }
            }else if(  element.text().contains(RECHTECK3D)  ||  element.text().contains(WUERFEL)  )
            {
                punkt3d pol, por, pul, pur;
                if(element.text().contains(RECHTECK3D))
                {
                    rechteck3d r;
                    r.set_text(element.text());
                    pol = r.obl();
                    por = r.obr();
                    pul = r.unl();
                    pur = r.unr();
                }else
                {
                    wuerfel w;
                    w.set_text(element.text());
                    pol = w.obl();
                    por = w.obr();
                    pul = w.unl();
                    pur = w.unr();
                }
                strecke sli, sre, sob, sun;
                sli.set_stapu(pul);
                sli.set_endpu(pol);
                sre.set_stapu(pur);
                sre.set_endpu(por);
                sob.set_stapu(pol);
                sob.set_endpu(por);
                sun.set_stapu(pul);
                sun.set_endpu(pur);
                double abst_li, abst_re, abst_ob, abst_un;
                abst_li = sli.abst(mauspos_npanschlag());
                abst_re = sre.abst(mauspos_npanschlag());
                abst_ob = sob.abst(mauspos_npanschlag());
                abst_un = sun.abst(mauspos_npanschlag());
                double min = abst_li;
                if(abst_re < min)
                {
                    min = abst_re;
                }
                if(abst_ob < min)
                {
                    min = abst_ob;
                }
                if(abst_un < min)
                {
                    min = abst_un;
                }
                if(min < abst)
                {
                    abst = min;
                    zeile = i;
                }
            }
        }
    }
    return zeile;
}

void vorschau::mouseMoveEvent(QMouseEvent *event)
{
    if(Mrg)
    {
        Npv.x = Npv.x + Maus_pos_alt_x-event->x();
        Npv.y = Npv.y + Maus_pos_alt_y-event->y();
        Maus_pos_alt_x = event->x();
        Maus_pos_alt_y = event->y();
        this->update();
    }

    QPoint p = this->mapFromGlobal(QCursor::pos());
    int abst_nullp_x = p.x() - N.x+Npv.x;
    int abst_nullp_y = p.y() - N.y+Npv.y;

    QPoint p_real;
    p_real.setX(abst_nullp_x/Sf/Zf);
    p_real.setY(abst_nullp_y/Sf*-1/Zf);

    emit sende_maus_pos(p_real);
}

void vorschau::wheelEvent(QWheelEvent *event)
{
    QPoint mauspos = event->pos();
    mauspos.setY(this->height()-mauspos.y());
    QPoint wstpos;
    wstpos.setX(  (mauspos.x() - N.x+Npv.x)  /Sf/Zf  );
    wstpos.setY(  (N.x+Npv.y - mauspos.y())  /Sf/Zf  );

    int i = event->delta();
    if(i<0)
    {
        zoom(false);
    }else
    {
        zoom(true);
    }

    QPoint wstposneu;
    wstposneu.setX(  (mauspos.x() - N.x+Npv.x)  /Sf/Zf  );
    wstposneu.setY(  (N.x+Npv.y - mauspos.y())  /Sf/Zf  );
    int xversmm = wstposneu.x() - wstpos.x();
    int yversmm = wstposneu.y() - wstpos.y();
    int xverspixel = xversmm*Sf*Zf;
    int yverspixel = yversmm*Sf*Zf;
    Npv.x = Npv.x-xverspixel;
    Npv.y = Npv.y-yverspixel;
    if(Zf<=1)
    {
        Npv.x = 0;
        Npv.y = 0;
    }
    this->update();
}

void vorschau::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MidButton)
    {
        Mrg = true;
        Maus_pos_alt_x = event->x();
        Maus_pos_alt_y = event->y();
    }else if(event->button() == Qt::RightButton)
    {
        punkt2d pwst;
        pwst = mauspos_npwst();
        QString msg_pos_wst;
        msg_pos_wst += "(X: ";
        msg_pos_wst += pwst.x_QString();
        msg_pos_wst += " / Y: ";
        msg_pos_wst += pwst.y_QString();
        msg_pos_wst += ")";

        uint zeile = zeile_von_Mauspos();
        Zeile_von_maus_pos = zeile;
        slot_aktives_Element_einfaerben(zeile);

        sende_zeilennummer(Zeile_von_maus_pos, false);

        QMenu m(this);
        m.addAction("Ansicht einpassen", this, SLOT(slot_zf_gleich_eins()), 0) ;
        m.addAction(msg_pos_wst, this, SLOT(slot_tunix()), 0) ;
        if(Bearb_erlaubt == true)
        {
            QString msgedit;
            msgedit += "Zeile ";
            msgedit += int_to_qstring(zeile);
            msgedit += " bearbeiten";
            m.addAction(msgedit, this, SLOT(slot_sende_zeilennummer()), 0) ;
        }
        m.exec(this->mapFrom(this, QCursor::pos()));

    }else if(event->button() == Qt::LeftButton)
    {
        uint zeile = zeile_von_Mauspos();
        Zeile_von_maus_pos = zeile;
        slot_aktives_Element_einfaerben(zeile);
        sende_zeilennummer(Zeile_von_maus_pos, false);
    }
}

void vorschau::slot_sende_zeilennummer()
{
    uint zeile = Zeile_von_maus_pos;
    slot_aktives_Element_einfaerben(zeile);
    emit sende_zeilennummer(zeile, true);
}

void vorschau::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MidButton)
    {
        Mrg = false;
    }
}

void vorschau::slot_zf_gleich_eins()
{
    Zf = 1;
    Npv.x = 0;
    Npv.y = 0;
    update_cad();
}

void vorschau::slot_tunix()
{

}

QColor vorschau::set_farbe(QString farbe)
{
    QColor qfarbe = Qt::black;
    if(farbe == FARBE_KEINE)
    {
        qfarbe = Qt::transparent;
    }else if(farbe == FARBE_SCHWARZ)
    {
        qfarbe = Qt::black;
    }else if(farbe == FARBE_WEISS)
    {
        qfarbe = Qt::white;
    }else if(farbe == FARBE_BLAU)
    {
        qfarbe = Qt::blue;
    }else if(farbe == FARBE_HELLBLAU)
    {
        qfarbe.setRgb(0,240,240);
    }else if(farbe == FARBE_ROT)
    {
        qfarbe = Qt::red;
    }else if(farbe == FARBE_ROSE)
    {
        qfarbe.setRgb(255,0,128);
    }else if(farbe == FARBE_GRUEN)
    {
        qfarbe = Qt::green;
    }else if(farbe == FARBE_GELB)
    {
        qfarbe = Qt::yellow;
    }else if(farbe == FARBE_GRAU)
    {
        qfarbe = Qt::gray;
    }else if(farbe == FARBE_DUNKELGRAU)
    {
        qfarbe = Qt::darkGray;
    }else if(farbe == FARBE_BRAUN)
    {
        qfarbe.setRgb(185,122,87);
    }
    return qfarbe;
}

Qt::PenStyle vorschau::set_linienstil(QString stil)
{
    Qt::PenStyle style = Qt::SolidLine;
    if(stil == STIL_TRANSPARENT)
    {
        style = Qt::NoPen;
    }else if(stil == STIL_TRANSPARENT)
    {
        style = Qt::NoPen;
    }else if(stil == STIL_DURCHGEHEND)
    {
        style = Qt::SolidLine;
    }else if(stil == STIL_GESTRICHELT)
    {
        style = Qt::DashLine;
    }else if(stil == STIL_GEPUNKTET)
    {
        style = Qt::DotLine;
    }else if(stil == STIL_STRICHP)
    {
        style = Qt::DashDotLine;
    }else if(stil == STIL_STRICHPP)
    {
        style = Qt::DashDotDotLine;
    }

    return style;
}


















