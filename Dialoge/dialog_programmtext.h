#ifndef DIALOG_PROGRAMMTEXT_H
#define DIALOG_PROGRAMMTEXT_H

#include <QDialog>
#include <QListWidgetItem>

#include "Klassen/wst/werkstueck.h"
#include "Funktionen/funktionen_prgtext.h"
#include "Dialoge/dialog_bearb_rta.h"

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
    //QString bezug(QString b);
    werkstueck *Wst;

    //QString rta_zu_prgeile(QString text);

signals:
    void signalIndexChange(int index);
    void signalWstChanged(werkstueck *w, int index);

public slots:
    void slot_wst(werkstueck* w);
    void slot_zeilennummer(uint nr);

private slots:
    void resizeEvent(QResizeEvent *event);
    void on_listWidget_prgtext_currentRowChanged(int currentRow);

};

#endif // DIALOG_PROGRAMMTEXT_H
