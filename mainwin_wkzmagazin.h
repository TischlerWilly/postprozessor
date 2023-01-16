#ifndef MAINWIN_WKZMAGAZIN_H
#define MAINWIN_WKZMAGAZIN_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <Klassen/undo_redo.h>
#include "Klassen/wkz/wkz_magazin.h"
#include "Dialoge/dialog_fraeser.h"
#include "Dialoge/dialog_bohrer.h"
#include "Dialoge/dialog_saege.h"

QT_BEGIN_NAMESPACE
namespace Ui { class mainwin_wkzmagazin; }
QT_END_NAMESPACE

class mainwin_wkzmagazin : public QMainWindow
{
    Q_OBJECT

public:
    mainwin_wkzmagazin(QWidget *parent = nullptr);
    ~mainwin_wkzmagazin();

    //-------------------------------------set:
    void set_wkzmag(wkz_magazin w);

private slots:
    void on_actionFraeser_anlegen_triggered();
    void on_actionBohrer_anlegen_triggered();
    void on_actionSaege_anlegen_triggered();
    void on_actionRunter_triggered();
    void on_actionHoch_triggered();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
    void on_listWidget_currentRowChanged(int currentRow);
    void on_actionL_schen_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionDuplizieren_triggered();

public slots:
    void getData(text_zw wkz, bool ist_neues_wkz);

private:
    void liste_aktualisieren();
    void info_aktualisieren(uint index);
    void edit(uint index);

    Ui::mainwin_wkzmagazin *ui;
    wkz_magazin     Magazin;
    undo_redo<wkz_magazin> UnReDo;
    Dialog_fraeser  dlg_fraeser;
    Dialog_bohrer   dlg_bohrer;
    Dialog_saege    dlg_saege;
};
#endif // MAINWIN_WKZMAGAZIN_H
