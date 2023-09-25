/********************************************************************************
** Form generated from reading UI file 'dialog_bearb_verschieben.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_BEARB_VERSCHIEBEN_H
#define UI_DIALOG_BEARB_VERSCHIEBEN_H

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

class Ui_Dialog_bearb_verschieben
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_abbrechen;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *lineEdit_ax;
    QLineEdit *lineEdit_ay;
    QLineEdit *lineEdit_az;

    void setupUi(QDialog *Dialog_bearb_verschieben)
    {
        if (Dialog_bearb_verschieben->objectName().isEmpty())
            Dialog_bearb_verschieben->setObjectName(QStringLiteral("Dialog_bearb_verschieben"));
        Dialog_bearb_verschieben->resize(420, 237);
        layoutWidget = new QWidget(Dialog_bearb_verschieben);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(80, 200, 271, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_ok = new QPushButton(layoutWidget);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        horizontalLayout->addWidget(pushButton_ok);

        pushButton_abbrechen = new QPushButton(layoutWidget);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));

        horizontalLayout->addWidget(pushButton_abbrechen);

        layoutWidget_2 = new QWidget(Dialog_bearb_verschieben);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 10, 401, 171));
        gridLayout = new QGridLayout(layoutWidget_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(layoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        lineEdit_ax = new QLineEdit(layoutWidget_2);
        lineEdit_ax->setObjectName(QStringLiteral("lineEdit_ax"));

        gridLayout->addWidget(lineEdit_ax, 0, 1, 1, 1);

        lineEdit_ay = new QLineEdit(layoutWidget_2);
        lineEdit_ay->setObjectName(QStringLiteral("lineEdit_ay"));

        gridLayout->addWidget(lineEdit_ay, 2, 1, 1, 1);

        lineEdit_az = new QLineEdit(layoutWidget_2);
        lineEdit_az->setObjectName(QStringLiteral("lineEdit_az"));

        gridLayout->addWidget(lineEdit_az, 3, 1, 1, 1);

        QWidget::setTabOrder(lineEdit_ax, lineEdit_ay);
        QWidget::setTabOrder(lineEdit_ay, lineEdit_az);
        QWidget::setTabOrder(lineEdit_az, pushButton_ok);
        QWidget::setTabOrder(pushButton_ok, pushButton_abbrechen);

        retranslateUi(Dialog_bearb_verschieben);

        QMetaObject::connectSlotsByName(Dialog_bearb_verschieben);
    } // setupUi

    void retranslateUi(QDialog *Dialog_bearb_verschieben)
    {
        Dialog_bearb_verschieben->setWindowTitle(QApplication::translate("Dialog_bearb_verschieben", "Dialog", nullptr));
        pushButton_ok->setText(QApplication::translate("Dialog_bearb_verschieben", "OK", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("Dialog_bearb_verschieben", "Abbrechen", nullptr));
        label->setText(QApplication::translate("Dialog_bearb_verschieben", "X-Versatz", nullptr));
        label_2->setText(QApplication::translate("Dialog_bearb_verschieben", "Y-Versatz", nullptr));
        label_3->setText(QApplication::translate("Dialog_bearb_verschieben", "Z-Versatz", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_bearb_verschieben: public Ui_Dialog_bearb_verschieben {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_BEARB_VERSCHIEBEN_H
