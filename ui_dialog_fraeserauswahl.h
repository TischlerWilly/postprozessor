/********************************************************************************
** Form generated from reading UI file 'dialog_fraeserauswahl.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_FRAESERAUSWAHL_H
#define UI_DIALOG_FRAESERAUSWAHL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_fraeserauswahl
{
public:
    QTableWidget *tableWidget;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_abbrechen;

    void setupUi(QDialog *Dialog_fraeserauswahl)
    {
        if (Dialog_fraeserauswahl->objectName().isEmpty())
            Dialog_fraeserauswahl->setObjectName(QStringLiteral("Dialog_fraeserauswahl"));
        Dialog_fraeserauswahl->resize(867, 538);
        Dialog_fraeserauswahl->setModal(true);
        tableWidget = new QTableWidget(Dialog_fraeserauswahl);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setEnabled(true);
        tableWidget->setGeometry(QRect(10, 10, 841, 481));
        pushButton_ok = new QPushButton(Dialog_fraeserauswahl);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(230, 500, 200, 23));
        pushButton_abbrechen = new QPushButton(Dialog_fraeserauswahl);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));
        pushButton_abbrechen->setGeometry(QRect(440, 500, 200, 23));

        retranslateUi(Dialog_fraeserauswahl);

        QMetaObject::connectSlotsByName(Dialog_fraeserauswahl);
    } // setupUi

    void retranslateUi(QDialog *Dialog_fraeserauswahl)
    {
        Dialog_fraeserauswahl->setWindowTitle(QApplication::translate("Dialog_fraeserauswahl", "Dialog", nullptr));
        pushButton_ok->setText(QApplication::translate("Dialog_fraeserauswahl", "OK", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("Dialog_fraeserauswahl", "Abbrechen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_fraeserauswahl: public Ui_Dialog_fraeserauswahl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_FRAESERAUSWAHL_H
