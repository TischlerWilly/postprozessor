#ifndef DIALOG_EINSTELLUNG_DXF_KLASSEN_H
#define DIALOG_EINSTELLUNG_DXF_KLASSEN_H

#include <QDialog>
#include "Klassen/einstellung_dxf_klassen.h"

namespace Ui {
class Dialog_einstellung_dxf_klassen;
}

class Dialog_einstellung_dxf_klassen : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_einstellung_dxf_klassen(QWidget *parent = nullptr);
    ~Dialog_einstellung_dxf_klassen();
    einstellung_dxf_klassen einstellung();

signals:
    void send_einstellung(einstellung_dxf_klassen e);

public slots:
    void slot_einstellung(einstellung_dxf_klassen e);

private slots:
    void on_pushButton_abbrechen_clicked();
    void on_pushButton_speichern_clicked();

    void on_lineEdit_wst_textChanged(const QString &arg1);

private:
    Ui::Dialog_einstellung_dxf_klassen *ui;
    einstellung_dxf_klassen Einstellung;
};

#endif // DIALOG_EINSTELLUNG_DXF_KLASSEN_H
