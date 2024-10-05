#include "ewx_reference.h"

ewx_reference::ewx_reference()
{
    //Default-Werte:
    Refpunkt.set_x(0);
    Refpunkt.set_y(0);
    Refpunkt.set_z(0);
    Richtung_x = 1;
    Richtung_y = 1;
    Richtung_z = 1;
}

void ewx_reference::set_text(QString text)
{
    //Beispiel-text:
    //reference2 = Reference(pt=(1.0000, 2.0000, 3.0000), vz=(0.0000, 0.0000, 1.0000), vx=(1.0000, 0.0000, 0.0000))
    if(text.contains("Reference("))
    {
        text = text_rechts(text, "Reference(");
        if(text.contains("pt=("))
        {
            text_zw parameter;
            parameter.set_text(selektiereEintrag(text, "pt=(", ")"), ',');
            Refpunkt.set_x(parameter.at(0));
            Refpunkt.set_y(parameter.at(1));
            Refpunkt.set_z(parameter.at(2));
        }
        if(text.contains("vx=("))
        {
            text_zw parameter;
            parameter.set_text(selektiereEintrag(text, "vx=(", ")"), ',');
            if(parameter.at(0).toDouble() > 0)
            {
                Richtung_x = 1;
            }else
            {
                Richtung_x = -1;
            }
        }
        if(text.contains("vy=("))
        {
            text_zw parameter;
            parameter.set_text(selektiereEintrag(text, "vy=(", ")"), ',');
            if(parameter.at(1).toDouble() > 0)
            {
                Richtung_y = 1;
            }else
            {
                Richtung_y = -1;
            }
        }
        if(text.contains("vz=("))
        {
            text_zw parameter;
            parameter.set_text(selektiereEintrag(text, "vz=(", ")"), ',');
            if(parameter.at(2).toDouble() > 0)
            {
                Richtung_z = 1;
            }else
            {
                Richtung_z = -1;
            }
        }
    }
}

//----------------------get:
punkt3d ewx_reference::refpu()
{
    return Refpunkt;
}

double ewx_reference::richtung_x()
{
    return Richtung_x;
}

double ewx_reference::richtung_y()
{
    return Richtung_y;
}

double ewx_reference::richtung_z()
{
    return Richtung_z;
}




