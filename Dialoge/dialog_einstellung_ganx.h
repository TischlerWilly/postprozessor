#ifndef DIALOG_EINSTELLUNG_GANX_H
#define DIALOG_EINSTELLUNG_GANX_H

#include <QDialog>
#include "Klassen/einstellung_ganx.h"

namespace Ui {
class Dialog_einstellung_ganx;
}

class Dialog_einstellung_ganx : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_einstellung_ganx(QWidget *parent = nullptr);
    ~Dialog_einstellung_ganx();
    einstellung_ganx einstellung();

signals:
    void send_einstellung(einstellung_ganx e);

public slots:
    void slot_einstellung(einstellung_ganx e);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();

private:
    Ui::Dialog_einstellung_ganx *ui;
    einstellung_ganx Einstellung;
};

#endif // DIALOG_EINSTELLUNG_GANX_H
