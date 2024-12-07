#include "bogen.h"

bogen::bogen()
{
    Fehler = true;
}

bogen::bogen(punkt3d startpunkt, punkt3d endpunkt)
{
    set_startpunkt(startpunkt);
    set_endpunkt(endpunkt);
}

bogen::bogen(QString geotext)
{
    set_text(geotext);
}

bogen::bogen(punkt3d startpunkt, punkt3d endpunkt, \
             float radiuswert, bool im_uhrzeigersinn)
{
    set_startpunkt(startpunkt);
    set_endpunkt(endpunkt);
    set_radius(radiuswert, im_uhrzeigersinn);
}

bogen::bogen(punkt2d mipu, double rad, double startwinkel, double endwinkel)
{
    Rad = rad;
    punkt3d p;
    p.set_x(mipu.x());
    p.set_y(mipu.y());
    strecke ssp;
    ssp.set_stapu(p);
    p.set_x(mipu.x()+rad);
    ssp.set_endpu(p);
    strecke sep = ssp;
    ssp.drenen_um_stapu_2d(startwinkel, false);
    sep.drenen_um_stapu_2d(endwinkel, false);
    Stapu = ssp.endpu();
    Endpu = sep.endpu();
    Bogen_im_uzs = false;

}

bogen::bogen(punkt3d mipu, double rad, double startwinkel, double endwinkel)
{
    Rad = rad;
    punkt3d p;
    p.set_x(mipu.x());
    p.set_y(mipu.y());
    p.set_z(mipu.z());
    strecke ssp;
    ssp.set_stapu(p);
    p.set_x(mipu.x()+rad);
    ssp.set_endpu(p);
    strecke sep = ssp;
    ssp.drenen_um_stapu_2d(startwinkel, false);
    sep.drenen_um_stapu_2d(endwinkel, false);
    Stapu = ssp.endpu();
    Endpu = sep.endpu();
    Bogen_im_uzs = false;

}

void bogen::set_text(QString geotext)
{
    text_zw tz;
    tz.set_text(geotext,TRZ_PA_);
    punkt3d start;
    start.set_x(tz.at(1).toDouble());
    start.set_y(tz.at(2).toDouble());
    start.set_z(tz.at(3).toDouble());
    punkt3d ende;
    ende.set_x(tz.at(4).toDouble());
    ende.set_y(tz.at(5).toDouble());
    ende.set_z(tz.at(6).toDouble());
    float rad =tz.at(7).toFloat();
    bool uzs;
    if(tz.at(8).contains("ja"))
    {
        uzs = true;
    }else
    {
        uzs = false;
    }
    set_startpunkt(start);
    set_endpunkt(ende);
    set_radius(rad, uzs);
    set_farbe(tz.at(11));
    set_linienbreite(tz.at(12).toInt());
    set_stil(tz.at(13));
}

void bogen::set_startpunkt(punkt3d startpunkt)
{
    Stapu = startpunkt;
}

void bogen::set_endpunkt(punkt3d endpunkt)
{
    Endpu = endpunkt;
}

void bogen::set_radius(float radiuswert, bool im_uhrzeigersinn)
{
    Rad = radiuswert;
    Bogen_im_uzs = im_uhrzeigersinn;
}

void bogen::set_radius(float radiuswert, punkt2d bogenrichtung)
{

    //Es muss geprüft werden, ob der Punkt links oder rechts von der Strecke liegt,
    //die vom Bogenstart- bis Bogenendpunkt geht

    /*
     * p = (px-x1)*(y1-y2) + (py-y1)*(x2-x1)
     * p = 0 : Punkt auf Linie
     * p < 0 : Punkt unter Linie
     * p > 0 : Punkt über Linie
    */

    double px = bogenrichtung.x();
    double py = bogenrichtung.y();
    double x1 = start().x();
    double x2 = ende().x();
    double y1 = start().y();
    double y2 = ende().y();

    double p = ((px-x1)*(y1-y2)) + ((py-y1)*(x2-x1));

    if(p<0)
    {
        set_radius(radiuswert, false);
    }else if(p>0)
    {
        set_radius(radiuswert, true);
    }else
    {
        //if(p=0)
        //-->der Punkt "Bogenrichtung" liegt auf der Linie
        Fehler = true;
        Fehlertext = "Bogenrichtung nicht bestimmbar!";
    }
}

QString bogen::text()
{
    QString msg = BOGEN;
    msg += TRZ_PA;
    msg += start().x_QString();
    msg += TRZ_PA;
    msg += start().y_QString();
    msg += TRZ_PA;
    msg += start().z_QString();
    msg += TRZ_PA;
    msg += ende().x_QString();
    msg += TRZ_PA;
    msg += ende().y_QString();
    msg += TRZ_PA;
    msg += ende().z_QString();
    msg += TRZ_PA;
    msg += rad_qString();
    msg += TRZ_PA;
    msg += im_uzs_QString();
    msg += TRZ_PA;
    msg += mitte().x_QString();
    msg += TRZ_PA;
    msg += mitte().y_QString();
    msg += TRZ_PA;
    msg += farbe();
    msg += TRZ_PA;
    msg += linienbreite_qstring();
    msg += TRZ_PA;
    msg += stil();

    return msg;
}

