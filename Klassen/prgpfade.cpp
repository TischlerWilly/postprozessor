#include "prgpfade.h"

prgpfade::prgpfade()
{
    Inifile             = "postprozessor.ini";
    StdNamen            = "namen_std.ini";
    ini_ganx            = "ganx.ini";
    Wkz_fmc             = "wkz_magazin_fmc.csv";
    Wkz_ganx            = "wkz_magazin_ganx.csv";
    Wkz_ggf             = "wkz_magazin_ggf.csv";
}

void prgpfade::ordner_erstellen()
{
    QDir dir_prg(path_prg());
    if(!dir_prg.exists())
    {
        dir_prg.mkdir(path_prg());
    }
    QDir dir_user(path_user());
    if(!dir_user.exists())
    {
        dir_user.mkdir(path_user());
    }
}

//--------------------------------------
QString prgpfade::name_inifile()
{
    return Inifile;
}
QString prgpfade::name_stdNamen()
{
    return StdNamen;
}
QString prgpfade::name_ini_ganx()
{
    return ini_ganx;
}
QString prgpfade::name_wkz_fmc()
{
    return Wkz_fmc;
}
QString prgpfade::name_wkz_ganx()
{
    return Wkz_ganx;
}
QString prgpfade::name_wkz_ggf()
{
    return Wkz_ggf;
}

//--------------------------------------Programmordner:
QString prgpfade::path_prg()
{
    QString tmp;
    tmp = "C:\\Program Files\\postprozessor";
    return tmp;
}

//--------------------------------------Nutzerordner:
QString prgpfade::path_user()
{
    QString tmp;
    tmp = QDir::homePath();
    tmp += QDir::separator();
    tmp += ".postprozessor";
    return tmp;
}
QString prgpfade::path_inifile()
{
    QString tmp;
    tmp = path_user();
    tmp += QDir::separator();
    tmp += Inifile;
    return tmp;
}
QString prgpfade::path_stdNamen()
{
    QString tmp;
    tmp = path_user();
    tmp += QDir::separator();
    tmp += StdNamen;
    return tmp;
}
QString prgpfade::path_ini_ganx()
{
    QString tmp;
    tmp = path_user();
    tmp += QDir::separator();
    tmp += ini_ganx;
    return tmp;
}
QString prgpfade::path_wkz_fmc()
{
    QString tmp;
    tmp = path_user();
    tmp += QDir::separator();
    tmp += Wkz_fmc;
    return tmp;
}
QString prgpfade::path_wkz_ganx()
{
    QString tmp;
    tmp = path_user();
    tmp += QDir::separator();
    tmp += Wkz_ganx;
    return tmp;
}
QString prgpfade::path_wkz_ggf()
{
    QString tmp;
    tmp = path_user();
    tmp += QDir::separator();
    tmp += Wkz_ggf;
    return tmp;
}
