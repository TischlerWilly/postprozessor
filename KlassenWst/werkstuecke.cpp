#include "werkstuecke.h"


werkstuecke::werkstuecke()
{
    min_fkon_gerade_laenge = 1;
    kurze_geraden_import = false;
}

//---------------------------------------------------------------allgemeine Funktionen:
bool werkstuecke::ist_bekannt(QString Werkstueckname)
{
    for(uint i=1; i<=namen.zeilenanzahl() ;i++)
    {
        if(Werkstueckname == namen.zeile(i))
        {
            return true;
        }
    }
    return false;
}
bool werkstuecke::neu(QString Werkstueckname, QString Quellformat)
{
    if(ist_bekannt(Werkstueckname))
    {
        return true;//FEHLER, der Teil gibt es bereits!!!
    }else
    {
        namen.zeile_anhaengen(Werkstueckname);
        quellformate.zeile_anhaengen(Quellformat);
        werkstueck w(Werkstueckname);
        wste.append(w);
    }
    return false;
}
void werkstuecke::clear()
{
    namen.clear();
    quellformate.clear();
    wste.clear();
}
uint werkstuecke::get_index(QString Werkstueckname)
{
    for(uint i=1; i<=namen.zeilenanzahl() ;i++)
    {
        if(namen.zeile(i)==Werkstueckname)
        {
            return i;
        }
    }
    return 0; //Wenn der Name nicht gefunden wurde
}
QString werkstuecke::wert_nach_istgleich(QString text)
{
    if(text.contains("="))
    {
        if(text.contains("\n"))
        {
            return text_mitte(text, "=", "\n");
        }else
        {
            return text_rechts(text, "=");
        }
    }else
    {
        return "";
    }
}
werkstueck werkstuecke::get_wst(uint index)
{
    if(index > 0 && index <= namen.zeilenanzahl())
    {
        return wste.at(index-1);
    }else
    {
        werkstueck w;   //leeres Wst
        return w;
    }
}
QString werkstuecke::get_name(uint index)
{
    if(index > 0 && index <= namen.zeilenanzahl())
    {
        return namen.zeile(index);
    }else
    {
        return "";
    }
}
void werkstuecke::stdnamen(text_zeilenweise namen_alt, text_zeilenweise namen_neu)
{
    //erster Durchlauf: Namen tauschen
    for(uint i = 1; i<=namen.zeilenanzahl() ;i++)
    {
        QString tmp = namen.zeile(i);
        for(uint ii=1; ii<=namen_alt.zeilenanzahl();ii++)
        {
            if(tmp.contains(namen_alt.zeile(ii)))
            {
                tmp.replace(namen_alt.zeile(ii), namen_neu.zeile(ii));
                namen.zeile_ersaetzen(i, tmp);
                break;
            }
        }
    }
    //zweiter Durchlauf: Schranknummer löschen wenn möglich
    QString tmp = namen.zeile(1);
    bool schranknummer_wurde_entfernt = false;//wird gebraucht als Prüfung für den 3. Durchlauf
    if(tmp.contains("_"))
    {
        tmp = text_links(tmp, "_");
        bool identisch = true;
        for(uint i = 2; i<=namen.zeilenanzahl() ;i++)
        {
            if(  tmp != text_links(namen.zeile(i), "_")  )
            {
                identisch = false;
                break;
            }
        }
        if(identisch == true)
        {
            for(uint i = 1; i<=namen.zeilenanzahl() ;i++)
            {
                namen.zeile_ersaetzen(  i, text_rechts(namen.zeile(i),"_")  );
            }
            schranknummer_wurde_entfernt = true;
        }
    }
    //dritter Durchlauf: Nummer hinter Teilenamen löschen wenn möglich
    text_zeilenweise bekannte_namen;
    if(schranknummer_wurde_entfernt)
    {
        for(uint i = 1; i<=namen.zeilenanzahl() ;i++)//Name für Name durchgehen
        {
            tmp = namen.zeile(i);
            QString name_bis_ziffer ="";
            //Namen und Ziffer trennen:
            for(int ii=0; ii<tmp.count() ;ii++)//Namen zeichenweise durchgehen
            {
                if(!ist_ziffer(tmp.at(ii)))
                {
                    name_bis_ziffer += tmp.at(ii);
                }else
                {
                    break;
                }
            }
            //Prüfen, ob es diesen Namen bereits gibt:
            bool bekannt = false;
            for(uint iii=1; iii<=bekannte_namen.zeilenanzahl() ;iii++)//bekannte Namen nacheinander durchgehen
            {
                if(name_bis_ziffer.length() >0 && bekannte_namen.zeile(iii) == name_bis_ziffer)
                {
                    bekannt = true;
                    break;
                }
            }
            if(name_bis_ziffer.length() >0 && bekannt == false)//Wenn der Name noch nicht vergeben war
            {
                namen.zeile_ersaetzen(i, name_bis_ziffer);
                bekannte_namen.zeile_anhaengen(name_bis_ziffer);
            }
        }
    }

    //Nameninformatione in den einzenen werkstücken aktualisieren:
    for(uint i=1; i<=namen.zeilenanzahl() ;i++)
    {
        werkstueck w = wste.at(i-1);
        w.set_name(namen.zeile(i));
        wste.replace(i-1, w);
    }
}
bool werkstuecke::ist_ziffer(const QChar zeichen)
{
    if(zeichen == '0' || zeichen == '1' || zeichen == '2' || zeichen == '2' || zeichen == '3' || zeichen == '4' || zeichen == '5' || zeichen == '6' || zeichen == '7' || zeichen == '8' || zeichen == '9')
    {
        return true;
    }else
    {
        return false;
    }
}
QString werkstuecke::var_einsetzen(werkstueck w, QString formel)
{
    if(formel.contains("'"))
    {
        formel.replace("'", ".");
    }
    if(formel.contains("B"))
    {
        formel.replace("B", w.get_breite_qstring());
    }
    if(formel.contains("L"))
    {
        formel.replace("L", w.get_laenge_qstring());
    }
    if(formel.contains("D"))
    {
        formel.replace("D", w.get_dicke_qstring());
    }
    return formel;
}
QString werkstuecke::suche_cad_fehler()
{
    QString msg;

    for(uint i=1; i<=anzahl() ;i++)
    {
        werkstueck teil = wste.at(i-1);
        msg += teil.suche_cad_fehler();
    }

    return msg;
}
void werkstuecke::set_fkon_gerade_laenge(double wert)
{
    min_fkon_gerade_laenge = wert;
}
void werkstuecke::set_kurze_geraden_importieren(bool wert)
{
    kurze_geraden_import = wert;
}

