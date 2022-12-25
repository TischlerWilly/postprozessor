#ifndef DIALOG_BEARB_NUT_H
#define DIALOG_BEARB_NUT_H

#include <Klassen/wst/nut.h>
#include <QDialog>

namespace Ui {
class Dialog_bearb_nut;
}

class Dialog_bearb_nut : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_bearb_nut(QWidget *parent = nullptr);
    ~Dialog_bearb_nut();
    void set_data(QString d);

private slots:
    void on_btn_ok_clicked();
    void on_btn_abbrechen_clicked();

signals:
    void signal_nut(nut nu);

private:
    Ui::Dialog_bearb_nut *ui;
};

#endif // DIALOG_BEARB_NUT_H
