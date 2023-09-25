/********************************************************************************
** Form generated from reading UI file 'dialog_exportuebersicht.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_EXPORTUEBERSICHT_H
#define UI_DIALOG_EXPORTUEBERSICHT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_ExportUebersicht
{
public:
    QTableWidget *tableWidget_exporte;

    void setupUi(QDialog *Dialog_ExportUebersicht)
    {
        if (Dialog_ExportUebersicht->objectName().isEmpty())
            Dialog_ExportUebersicht->setObjectName(QStringLiteral("Dialog_ExportUebersicht"));
        Dialog_ExportUebersicht->resize(260, 750);
        tableWidget_exporte = new QTableWidget(Dialog_ExportUebersicht);
        tableWidget_exporte->setObjectName(QStringLiteral("tableWidget_exporte"));
        tableWidget_exporte->setGeometry(QRect(10, 10, 191, 151));

        retranslateUi(Dialog_ExportUebersicht);

        QMetaObject::connectSlotsByName(Dialog_ExportUebersicht);
    } // setupUi

    void retranslateUi(QDialog *Dialog_ExportUebersicht)
    {
        Dialog_ExportUebersicht->setWindowTitle(QApplication::translate("Dialog_ExportUebersicht", "Export\303\274bersicht", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_ExportUebersicht: public Ui_Dialog_ExportUebersicht {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_EXPORTUEBERSICHT_H