//---------------------------------------------------------------Import-Funktionen:
bool werkstuecke::import_fmc_oberseite(QString Werkstueckname, QString importtext)
{
    importtext = importtext.toUpper();
    uint index = get_index(Werkstueckname);
    if(index == 0)
    {
        neu(Werkstueckname, FMC);
        index = get_index(Werkstueckname);
    }
    text_zeilenweise tz;
    tz.set_text(importtext);

    werkstueck w = wste.at(index-1);

    for(uint i=1; i<=tz.zeilenanzahl() ;i++)
    {
        QString zeile = tz.zeile(i);
        if(zeile.contains(FMC_PRGKOPF))
        {
            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_PRGKOPF_LAENGE)
                    { 
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        w.set_laenge(tmp);
                    }else if(schluessel == FMC_PRGKOPF_BREITE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        w.set_breite(tmp);
                    }else if(schluessel == FMC_PRGKOPF_DICKE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        w.set_dicke(tmp);
                    }                    
                }
            }
        }else if(zeile.contains(FMC_KOMMENTAR))
        {
            i++;
            zeile = tz.zeile(i);
            QString schluessel = text_links(zeile, "=");

            if(schluessel == FMC_KOMMENTAR_TEXT)
            {
                QString vo = VW_KANTE_VO;
                vo = vo.toUpper();
                QString hi = VW_KANTE_HI;
                hi = hi.toUpper();
                QString li = VW_KANTE_LI;
                li = li.toUpper();
                QString re = VW_KANTE_RE;
                re = re.toUpper();
                QString kom = text_rechts(zeile, "=");
                if(kom.contains(vo))
                {
                    w.set_kante_vo(text_rechts(kom, vo));
                }else if(kom.contains(hi))
                {
                    w.set_kante_hi(text_rechts(kom, hi));
                }else if(kom.contains(li))
                {
                    w.set_kante_li(text_rechts(kom, li));
                }else if(kom.contains(re))
                {
                    w.set_kante_re(text_rechts(kom, re));
                }
            }
        }else if(zeile.contains(FMC_BOHR_DM))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_OBSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(bo.get_text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_BOHR_DM_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_BOHR_DM_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_BOHR_DM_TIEFE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        if(tiefe < 0)
                        {
                            tiefe = w.get_dicke() - tiefe;
                        }
                        bo.set_tiefe(tiefe);
                    }else if(schluessel == FMC_BOHR_DM_X)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_x(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_BOHR_DM_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_y(ausdruck_auswerten(tmp));
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEXP))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_LI);
            double bohrtiefe = 0;
            double x1 = 0;
            double x2 = -1;
            bool kettenmass = false;
            double y1 = 0;
            double y2 = 0;
            double y3 = 0;
            double y4 = 0;
            double y5 = 0;
            double y6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    bo.set_tiefe(x1 + bohrtiefe);
                    bo.set_x(x1);
                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(x2 > 0)
                    {
                        bo.set_bezug(WST_BEZUG_RE);
                        bo.set_tiefe(w.get_laenge() - x2 + bohrtiefe);
                        bo.set_x(x2);

                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(y2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_HBEXP_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_HBEXP_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_HBEXP_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bohrtiefe = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double z = ausdruck_auswerten(tmp).toDouble();
                        bo.set_z(z);
                    }else if(schluessel == FMC_HBEXP_X1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_X2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Y1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEXM))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_RE);
            double bohrtiefe = 0;
            double x1 = w.get_laenge();
            double x2 = -1;
            bool kettenmass = false;
            double y1 = 0;
            double y2 = 0;
            double y3 = 0;
            double y4 = 0;
            double y5 = 0;
            double y6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    bo.set_tiefe(w.get_laenge() - x1 + bohrtiefe);
                    bo.set_x(x1);
                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(x2 >= 0)
                    {
                        bo.set_bezug(WST_BEZUG_LI);
                        bo.set_tiefe(x2 + bohrtiefe);
                        bo.set_x(x2);

                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(y2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_HBEXP_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_HBEXP_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_HBEXP_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bohrtiefe = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double z = ausdruck_auswerten(tmp).toDouble();
                        bo.set_z(z);
                    }else if(schluessel == FMC_HBEXP_X2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_X1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Y1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEYP))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_VO);
            double bohrtiefe = 0;
            double y1 = 0;
            double y2 = -1;
            bool kettenmass = false;
            double x1 = 0;
            double x2 = 0;
            double x3 = 0;
            double x4 = 0;
            double x5 = 0;
            double x6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    bo.set_tiefe(y1 + bohrtiefe);
                    bo.set_y(y1);
                    if(x1)
                    {
                        bo.set_x(x1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(x2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5+x6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(y2 > 0)
                    {
                        bo.set_bezug(WST_BEZUG_HI);
                        bo.set_tiefe(w.get_breite() - y2 + bohrtiefe);
                        bo.set_y(y2);

                        if(x1)
                        {
                            bo.set_x(x1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(x2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5+x6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_HBEYP_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_HBEYP_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_HBEYP_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bohrtiefe = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double z = ausdruck_auswerten(tmp).toDouble();
                        bo.set_z(z);
                    }else if(schluessel == FMC_HBEXP_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_X1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEYM))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_HI);
            double bohrtiefe = 0;
            double y1 = 0;
            double y2 = -1;
            bool kettenmass = false;
            double x1 = 0;
            double x2 = 0;
            double x3 = 0;
            double x4 = 0;
            double x5 = 0;
            double x6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    bo.set_tiefe(w.get_breite() - y1 + bohrtiefe);
                    bo.set_y(y1);
                    if(x1)
                    {
                        bo.set_x(x1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(x2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5+x6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(y2 >= 0)
                    {
                        bo.set_bezug(WST_BEZUG_VO);
                        bo.set_tiefe(y2 + bohrtiefe);
                        bo.set_y(y2);

                        if(x1)
                        {
                            bo.set_x(x1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(x2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5+x6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_HBEYP_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_HBEYP_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_HBEYP_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bohrtiefe = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double z = ausdruck_auswerten(tmp).toDouble();
                        bo.set_z(z);
                    }else if(schluessel == FMC_HBEXP_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_X1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEYP_X6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_BOBIY))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_OBSEI);
            double x1 = 0;
            double x2 = -1;
            bool kettenmass = false;
            double y1 = 0;
            double y2 = 0;
            double y3 = 0;
            double y4 = 0;
            double y5 = 0;
            double y6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;

                    bo.set_x(x1);

                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(x2 > 0)
                    {
                        bo.set_x(x2);

                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(y2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }

                    break;

                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_BOBIY_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_BOBIY_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_BOBIY_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        bo.set_tiefe(tmp);
                    }else if(schluessel == FMC_BOBIY_X1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIY_X2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp.contains("X1"))
                        {
                            tmp.replace("X1",double_to_qstring(x1));
                        }
                        tmp = var_einsetzen(w, tmp);
                        x2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIY_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIY_Y1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIY_Y2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIY_Y3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIY_Y4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIY_Y5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIY_Y6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_BOBIX))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_OBSEI);
            double y1 = 0;
            double y2 = -1;
            bool kettenmass = false;
            double x1 = 0;
            double x2 = 0;
            double x3 = 0;
            double x4 = 0;
            double x5 = 0;
            double x6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;

                    bo.set_y(y1);

                    if(x1)
                    {
                        bo.set_x(x1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(x2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5+x6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(y2 > 0)
                    {
                        bo.set_y(y2);

                        if(x1)
                        {
                            bo.set_x(x1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(x2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5+x6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }

                    break;

                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_BOBIX_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_BOBIX_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_BOBIX_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        bo.set_tiefe(tmp);
                    }else if(schluessel == FMC_BOBIX_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIX_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp.contains("Y1"))
                        {
                            tmp.replace("Y1",double_to_qstring(x1));
                        }
                        tmp = var_einsetzen(w, tmp);
                        y2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIX_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIX_X1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_KTA))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_OBSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(bo.get_text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_KTA_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_KTA_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        bo.set_dm(tmp);
                    }else if(schluessel == FMC_KTA_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        if(tiefe < 0)
                        {
                            tiefe = w.get_dicke() - tiefe;
                        }
                        bo.set_tiefe(tiefe);
                    }else if(schluessel == FMC_KTA_X)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        bo.set_x(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_KTA_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        bo.set_y(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_KTA_ZUST)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        bo.set_zustellmass(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_KTA_WKZ)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        bo.set_wkznum(tmp);
                    }
                }
            }
        }else if(zeile.contains(FMC_RTA))
        {
            rechtecktasche rt;
            rt.set_bezug(WST_BEZUG_OBSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(rt.get_text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_RTA_AFB)
                    {
                        rt.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_RTA_L)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_laenge(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_B)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_breite(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        if(tiefe < 0)
                        {
                            tiefe = w.get_dicke() - tiefe;
                        }
                        rt.set_tiefe(tiefe);
                    }else if(schluessel == FMC_RTA_X)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_x(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_y(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_ZUST)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_zustellmass(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_WI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_drewi(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_RAD)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_rad(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_RAEUM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_ausraeumen(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_WKZ)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        rt.set_wkznum(tmp);
                    }
                }
            }
        }else if(zeile.contains(FMC_NUT))
        {
            nut n;
            n.set_bezug(WST_BEZUG_OBSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(n.get_text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_NUT_AFB)
                    {
                        n.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_NUT_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_tiefe(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_BR)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_breite(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_XS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_xs(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_YS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_ys(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_xe(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_ye(ausdruck_auswerten(tmp));
                    }
                }
            }
        }else if(zeile.contains(FMC_LORAE))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_OBSEI);
            double xs = 0;
            double xe = 0;
            double y1 = 0;
            double y2 = 0;
            double raster = 32;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii;

                    if(xe < xs)
                    {
                        double tmp;
                        tmp = xe;
                        xe = xs;
                        xs = tmp;
                    }
                    if(y1 != 0)
                    {
                        bo.set_y(y1);
                        double tmp_x = xs;
                        while(tmp_x <= xe)
                        {
                            bo.set_x(tmp_x);
                            w.neue_bearbeitung(bo.get_text());
                            tmp_x = tmp_x + raster;
                        }
                    }
                    if(y2 != 0)
                    {
                        bo.set_y(y2);
                        double tmp_x = xs;
                        while(tmp_x <= xe)
                        {
                            bo.set_x(tmp_x);
                            w.neue_bearbeitung(bo.get_text());
                            tmp_x = tmp_x + raster;
                        }
                    }


                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_LORAE_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_LORAE_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_LORAE_DM_)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_LORAE_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        if(tiefe < 0)
                        {
                            tiefe = w.get_dicke() - tiefe;
                        }
                        bo.set_tiefe(tiefe);
                    }else if(schluessel == FMC_LORAE_XS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        xs = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAE_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        xe = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAE_Y1)
                    {                        
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAE_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAE_RASTER)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        raster = ausdruck_auswerten(tmp).toDouble();
                    }
                }
            }
        }else if(zeile.contains(FMC_LORAM))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_OBSEI);
            double xs = 0;
            double xm = 0;
            double y1 = 0;
            double y2 = 0;
            double raster = 32;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;

                    double diff = xm - xs;
                    double xe = xm + diff;

                    if(xe < xs)
                    {
                        double tmp;
                        tmp = xe;
                        xe = xs;
                        xs = tmp;
                    }
                    if(y1 != 0)
                    {
                        bo.set_y(y1);
                        double tmp_x = xs;
                        while(tmp_x <= xe)
                        {
                            bo.set_x(tmp_x);
                            w.neue_bearbeitung(bo.get_text());
                            tmp_x = tmp_x + raster;
                        }
                    }
                    if(y2 != 0)
                    {
                        bo.set_y(y2);
                        double tmp_x = xs;
                        while(tmp_x <= xe)
                        {
                            bo.set_x(tmp_x);
                            w.neue_bearbeitung(bo.get_text());
                            tmp_x = tmp_x + raster;
                        }
                    }

                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_LORAM_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_LORAM_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_LORAM_DM_)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_LORAM_TI   || \
                             schluessel == FMC_LORAM_TI_     )
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        if(tiefe < 0)
                        {
                            tiefe = w.get_dicke() - tiefe;
                        }
                        bo.set_tiefe(tiefe);
                    }else if(schluessel == FMC_LORAM_XS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        xs = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAM_XM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        xm = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAM_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAM_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAM_RASTER  || \
                             schluessel == FMC_LORAM_RASTER_)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        raster = ausdruck_auswerten(tmp).toDouble();
                    }
                }
            }
        }else if(zeile.contains(FMC_FKON))
        {
            fraueseraufruf fa;
            fa.set_bezug(WST_BEZUG_OBSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(fa.get_text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_FKON_AFB)
                    {
                        fa.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_FKON_X)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fa.set_x(tmp);
                    }else if(schluessel == FMC_FKON_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fa.set_y(tmp);
                    }else if(schluessel == FMC_FKON_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        //werkstueck w = wste.at(index-1);  //w ist bereits bekannt
                        double tiefe = w.get_dicke() - tmp.toDouble();
                        fa.set_tiefe(tiefe);//Tiefe, nicht Z-Wert!!
                                            //Z-Wert ist für horizontale Fräseraufrufe gedacht
                    }else if(schluessel == FMC_FKON_KOR)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        if(tmp == "1")
                        {
                            fa.set_radkor(FRKOR_L);
                        }else if(tmp == "0")
                        {
                            fa.set_radkor(FRKOR_M);
                        }else if(tmp == "2")
                        {
                            fa.set_radkor(FRKOR_R);
                        }

                    }else if(schluessel == FMC_FKON_WKZ)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        fa.set_wkznum(tmp);
                    }
                }
            }

        }else if(zeile.contains(FMC_FKONG))
        {
            fraesergerade fg;
            fg.set_bezug(WST_BEZUG_OBSEI);

            //Startpunkt aus der vorherigen Bearbeitung heraus einlesen:
            text_zeilenweise bearb;
            bearb = w.get_bearb();
            text_zeilenweise letzte_bearb;
            letzte_bearb.set_trennzeichen(TRENNZ_BEARB_PARAM);
            letzte_bearb.set_text(bearb.zeile(bearb.zeilenanzahl()));
            if(letzte_bearb.zeile(1) == BEARBART_FRAESERAUFRUF)
            {
                fraueseraufruf tmp(letzte_bearb.get_text());
                fg.set_startpunkt(tmp.get_pos_vertikal());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERGERADE)
            {
                fraesergerade tmp(letzte_bearb.get_text());
                fg.set_startpunkt(tmp.get_ep());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERBOGEN)
            {
                fraeserbogen tmp(letzte_bearb.get_text());
                fg.set_startpunkt(tmp.get_ep());
            }

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    if(kurze_geraden_import == true)
                    {
                        w.neue_bearbeitung(fg.get_text());
                    }else if(fg.get_laenge_2d() > min_fkon_gerade_laenge || \
                             fg.get_zs() != fg.get_ze())
                    {
                        w.neue_bearbeitung(fg.get_text());
                    }

                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_FKONG_AFB)
                    {
                        fg.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_FKONG_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fg.set_xe(tmp);
                    }else if(schluessel == FMC_FKONG_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fg.set_ye(tmp);
                    }else if(schluessel == FMC_FKONG_ZE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp == "Z")
                        {
                            fg.set_ze(fg.get_zs());//Der Z-Wert gibt die Tiefe an
                        }else
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            double tiefe = w.get_dicke() - tmp.toDouble();
                            fg.set_ze(tiefe);//Der Z-Wert gibt die Tiefe an
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_FKONBOGUZS)   || \
                 zeile.contains(FMC_FKONBOGGUZS)     )
        {
            fraeserbogen fb;
            fb.set_bezug(WST_BEZUG_OBSEI);

            if(zeile.contains(FMC_FKONBOGUZS))
            {
                fb.set_uzs(true);
            }else
            {
                fb.set_uzs(false);
            }

            //Startpunkt aus der vorherigen Bearbeitung heraus einlesen:
            text_zeilenweise bearb;
            bearb = w.get_bearb();
            text_zeilenweise letzte_bearb;
            letzte_bearb.set_trennzeichen(TRENNZ_BEARB_PARAM);
            letzte_bearb.set_text(bearb.zeile(bearb.zeilenanzahl()));
            if(letzte_bearb.zeile(1) == BEARBART_FRAESERAUFRUF)
            {
                fraueseraufruf tmp(letzte_bearb.get_text());
                fb.set_startpunkt(tmp.get_pos_vertikal());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERGERADE)
            {
                fraesergerade tmp(letzte_bearb.get_text());
                fb.set_startpunkt(tmp.get_ep());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERBOGEN)
            {
                fraeserbogen tmp(letzte_bearb.get_text());
                fb.set_startpunkt(tmp.get_ep());
            }

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(fb.get_text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_FKONBOG_AFB)
                    {
                        fb.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_FKONBOG_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fb.set_xe(tmp);
                    }else if(schluessel == FMC_FKONBOG_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fb.set_ye(tmp);
                    }else if(schluessel == FMC_FKONBOG_ZE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp == "Z")
                        {
                            fb.set_ze(fb.get_zs());//Der Z-Wert gibt die Tiefe an
                        }else
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            double tiefe = w.get_dicke() - tmp.toDouble();
                            fb.set_ze(tiefe);//Der Z-Wert gibt die Tiefe an
                        }
                    }else if(schluessel == FMC_FKONBOG_RAD)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fb.set_rad(tmp);
                    }
                }
            }
        }else if(zeile.contains(FMC_FALZ))
        {
            fraueseraufruf fa;
            fraesergerade fg;
            fa.set_bezug(WST_BEZUG_OBSEI);
            fg.set_bezug(WST_BEZUG_OBSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(fa.get_text());
                    w.neue_bearbeitung(fg.get_text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_FALZ_AFB)
                    {
                        fa.set_afb(wert_nach_istgleich(zeile));
                        fg.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_FALZ_XS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fa.set_x(tmp);
                        fg.set_xs(tmp);
                    }else if(schluessel == FMC_FALZ_YS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fa.set_y(tmp);
                        fg.set_ys(tmp);
                    }else if(schluessel == FMC_FALZ_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fg.set_xe(tmp);
                    }else if(schluessel == FMC_FALZ_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fg.set_ye(tmp);
                    }else if(schluessel == FMC_FALZ_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        //werkstueck w = wste.at(index-1);  //w ist bereits bekannt
                        double tiefe = w.get_dicke() - tmp.toDouble();
                        fa.set_tiefe(tiefe);//Tiefe, nicht Z-Wert!!
                                            //Z-Wert ist für horizontale Fräseraufrufe gedacht
                        fg.set_zs(tiefe);
                        fg.set_ze(tiefe);
                    }else if(schluessel == FMC_FALZ_KOR)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        if(tmp == "1")
                        {
                            fa.set_radkor(FRKOR_L);
                        }else if(tmp == "0")
                        {
                            fa.set_radkor(FRKOR_M);
                        }else if(tmp == "2")
                        {
                            fa.set_radkor(FRKOR_R);
                        }

                    }else if(schluessel == FMC_FKON_WKZ)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        fa.set_wkznum(tmp);
                    }
                }
            }

        }else if(zeile.contains(FMC_TOPF))
        {
            bohrung botopf;
            bohrung boduebel;
            botopf.set_bezug(WST_BEZUG_OBSEI);
            boduebel.set_bezug(WST_BEZUG_OBSEI);

            double topfabst = 0;
            double abst1 = 0;
            double abst2 = 0;
            double abst3 = 0;
            double abst4 = 0;
            double abst5 = 0;
            double massA = 0;
            double massB = 0;
            bool kettenmass = false;
            double seite = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;

                    if(seite == 1)
                    {
                        if(abst1 > 0)
                        {
                            double abst_tmp = abst1;

                            botopf.set_x(abst_tmp);
                            botopf.set_y(topfabst);
                            w.neue_bearbeitung(botopf.get_text());

                            boduebel.set_y(topfabst+massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                        }
                        if(abst2 > 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2;
                            }else
                            {
                                abst_tmp = abst2;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(topfabst);
                            w.neue_bearbeitung(botopf.get_text());

                            boduebel.set_y(topfabst+massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                        }
                        if(abst3 > 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3;
                            }else
                            {
                                abst_tmp = abst3;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(topfabst);
                            w.neue_bearbeitung(botopf.get_text());

                            boduebel.set_y(topfabst+massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                        }
                        if(abst4 > 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3+abst4;
                            }else
                            {
                                abst_tmp = abst4;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(topfabst);
                            w.neue_bearbeitung(botopf.get_text());

                            boduebel.set_y(topfabst+massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                        }
                        if(abst5 > 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3+abst4+abst5;
                            }else
                            {
                                abst_tmp = abst5;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(topfabst);
                            w.neue_bearbeitung(botopf.get_text());

                            boduebel.set_y(topfabst+massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                        }
                    }else if(seite == 2)
                    {

                    }else if(seite == 3)
                    {
                        if(abst1 > 0)
                        {
                            double abst_tmp = abst1;

                            botopf.set_x(abst_tmp);
                            botopf.set_y(w.get_breite() - topfabst);
                            w.neue_bearbeitung(botopf.get_text());

                            boduebel.set_y(w.get_breite() - topfabst - massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                        }
                        if(abst2 > 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2;
                            }else
                            {
                                abst_tmp = abst2;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(w.get_breite() - topfabst);
                            w.neue_bearbeitung(botopf.get_text());

                            boduebel.set_y(w.get_breite() - topfabst - massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                        }
                        if(abst3 > 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3;
                            }else
                            {
                                abst_tmp = abst3;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(w.get_breite() - topfabst);
                            w.neue_bearbeitung(botopf.get_text());

                            boduebel.set_y(w.get_breite() - topfabst - massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                        }
                        if(abst4 > 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3+abst4;
                            }else
                            {
                                abst_tmp = abst4;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(w.get_breite() - topfabst);
                            w.neue_bearbeitung(botopf.get_text());

                            boduebel.set_y(w.get_breite() - topfabst - massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                        }
                        if(abst5 > 0)
                        {
                            double abst_tmp;
                            if(kettenmass == true)
                            {
                                abst_tmp = abst1+abst2+abst3+abst4+abst5;
                            }else
                            {
                                abst_tmp = abst5;
                            }

                            botopf.set_x(abst_tmp);
                            botopf.set_y(w.get_breite() - topfabst);
                            w.neue_bearbeitung(botopf.get_text());

                            boduebel.set_y(w.get_breite() - topfabst - massB);
                            boduebel.set_x(abst_tmp - massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                            boduebel.set_x(abst_tmp + massA/2);
                            w.neue_bearbeitung(boduebel.get_text());
                        }
                    }else if(seite == 4)
                    {

                    }

                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_TOPF_AFB)
                    {
                        botopf.set_afb(wert_nach_istgleich(zeile));
                        boduebel.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_TOPF_TODM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        botopf.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_TOPF_DDM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        boduebel.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_TOPF_TOTI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        botopf.set_tiefe(tmp);
                    }else if(schluessel == FMC_TOPF_DTI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        boduebel.set_tiefe(tmp);
                    }else if(schluessel == FMC_TOPF_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_TOPF_ABST)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        topfabst = tmp.toDouble();
                    }else if(schluessel == FMC_TOPF_MA)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        massA = tmp.toDouble();
                    }else if(schluessel == FMC_TOPF_MB)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        massB = tmp.toDouble();
                    }else if(schluessel == FMC_TOPF_A1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            abst1 = tmp.toDouble();
                        }
                    }else if(schluessel == FMC_TOPF_A2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp.replace("A1",double_to_qstring(abst1));
                            tmp = ausdruck_auswerten(tmp);
                            abst2 = tmp.toDouble();
                        }
                    }else if(schluessel == FMC_TOPF_A3)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp.replace("A1",double_to_qstring(abst1));
                            tmp.replace("A2",double_to_qstring(abst2));
                            tmp = ausdruck_auswerten(tmp);
                            abst3 = tmp.toDouble();
                        }
                    }else if(schluessel == FMC_TOPF_A4)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp.replace("A1",double_to_qstring(abst1));
                            tmp.replace("A2",double_to_qstring(abst2));
                            tmp.replace("A3",double_to_qstring(abst3));
                            tmp = ausdruck_auswerten(tmp);
                            abst4 = tmp.toDouble();
                        }
                    }else if(schluessel == FMC_TOPF_A5)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp.replace("A1",double_to_qstring(abst1));
                            tmp.replace("A2",double_to_qstring(abst2));
                            tmp.replace("A3",double_to_qstring(abst3));
                            tmp.replace("A4",double_to_qstring(abst4));
                            tmp = ausdruck_auswerten(tmp);
                            abst5 = tmp.toDouble();
                        }
                    }else if(schluessel == FMC_TOPF_TOWKZ)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        botopf.set_wkznum(tmp);
                    }else if(schluessel == FMC_TOPF_SEITE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        seite = tmp.toDouble();
                    }
                }
            }
        }

    }

    wste.replace(index-1, w);

    return 0;
}

