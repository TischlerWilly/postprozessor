#ifndef DIALOG_PROGRAMMTEXT_H
#define DIALOG_PROGRAMMTEXT_H

#include <QDialog>

#include "Klassen/wst/werkstueck.h"

namespace Ui {
class Dialog_programmtext;
}

class Dialog_programmtext : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_programmtext(QWidget *parent = nullptr);
    ~Dialog_programmtext();

private:
    Ui::Dialog_programmtext *ui;
    werkstueck Wst;

public slots:
    void slot_wst(werkstueck w_neu,\
                  QString format, text_zeilenweise wkzmagazin, QString drehwinkel);

};

#endif // DIALOG_PROGRAMMTEXT_H
