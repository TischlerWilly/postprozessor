#ifndef DIALOG_STDNAME_H
#define DIALOG_STDNAME_H

#include <QDialog>

namespace Ui {
class Dialog_stdname;
}

class Dialog_stdname : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_stdname(QWidget *parent = 0);
    ~Dialog_stdname();

public slots:
    void slot_getData(QString vor, QString nach);

private slots:
    void on_pushButton_ok_clicked();
    void on_pushButton_abbrechen_clicked();

signals:
    void signal_sendData(QString vor, QString nach);

private:
    Ui::Dialog_stdname *ui;
};

#endif // DIALOG_STDNAME_H
