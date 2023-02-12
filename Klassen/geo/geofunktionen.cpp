#include "geofunktionen.h"

punkt drehen(punkt drehzentrum, punkt alter_punkt, \
             float drehwinkel, bool drehrichtung_im_uhrzeigersinn)
{
    if(drehwinkel == 0)
    {
        return alter_punkt;
    }else{
        punkt neuer_punkt;
        if(drehrichtung_im_uhrzeigersinn == true)
        {
            drehwinkel = -drehwinkel;
        }
        neuer_punkt.x = drehzentrum.x + (alter_punkt.x - drehzentrum.x)\
                *cos_d(drehwinkel) - (alter_punkt.y - drehzentrum.y)*sin_d(drehwinkel);
        neuer_punkt.y = drehzentrum.y + (alter_punkt.x - drehzentrum.x)\
                *sin_d(drehwinkel) + (alter_punkt.y - drehzentrum.y)*cos_d(drehwinkel);
        return neuer_punkt;
    }
}

punkt2d drehen(punkt2d drehzentrum, punkt2d alter_punkt, \
             float drehwinkel, bool drehrichtung_im_uhrzeigersinn)
{
    if(drehwinkel == 0)
    {
        return alter_punkt;
    }else{
        punkt2d neuer_punkt;
        if(drehrichtung_im_uhrzeigersinn == true)
        {
            drehwinkel = -drehwinkel;
        }
        neuer_punkt.set_x(\
                           drehzentrum.x() + (alter_punkt.x() - drehzentrum.x())\
                           *cos_d(drehwinkel) - (alter_punkt.y() - drehzentrum.y())\
                           *sin_d(drehwinkel)\
                           );
        neuer_punkt.set_y(\
                          drehzentrum.y() + (alter_punkt.x() - drehzentrum.x())\
                          *sin_d(drehwinkel) + (alter_punkt.y() - drehzentrum.y())\
                          *cos_d(drehwinkel)\
                          );
        return neuer_punkt;
    }
}

punkt3d drehen(punkt3d drehzentrum, punkt3d alter_punkt, \
               double drehwinkel, bool drehrichtung_im_uhrzeigersinn = false)
{
    if(drehwinkel == 0)
    {
        return alter_punkt;
    }else{
        punkt3d neuer_punkt;
        if(drehrichtung_im_uhrzeigersinn == true)
        {
            drehwinkel = -drehwinkel;
        }
        neuer_punkt.set_x(\
                           drehzentrum.x() + (alter_punkt.x() - drehzentrum.x())\
                           *cos_d(drehwinkel) - (alter_punkt.y() - drehzentrum.y())\
                           *sin_d(drehwinkel)\
                           );
        neuer_punkt.set_y(\
                          drehzentrum.y() + (alter_punkt.x() - drehzentrum.x())\
                          *sin_d(drehwinkel) + (alter_punkt.y() - drehzentrum.y())\
                          *cos_d(drehwinkel)\
                          );
        neuer_punkt.set_z(alter_punkt.z());
        return neuer_punkt;
    }
}
punkt drehen_ij(punkt drehzentrum, float drehwinkel, bool drehrichtung_im_uhrzeigersinn, \
                punkt bezugspunkt_ij, punkt punkt_ij)
{
    if(drehwinkel == 0)
    {
        return punkt_ij;
    }else{
        bezugspunkt_ij = drehen(drehzentrum, bezugspunkt_ij, \
                                drehwinkel, drehrichtung_im_uhrzeigersinn);
        punkt p;
        p.x = 0;
        p.y = 0;
        punkt_ij = drehen(p, punkt_ij, drehwinkel, drehrichtung_im_uhrzeigersinn);
        return punkt_ij;
    }
}

double winkel(double endpunkt_x, double endpunkt_y,\
              double mittelpunkt_x, double mittelpunkt_y)
{
    //berechnet wird immer der Winkel zur gedachten waagerechten Grundlinie
    //im Gegenuhrzeigersinn
    double wi, xdif, ydif;
    xdif = endpunkt_x - mittelpunkt_x;
    ydif = endpunkt_y - mittelpunkt_y;
    if(  (xdif > 0)  &&  (ydif == 0)  )
    {
        wi = 0;
    }else if(  (xdif < 0)  &&  (ydif == 0)  )
    {
        wi = 180;
    }else if(  (xdif == 0)  &&  (ydif > 0)  )
    {
        wi = 90;
    }else if(  (xdif == 0)  &&  (ydif < 0)  )
    {
        wi = 270;
    }else if(  (xdif > 0)  &&  (ydif > 0)  )
    {
        //tan(alpha) == Gegenkathete / Ankathete
        //tan(wi)    == ydif         / xdif
        wi = atan(ydif/xdif);
        wi = wi*180/M_PI;//Weil sonst Ergebnis in Bogenmaß;
    }else if(  (xdif < 0)  &&  (ydif > 0)  )
    {
        xdif = xdif * -1;
        wi = atan(ydif/xdif);
        wi = wi*180/M_PI;//Weil sonst Ergebnis in Bogenmaß;
        wi = 180 - wi;
    }else if(  (xdif < 0)  &&  (ydif < 0)  )
    {
        xdif = xdif * -1;
        ydif = ydif * -1;
        wi = atan(ydif/xdif);
        wi = wi*180/M_PI;//Weil sonst Ergebnis in Bogenmaß;
        wi = wi + 180;
    }else//(xdif > 0)  &&  (ydif < 0)
    {
        ydif = ydif * -1;
        wi = atan(ydif/xdif);
        wi = wi*180/M_PI;//Weil sonst Ergebnis in Bogenmaß;
        wi = 360 - wi;
    }
    return wi;
    /*
    punkt3d mipu;
    mipu.set_x(mittelpunkt_x);
    mipu.set_y(mittelpunkt_y);
    punkt3d enpu;
    enpu.set_x(endpunkt_x);
    enpu.set_y(endpunkt_y);
    strecke s;
    s.set_start(mipu);
    s.set_ende(enpu);

    double hypthenuse = s.laenge2dim();
    double gegenkathete = mittelpunkt_y - endpunkt_y;

    double wi =  asin(gegenkathete/hypthenuse)/M_PI*180*-1;//Weil sonst Ergebnis in Bogenmaß;

    if(endpunkt_x - mittelpunkt_x < 0   &&\
       wi > 0)
    {
        wi = 180-wi;
    }

    if(endpunkt_x - mittelpunkt_x < 0   &&\
       wi < 0)
    {
        wi = 180-wi;
    }else if(mittelpunkt_x - endpunkt_x < 0   &&\
             wi < 0)
    {
        wi = 360+wi;
    }else if(wi == 0)
    {
        if(mittelpunkt_x < endpunkt_x)
        {
            wi = 0;
        }else
        {
            wi = 180;
        }
    }
    if(wi == -90)
    {
        wi = 270;
    }
    */
}

