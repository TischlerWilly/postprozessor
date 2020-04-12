#include "prgpfade.h"

prgpfade::prgpfade()
{
    inifile             = "postprozessor.ini";
    stdNamen            = "namen_std.ini";
    wkz_fmc             = "wkz_magazin_fmc.csv";
    wkz_ganx            = "wkz_magazin_ganx.csv";
    wkz_ggf             = "wkz_magazin_ggf.csv";
}

void prgpfade::ordner_erstellen()
{
    QDir dir_prg(get_path_prg());
    if(!dir_prg.exists())
    {
        dir_prg.mkdir(get_path_prg());
    }
    QDir dir_user(get_path_user());
    if(!dir_user.exists())
    {
        dir_user.mkdir(get_path_user());
    }
}

//--------------------------------------
QString prgpfade::get_name_inifile()
{
    return inifile;
}
QString prgpfade::get_name_stdNamen()
{
    return stdNamen;
}
QString prgpfade::get_name_wkz_fmc()
{
    return wkz_fmc;
}
QString prgpfade::get_name_wkz_ganx()
{
    return wkz_ganx;
}
QString prgpfade::get_name_wkz_ggf()
{
    return wkz_ggf;
}

//--------------------------------------Programmordner:
QString prgpfade::get_path_prg()
{
    QString tmp;
    tmp = "C:\\Program Files\\postprozessor";
    return tmp;
}

//--------------------------------------Nutzerordner:
QString prgpfade::get_path_user()
{
    QString tmp;
    tmp = QDir::homePath();
    tmp += QDir::separator();
    tmp += ".postprozessor";
    return tmp;
}
QString prgpfade::get_path_inifile()
{
    QString tmp;
    tmp = get_path_user();
    tmp += QDir::separator();
    tmp += inifile;
    return tmp;
}
QString prgpfade::get_path_stdNamen()
{
    QString tmp;
    tmp = get_path_user();
    tmp += QDir::separator();
    tmp += stdNamen;
    return tmp;
}
QString prgpfade::get_path_wkz_fmc()
{
    QString tmp;
    tmp = get_path_user();
    tmp += QDir::separator();
    tmp += wkz_fmc;
    return tmp;
}
QString prgpfade::get_path_wkz_ganx()
{
    QString tmp;
    tmp = get_path_user();
    tmp += QDir::separator();
    tmp += wkz_ganx;
    return tmp;
}
QString prgpfade::get_path_wkz_ggf()
{
    QString tmp;
    tmp = get_path_user();
    tmp += QDir::separator();
    tmp += wkz_ggf;
    return tmp;
}