void bogen::richtung_unkehren()
{
    punkt3d tmp = Stapu;
    Stapu = Endpu;
    Endpu = tmp;

    if(Bogen_im_uzs == true)
    {
        Bogen_im_uzs = false;
    }else
    {
        Bogen_im_uzs = true;
    }
}

void bogen::verschieben_um(double xversatz, double yversatz)
{
    //if(hat_fehler() == false)
    //{
        Stapu.verschieben_um(xversatz, yversatz);
        Endpu.verschieben_um(xversatz, yversatz);
    //}
}

double bogen::bogenwinkel()
{
    return winkel(start(), mitte(), ende());
}

punkt2d bogen::mitte()
{
    punkt2d mittelp;
    punkt2d pstart(Stapu); //Z-Werte sollen hier ignoriert werden
    punkt2d pende(Endpu);    //Z-Werte sollen hier ignoriert werden
    strecke stre_spep;
    stre_spep.set_stapu(Stapu);
    stre_spep.set_endpu(Endpu);
    double laenge = stre_spep.laenge2d();
    Fehler = false;
    if(  start() == ende()  )
    {
        Fehler = true;
        Fehlertext = "Fehler! Start und Endpunkt sind deckungsgleich!";
    }else if( rad() <= 0)
    {
        Fehler = true;
        Fehlertext = "Fehler! Radius <= 0!";
    }else if( rad() < laenge/2)
    {
        Fehler = true;
        Fehlertext = "Fehler! Radius zu klein für Punktabstand Start-Ende";
    }else if( rad() == laenge/2)
    {
        mittelp = stre_spep.mipu2d();
    }else
    {
        double a = stre_spep.laenge2d()/2; //Hälfte des Abstandes von
                                             //Start und Endpunkt
        double r = rad();
        double x = sqrt(r*r - a*a)*2; //Länge der Mittelsenkrechtenn zu stre_spep

        strecke stre_tmp = stre_spep;
        stre_tmp.drenen_um_mipu_2d(90,true);
        stre_tmp.set_laenge_2d(x, strecke_bezugspunkt_mitte);

        if(im_uzs() == false)
        {
            mittelp.set_x(stre_tmp.stapu().x());
            mittelp.set_y(stre_tmp.stapu().y());
        }else
        {
            mittelp.set_x(stre_tmp.endpu().x());
            mittelp.set_y(stre_tmp.endpu().y());
        }
    }

    if(Fehler == false)
    {
        return mittelp;
    }else
    {
        punkt2d tmp;
        tmp.set_x(0);
        tmp.set_y(0);
        return tmp;
    }
}
punkt2d mitte_(punkt3d stapu, punkt3d endpu, double rad, bool bogen_im_uzs)
{
    double dx = endpu.x() - stapu.x();
    double dy = endpu.y() - stapu.y();

    // Abstand zwischen Start- und Endpunkt
    double chord = std::sqrt(dx * dx + dy * dy);

    // Mittelpunkt der Sehne
    punkt2d chordMidpoint;
    chordMidpoint.set_x((stapu.x() + endpu.x()) / 2);
    chordMidpoint.set_y((stapu.y() + endpu.y()) / 2);
    //Point chordMidpoint = {(start.x + end.x) / 2, (start.y + end.y) / 2};

    // Höhe des Kreisbogens
    double h = std::sqrt(rad * rad - (chord / 2) * (chord / 2));

    // Normalisierter Vektor senkrecht zur Sehne
    double nx = -dy / chord;
    double ny = dx / chord;

    // Vorzeichen der Höhe basierend auf der Bogenrichtung
    //int sign = (direction == Direction::CCW) ? 1 : -1;
    int sign;
    if(bogen_im_uzs)
    {
        sign = -1;
    }else
    {
        sign = 1;
    }

    // Bogenmittelpunkt
    punkt2d arcMidpoint;
    arcMidpoint.set_x(chordMidpoint.x() + sign * h * nx);
    arcMidpoint.set_y(chordMidpoint.y() + sign * h * ny);

    return arcMidpoint;
}
punkt2d bogen::mitte2()
{
    return mitte_(Stapu, Endpu, Rad, Bogen_im_uzs);
}

