#ifndef DIALOG_EINSTELLUNG_WKZ_PP_H
#define DIALOG_EINSTELLUNG_WKZ_PP_H

#include <QDialog>
#include "Klassen/einstellung.h"

namespace Ui {
class Dialog_einstellung_wkz_pp;
}

class Dialog_einstellung_wkz_pp : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_einstellung_wkz_pp(QWidget *parent = nullptr);
    ~Dialog_einstellung_wkz_pp();
    void set_einstellung(einstellung e);

signals:
    void send_einstellungen(einstellung e);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();

private:
    Ui::Dialog_einstellung_wkz_pp *ui;
    einstellung Einstellung;
};

#endif // DIALOG_EINSTELLUNG_WKZ_PP_H
