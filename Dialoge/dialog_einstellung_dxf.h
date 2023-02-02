#ifndef DIALOG_EINSTELLUNG_DXF_H
#define DIALOG_EINSTELLUNG_DXF_H

#include <QDialog>
#include "Klassen/einstellung_dxf.h"

namespace Ui {
class Dialog_einstellung_dxf;
}

class Dialog_einstellung_dxf : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_einstellung_dxf(QWidget *parent = nullptr);
    ~Dialog_einstellung_dxf();
    einstellung_dxf einstellung();

signals:
    void send_einstellung(einstellung_dxf e);

public slots:
    void slot_einstellung(einstellung_dxf e);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();

private:
    Ui::Dialog_einstellung_dxf *ui;
    einstellung_dxf Einstellung;
};

#endif // DIALOG_EINSTELLUNG_DXF_H
