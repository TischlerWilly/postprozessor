#include "cix_index_geo.h"

cix_index_geo::cix_index_geo()
{
    Index = 1;
}

QString cix_index_geo::index_QString()
{
    QString ret = int_to_qstring(Index);
    Index++;
    return ret;
}
