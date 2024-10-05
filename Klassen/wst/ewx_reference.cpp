#include "ewx_reference.h"

ewx_reference::ewx_reference()
{
    Bezug = "NULL";//Nicht definiert
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
            Vector_x.set_x(parameter.at(0));
            Vector_x.set_y(parameter.at(1));
            Vector_x.set_z(parameter.at(2));
        }
        if(text.contains("vy=("))
        {
            text_zw parameter;
            parameter.set_text(selektiereEintrag(text, "vy=(", ")"), ',');
            Vector_y.set_x(parameter.at(0));
            Vector_y.set_y(parameter.at(1));
            Vector_y.set_z(parameter.at(2));
        }
        if(text.contains("vz=("))
        {
            text_zw parameter;
            parameter.set_text(selektiereEintrag(text, "vz=(", ")"), ',');
            Vector_z.set_x(parameter.at(0));
            Vector_z.set_y(parameter.at(1));
            Vector_z.set_z(parameter.at(2));
        }

        //Achtung!!!
        //Die EWX-Datei definiert den WST-Nullpunkt auf der WST-Oberseite!!!
        //Im Postprozessor ist der WST-Nullpunkt auf der WST-Unterseite!!!
        //Bei der weiteren Verwendung der Koordinaten muss der Z-Wert um die
        //Wst-Dicke nach unten versetzt werden!!!

        if(Vector_z.x() ==  0 && Vector_z.y() ==  0 && Vector_z.z() ==  1 && \
           Vector_x.x() ==  1 && Vector_x.y() ==  0 && Vector_x.z() ==  0  )
        {
            //Reference(pt=(0.0000, 0.0000, 0.0000), vz=(0.0000, 0.0000, 1.0000), vx=(1.0000, 0.0000, 0.0000))
            //Hole(pos=(100.0000, 50.0000, 0.0000), diameter=8.0000, depth=14.0000, passing=False),
            //->bo.x = 100
            //->bo.y = 50
            //->bo.z = 19
            Bezug = WST_BEZUG_OBSEI;
            //X = Refpunkt.x() + bearb.x()
            //Y = Refpunkt.y() + bearb.y()
            //Z = Refpunkt.z() + Wst_dicke
        }else if(Vector_z.x() ==  0 && Vector_z.y() ==  0 && Vector_z.z() == -1 && \
                 Vector_x.x() == -1 && Vector_x.y() ==  0 && Vector_x.z() ==  0  )
        {
            //Reference(pt=(1000.0000, 0.0000, -19.0000), vz=(0.0000, 0.0000, -1.0000), vx=(-1.0000, 0.0000, 0.0000))
            //Hole(pos=(920.0000, 40.0000, 0.0000), diameter=15.0000, depth=10.0000, passing=False),
            //->bo.x = 80
            //->bo.y = 40
            //->bo.z = 0
            Bezug = WST_BEZUG_UNSEI;
            //X = Refpunkt.x() - bearb.x()
            //Y = Refpunkt.y() + bearb.y()
            //Z = Refpunkt.z() + Wst_dicke
        }else if(Vector_z.x() == -1 && Vector_z.y() ==  0 && Vector_z.z() ==  0 && \
                 Vector_x.x() ==  0 && Vector_x.y() == -1 && Vector_x.z() ==  0  )
        {
            //Reference(pt=(0.0000, 500.0000, -19.0000), vz=(-1.0000, 0.0000, 0.0000), vx=(0.0000, -1.0000, 0.0000))
            //Hole(pos=(480.0000, 5.0000, 0.0000), diameter=8.0000, depth=18.0000, passing=False),
            //->bo.x = 0
            //->bo.y = 20
            //->bo.z = 5
            Bezug = WST_BEZUG_LI;
            //X = Refpunkt.x()
            //Y = Refpunkt.y() - bearb.x()
            //Z = Refpunkt.z() + Wst_dicke + bearb.y()
        }else if(Vector_z.x() ==  1 && Vector_z.y() ==  0 && Vector_z.z() ==  0 && \
                 Vector_x.x() ==  0 && Vector_x.y() ==  1 && Vector_x.z() ==  0  )
        {
            //Reference(pt=(1000.0000, 0.0000, -19.0000), vz=(1.0000, 0.0000, 0.0000), vx=(0.0000, 1.0000, 0.0000))
            //Hole(pos=(30.0000, 5.0000, 0.0000), diameter=8.0000, depth=18.0000, passing=False),
            //->bo.x = 1000
            //->bo.y = 30
            //->bo.z = 5
            Bezug = WST_BEZUG_RE;
            //X = Refpunkt.x()
            //Y = Refpunkt.y() + bearb.x()
            //Z = Refpunkt.z() + Wst_dicke + bearb.y()
        }else if(Vector_z.x() ==  0 && Vector_z.y() == -1 && Vector_z.z() ==  0 && \
                 Vector_x.x() ==  1 && Vector_x.y() ==  0 && Vector_x.z() ==  0  )
        {
            //Reference(pt=(0.0000, 0.0000, -19.0000), vz=(0.0000, -1.0000, 0.0000), vx=(1.0000, 0.0000, 0.0000))
            //Hole(pos=(40.0000, 5.0000, 0.0000), diameter=8.0000, depth=18.0000, passing=False),
            //->bo.x = 40
            //->bo.y = 0
            //->bo.z = 5
            Bezug = WST_BEZUG_VO;
            //X = Refpunkt.x() + bearb.x()
            //Y = Refpunkt.y()
            //Z = Refpunkt.z() + Wst_dicke + bearb.y()
        }else if(Vector_z.x() ==  0 && Vector_z.y() ==  1 && Vector_z.z() ==  0 && \
                 Vector_x.x() == -1 && Vector_x.y() ==  0 && Vector_x.z() ==  0  )
        {
            //Reference(pt=(1000.0000, 500.0000, -19.0000), vz=(0.0000, 1.0000, 0.0000), vx=(-1.0000, 0.0000, 0.0000))
            //Hole(pos=(950.0000, 5.0000, 0.0000), diameter=8.0000, depth=18.0000, passing=False),
            //->bo.x = 50
            //->bo.y = 500
            //->bo.z = 5
            Bezug = WST_BEZUG_HI;
            //X = Refpunkt.x() - bearb.x()
            //Y = Refpunkt.y()
            //Z = Refpunkt.z() + Wst_dicke + bearb.y()
        }
    }
}
void ewx_reference::set_wst_dicke(double dicke)
{
    Wst_dicke = dicke;
}