double winkel(double endpunkt1_x, double endpunkt1_y,\
              double mittelpunkt_x, double mittelpunkt_y,\
              double endpunkt2_x, double endpunkt2_y)
{
    //sp, mipu, ep
    double w1 = winkel(endpunkt1_x, endpunkt1_y,\
                       mittelpunkt_x, mittelpunkt_y);

    double w2 = winkel(endpunkt2_x, endpunkt2_y,\
                       mittelpunkt_x, mittelpunkt_y);
    double wi;
    wi = w1 - w2;
    if(wi < 0)
    {
        wi = wi * -1;
    }
    if(w1 > w2)
    {
        wi = 360 - wi;
    }

    QString msg;
    msg += "Winkel 1: ";
    msg += double_to_qstring(w1);
    msg += "\n";
    msg += "Winkel 2: ";
    msg += double_to_qstring(w2);
    msg += "\n";
    msg += "Winkel: ";
    msg += double_to_qstring(wi);
    QMessageBox mb;
    mb.setText(msg);
    //mb.exec();

    return wi;
}

double winkel(punkt2d ep1, punkt2d mipu, punkt2d ep2)
{
    return winkel(ep1.x(), ep1.y(), mipu.x(), mipu.y(), ep2.x(), ep2.y());
}

double winkel(punkt3d ep1, punkt3d mipu, punkt3d ep2)
{
    return winkel(ep1.x(), ep1.y(), mipu.x(), mipu.y(), ep2.x(), ep2.y());
}

double winkel(punkt3d ep1, punkt2d mipu, punkt3d ep2)
{
    return winkel(ep1.x(), ep1.y(), mipu.x(), mipu.y(), ep2.x(), ep2.y());
}

