#include "werkstuecke.h"


werkstuecke::werkstuecke()
{

}

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
    }
    return false;
}

void werkstuecke::clear()
{
    namen.clear();
    quellformate.clear();
}
