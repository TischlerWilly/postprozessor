#ifndef UNDO_REDO_TZ_H
#define UNDO_REDO_TZ_H

#include <vector>
#include "Klassen/text_zw.h"


template<typename T>
class undo_redo
{
public:
    undo_redo()
    {
        set_groesse_max(20);
        clear();
    }
    void neu(T t_neu)
    {
        if((uint)Aktuelle_position+1 == Vector_t.size())
        {
            if(Vector_t.size() < Max_anzahl)
            {
                Vector_t.push_back(t_neu);
                Aktuelle_position++;
            }else
            {
                Vector_t.erase(Vector_t.begin());
                Vector_t.push_back(t_neu);
            }
        }else
        {
            Vector_t.erase(Vector_t.begin()+Aktuelle_position+1, Vector_t.end());
            Vector_t.push_back(t_neu);
            Aktuelle_position = Vector_t.size()-1;
        }
    }

    //----------------------------------------set_xy:
    void set_groesse_max(uint maximale_anzahl_an_wiederrufenschritten)
    {
        if(maximale_anzahl_an_wiederrufenschritten > Vector_t.size())
        {
            Max_anzahl = maximale_anzahl_an_wiederrufenschritten;
        }
        if(maximale_anzahl_an_wiederrufenschritten < Vector_t.size())
        {
            Vector_t.clear();
            Max_anzahl = maximale_anzahl_an_wiederrufenschritten;
        }
    }

    //----------------------------------------get_xy:
    uint groesse_max()
    {
        return Max_anzahl;
    }
    uint groesse()
    {
        return Vector_t.size();
    }
    int  erstes_aktives_element()
    {
        return Erstes_aktives_element_t.at(Aktuelle_position);
    }
    int  anz_aktive_elemente()
    {
        return Anz_aktive_elemente_t.at(Aktuelle_position);
    }

    //----------------------------------------Manipulationen:
    void             clear()
    {
        Aktuelle_position = -1;
        Vector_t.clear();
    }
    T undo()
    {
        if(Aktuelle_position > 0)
        {
            Aktuelle_position--;
            return Vector_t.at(Aktuelle_position);
        }else
        {
            return Vector_t.at(0);
        }
    }
    T redo()
    {
        if((uint)Aktuelle_position+1 < Vector_t.size())
        {
            Aktuelle_position++;
            return Vector_t.at(Aktuelle_position);
        }else
        {
            return Vector_t.at(Aktuelle_position);
        }
    }

    //----------------------------------------

private:

    std::vector<T> Vector_t;
    std::vector<int>              Erstes_aktives_element_t;
    std::vector<int>              Anz_aktive_elemente_t;

    int  Aktuelle_position;
    uint Max_anzahl;




};



#endif // UNDO_REDO_TZ_H
