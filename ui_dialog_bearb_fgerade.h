/********************************************************************************
** Form generated from reading UI file 'dialog_bearb_fgerade.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_BEARB_FGERADE_H
#define UI_DIALOG_BEARB_FGERADE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_bearb_fgerade
{
public:
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_ok;
    QPushButton *btn_abbrechen;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_afb;
    QLineEdit *lineEdit_ys;
    QLineEdit *lineEdit_xe;
    QLineEdit *lineEdit_zs;
    QLineEdit *lineEdit_xs;
    QLabel *label_6;
    QLineEdit *lineEdit_ye;
    QLabel *label_11;
    QLabel *label_3;
    QLineEdit *lineEdit_ze;
    QLabel *label_5;
    QComboBox *comboBox_bezug;
    QLabel *label_10;
    QLabel *label_4;
    QLabel *label_12;
    QLabel *label;

    void setupUi(QDialog *Dialog_bearb_fgerade)
    {
        if (Dialog_bearb_fgerade->objectName().isEmpty())
            Dialog_bearb_fgerade->setObjectName(QStringLiteral("Dialog_bearb_fgerade"));
        Dialog_bearb_fgerade->resize(493, 580);
        layoutWidget_2 = new QWidget(Dialog_bearb_fgerade);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(130, 540, 231, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btn_ok = new QPushButton(layoutWidget_2);
        btn_ok->setObjectName(QStringLiteral("btn_ok"));

        horizontalLayout->addWidget(btn_ok);

        btn_abbrechen = new QPushButton(layoutWidget_2);
        btn_abbrechen->setObjectName(QStringLiteral("btn_abbrechen"));

        horizontalLayout->addWidget(btn_abbrechen);

        layoutWidget = new QWidget(Dialog_bearb_fgerade);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 471, 491));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_afb = new QLineEdit(layoutWidget);
        lineEdit_afb->setObjectName(QStringLiteral("lineEdit_afb"));

        gridLayout->addWidget(lineEdit_afb, 8, 1, 1, 1);

        lineEdit_ys = new QLineEdit(layoutWidget);
        lineEdit_ys->setObjectName(QStringLiteral("lineEdit_ys"));
        lineEdit_ys->setEnabled(true);

        gridLayout->addWidget(lineEdit_ys, 2, 1, 1, 1);

        lineEdit_xe = new QLineEdit(layoutWidget);
        lineEdit_xe->setObjectName(QStringLiteral("lineEdit_xe"));
        lineEdit_xe->setEnabled(true);

        gridLayout->addWidget(lineEdit_xe, 4, 1, 1, 1);

        lineEdit_zs = new QLineEdit(layoutWidget);
        lineEdit_zs->setObjectName(QStringLiteral("lineEdit_zs"));
        lineEdit_zs->setEnabled(true);

        gridLayout->addWidget(lineEdit_zs, 3, 1, 1, 1);

        lineEdit_xs = new QLineEdit(layoutWidget);
        lineEdit_xs->setObjectName(QStringLiteral("lineEdit_xs"));
        lineEdit_xs->setEnabled(true);

        gridLayout->addWidget(lineEdit_xs, 1, 1, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        lineEdit_ye = new QLineEdit(layoutWidget);
        lineEdit_ye->setObjectName(QStringLiteral("lineEdit_ye"));
        lineEdit_ye->setEnabled(true);

        gridLayout->addWidget(lineEdit_ye, 5, 1, 1, 1);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 7, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        lineEdit_ze = new QLineEdit(layoutWidget);
        lineEdit_ze->setObjectName(QStringLiteral("lineEdit_ze"));
        lineEdit_ze->setEnabled(true);

        gridLayout->addWidget(lineEdit_ze, 6, 1, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        comboBox_bezug = new QComboBox(layoutWidget);
        comboBox_bezug->setObjectName(QStringLiteral("comboBox_bezug"));
        comboBox_bezug->setEnabled(false);

        gridLayout->addWidget(comboBox_bezug, 7, 1, 1, 1);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 5, 0, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 8, 0, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 6, 0, 1, 1);

        QWidget::setTabOrder(lineEdit_xs, lineEdit_ys);
        QWidget::setTabOrder(lineEdit_ys, lineEdit_zs);
        QWidget::setTabOrder(lineEdit_zs, lineEdit_xe);
        QWidget::setTabOrder(lineEdit_xe, lineEdit_ye);
        QWidget::setTabOrder(lineEdit_ye, lineEdit_ze);
        QWidget::setTabOrder(lineEdit_ze, comboBox_bezug);
        QWidget::setTabOrder(comboBox_bezug, lineEdit_afb);
        QWidget::setTabOrder(lineEdit_afb, btn_ok);
        QWidget::setTabOrder(btn_ok, btn_abbrechen);

        retranslateUi(Dialog_bearb_fgerade);

        QMetaObject::connectSlotsByName(Dialog_bearb_fgerade);
    } // setupUi

    void retranslateUi(QDialog *Dialog_bearb_fgerade)
    {
        Dialog_bearb_fgerade->setWindowTitle(QApplication::translate("Dialog_bearb_fgerade", "Dialog", nullptr));
        btn_ok->setText(QApplication::translate("Dialog_bearb_fgerade", "OK", nullptr));
        btn_abbrechen->setText(QApplication::translate("Dialog_bearb_fgerade", "Abbrechen", nullptr));
        label_6->setText(QApplication::translate("Dialog_bearb_fgerade", "Start Z", nullptr));
        label_11->setText(QApplication::translate("Dialog_bearb_fgerade", "Bezug", nullptr));
        label_3->setText(QApplication::translate("Dialog_bearb_fgerade", "Ende X", nullptr));
        label_5->setText(QApplication::translate("Dialog_bearb_fgerade", "Start Y", nullptr));
        label_10->setText(QApplication::translate("Dialog_bearb_fgerade", "Ende Y", nullptr));
        label_4->setText(QApplication::translate("Dialog_bearb_fgerade", "Start X", nullptr));
        label_12->setText(QApplication::translate("Dialog_bearb_fgerade", "Ausf\303\274hrbedingung", nullptr));
        label->setText(QApplication::translate("Dialog_bearb_fgerade", "Ende Z", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_bearb_fgerade: public Ui_Dialog_bearb_fgerade {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_BEARB_FGERADE_H
