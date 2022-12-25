#ifndef EINSTELLUNG_DXF_H
#define EINSTELLUNG_DXF_H

#include <QString>
#include <QMessageBox>
#include "Klassen/text_zeilenweise.h"
#include "Funktionen/umwandeln.h"

class einstellung_dxf
{
public:
    einstellung_dxf();

    //set:
    void set_text(QString t);
    void set_paramtren(QString parametertrennzeichen);
    void set_dezitren(QString dezimaltrenner);
    void set_kenObsei(QString kennung_oberseite);
    void set_kenUnsei(QString kennung_unterseite);
    void set_dretypUnsei(QString drehtyp);
    void set_kenWKZnr(QString kennung);
    void set_kenRadKorLi(QString kennung);
    void set_kenRadKorMi(QString kennung);
    void set_kenRadKorRe(QString kennung);
    void set_bezugTiFkon(QString bezug);

    //get:
    QString text();
    QString paramtren();
    QString dezitren();
    QString kenObsei();
    QString kenUnsei();
    QString drehtypUnsei();
    bool drehtyp_L();
    bool drehtyp_B();
    QString kenWKZnr();
    QString kenRadKorLi();
    QString kenRadKorMi();
    QString kenRadKorRe();
    QString bezugTiFkon();
    bool bezugTiFkonObSei();
    bool bezugTiFkonUnSei();

private:
    QString Paramtren;
    QString Dezitren;
    QString KennungOberseite;
    QString KennungUnterseite;
    QString DrehtypUnterseite; // "L" "B"
    QString KennungWKZnr;
    QString KennungRadKorLi;
    QString KennungRadKorMi;
    QString KennungRadKorRe;
    QString BezugTiFkon;

};

#endif // EINSTELLUNG_DXF_H

//-------------------Funktionen nicht innerhalb der Klasse:
bool operator ==(einstellung_dxf e1, einstellung_dxf e2);
bool operator !=(einstellung_dxf e1, einstellung_dxf e2);

