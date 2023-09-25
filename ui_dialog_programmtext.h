/********************************************************************************
** Form generated from reading UI file 'dialog_programmtext.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_PROGRAMMTEXT_H
#define UI_DIALOG_PROGRAMMTEXT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_programmtext
{
public:
    QListWidget *listWidget_prgtext;

    void setupUi(QDialog *Dialog_programmtext)
    {
        if (Dialog_programmtext->objectName().isEmpty())
            Dialog_programmtext->setObjectName(QStringLiteral("Dialog_programmtext"));
        Dialog_programmtext->resize(422, 651);
        listWidget_prgtext = new QListWidget(Dialog_programmtext);
        listWidget_prgtext->setObjectName(QStringLiteral("listWidget_prgtext"));
        listWidget_prgtext->setGeometry(QRect(10, 10, 401, 631));

        retranslateUi(Dialog_programmtext);

        QMetaObject::connectSlotsByName(Dialog_programmtext);
    } // setupUi

    void retranslateUi(QDialog *Dialog_programmtext)
    {
        Dialog_programmtext->setWindowTitle(QApplication::translate("Dialog_programmtext", "Programmtext", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_programmtext: public Ui_Dialog_programmtext {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_PROGRAMMTEXT_H