bool werkstuecke::import_fmc_unterseite(QString Werkstueckname, QString importtext)
{
    importtext = importtext.toUpper();
    uint index = get_index(Werkstueckname);
    if(index == 0)
    {
        return 1;   //Die Bearbeitung soll nur auf die Unterseite importiert werden,
                    //wenn bereits die Bearbeitung auf der Oberseite importiert wurde
    }
    text_zeilenweise tz;
    tz.set_text(importtext);

    werkstueck w = wste.at(index-1);

    for(uint i=1; i<=tz.zeilenanzahl() ;i++)
    {
        QString zeile = tz.zeile(i);

        if(zeile.contains(FMC_BOHR_DM))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_UNSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(bo.get_text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_BOHR_DM_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_BOHR_DM_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_BOHR_DM_TIEFE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        if(tiefe < 0)
                        {
                            tiefe = w.get_dicke() - tiefe;
                        }
                        bo.set_tiefe(tiefe);
                    }else if(schluessel == FMC_BOHR_DM_X)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double x = ausdruck_auswerten(tmp).toDouble();
                        x = w.get_laenge()-x;
                        bo.set_x(x);
                    }else if(schluessel == FMC_BOHR_DM_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_y(ausdruck_auswerten(tmp));
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEXP))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_RE); //Bearbeitung von Unterseite auf Oberseite bringen (drehen um l/2)
            double bohrtiefe = 0;
            double x1 = 0;
            double x2 = -1;
            bool kettenmass = false;
            double y1 = 0;
            double y2 = 0;
            double y3 = 0;
            double y4 = 0;
            double y5 = 0;
            double y6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    bo.set_tiefe(x1 + bohrtiefe);
                    bo.set_x(x1);
                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(x2 > 0)
                    {
                        bo.set_bezug(WST_BEZUG_LI);//Bearbeitung von Unterseite auf Oberseite bringen (drehen um l/2)
                        bo.set_tiefe(w.get_laenge() - x2 + bohrtiefe);
                        bo.set_x(x2);

                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(y2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_HBEXP_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_HBEXP_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_HBEXP_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bohrtiefe = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double z = w.get_dicke() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        bo.set_z(z);
                    }else if(schluessel == FMC_HBEXP_X1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_X2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Y1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEXM))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_LI);//Bearbeitung von Unterseite auf Oberseite bringen (drehen um l/2)
            double bohrtiefe = 0;
            double x1 = w.get_laenge();
            double x2 = -1;
            bool kettenmass = false;
            double y1 = 0;
            double y2 = 0;
            double y3 = 0;
            double y4 = 0;
            double y5 = 0;
            double y6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    bo.set_tiefe(w.get_laenge() - x1 + bohrtiefe);
                    bo.set_x(x1);
                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(x2 >= 0)
                    {
                        bo.set_bezug(WST_BEZUG_RE);//Bearbeitung von Unterseite auf Oberseite bringen (drehen um l/2)
                        bo.set_tiefe(x2 + bohrtiefe);
                        bo.set_x(x2);

                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(y2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_HBEXP_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_HBEXP_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_HBEXP_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bohrtiefe = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double z = w.get_dicke() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        bo.set_z(z);
                    }else if(schluessel == FMC_HBEXP_X2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_X1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        x1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Y1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_HBEXP_Y6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEYP))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_VO);
            double bohrtiefe = 0;
            double y1 = 0;
            double y2 = -1;
            bool kettenmass = false;
            double x1 = 0;
            double x2 = 0;
            double x3 = 0;
            double x4 = 0;
            double x5 = 0;
            double x6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    bo.set_tiefe(y1 + bohrtiefe);
                    bo.set_y(y1);

                    if(x1)
                    {
                        bo.set_x(x1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(x2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5+x6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(y2 > 0)
                    {
                        bo.set_bezug(WST_BEZUG_HI);
                        bo.set_tiefe(w.get_breite() - y2 + bohrtiefe);
                        bo.set_y(y2);

                        if(x1)
                        {
                            bo.set_x(x1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(x2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5+x6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_HBEYP_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_HBEYP_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_HBEYP_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bohrtiefe = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double z = w.get_dicke() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        z = w.get_dicke()-z;
                        bo.set_z(z);
                    }else if(schluessel == FMC_HBEXP_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_X1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x1 = w.get_laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x2 = w.get_laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x3 = w.get_laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x4 = w.get_laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x5 = w.get_laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x6 = w.get_laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_HBEYM))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_HI);
            double bohrtiefe = 0;
            double y1 = 0;
            double y2 = -1;
            bool kettenmass = false;
            double x1 = 0;
            double x2 = 0;
            double x3 = 0;
            double x4 = 0;
            double x5 = 0;
            double x6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    bo.set_tiefe(w.get_breite() - y1 + bohrtiefe);
                    bo.set_y(y1);

                    if(x1)
                    {
                        bo.set_x(x1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(x2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5+x6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(y2 >= 0)
                    {
                        bo.set_bezug(WST_BEZUG_VO);
                        bo.set_tiefe(y2 + bohrtiefe);
                        bo.set_y(y2);

                        if(x1)
                        {
                            bo.set_x(x1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(x2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5+x6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_HBEYP_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_HBEYP_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_HBEYP_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bohrtiefe = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double z = w.get_dicke() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        bo.set_z(z);
                    }else if(schluessel == FMC_HBEXP_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEXP_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_HBEYP_X1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x1 = w.get_laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x2 = w.get_laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x3 = w.get_laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x4 = w.get_laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x5 = w.get_laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }else if(schluessel == FMC_HBEYP_X6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            x6 = w.get_laenge() - ausdruck_auswerten(tmp).toDouble();//Umrechen auf Oberseite
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_BOBIY))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_UNSEI);
            double x1 = 0;
            double x2 = -1;
            bool kettenmass = false;
            double y1 = 0;
            double y2 = 0;
            double y3 = 0;
            double y4 = 0;
            double y5 = 0;
            double y6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;

                    bo.set_x(x1);

                    if(y1)
                    {
                        bo.set_y(y1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(y2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(y6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_y(y6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_y(y1+y2+y3+y4+y5+y6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(x2 > 0)
                    {
                        bo.set_x(x2);

                        if(y1)
                        {
                            bo.set_y(y1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(y2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(y6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_y(y6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_y(y1+y2+y3+y4+y5+y6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }

                    break;

                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_BOBIY_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_BOBIY_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_BOBIY_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        bo.set_tiefe(tmp);
                    }else if(schluessel == FMC_BOBIY_X1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        x1 = w.get_laenge() - tmp.toDouble();
                    }else if(schluessel == FMC_BOBIY_X2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp.contains("X1"))
                        {
                            tmp.replace("X1",double_to_qstring(x1));
                        }
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        x2 = w.get_laenge() - tmp.toDouble();
                    }else if(schluessel == FMC_BOBIY_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIY_Y1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y1 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIY_Y2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y2 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIY_Y3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y3 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIY_Y4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y4 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIY_Y5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y5 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }else if(schluessel == FMC_BOBIY_Y6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            y6 = ausdruck_auswerten(tmp).toDouble();
                        }
                    }
                }
            }


        }else if(zeile.contains(FMC_BOBIX))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_OBSEI);
            double y1 = 0;
            double y2 = -1;
            bool kettenmass = false;
            double x1 = 0;
            double x2 = 0;
            double x3 = 0;
            double x4 = 0;
            double x5 = 0;
            double x6 = 0;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;

                    bo.set_y(y1);

                    if(x1)
                    {
                        bo.set_x(x1);
                        w.neue_bearbeitung(bo.get_text());
                    }
                    if(x2)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x2);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x3)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x3);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x4)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x4);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x5)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x5);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }
                    if(x6)
                    {
                        if(kettenmass == false)
                        {
                            bo.set_x(x6);
                            w.neue_bearbeitung(bo.get_text());
                        }else
                        {
                            bo.set_x(x1+x2+x3+x4+x5+x6);
                            w.neue_bearbeitung(bo.get_text());
                        }
                    }

                    if(y2 > 0)
                    {
                        bo.set_y(y2);

                        if(x1)
                        {
                            bo.set_x(x1);
                            w.neue_bearbeitung(bo.get_text());
                        }
                        if(x2)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x2);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x3)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x3);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x4)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x4);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x5)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x5);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                        if(x6)
                        {
                            if(kettenmass == false)
                            {
                                bo.set_x(x6);
                                w.neue_bearbeitung(bo.get_text());
                            }else
                            {
                                bo.set_x(x1+x2+x3+x4+x5+x6);
                                w.neue_bearbeitung(bo.get_text());
                            }
                        }
                    }

                    break;

                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_BOBIX_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_BOBIX_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_BOBIX_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        bo.set_tiefe(tmp);
                    }else if(schluessel == FMC_BOBIX_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIX_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp.contains("Y1"))
                        {
                            tmp.replace("Y1",double_to_qstring(x1));
                        }
                        tmp = var_einsetzen(w, tmp);
                        y2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIX_KM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        kettenmass = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_BOBIX_X1)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            x1 = w.get_laenge() - tmp.toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X2)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            x2 = w.get_laenge() - tmp.toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X3)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            x3 = w.get_laenge() - tmp.toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X4)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            x4 = w.get_laenge() - tmp.toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X5)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            x5 = w.get_laenge() - tmp.toDouble();
                        }
                    }else if(schluessel == FMC_BOBIX_X6)
                    {
                        QString tmp = (wert_nach_istgleich(zeile));
                        if(tmp != "0" && \
                           tmp != "(NULL)" && \
                           !tmp.isEmpty())
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            x6 = w.get_laenge() - tmp.toDouble();
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_KTA))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_UNSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(bo.get_text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_KTA_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_KTA_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_KTA_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        if(tiefe < 0)
                        {
                            tiefe = w.get_dicke() - tiefe;
                        }
                        bo.set_tiefe(tiefe);
                    }else if(schluessel == FMC_KTA_X)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        double x = ausdruck_auswerten(tmp).toDouble();
                        x = w.get_laenge()-x;
                        bo.set_x(x);
                    }else if(schluessel == FMC_KTA_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        bo.set_y(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_KTA_ZUST)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        bo.set_zustellmass(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_KTA_WKZ)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        bo.set_wkznum(tmp);
                    }
                }
            }
        }else if(zeile.contains(FMC_RTA))
        {
            rechtecktasche rt;
            rt.set_bezug(WST_BEZUG_UNSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(rt.get_text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_RTA_AFB)
                    {
                        rt.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_RTA_L)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_laenge(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_B)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_breite(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        if(tiefe < 0)
                        {
                            tiefe = w.get_dicke() - tiefe;
                        }
                        rt.set_tiefe(tiefe);
                    }else if(schluessel == FMC_RTA_X)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        double x = ausdruck_auswerten(tmp).toDouble();
                        x = w.get_laenge()-x;
                        rt.set_x(x);
                    }else if(schluessel == FMC_RTA_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_y(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_ZUST)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_zustellmass(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_WI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        double winkel = tmp.toDouble();
                        //Der Winkel hau einen Werk zwischen 0 und 360°
                        //1° entspricht 181° usw.
                        //das heißt, der Winkel kann bei Bedarf gekürzt werden:
                        if(winkel > 180)
                        {
                            winkel = winkel -180;
                        }
                        //Auf die Unterseite drehen, weil Drehen um L/2
                        //Bei drehen um B/2 verhällt sich der winkel genauso:
                        winkel = 180 - winkel;
                        rt.set_drewi(winkel);
                    }else if(schluessel == FMC_RTA_RAD)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_rad(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_RAEUM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp.replace(",",".");
                        tmp = var_einsetzen(w, tmp);
                        rt.set_ausraeumen(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_RTA_WKZ)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        rt.set_wkznum(tmp);
                    }
                }
            }
        }else if(zeile.contains(FMC_NUT))
        {
            nut n;
            n.set_bezug(WST_BEZUG_UNSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(n.get_text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_NUT_AFB)
                    {
                        n.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_NUT_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_tiefe(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_BR)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_breite(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_XS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double x = ausdruck_auswerten(tmp).toDouble();
                        x = w.get_laenge()-x;
                        n.set_xs(x);
                    }else if(schluessel == FMC_NUT_YS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_ys(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_NUT_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double x = ausdruck_auswerten(tmp).toDouble();
                        x = w.get_laenge()-x;
                        n.set_xe(x);
                    }else if(schluessel == FMC_NUT_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        n.set_ye(ausdruck_auswerten(tmp));
                    }
                }
            }
        }else if(zeile.contains(FMC_LORAE))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_UNSEI);
            double xs = 0;
            double xe = 0;
            double y1 = 0;
            double y2 = 0;
            double raster = 32;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;

                    if(xe < xs)
                    {
                        double tmp;
                        tmp = xe;
                        xe = xs;
                        xs = tmp;
                    }
                    if(y1 != 0)
                    {
                        bo.set_y(y1);
                        double tmp_x = xs;
                        while(tmp_x <= xe)
                        {
                            bo.set_x(tmp_x);
                            w.neue_bearbeitung(bo.get_text());
                            tmp_x = tmp_x + raster;
                        }
                    }
                    if(y2 != 0)
                    {
                        bo.set_y(y2);
                        double tmp_x = xs;
                        while(tmp_x <= xe)
                        {
                            bo.set_x(tmp_x);
                            w.neue_bearbeitung(bo.get_text());
                            tmp_x = tmp_x + raster;
                        }
                    }


                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_LORAE_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_LORAE_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_LORAE_DM_)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_LORAE_TI)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        if(tiefe < 0)
                        {
                            tiefe = w.get_dicke() - tiefe;
                        }
                        bo.set_tiefe(tiefe);
                    }else if(schluessel == FMC_LORAE_XS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        xs = ausdruck_auswerten(tmp).toDouble();
                        xs = w.get_laenge()-xs;
                    }else if(schluessel == FMC_LORAE_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        xe = ausdruck_auswerten(tmp).toDouble();
                        xe = w.get_laenge()-xe;
                    }else if(schluessel == FMC_LORAE_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAE_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAE_RASTER)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        raster = ausdruck_auswerten(tmp).toDouble();
                    }
                }
            }
        }else if(zeile.contains(FMC_LORAM))
        {
            bohrung bo;
            bo.set_bezug(WST_BEZUG_UNSEI);
            double xs = 0;
            double xm = 0;
            double y1 = 0;
            double y2 = 0;
            double raster = 32;

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;

                    double diff = xm - xs;
                    double xe = xm + diff;

                    if(xe < xs)
                    {
                        double tmp;
                        tmp = xe;
                        xe = xs;
                        xs = tmp;
                    }
                    if(y1 != 0)
                    {
                        bo.set_y(y1);
                        double tmp_x = xs;
                        while(tmp_x <= xe)
                        {
                            bo.set_x(tmp_x);
                            w.neue_bearbeitung(bo.get_text());
                            tmp_x = tmp_x + raster;
                        }
                    }
                    if(y2 != 0)
                    {
                        bo.set_y(y2);
                        double tmp_x = xs;
                        while(tmp_x <= xe)
                        {
                            bo.set_x(tmp_x);
                            w.neue_bearbeitung(bo.get_text());
                            tmp_x = tmp_x + raster;
                        }
                    }


                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_LORAM_AFB)
                    {
                        bo.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_LORAM_DM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_LORAM_DM_)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        bo.set_dm(ausdruck_auswerten(tmp));
                    }else if(schluessel == FMC_LORAM_TI   || \
                             schluessel == FMC_LORAM_TI_     )
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        double tiefe = ausdruck_auswerten(tmp).toDouble();
                        if(tiefe < 0)
                        {
                            tiefe = w.get_dicke() - tiefe;
                        }
                        bo.set_tiefe(tiefe);
                    }else if(schluessel == FMC_LORAM_XS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        xs = ausdruck_auswerten(tmp).toDouble();
                        xs = w.get_laenge()-xs;
                    }else if(schluessel == FMC_LORAM_XM)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        xm = ausdruck_auswerten(tmp).toDouble();
                        xm = w.get_laenge()-xm;
                    }else if(schluessel == FMC_LORAM_Y1)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y1 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAM_Y2)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        y2 = ausdruck_auswerten(tmp).toDouble();
                    }else if(schluessel == FMC_LORAM_RASTER  || \
                             schluessel == FMC_LORAM_RASTER_)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        raster = ausdruck_auswerten(tmp).toDouble();
                    }
                }
            }
        }else if(zeile.contains(FMC_FKON))
        {
            fraueseraufruf fa;
            fa.set_bezug(WST_BEZUG_UNSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(fa.get_text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_FKON_AFB)
                    {
                        fa.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_FKON_X)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        double x = tmp.toDouble();
                        x = w.get_laenge()-x;
                        fa.set_x(x);
                    }else if(schluessel == FMC_FKON_Y)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fa.set_y(tmp);
                    }else if(schluessel == FMC_FKON_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        werkstueck w = wste.at(index-1);
                        double tiefe = w.get_dicke() - tmp.toDouble();
                        fa.set_tiefe(tiefe);//Tiefe, nicht Z-Wert!!
                                            //Z-Wert ist für horizontale Fräseraufrufe gedacht
                    }else if(schluessel == FMC_FKON_KOR)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        if(tmp == "1")
                        {
                            fa.set_radkor(FRKOR_L);
                        }else if(tmp == "0")
                        {
                            fa.set_radkor(FRKOR_M);
                        }else if(tmp == "2")
                        {
                            fa.set_radkor(FRKOR_R);
                        }
                    }else if(schluessel == FMC_FKON_WKZ)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        fa.set_wkznum(tmp);
                    }
                }
            }

        }else if(zeile.contains(FMC_FKONG))
        {
            fraesergerade fg;
            fg.set_bezug(WST_BEZUG_UNSEI);

            //Startpunkt aus der vorherigen Bearbeitung heraus einlesen:
            text_zeilenweise bearb;
            bearb = w.get_bearb();
            text_zeilenweise letzte_bearb;
            letzte_bearb.set_trennzeichen(TRENNZ_BEARB_PARAM);
            letzte_bearb.set_text(bearb.zeile(bearb.zeilenanzahl()));
            if(letzte_bearb.zeile(1) == BEARBART_FRAESERAUFRUF)
            {
                fraueseraufruf tmp(letzte_bearb.get_text());
                fg.set_startpunkt(tmp.get_pos_vertikal());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERGERADE)
            {
                fraesergerade tmp(letzte_bearb.get_text());
                fg.set_startpunkt(tmp.get_ep());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERBOGEN)
            {
                fraeserbogen tmp(letzte_bearb.get_text());
                fg.set_startpunkt(tmp.get_ep());
            }

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    if(fg.get_laenge_2d() > min_fkon_gerade_laenge || \
                       fg.get_zs() != fg.get_ze())
                    {
                        w.neue_bearbeitung(fg.get_text());
                    }
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_FKONG_AFB)
                    {
                        fg.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_FKONG_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        double x = tmp.toDouble();
                        x = w.get_laenge()-x;
                        fg.set_xe(x);
                    }else if(schluessel == FMC_FKONG_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fg.set_ye(tmp);
                    }else if(schluessel == FMC_FKONG_ZE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp == "Z")
                        {
                            fg.set_ze(fg.get_zs());//Der Z-Wert gibt die Tiefe an
                        }else
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            //werkstueck w = wste.at(index-1); //w ist bereits bekannt
                            double tiefe = w.get_dicke() - tmp.toDouble();
                            fg.set_ze(tiefe);//Der Z-Wert gibt die Tiefe an
                        }
                    }
                }
            }
        }else if(zeile.contains(FMC_FKONBOGUZS)   || \
                 zeile.contains(FMC_FKONBOGGUZS)     )
        {
            fraeserbogen fb;
            fb.set_bezug(WST_BEZUG_UNSEI);

            if(zeile.contains(FMC_FKONBOGUZS))
            {
                fb.set_uzs(true);
            }else
            {
                fb.set_uzs(false);
            }

            //Startpunkt aus der vorherigen Bearbeitung heraus einlesen:
            text_zeilenweise bearb;
            bearb = w.get_bearb();
            text_zeilenweise letzte_bearb;
            letzte_bearb.set_trennzeichen(TRENNZ_BEARB_PARAM);
            letzte_bearb.set_text(bearb.zeile(bearb.zeilenanzahl()));
            if(letzte_bearb.zeile(1) == BEARBART_FRAESERAUFRUF)
            {
                fraueseraufruf tmp(letzte_bearb.get_text());
                fb.set_startpunkt(tmp.get_pos_vertikal());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERGERADE)
            {
                fraesergerade tmp(letzte_bearb.get_text());
                fb.set_startpunkt(tmp.get_ep());
            }else if(letzte_bearb.zeile(1) == BEARBART_FRAESERBOGEN)
            {
                fraeserbogen tmp(letzte_bearb.get_text());
                fb.set_startpunkt(tmp.get_ep());
            }

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(fb.get_text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_FKONBOG_AFB)
                    {
                        fb.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_FKONBOG_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        double x = tmp.toDouble();
                        x = w.get_laenge()-x;
                        fb.set_xe(x);
                    }else if(schluessel == FMC_FKONBOG_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fb.set_ye(tmp);
                    }else if(schluessel == FMC_FKONBOG_ZE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        if(tmp == "Z")
                        {
                            fb.set_ze(fb.get_zs());//Der Z-Wert gibt die Tiefe an
                        }else
                        {
                            tmp = var_einsetzen(w, tmp);
                            tmp = ausdruck_auswerten(tmp);
                            double tiefe = w.get_dicke() - tmp.toDouble();
                            fb.set_ze(tiefe);//Der Z-Wert gibt die Tiefe an
                        }
                    }else if(schluessel == FMC_FKONBOG_RAD)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fb.set_rad(tmp);
                    }
                }
            }
        }else if(zeile.contains(FMC_FALZ))
        {
            fraueseraufruf fa;
            fraesergerade fg;
            fa.set_bezug(WST_BEZUG_UNSEI);
            fg.set_bezug(WST_BEZUG_UNSEI);

            for(uint ii=i+1; ii<=tz.zeilenanzahl() ;ii++)
            {
                zeile = tz.zeile(ii);
                if(!zeile.contains("=")) //Ende des Abschnittes
                {
                    i=ii-1;
                    w.neue_bearbeitung(fa.get_text());
                    w.neue_bearbeitung(fg.get_text());
                    break;
                }else
                {
                    QString schluessel = text_links(zeile, "=");
                    if(schluessel == FMC_FALZ_AFB)
                    {
                        fa.set_afb(wert_nach_istgleich(zeile));
                        fg.set_afb(wert_nach_istgleich(zeile));
                    }else if(schluessel == FMC_FALZ_XS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        double x = tmp.toDouble();
                        x = w.get_laenge()-x;
                        fa.set_x(x);
                        fg.set_xs(x);
                    }else if(schluessel == FMC_FALZ_YS)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fa.set_y(tmp);
                        fg.set_ys(tmp);
                    }else if(schluessel == FMC_FALZ_XE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        double x = tmp.toDouble();
                        x = w.get_laenge()-x;
                        fg.set_xe(x);
                    }else if(schluessel == FMC_FALZ_YE)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        fg.set_ye(tmp);
                    }else if(schluessel == FMC_FALZ_Z)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        //werkstueck w = wste.at(index-1);  //w ist bereits bekannt
                        double tiefe = w.get_dicke() - tmp.toDouble();
                        fa.set_tiefe(tiefe);//Tiefe, nicht Z-Wert!!
                                            //Z-Wert ist für horizontale Fräseraufrufe gedacht
                        fg.set_zs(tiefe);
                        fg.set_ze(tiefe);
                    }else if(schluessel == FMC_FALZ_KOR)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        tmp = var_einsetzen(w, tmp);
                        tmp = ausdruck_auswerten(tmp);
                        if(tmp == "1")
                        {
                            fa.set_radkor(FRKOR_L);
                        }else if(tmp == "0")
                        {
                            fa.set_radkor(FRKOR_M);
                        }else if(tmp == "2")
                        {
                            fa.set_radkor(FRKOR_R);
                        }

                    }else if(schluessel == FMC_FKON_WKZ)
                    {
                        QString tmp = wert_nach_istgleich(zeile);
                        fa.set_wkznum(tmp);
                    }
                }
            }

        }


    }

    wste.replace(index-1, w);

    return 0;
}




