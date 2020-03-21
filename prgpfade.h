#ifndef PRGPFADE_H
#define PRGPFADE_H

#include <QString>
#include <QDir>

class prgpfade
{
public:
    prgpfade();
    void ordner_erstellen();
    QString get_path_prg();
    QString get_path_user();
    QString get_path_inifile();
    QString get_path_stdNamen();
    QString get_path_wkz_fmc();
    QString get_path_wkz_ganx();
    QString get_path_wkz_ggf();

    QString get_name_inifile();
    QString get_name_stdNamen();
    QString get_name_wkz_fmc();
    QString get_name_wkz_ganx();
    QString get_name_wkz_ggf();

private:
    //Ordner:

    //ini-Dateien:
    QString inifile;
    QString stdNamen;

    //WKZ-Dateien:
    QString wkz_fmc;
    QString wkz_ganx;
    QString wkz_ggf;

};

#endif // PRGPFADE_H
