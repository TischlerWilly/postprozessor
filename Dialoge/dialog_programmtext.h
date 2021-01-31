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
    QString bezug(QString b);

signals:
    void signalIndexChange(int index);

public slots:
    void slot_wst(werkstueck* w);
    void slot_zeilennummer(uint nr);

private slots:
    void resizeEvent(QResizeEvent *event);
    void on_listWidget_prgtext_currentRowChanged(int currentRow);
};

#endif // DIALOG_PROGRAMMTEXT_H
