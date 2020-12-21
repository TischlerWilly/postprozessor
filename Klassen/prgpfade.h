#ifndef PRGPFADE_H
#define PRGPFADE_H

#include <QString>
#include <QDir>

class prgpfade
{
public:
    prgpfade();
    void ordner_erstellen();
    QString path_prg();
    QString path_user();
    QString path_inifile();
    QString path_stdNamen();
    QString path_ini_ganx();
    QString path_wkz_fmc();
    QString path_wkz_ganx();
    QString path_wkz_ggf();

    QString name_inifile();
    QString name_stdNamen();
    QString name_ini_ganx();
    QString name_wkz_fmc();
    QString name_wkz_ganx();
    QString name_wkz_ggf();

private:
    //Ordner:

    //ini-Dateien:
    QString Inifile;
    QString StdNamen;
    QString ini_ganx;

    //WKZ-Dateien:
    QString Wkz_fmc;
    QString Wkz_ganx;
    QString Wkz_ggf;

};

#endif // PRGPFADE_H
