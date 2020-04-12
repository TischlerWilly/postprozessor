#include "myfunktion.h"


QString ausdruck_auswerten(QString ausdruck)
{
    if(ausdruck == "AUTO")
    {
        return ausdruck;
    }
    QString returnstring ="";
    WennDannSonst f(ausdruck);
    returnstring = f.bekomme_Ergebnis_als_String();
    return returnstring;
}

bool ist_ziffer(const QChar zeichen)
{
    if(zeichen == '0' || zeichen == '1' || zeichen == '2' || zeichen == '2' || zeichen == '3' || zeichen == '4' || zeichen == '5' || zeichen == '6' || zeichen == '7' || zeichen == '8' || zeichen == '9')
    {
        return true;
    }else
    {
        return false;
    }
}

bool ist_zahl(const QString text)
{
    if(ist_ziffer(text.at(0))  || text.at(0)=='+' || text.at(0)=='-')//wenn erstes Zeichen eine Zahl oder ein Vorzeichen ist
    {
        int laenge = text.count();
        for(int i=1 ; i<laenge ; i++)
        {
            if(!ist_ziffer(text.at(i)) && text.at(i)!='.' && text.at(i)!=',' )
            {
                return false;
            }
        }
    }else
    {
        return false;
    }
    //Wenn diese Stelle erreicht wird dann enthällt der Text nur Zahlen:
    return true;
}

bool ist_buchstabe(QChar zeichen)
{
    zeichen = zeichen.toUpper();
    bool erg = false;

    if(zeichen=='A'||zeichen=='B'||zeichen=='C'||zeichen=='D'||zeichen=='E'||zeichen=='F'||zeichen=='G'||zeichen=='H'||zeichen=='I'||zeichen=='J'||zeichen=='K'||zeichen=='L'||zeichen=='M'||zeichen=='N'||zeichen=='O'||zeichen=='P'||zeichen=='Q'||zeichen=='R'||zeichen=='S'||zeichen=='T'||zeichen=='U'||zeichen=='V'||zeichen=='W'||zeichen=='X'||zeichen=='Y'||zeichen=='Z')
    {
        erg = true;
    }

    return erg;
}

QString genauigkeit_reduzieren(QString zahl, uint nachkommastellen)
{
    if(zahl.contains("."))
    {
        QString li = text_links(zahl, ".");
        QString re = text_rechts(zahl, ".");
        zahl = li;
        zahl += ".";
        for(uint i=0; i<nachkommastellen && i<re.length();i++)
        {
            zahl += re.at(i);
        }
    }else if(zahl.contains(","))
    {
        QString li = text_links(zahl, ",");
        QString re = text_rechts(zahl, ",");
        zahl = li;
        zahl += ",";
        for(uint i=0; i<nachkommastellen && i<re.length();i++)
        {
            zahl += re.at(i);
        }
    }
    return zahl;
}

QString genauigkeit_reduzieren(double zahl, uint nachkommastellen)
{
    int zahlalsint = zahl*(10*nachkommastellen);
    zahl = zahlalsint/(10*nachkommastellen);
    return double_to_qstring(zahl);
}