void trimmen(QString *geo1, QString *geo2)
{
    QString text_a = *geo1;
    QString text_b = *geo2;
    if(text_a.contains(STRECKE) && text_b.contains(STRECKE))
    {
        strecke s1(text_a);
        strecke s2(text_b);

        if(s1.endpu() == s2.stapu())
        {
            return;
        }

        punkt3d schnittpunkt;
        schnittpunkt.set_z(s1.endpu().z());
        //Schnittpunkt der beiden Geraden berechnen:
        if(s1.stapu().x()!=s1.endpu().x()  &&  s2.stapu().x()!=s2.endpu().x())//sonst div/0 möglich
        {
            //Geradengleichungen aufstellen y = m*x + t:
            //m = (y2-y1):(x2-x1)
            double m1 = (  s1.endpu().y()-s1.stapu().y()  )  /  (  s1.endpu().x()-s1.stapu().x()  );
            double m2 = (  s2.endpu().y()-s2.stapu().y()  )  /  (  s2.endpu().x()-s2.stapu().x()  );
            //t = y1 - (m1*x1)
            double t1 = s1.stapu().y()  -  (m1*s1.stapu().x());
            double t2 = s2.stapu().y()  -  (m2*s2.stapu().x());
            //Geradengleichungen gleichsetzen:
            //m1*x+t1 = m2*x+t2     /-m2*x
            //(m1-m2)*x+t1 = t2     /-t1
            //(m1-m2)*x = t2-t1     / :(m1-m2)
            //x = (t2-t1):(m1-m2)
            double x = (t2-t1)/(m1-m2);
            //x in eine der beiden Gleichungen einsetzen:
            double y = m1*x+t1;

            schnittpunkt.set_x(x);
            schnittpunkt.set_y(y);
            s1.set_endpu(schnittpunkt);
            s2.set_stapu(schnittpunkt);
        }else
        {
            if(s1.stapu().x()==s1.endpu().x()  &&  s2.stapu().x()!=s2.endpu().x())//s1 ist senkrecht
            {
                //heißt x von s1 ist bekannt
                //Geradengleichungen aufstellen für s2     y = m*x + t:
                double m = (  s2.endpu().y()-s2.stapu().y()  )  /  (  s2.endpu().x()-s2.stapu().x()  );
                //t = y1 - (m*x)
                double t = s2.stapu().y()  -  (m*s2.stapu().x());
                double x = s1.stapu().x();
                //x in die Gleichung einsetzen:
                double y = m*x+t;

                schnittpunkt.set_x(x);
                schnittpunkt.set_y(y);
                s1.set_endpu(schnittpunkt);
                s2.set_stapu(schnittpunkt);
            }else if(s1.stapu().x()!=s1.endpu().x()  &&  s2.stapu().x()==s2.endpu().x())//s2 ist senkrecht
            {
                //heißt x von s2 ist bekannt
                //Geradengleichungen aufstellen für s1     y = m*x + t:
                double m = (  s1.endpu().y()-s1.stapu().y()  )  /  (  s1.endpu().x()-s1.stapu().x()  );
                //t = y - (m*x)
                double t = s1.stapu().y()  -  (m*s1.stapu().x());
                double x = s2.stapu().x();
                //x in die Gleichung einsetzen:
                double y = m*x+t;

                schnittpunkt.set_x(x);
                schnittpunkt.set_y(y);
                s1.set_endpu(schnittpunkt);
                s2.set_stapu(schnittpunkt);
            }else
            {
                //beide geraden sind senkrecht
                //soetwas sollte nicht an die Funktion übergeben werden
            }
        }

        //Werte zurück in die geo-QStrings schreiben:
        *geo1 = s1.text();
        *geo2 = s2.text();

        //QMessageBox mb;
        //mb.setText("m1: " + double_to_qstring(m1) + "\nm2: " + double_to_qstring(m2));
        //mb.exec();
    }else if(text_a.contains(STRECKE) && text_b.contains(BOGEN))
    {
        strecke s(text_a);
        bogen b(text_b);

        if(s.endpu() == b.start())
        {
            return;
        }

        //Kreisformel aufstellen:
        //  mx = Kreismittelpunkt X-Wert
        //  my = Kreismittelpunkt Y-Wert
        //  r  = Kreisradius
        //  (x-mx)²+(y-my)²=r²
        double mx = b.mitte().x();
        double my = b.mitte().y();
        double r  = b.rad();

        //Geradenformel aufstellen:
        //  a*x + b*y = c
        //    x1 = X-Wert der vom Startpunkt der Strecke
        //    x2 = X-Wert der vom Endpunkt der Strecke
        //    y1 = Y-Wert der vom Startpunkt der Strecke
        //    y2 = Y-Wert der vom Endpunkt der Strecke
        double x1= s.stapu().x();
        double x2= s.endpu().x();
        double y1= s.stapu().y();
        double y2= s.endpu().y();
        // a = y1-y2
        // b = x2-x1
        // c = x2*y1 - x1*y2
        double var_a = y1-y2;
        double var_b = x2-x1;
        double var_c = x2*y1 - x1*y2;
        // d = c-a*mx-b*my
        double var_d = var_c-var_a*mx-var_b*my;
        // e = r²*(a²+b²)-d²
        double var_e = r*r * (var_a*var_a + var_b*var_b) - var_d*var_d;

        //QMessageBox mb;
        //mb.setText("e= " + double_to_qstring(var_e));
        //mb.exec();

        if(var_e == 0)
        {
            //Es gibt genau eine Lösung
            // x = mx+ a*d / (a²+b²)
            double var_x = mx+ var_a*var_d / (var_a*var_a + var_b*var_b);

            // y = my+ b*d / (a²+b²)
            double var_y = my+ var_b*var_d / (var_a*var_a + var_b*var_b);

            punkt3d p3d = s.endpu();
            p3d.set_x(var_x);
            p3d.set_y(var_y);
            s.set_endpu(p3d);
            b.set_startpunkt(p3d);

        }else if(var_e > 0)
        {
            //Es gibt zwei Lösungen
            // x1 = mx+ (a*d + b* wurzel(e)) /  (a²+b²)
            // x2 = mx+ (a*d - b* wurzel(e)) /  (a²+b²)
            double var_x1 = mx+ (var_a*var_d + var_b*sqrt(var_e)) / (var_a*var_a + var_b*var_b);
            double var_x2 = mx+ (var_a*var_d - var_b*sqrt(var_e)) / (var_a*var_a + var_b*var_b);

            // y1 = my+ (b*d - a* wurzel(e)) /  (a²+b²)
            // y2 = my+ (b*d + a* wurzel(e)) /  (a²+b²)
            double var_y1 = my+ (var_b*var_d - var_a*sqrt(var_e)) / (var_a*var_a + var_b*var_b);
            double var_y2 = my+ (var_b*var_d + var_a*sqrt(var_e)) / (var_a*var_a + var_b*var_b);

            punkt3d p3d1 = s.endpu();
            punkt3d p3d2 = s.endpu();

            p3d1.set_x(var_x1);
            p3d1.set_y(var_y1);
            p3d2.set_x(var_x2);
            p3d2.set_y(var_y2);

            //entscheiden ob p3d1 oder p3d2 richtig sind
            double winkel_orgi = winkel(b.start().x(),b.start().y(),\
                                        b.ende().x(),b.ende().y(),\
                                        b.mitte().x(),b.mitte().y());
            double winkep_p3d1 = winkel(p3d1.x(),p3d1.y(),\
                                        b.ende().x(),b.ende().y(),\
                                        b.mitte().x(),b.mitte().y());
            double winkep_p3d2 = winkel(p3d2.x(),p3d2.y(),\
                                        b.ende().x(),b.ende().y(),\
                                        b.mitte().x(),b.mitte().y());
            double diff_1 = winkel_orgi - winkep_p3d1;
            if(diff_1 < 0)
            {
                diff_1 = -diff_1;
            }
            double diff_2 = winkel_orgi - winkep_p3d2;
            if(diff_2 < 0)
            {
                diff_2 = -diff_2;
            }
            if(diff_1 < diff_2)
            {
                s.set_endpu(p3d1);
                b.set_startpunkt(p3d1);
            }else
            {
                s.set_endpu(p3d2);
                b.set_startpunkt(p3d2);
            }
        }


        //Werte zurück in die geo-QStrings schreiben:
        *geo1 = s.text();
        *geo2 = b.text();

    }else if(text_a.contains(BOGEN) && text_b.contains(STRECKE))
    {
        bogen b(text_a);
        strecke s(text_b);

        if(b.ende() == s.stapu())
        {
            return;
        }

        //Kreisformel aufstellen:
        //  mx = Kreismittelpunkt X-Wert
        //  my = Kreismittelpunkt Y-Wert
        //  r  = Kreisradius
        //  (x-mx)²+(y-my)²=r²
        double mx = b.mitte().x();
        double my = b.mitte().y();
        double r  = b.rad();

        //Geradenformel aufstellen:
        //  a*x + b*y = c
        //    x1 = X-Wert der vom Startpunkt der Strecke
        //    x2 = X-Wert der vom Endpunkt der Strecke
        //    y1 = Y-Wert der vom Startpunkt der Strecke
        //    y2 = Y-Wert der vom Endpunkt der Strecke
        double x2= s.stapu().x();
        double x1= s.endpu().x();
        double y2= s.stapu().y();
        double y1= s.endpu().y();
        // a = y1-y2
        // b = x2-x1
        // c = x2*y1 - x1*y2
        double var_a = y1-y2;
        double var_b = x2-x1;
        double var_c = x2*y1 - x1*y2;
        // d = c-a*mx-b*my
        double var_d = var_c-var_a*mx-var_b*my;
        // e = r²*(a²+b²)-d²
        double var_e = r*r * (var_a*var_a + var_b*var_b) - var_d*var_d;

        //QMessageBox mb;
        //mb.setText("e= " + double_to_qstring(var_e));
        //mb.exec();

        if(var_e == 0)
        {
            //Es gibt genau eine Lösung
            // x = mx+ a*d / (a²+b²)
            double var_x = mx+ var_a*var_d / (var_a*var_a + var_b*var_b);

            // y = my+ b*d / (a²+b²)
            double var_y = my+ var_b*var_d / (var_a*var_a + var_b*var_b);

            punkt3d p3d = s.stapu();
            p3d.set_x(var_x);
            p3d.set_y(var_y);
            s.set_stapu(p3d);
            b.set_endpunkt(p3d);

        }else if(var_e > 0)
        {
            //Es gibt zwei Lösungen
            // x1 = mx+ (a*d + b* wurzel(e)) /  (a²+b²)
            // x2 = mx+ (a*d - b* wurzel(e)) /  (a²+b²)
            double var_x1 = mx+ (var_a*var_d + var_b*sqrt(var_e)) / (var_a*var_a + var_b*var_b);
            double var_x2 = mx+ (var_a*var_d - var_b*sqrt(var_e)) / (var_a*var_a + var_b*var_b);

            // y1 = my+ (b*d - a* wurzel(e)) /  (a²+b²)
            // y2 = my+ (b*d + a* wurzel(e)) /  (a²+b²)
            double var_y1 = my+ (var_b*var_d - var_a*sqrt(var_e)) / (var_a*var_a + var_b*var_b);
            double var_y2 = my+ (var_b*var_d + var_a*sqrt(var_e)) / (var_a*var_a + var_b*var_b);

            punkt3d p3d1 = s.stapu();
            punkt3d p3d2 = s.stapu();

            p3d1.set_x(var_x1);
            p3d1.set_y(var_y1);
            p3d2.set_x(var_x2);
            p3d2.set_y(var_y2);

            //entscheiden ob p3d1 oder p3d2 richtig sind
            double winkel_orgi = winkel(b.start().x(),b.start().y(),\
                                        b.ende().x(),b.ende().y(),\
                                        b.mitte().x(),b.mitte().y());
            double winkep_p3d1 = winkel(b.start().x(),b.start().y(),\
                                        p3d1.x(),p3d1.y(),\
                                        b.mitte().x(),b.mitte().y());
            double winkep_p3d2 = winkel(b.start().x(),b.start().y(),\
                                        p3d2.x(),p3d2.y(),\
                                        b.mitte().x(),b.mitte().y());
            double diff_1 = winkel_orgi - winkep_p3d1;
            if(diff_1 < 0)
            {
                diff_1 = -diff_1;
            }
            double diff_2 = winkel_orgi - winkep_p3d2;
            if(diff_2 < 0)
            {
                diff_2 = -diff_2;
            }
            if(diff_1 < diff_2)
            {
                s.set_stapu(p3d1);
                b.set_endpunkt(p3d1);
            }else
            {
                s.set_stapu(p3d2);
                b.set_endpunkt(p3d2);
            }
        }


        //Werte zurück in die geo-QStrings schreiben:
        *geo2 = s.text();
        *geo1 = b.text();
    }else if(text_a.contains(BOGEN) && text_b.contains(BOGEN))
    {
        bogen b1(text_a);
        bogen b2(text_b);

        if(b1.ende() == b2.start())
        {
            return;
        }

        //Kreisformel aufstellen:
        //  mx = Kreismittelpunkt X-Wert
        //  my = Kreismittelpunkt Y-Wert
        //  r  = Kreisradius
        //  (x-mx)²+(y-my)²=r²
        double mx1 = b1.mitte().x();
        double my1 = b1.mitte().y();
        double r1  = b1.rad();

        double mx2 = b2.mitte().x();
        double my2 = b2.mitte().y();
        double r2  = b2.rad();

        //Prüfen, wie weit die Kreise auseinander liegen
        strecke s;
        punkt3d tmp;
        tmp.set_x(b1.mitte().x());
        tmp.set_y(b1.mitte().y());
        s.set_stapu(tmp);
        tmp.set_x(b2.mitte().x());
        tmp.set_y(b2.mitte().y());
        s.set_endpu(tmp);
        double abst = s.laenge2d();

        if(abst > r1+r2)//Kreise liegen zu weit auseinander
        {
            return;
        }else if(abst == r1+r2)//Kreise berühren sich in genau einem Punkt
        {
            strecke_bezugspunkt sb = strecke_bezugspunkt_start;
            s.set_laenge_2d(r1, sb);
            b1.set_endpunkt(s.endpu());
            b1.set_startpunkt(s.endpu());
        }else//Kreise schneiden sich in 2 Punkten
        {
            //http://walter.bislins.ch/blog/index.asp?page=Schnittpunkte+zweier+Kreise+berechnen+%28JavaScript%29

            double var_x = (r1*r1 + abst*abst - r2*r2) / (2*abst);
            double var_y = r1*r1 - var_x*var_x;
            if(var_y > 0)
            {
                var_y = sqrt(var_y);
            }
            double AB0 = mx2-mx1;
            double AB1 = my2-my1;
            double ex0 = AB0/abst;
            double ex1 = AB1/abst;
            double ey0 = -ex1;
            double ey1 =  ex0;
            double Q1x = mx1 + var_x * ex0;
            double Q1y = my1 + var_x * ex1;
            double Q2x = Q1x - var_y * ey0;
            double Q2y = Q1y - var_y * ey1;
            Q1x += var_y * ey0;
            Q1y += var_y * ey1;

            punkt3d p3d1 = b1.ende();
            punkt3d p3d2 = p3d1;
            p3d1.set_x(Q1x);
            p3d1.set_y(Q1y);
            p3d2.set_x(Q2x);
            p3d2.set_y(Q2y);

            //entscheiden ob p3d1 oder p3d2 richtig sind
            double winkel_orgi = winkel(b1.start().x(),b1.start().y(),\
                                        b1.ende().x(),b1.ende().y(),\
                                        b1.mitte().x(),b1.mitte().y());
            double winkep_p3d1 = winkel(b1.start().x(),b1.start().y(),\
                                        p3d1.x(),p3d1.y(),\
                                        b1.mitte().x(),b1.mitte().y());
            double winkep_p3d2 = winkel(b1.start().x(),b1.start().y(),\
                                        p3d2.x(),p3d2.y(),\
                                        b1.mitte().x(),b1.mitte().y());
            double diff_1 = winkel_orgi - winkep_p3d1;
            if(diff_1 < 0)
            {
                diff_1 = -diff_1;
            }
            double diff_2 = winkel_orgi - winkep_p3d2;
            if(diff_2 < 0)
            {
                diff_2 = -diff_2;
            }
            if(diff_1 < diff_2)
            {
                b1.set_endpunkt(p3d1);
                b2.set_startpunkt(p3d1);
            }else
            {
                b1.set_endpunkt(p3d2);
                b2.set_startpunkt(p3d2);
            }

        }


        //Werte zurück in die geo-QStrings schreiben:
        *geo1 = b1.text();
        *geo2 = b2.text();

    }
}

