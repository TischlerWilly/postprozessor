#ifndef DIALOG_EXPORTUEBERSICHT_H
#define DIALOG_EXPORTUEBERSICHT_H

#include <QDialog>
#include <QMessageBox>
#include "Klassen/text_zw.h"
#include "Funktionen/text.h"

namespace Ui {
class Dialog_ExportUebersicht;
}

class Dialog_ExportUebersicht : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_ExportUebersicht(QWidget *parent = nullptr);
    ~Dialog_ExportUebersicht();

public slots:
    void slot_wstnamen(text_zw namen);
    void slot_wstexport(QString name, QString format, bool exportiert);
    void slot_wst_umbenennen(QString name_vor, QString name_nach);
    void slot_wst_ausblenden(QString name, bool ausblenden);

private:
    Ui::Dialog_ExportUebersicht *ui;
    int spalte_namen;
    int spalte_fmc;
    int spalte_ganx;
    int spalte_cix;
    int spalte_ggf;
    int spalte_eigen;

private slots:
    void resizeEvent(QResizeEvent *event);

};

#endif // DIALOG_EXPORTUEBERSICHT_H
