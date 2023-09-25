/********************************************************************************
** Form generated from reading UI file 'dialog_stdname.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_STDNAME_H
#define UI_DIALOG_STDNAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_stdname
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_vor;
    QLineEdit *lineEdit_vor;
    QLabel *label_nach;
    QLineEdit *lineEdit_nach;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_abbrechen;

    void setupUi(QDialog *Dialog_stdname)
    {
        if (Dialog_stdname->objectName().isEmpty())
            Dialog_stdname->setObjectName(QStringLiteral("Dialog_stdname"));
        Dialog_stdname->resize(400, 204);
        Dialog_stdname->setModal(true);
        widget = new QWidget(Dialog_stdname);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 5, 381, 121));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_vor = new QLabel(widget);
        label_vor->setObjectName(QStringLiteral("label_vor"));

        gridLayout->addWidget(label_vor, 0, 0, 1, 1);

        lineEdit_vor = new QLineEdit(widget);
        lineEdit_vor->setObjectName(QStringLiteral("lineEdit_vor"));

        gridLayout->addWidget(lineEdit_vor, 0, 1, 1, 1);

        label_nach = new QLabel(widget);
        label_nach->setObjectName(QStringLiteral("label_nach"));

        gridLayout->addWidget(label_nach, 1, 0, 1, 1);

        lineEdit_nach = new QLineEdit(widget);
        lineEdit_nach->setObjectName(QStringLiteral("lineEdit_nach"));

        gridLayout->addWidget(lineEdit_nach, 1, 1, 1, 1);

        widget1 = new QWidget(Dialog_stdname);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(17, 140, 371, 51));
        horizontalLayout = new QHBoxLayout(widget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_ok = new QPushButton(widget1);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        horizontalLayout->addWidget(pushButton_ok);

        pushButton_abbrechen = new QPushButton(widget1);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));

        horizontalLayout->addWidget(pushButton_abbrechen);


        retranslateUi(Dialog_stdname);

        QMetaObject::connectSlotsByName(Dialog_stdname);
    } // setupUi

    void retranslateUi(QDialog *Dialog_stdname)
    {
        Dialog_stdname->setWindowTitle(QApplication::translate("Dialog_stdname", "Namenspaar editieren", nullptr));
        label_vor->setText(QApplication::translate("Dialog_stdname", "Name Quelldatei", nullptr));
        label_nach->setText(QApplication::translate("Dialog_stdname", "NAme Zieldatei", nullptr));
        pushButton_ok->setText(QApplication::translate("Dialog_stdname", "OK", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("Dialog_stdname", "Abbrechen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_stdname: public Ui_Dialog_stdname {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_STDNAME_H