//----------------------get:
punkt3d ewx_reference::refpu()
{
    return Refpunkt;
}
punkt3d ewx_reference::vector_x()
{
    return Vector_x;
}
punkt3d ewx_reference::vector_y()
{
    return Vector_y;
}
punkt3d ewx_reference::vector_z()
{
    return Vector_z;
}
QString ewx_reference::bezug()
{
    return Bezug;
}
punkt3d ewx_reference::bearbpos(punkt3d pos_in_ewx)
{
    punkt3d retpos;
    //Achtung!!!
    //Die EWX-Datei definiert den WST-Nullpunkt auf der WST-Oberseite!!!
    //Im Postprozessor ist der WST-Nullpunkt auf der WST-Unterseite!!!
    //Bei der weiteren Verwendung der Koordinaten muss der Z-Wert um die
    //Wst-Dicke nach unten versetzt werden!!!

    if(Vector_z.x() ==  0 && Vector_z.y() ==  0 && Vector_z.z() ==  1 && \
       Vector_x.x() ==  1 && Vector_x.y() ==  0 && Vector_x.z() ==  0  )
    {
        //Reference(pt=(0.0000, 0.0000, 0.0000), vz=(0.0000, 0.0000, 1.0000), vx=(1.0000, 0.0000, 0.0000))
        //Hole(pos=(100.0000, 50.0000, 0.0000), diameter=8.0000, depth=14.0000, passing=False),
        //->bo.x = 100
        //->bo.y = 50
        //->bo.z = 19
        //Bezug = WST_BEZUG_OBSEI;
        retpos.set_x( Refpunkt.x() + pos_in_ewx.x() );
        retpos.set_y( Refpunkt.y() + pos_in_ewx.y() );
        retpos.set_z( Refpunkt.z() + Wst_dicke );
    }else if(Vector_z.x() ==  0 && Vector_z.y() ==  0 && Vector_z.z() == -1 && \
             Vector_x.x() == -1 && Vector_x.y() ==  0 && Vector_x.z() ==  0  )
    {
        //Reference(pt=(1000.0000, 0.0000, -19.0000), vz=(0.0000, 0.0000, -1.0000), vx=(-1.0000, 0.0000, 0.0000))
        //Hole(pos=(920.0000, 40.0000, 0.0000), diameter=15.0000, depth=10.0000, passing=False),
        //->bo.x = 80
        //->bo.y = 40
        //->bo.z = 0
        //Bezug = WST_BEZUG_UNSEI;
        retpos.set_x(  Refpunkt.x() - pos_in_ewx.x() );
        retpos.set_y(  Refpunkt.y() + pos_in_ewx.y() );
        retpos.set_z( Refpunkt.z() + Wst_dicke );
    }else if(Vector_z.x() == -1 && Vector_z.y() ==  0 && Vector_z.z() ==  0 && \
             Vector_x.x() ==  0 && Vector_x.y() == -1 && Vector_x.z() ==  0  )
    {
        //Reference(pt=(0.0000, 500.0000, -19.0000), vz=(-1.0000, 0.0000, 0.0000), vx=(0.0000, -1.0000, 0.0000))
        //Hole(pos=(480.0000, 5.0000, 0.0000), diameter=8.0000, depth=18.0000, passing=False),
        //->bo.x = 0
        //->bo.y = 20
        //->bo.z = 5
        //Bezug = WST_BEZUG_LI;
        retpos.set_x(  Refpunkt.x() );
        retpos.set_y(  Refpunkt.y()  - pos_in_ewx.x() );
        retpos.set_z( Refpunkt.z() + Wst_dicke + pos_in_ewx.y() );
    }else if(Vector_z.x() ==  1 && Vector_z.y() ==  0 && Vector_z.z() ==  0 && \
             Vector_x.x() ==  0 && Vector_x.y() ==  1 && Vector_x.z() ==  0  )
    {
        //Reference(pt=(1000.0000, 0.0000, -19.0000), vz=(1.0000, 0.0000, 0.0000), vx=(0.0000, 1.0000, 0.0000))
        //Hole(pos=(30.0000, 5.0000, 0.0000), diameter=8.0000, depth=18.0000, passing=False),
        //->bo.x = 1000
        //->bo.y = 30
        //->bo.z = 5
        //Bezug = WST_BEZUG_RE;
        retpos.set_x(  Refpunkt.x() );
        retpos.set_y(  Refpunkt.y() + pos_in_ewx.x() );
        retpos.set_z( Refpunkt.z() + Wst_dicke + pos_in_ewx.y() );
    }else if(Vector_z.x() ==  0 && Vector_z.y() == -1 && Vector_z.z() ==  0 && \
             Vector_x.x() ==  1 && Vector_x.y() ==  0 && Vector_x.z() ==  0  )
    {
        //Reference(pt=(0.0000, 0.0000, -19.0000), vz=(0.0000, -1.0000, 0.0000), vx=(1.0000, 0.0000, 0.0000))
        //Hole(pos=(40.0000, 5.0000, 0.0000), diameter=8.0000, depth=18.0000, passing=False),
        //->bo.x = 40
        //->bo.y = 0
        //->bo.z = 5
        //Bezug = WST_BEZUG_VO;
        retpos.set_x( Refpunkt.x() + pos_in_ewx.x() );
        retpos.set_y( Refpunkt.y() );
        retpos.set_z( Refpunkt.z() + Wst_dicke + pos_in_ewx.y() );
    }else if(Vector_z.x() ==  0 && Vector_z.y() ==  1 && Vector_z.z() ==  0 && \
             Vector_x.x() == -1 && Vector_x.y() ==  0 && Vector_x.z() ==  0  )
    {
        //Reference(pt=(1000.0000, 500.0000, -19.0000), vz=(0.0000, 1.0000, 0.0000), vx=(-1.0000, 0.0000, 0.0000))
        //Hole(pos=(950.0000, 5.0000, 0.0000), diameter=8.0000, depth=18.0000, passing=False),
        //->bo.x = 50
        //->bo.y = 500
        //->bo.z = 5
        //Bezug = WST_BEZUG_HI;
        retpos.set_x( Refpunkt.x() - pos_in_ewx.x() );
        retpos.set_y( Refpunkt.y() );
        retpos.set_z( Refpunkt.z() + Wst_dicke + pos_in_ewx.y() );
    }
    return retpos;
}


