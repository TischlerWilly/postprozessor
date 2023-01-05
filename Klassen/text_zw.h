#ifndef TEXT_TZ_H
#define TEXT_TZ_H

#include <QString>

class text_zw
{
public:
    text_zw();
    text_zw(QString text, char trennzeichen = '\n');

    //---------------------------------------------set_xy:
    void    set_text(QString text, char trennzeichen = '\n');

    //---------------------------------------------get_xy:
    QString     zeile(uint zeilennummer);
    QString     zeilen(uint zeilennummer_beginn, uint zeilenmenge);
    QString     text();
    char        trennz();
    uint        count();

    //---------------------------------------------Manipulationen:
    void    clear();
    void    add_before(QString text);
    void    add_after(QString text);

private:
    std::vector<QString> Daten;
    char Trennzeichen;

    std::vector<QString> to_vector(QString text, char trennzeichen = '\n');



};

#endif // TEXT_TZ_H