bool cagleich(punkt3d p1, punkt3d p2, double tolleranz = 0.1)
{
    if(  (  (p1.x() == p2.x()) || ((p1.x() - tolleranz <= p2.x()) && (p1.x() + tolleranz >= p2.x()))  )  && \
         (  (p1.y() == p2.y()) || ((p1.y() - tolleranz <= p2.y()) && (p1.y() + tolleranz >= p2.y()))  )  && \
         (  (p1.z() == p2.z()) || ((p1.z() - tolleranz <= p2.z()) && (p1.z() + tolleranz >= p2.z()))  )     )
    {
        return true;
    }else
    {
        return false;
    }
}
bool cagleich(punkt2d p1, punkt2d p2, double tolleranz = 0.1)
{
    if(  (  (p1.x() == p2.x()) || ((p1.x() - tolleranz <= p2.x()) && (p1.x() + tolleranz >= p2.x()))  )  && \
         (  (p1.y() == p2.y()) || ((p1.y() - tolleranz <= p2.y()) && (p1.y() + tolleranz >= p2.y()))  )      )
    {
        return true;
    }else
    {
        return false;
    }
}
bool cagleich(double p1, double p2, double tolleranz = 0.1)
{
    if(    (p1 == p2) || ((p1 - tolleranz <= p2) && (p1 + tolleranz >= p2))  )
    {
        return true;
    }else
    {
        return false;
    }
}

