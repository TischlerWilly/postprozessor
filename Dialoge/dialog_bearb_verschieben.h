#ifndef DIALOG_BEARB_VERSCHIEBEN_H
#define DIALOG_BEARB_VERSCHIEBEN_H

#include <QDialog>
#include "Klassen/formel.h"
#include "Klassen/geo/punkt3d.h"

namespace Ui {
class Dialog_bearb_verschieben;
}

class Dialog_bearb_verschieben : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_bearb_verschieben(QWidget *parent = nullptr);
    ~Dialog_bearb_verschieben();

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();

private:
    Ui::Dialog_bearb_verschieben *ui;

signals:
    void signal_punkt(punkt3d p);
};

#endif // DIALOG_BEARB_VERSCHIEBEN_H