void bogen::set_bogenwinkel(double wi, bogen_bezugspunkt bezug)
{
    if(Fehler == true)
    {
        return;
    }else
    {
        if(bezug == bogen_bezugspunkt_start)
        {
            strecke s;
            s.set_stapu(mitte());
            s.set_endpu(start());
            s.drenen_um_stapu_2d(wi, im_uzs());
            set_endpunkt(s.endpu());
        }else if(bezug == bogen_bezugspunkt_ende)
        {
            strecke s;
            s.set_stapu(mitte());
            s.set_endpu(ende());
            s.drenen_um_stapu_2d(wi, !im_uzs());
            set_startpunkt(s.endpu());
        }else
        {
            strecke s;
            s.set_stapu(start());
            s.set_endpu(ende());
            s.set_endpu(s.mipu());
            s.set_stapu(mitte());
            s.set_laenge_2d(rad(), strecke_bezugspunkt_start);
            s.drenen_um_stapu_2d(wi/2, im_uzs());
            set_endpunkt(s.endpu());
            s.drenen_um_stapu_2d(wi, !im_uzs());
            set_startpunkt(s.endpu());
        }
    }
}

void bogen::mb()
{
    QString msg;
    msg = "Bogenwerte:\n\n";
    msg += "Mittelpunkt:\n";
    msg += "X= ";
    msg += mitte().x_QString();
    msg += "\nY= ";
    msg += mitte().y_QString();
    msg += "\n\nStartpunkt:\n";
    msg += "X= ";
    msg += start().x_QString();
    msg += "\nY= ";
    msg += start().y_QString();
    msg += "\n\nEntpunkt:\n";
    msg += "X= ";
    msg += ende().x_QString();
    msg += "\nY= ";
    msg += ende().y_QString();
    msg += "\n\nRadius:\n";
    msg += rad_qString();
    msg += "\n\nBogenwinkel:\n";
    msg += double_to_qstring(bogenwinkel());
    msg += "\n\nFehlermeldungen:\n";
    msg += Fehlertext;

    QMessageBox mb;
    mb.setText(msg);
    mb.exec();
}

punkt3d bogsehnmipu(punkt3d stapu, punkt3d endpu, double rad, bool bogen_im_uzs)
{
    punkt2d mipu = mitte_(stapu, endpu, rad, bogen_im_uzs);

    // Vektoren vom Mittelpunkt zum Start- und Endpunkt berechnen
    double vx1 = stapu.x() - mipu.x();
    double vy1 = stapu.y() - mipu.y();
    double vx2 = endpu.x() - mipu.x();
    double vy2 = endpu.y() - mipu.y();

    // Radius berechnen
    //double radius = std::sqrt(vx1 * vx1 + vy1 * vy1);

    // Winkel zwischen den Vektoren berechnen
    double angle = std::atan2(vy2, vx2) - std::atan2(vy1, vx1);
    if (angle < 0) angle += 2 * M_PI;

    // Halben Winkel berechnen
    double halfAngle = angle / 2.0;

    // Rotationsmatrix anwenden
    double cosHalfAngle = std::cos(halfAngle);
    double sinHalfAngle = std::sin(halfAngle);
    double rotatedX = vx1 * cosHalfAngle - vy1 * sinHalfAngle;
    double rotatedY = vx1 * sinHalfAngle + vy1 * cosHalfAngle;

    // Punkt in der Mitte der Bogenlänge berechnen
    punkt3d bomipu;
    bomipu.set_x(mipu.x() + rotatedX);
    bomipu.set_y(mipu.y() + rotatedY);

    return bomipu;
}
punkt3d bogsehnmipu(punkt3d stapu, punkt3d endpu, punkt3d mipu, bool bogen_im_uzs)
{
    double vx1 = stapu.x() - mipu.x();
    double vy1 = stapu.y() - mipu.y();
    double vx2 = endpu.x() - mipu.x();
    double vy2 = endpu.y() - mipu.y();

    // Radius berechnen
    //double radius = std::sqrt(vx1 * vx1 + vy1 * vy1);

    // Winkel zwischen den Vektoren berechnen
    double angle = std::atan2(vy2, vx2) - std::atan2(vy1, vx1);

    // Winkel anpassen basierend auf der Richtung
    if (bogen_im_uzs)
    {
        if (angle > 0) angle -= 2 * M_PI;
    } else// CCW
    {
        if (angle < 0) angle += 2 * M_PI;
    }

    // Halben Winkel berechnen
    double halfAngle = angle / 2.0;

    // Rotationsmatrix anwenden
    double cosHalfAngle = std::cos(halfAngle);
    double sinHalfAngle = std::sin(halfAngle);
    double rotatedX = vx1 * cosHalfAngle - vy1 * sinHalfAngle;
    double rotatedY = vx1 * sinHalfAngle + vy1 * cosHalfAngle;

    // Punkt in der Mitte der Bogenlänge berechnen
    punkt3d midpoint;
    midpoint.set_x(mipu.x() + rotatedX);
    midpoint.set_y(mipu.y() + rotatedY);

    return midpoint;
}