/*
void geo(text_zw bearb, double wst_l, double wst_b, \
         QString kante_v, QString kante_h, QString kante_l, QString kante_r, \
         double versatz_x, double versatz_y)
{
    //-------------------------------------------
    geometrietext gt;
    //------------------------------
    //Nullpunkt darstellen:
    punkt3d nullpunkt(0,0,0);
    nullpunkt.set_linienbreite(15);
    gt.add_punkt(nullpunkt);
    //------------------------------
    //wst darstellen:
    rechteck3d rec;
    rec.set_bezugspunkt(UNTEN_LINKS);
    rec.set_einfuegepunkt(versatz_x,versatz_y,0);
    rec.set_laenge(wst_l);
    rec.set_breite(wst_b);
    rec.set_farbe_fuellung(FARBE_GRAU);
    gt.add_rechteck(rec);
    //------------------------------
    //Kanten darstellen:
    strecke skante;
    skante.set_linienbreite(5);
    if(!kante_v.isEmpty())
    {
        punkt3d sp(0,0,0);
        punkt3d ep(wst_l,0,0);
        skante.set_stapu(sp);
        skante.set_endpu(ep);
        skante.verschieben_um(versatz_x, versatz_y);
        gt.add_strecke(skante);
    }
    if(!kante_h.isEmpty())
    {
        punkt3d sp(0,wst_b,0);
        punkt3d ep(wst_l,wst_b,0);
        skante.set_stapu(sp);
        skante.set_endpu(ep);
        skante.verschieben_um(versatz_x, versatz_y);
        gt.add_strecke(skante);
    }
    if(!kante_l.isEmpty())
    {
        punkt3d sp(0,0,0);
        punkt3d ep(0,wst_b,0);
        skante.set_stapu(sp);
        skante.set_endpu(ep);
        skante.verschieben_um(versatz_x, versatz_y);
        gt.add_strecke(skante);
    }
    if(!kante_r.isEmpty())
    {
        punkt3d sp(wst_l,0,0);
        punkt3d ep(wst_l,wst_b,0);
        skante.set_stapu(sp);
        skante.set_endpu(ep);
        skante.verschieben_um(versatz_x, versatz_y);
        gt.add_strecke(skante);
    }
    //------------------------------
    gt.zeilenvorschub();
    //------------------------------
    //Bearbeitungen darstellen:
    QString farbe_unterseite = FARBE_ROSE;

    for(uint i=0; i<bearb.count() ;i++)
    {
        text_zw zeile;
        zeile.set_text(bearb.at(i),TRENNZ_BEARB_PARAM);
        if(zeile.at(0) == BEARBART_BOHR)
        {
            bohrung bo(zeile.text());
            if(bo.bezug() == WST_BEZUG_OBSEI)
            {
                kreis k;
                k.set_farbe(FARBE_SCHWARZ);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(bo.mipu());
                k.verschieben_um(versatz_x, versatz_y);
                if(bo.tiefe() > dicke())
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_HELLBLAU);
                }
                gt.add_kreis(k);
                strecke s;
                s.set_farbe(k.farbe());
                s.set_stapu(bo.x() - bo.dm()/2 - 2, bo.y(), bo.z());
                s.set_endpu(bo.x() + bo.dm()/2 + 2, bo.y(), bo.z());
                s.verschieben_um(versatz_x, versatz_y);
                gt.add_strecke(s);
                s.drenen_um_mipu_2d(90, true);
                gt.add_strecke(s);
            }else if(bo.bezug() == WST_BEZUG_UNSEI)
            {
                kreis k;
                k.set_farbe(farbe_unterseite);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(bo.mipu());
                if(bo.tiefe() > dicke())
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_HELLBLAU);
                }
                k.verschieben_um(versatz_x, versatz_y);
                gt.add_kreis(k);
                strecke s;
                s.set_farbe(k.farbe());
                s.set_stapu(bo.x() - bo.dm()/2 - 2, bo.y(), bo.z());
                s.set_endpu(bo.x() + bo.dm()/2 + 2, bo.y(), bo.z());
                s.drenen_um_mipu_2d(45, true);
                s.verschieben_um(versatz_x, versatz_y);
                gt.add_strecke(s);
                s.drenen_um_mipu_2d(90, true);
                gt.add_strecke(s);
            }else if(bo.bezug() == WST_BEZUG_LI)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.tiefe());
                r.set_breite(bo.dm());
                r.set_bezugspunkt(LINKS);
                r.set_einfuegepunkt(bo.x(), bo.y(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                gt.add_rechteck(r);
            }else if(bo.bezug() == WST_BEZUG_RE)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.tiefe());
                r.set_breite(bo.dm());
                r.set_bezugspunkt(RECHTS);
                r.set_einfuegepunkt(bo.x(), bo.y(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                gt.add_rechteck(r);
            }else if(bo.bezug() == WST_BEZUG_VO)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.dm());
                r.set_breite(bo.tiefe());
                r.set_bezugspunkt(UNTEN);
                r.set_einfuegepunkt(bo.x(), bo.y(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                gt.add_rechteck(r);
            }else if(bo.bezug() == WST_BEZUG_HI)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.dm());
                r.set_breite(bo.tiefe());
                r.set_bezugspunkt(OBEN);
                r.set_einfuegepunkt(bo.x(), bo.y(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                gt.add_rechteck(r);
            }
        }else if(zeile.at(0) == BEARBART_BOHRRASTER)
        {
            bohrraster bo(zeile.text());
            if(bo.bezug() == WST_BEZUG_OBSEI)
            {
                kreis k;
                k.set_farbe(FARBE_SCHWARZ);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(bo.mipu());
                k.verschieben_um(versatz_x, versatz_y);
                if(bo.tiefe() > dicke())
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_HELLBLAU);
                }
                strecke s1;
                s1.set_farbe(k.farbe());
                s1.set_stapu(bo.x() - bo.dm()/2 - 2, bo.y(), bo.z());
                s1.set_endpu(bo.x() + bo.dm()/2 + 2, bo.y(), bo.z());
                s1.verschieben_um(versatz_x, versatz_y);
                strecke s2 = s1;
                s2.drenen_um_mipu_2d(90, true);
                for(uint i=0; i<bo.anz_x() ;i++)
                {
                    kreis tmp_k = k;
                    tmp_k.verschieben_um(i*bo.raster_x(), 0);
                    strecke tmp_s1 = s1;
                    tmp_s1.verschieben_um(i*bo.raster_x(), 0);
                    strecke tmp_s2 = s2;
                    tmp_s2.verschieben_um(i*bo.raster_x(), 0);
                    for(uint ii=0; ii<bo.anz_y() ;ii++)
                    {
                        kreis tmp_kk = tmp_k;
                        strecke tmp_s11 = tmp_s1;
                        strecke tmp_s22 = tmp_s2;
                        tmp_kk.verschieben_um(0, ii*bo.raster_y());
                        tmp_s11.verschieben_um(0, ii*bo.raster_y());
                        tmp_s22.verschieben_um(0, ii*bo.raster_y());
                        gt.add_kreis(tmp_kk);
                        gt.add_strecke(tmp_s11);
                        gt.add_strecke(tmp_s22);
                    }
                }
            }else if(bo.bezug() == WST_BEZUG_UNSEI)
            {
                kreis k;
                k.set_farbe(farbe_unterseite);
                k.set_radius(bo.dm()/2);
                k.set_mittelpunkt(bo.mipu());
                k.verschieben_um(versatz_x, versatz_y);
                if(bo.tiefe() > dicke())
                {
                    k.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    k.set_farbe_fuellung(FARBE_HELLBLAU);
                }
                strecke s1;
                s1.set_farbe(k.farbe());
                s1.set_stapu(bo.x() - bo.dm()/2 - 2, bo.y(), bo.z());
                s1.set_endpu(bo.x() + bo.dm()/2 + 2, bo.y(), bo.z());
                s1.drenen_um_mipu_2d(45, true);
                s1.verschieben_um(versatz_x, versatz_y);
                strecke s2 = s1;
                s2.drenen_um_mipu_2d(90, true);
                for(uint i=0; i<bo.anz_x() ;i++)
                {
                    kreis tmp_k = k;
                    tmp_k.verschieben_um(i*bo.raster_x(), 0);
                    strecke tmp_s1 = s1;
                    tmp_s1.verschieben_um(i*bo.raster_x(), 0);
                    strecke tmp_s2 = s2;
                    tmp_s2.verschieben_um(i*bo.raster_x(), 0);
                    for(uint ii=0; ii<bo.anz_y() ;ii++)
                    {
                        kreis tmp_kk = tmp_k;
                        strecke tmp_s11 = tmp_s1;
                        strecke tmp_s22 = tmp_s2;
                        tmp_kk.verschieben_um(0, ii*bo.raster_y());
                        tmp_s11.verschieben_um(0, ii*bo.raster_y());
                        tmp_s22.verschieben_um(0, ii*bo.raster_y());
                        gt.add_kreis(tmp_kk);
                        gt.add_strecke(tmp_s11);
                        gt.add_strecke(tmp_s22);
                    }
                }
            }else if(bo.bezug() == WST_BEZUG_LI)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.tiefe());
                r.set_breite(bo.dm());
                r.set_bezugspunkt(LINKS);
                r.set_einfuegepunkt(0, bo.y(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                for(uint i=0; i<bo.anz_y() ;i++)
                {
                    rechteck3d tmp_r = r;
                    tmp_r.verschieben_um(0, i*bo.raster_y());
                    gt.add_rechteck(tmp_r);
                }
            }else if(bo.bezug() == WST_BEZUG_RE)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.tiefe());
                r.set_breite(bo.dm());
                r.set_bezugspunkt(RECHTS);
                r.set_einfuegepunkt(tmp_l, bo.y(), 0);
                r.verschieben_um(versatz_x, versatz_y);
                for(uint i=0; i<bo.anz_y() ;i++)
                {
                    rechteck3d tmp_r = r;
                    tmp_r.verschieben_um(0, i*bo.raster_y());
                    gt.add_rechteck(tmp_r);
                }
            }else if(bo.bezug() == WST_BEZUG_VO)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.dm());
                r.set_breite(bo.tiefe());
                r.set_bezugspunkt(UNTEN);
                r.set_einfuegepunkt(bo.x(), 0, 0);
                r.verschieben_um(versatz_x, versatz_y);
                for(uint i=0; i<bo.anz_x() ;i++)
                {
                    rechteck3d tmp_r = r;
                    tmp_r.verschieben_um(i*bo.raster_x(), 0);
                    gt.add_rechteck(tmp_r);
                }
            }else if(bo.bezug() == WST_BEZUG_HI)
            {
                rechteck3d r;
                r.set_farbe_fuellung(FARBE_BRAUN);
                r.set_laenge(bo.dm());
                r.set_breite(bo.tiefe());
                r.set_bezugspunkt(OBEN);
                r.set_einfuegepunkt(bo.x(), tmp_b, 0);
                r.verschieben_um(versatz_x, versatz_y);
                for(uint i=0; i<bo.anz_x() ;i++)
                {
                    rechteck3d tmp_r = r;
                    tmp_r.verschieben_um(i*bo.raster_x(), 0);
                    gt.add_rechteck(tmp_r);
                }
            }
        }else if(zeile.at(0) == BEARBART_NUT)
        {
            nut nu(zeile.text());
            strecke s;
            s.set_stapu(nu.xs(), nu.ys(), 0);
            s.set_endpu(nu.xe(), nu.ye(), 0);
            rechteck3d r;
            if(  (nu.bezug() == WST_BEZUG_OBSEI) ||  (nu.bezug() == WST_BEZUG_UNSEI)  )
            {
                if(nu.bezug() == WST_BEZUG_OBSEI)
                {
                    r.set_farbe_fuellung(FARBE_BLAU);
                }else
                {
                    r.set_farbe_fuellung(farbe_unterseite);
                    r.set_stil(STIL_GESTRICHELT);
                }
                r.set_laenge(s.laenge2d());
                r.set_breite(nu.breite());
                r.set_bezugspunkt(MITTE);
                r.set_einfuegepunkt(s.mipu());
                r.set_drewi(s.wink());
                r.verschieben_um(versatz_x, versatz_y);
                gt.add_rechteck(r);
            }else
            {
                if(nu.bezug() == WST_BEZUG_LI)
                {
                    r.set_laenge(nu.tiefe());
                    r.set_breite(s.laenge2d());
                }else if(nu.bezug() == WST_BEZUG_RE)
                {
                    r.set_laenge(nu.tiefe());
                    r.set_breite(s.laenge2d());
                }else if(nu.bezug() == WST_BEZUG_VO)
                {
                    r.set_laenge(s.laenge2d());
                    r.set_breite(nu.tiefe());
                }else if(nu.bezug() == WST_BEZUG_HI)
                {
                    r.set_laenge(s.laenge2d());
                    r.set_breite(nu.tiefe());
                }
                r.set_farbe_fuellung(FARBE_GELB);
                punkt3d mipu = s.mipu();
                r.set_bezugspunkt(MITTE);
                strecke s_mipu;
                s_mipu.set_stapu(mipu);
                s_mipu.set_endpu(s.endpu());
                s_mipu.set_laenge_2d(nu.tiefe()/2, strecke_bezugspunkt_start);
                s_mipu.drenen_um_stapu_2d(90, false);
                mipu = s_mipu.endpu();
                r.set_drewi(drehwinkel);
                r.set_einfuegepunkt(mipu);
                r.verschieben_um(versatz_x, versatz_y);
                //Start anzeigen:
                strecke stmp = s;
                stmp.drenen_um_stapu_2d(90, true);
                stmp.set_laenge_2d(stmp.laenge2d()+nu.tiefe(), strecke_bezugspunkt_ende);
                stmp.set_laenge_2d(30, strecke_bezugspunkt_start);
                kreis k;
                k.set_mittelpunkt(stmp.endpu());
                k.set_radius(30);
                k.set_farbe(FARBE_GELB);
                gt.add_kreis(k);
                //---
                gt.add_rechteck(r);
            }
        }else if(zeile.at(0) == BEARBART_RTA)
        {
            rechtecktasche rt(zeile.text());
            rechteck3d r;
            if(  (rt.bezug() == WST_BEZUG_OBSEI) ||  (rt.bezug() == WST_BEZUG_UNSEI)  )
            {
                r.set_bezugspunkt(MITTE);
                if(rt.tiefe() >= dicke())
                {
                    r.set_farbe_fuellung(FARBE_WEISS);
                }else
                {
                    if(rt.bezug() == WST_BEZUG_OBSEI)
                    {
                        r.set_farbe_fuellung(FARBE_DUNKELGRAU);
                    }else
                    {
                        r.set_farbe_fuellung(farbe_unterseite);
                        r.set_stil(STIL_GESTRICHELT);
                    }
                }
                r.set_laenge(rt.laenge());
                r.set_breite(rt.breite());
                r.set_mipu(rt.x(), rt.y(), rt.z());
                r.set_drewi(rt.drewi());
                r.verschieben_um(versatz_x, versatz_y);
                r.set_rad(rt.rad());
                gt.add_rechteck(r);
                if(rt.ausraeumen() == false)
                {
                    r.set_laenge(r.l()/8*5);
                    r.set_breite(r.b()/8*5);
                    r.set_farbe_fuellung(FARBE_WEISS);
                    gt.add_rechteck(r);
                }
            }else
            {
                if(rt.bezug() == WST_BEZUG_LI)
                {
                    r.set_bezugspunkt(LINKS);
                    r.set_laenge(rt.tiefe());
                    r.set_breite(rt.laenge());
                }else if(rt.bezug() == WST_BEZUG_RE)
                {
                    r.set_bezugspunkt(RECHTS);
                    r.set_laenge(rt.tiefe());
                    r.set_breite(rt.laenge());
                }else if(rt.bezug() == WST_BEZUG_VO)
                {
                    r.set_bezugspunkt(UNTEN);
                    r.set_laenge(rt.laenge());
                    r.set_breite(rt.tiefe());
                }else if(rt.bezug() == WST_BEZUG_HI)
                {
                    r.set_bezugspunkt(OBEN);
                    r.set_laenge(rt.laenge());
                    r.set_breite(rt.tiefe());
                }
                r.set_farbe_fuellung(FARBE_GRUEN);
                r.set_einfuegepunkt(rt.x(), rt.y(), rt.z());
                r.verschieben_um(versatz_x, versatz_y);
                //r.set_rad(rt.rad()); //hier darf nicht der rad gesetzt werden weil Draufsicht
                gt.add_rechteck(r);
            }

        }else if(zeile.at(0) == BEARBART_FRAESERAUFRUF)
        {
            fraeseraufruf fa(zeile.text());
            punkt3d p(fa.x(), fa.y(), fa.z());
            p.set_linienbreite(10);
            p.verschieben_um(versatz_x, versatz_y);
            if(fa.bezug() == WST_BEZUG_OBSEI)
            {
                p.set_farbe(FARBE_DUNKELGRAU);
            }else
            {
                p.set_farbe(farbe_unterseite);
            }
            gt.add_punkt(p);
        }else if(zeile.at(0) == BEARBART_FRAESERGERADE)
        {
            fraesergerade fg(zeile.text());
            strecke s;
            s = fg.strecke_();
            s.verschieben_um(versatz_x, versatz_y);
            if(fg.bezug() == WST_BEZUG_OBSEI)
            {
                s.set_farbe(FARBE_DUNKELGRAU);
            }else
            {
                s.set_farbe(farbe_unterseite);
                s.set_stil(STIL_GESTRICHELT);
            }
            gt.add_strecke(s);
        }else if(zeile.at(0) == BEARBART_FRAESERBOGEN)
        {
            fraeserbogen fb(zeile.text());
            bogen b;
            b.set_startpunkt(fb.stapu());
            b.set_endpunkt(fb.endpu());
            if(fb.bezug() == WST_BEZUG_OBSEI)
            {
                b.set_radius(fb.rad(), fb.uzs());
                b.set_farbe(FARBE_DUNKELGRAU);
            }else
            {
                b.set_radius(fb.rad(), !fb.uzs());
                b.set_farbe(farbe_unterseite);
                b.set_stil(STIL_GESTRICHELT);
            }
            b.verschieben_um(versatz_x, versatz_y);
            gt.add_bogen(b);
        }
        gt.zeilenvorschub();
    }
    Versatz_y.append(versatz_y);
    Geotext.append(gt);

}
*/
