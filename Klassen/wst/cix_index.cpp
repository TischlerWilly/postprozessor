#include "cix_index.h"

cix_index::cix_index()
{
    Index = 1001;
}

QString cix_index::index_QString()
{
    QString ret = "P";
    ret += int_to_qstring(Index);
    Index++;
    return ret;
}
