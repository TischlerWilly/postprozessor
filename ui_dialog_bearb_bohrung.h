/********************************************************************************
** Form generated from reading UI file 'dialog_bearb_bohrung.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_BEARB_BOHRUNG_H
#define UI_DIALOG_BEARB_BOHRUNG_H

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

class Ui_Dialog_bearb_bohrung
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_ok;
    QPushButton *btn_abbrechen;
    QWidget *layoutWidget_2;
    QGridLayout *gridLayout;
    QLabel *label_11;
    QLabel *label_5;
    QLabel *label_9;
    QLabel *label_3;
    QLabel *label_13;
    QLineEdit *lineEdit_wkz;
    QLabel *label_12;
    QLabel *label;
    QLabel *label_6;
    QLabel *label_4;
    QPushButton *pushButton_wkzwahl;
    QLineEdit *lineEdit_afb;
    QComboBox *comboBox_bezug;
    QLineEdit *lineEdit_zust;
    QLineEdit *lineEdit_z;
    QLineEdit *lineEdit_y;
    QLineEdit *lineEdit_x;
    QLineEdit *lineEdit_ti;
    QLineEdit *lineEdit_dm;
    QPushButton *pushButton_invert;

    void setupUi(QDialog *Dialog_bearb_bohrung)
    {
        if (Dialog_bearb_bohrung->objectName().isEmpty())
            Dialog_bearb_bohrung->setObjectName(QStringLiteral("Dialog_bearb_bohrung"));
        Dialog_bearb_bohrung->resize(491, 584);
        layoutWidget = new QWidget(Dialog_bearb_bohrung);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(180, 540, 301, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btn_ok = new QPushButton(layoutWidget);
        btn_ok->setObjectName(QStringLiteral("btn_ok"));

        horizontalLayout->addWidget(btn_ok);

        btn_abbrechen = new QPushButton(layoutWidget);
        btn_abbrechen->setObjectName(QStringLiteral("btn_abbrechen"));

        horizontalLayout->addWidget(btn_abbrechen);

        layoutWidget_2 = new QWidget(Dialog_bearb_bohrung);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 10, 471, 491));
        gridLayout = new QGridLayout(layoutWidget_2);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(layoutWidget_2);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 6, 0, 1, 1);

        label_5 = new QLabel(layoutWidget_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        label_9 = new QLabel(layoutWidget_2);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 5, 0, 1, 1);

        label_3 = new QLabel(layoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        label_13 = new QLabel(layoutWidget_2);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 8, 0, 1, 1);

        lineEdit_wkz = new QLineEdit(layoutWidget_2);
        lineEdit_wkz->setObjectName(QStringLiteral("lineEdit_wkz"));

        gridLayout->addWidget(lineEdit_wkz, 8, 1, 1, 1);

        label_12 = new QLabel(layoutWidget_2);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 7, 0, 1, 1);

        label = new QLabel(layoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_6 = new QLabel(layoutWidget_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 4, 0, 1, 1);

        label_4 = new QLabel(layoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        pushButton_wkzwahl = new QPushButton(layoutWidget_2);
        pushButton_wkzwahl->setObjectName(QStringLiteral("pushButton_wkzwahl"));

        gridLayout->addWidget(pushButton_wkzwahl, 8, 2, 1, 1);

        lineEdit_afb = new QLineEdit(layoutWidget_2);
        lineEdit_afb->setObjectName(QStringLiteral("lineEdit_afb"));

        gridLayout->addWidget(lineEdit_afb, 7, 1, 1, 2);

        comboBox_bezug = new QComboBox(layoutWidget_2);
        comboBox_bezug->setObjectName(QStringLiteral("comboBox_bezug"));

        gridLayout->addWidget(comboBox_bezug, 6, 1, 1, 2);

        lineEdit_zust = new QLineEdit(layoutWidget_2);
        lineEdit_zust->setObjectName(QStringLiteral("lineEdit_zust"));

        gridLayout->addWidget(lineEdit_zust, 5, 1, 1, 2);

        lineEdit_z = new QLineEdit(layoutWidget_2);
        lineEdit_z->setObjectName(QStringLiteral("lineEdit_z"));

        gridLayout->addWidget(lineEdit_z, 4, 1, 1, 2);

        lineEdit_y = new QLineEdit(layoutWidget_2);
        lineEdit_y->setObjectName(QStringLiteral("lineEdit_y"));

        gridLayout->addWidget(lineEdit_y, 3, 1, 1, 2);

        lineEdit_x = new QLineEdit(layoutWidget_2);
        lineEdit_x->setObjectName(QStringLiteral("lineEdit_x"));

        gridLayout->addWidget(lineEdit_x, 2, 1, 1, 2);

        lineEdit_ti = new QLineEdit(layoutWidget_2);
        lineEdit_ti->setObjectName(QStringLiteral("lineEdit_ti"));

        gridLayout->addWidget(lineEdit_ti, 1, 1, 1, 2);

        lineEdit_dm = new QLineEdit(layoutWidget_2);
        lineEdit_dm->setObjectName(QStringLiteral("lineEdit_dm"));

        gridLayout->addWidget(lineEdit_dm, 0, 1, 1, 2);

        pushButton_invert = new QPushButton(Dialog_bearb_bohrung);
        pushButton_invert->setObjectName(QStringLiteral("pushButton_invert"));
        pushButton_invert->setGeometry(QRect(10, 510, 91, 61));
        QWidget::setTabOrder(lineEdit_dm, lineEdit_ti);
        QWidget::setTabOrder(lineEdit_ti, lineEdit_x);
        QWidget::setTabOrder(lineEdit_x, lineEdit_y);
        QWidget::setTabOrder(lineEdit_y, lineEdit_z);
        QWidget::setTabOrder(lineEdit_z, lineEdit_zust);
        QWidget::setTabOrder(lineEdit_zust, comboBox_bezug);
        QWidget::setTabOrder(comboBox_bezug, lineEdit_afb);
        QWidget::setTabOrder(lineEdit_afb, lineEdit_wkz);
        QWidget::setTabOrder(lineEdit_wkz, btn_ok);
        QWidget::setTabOrder(btn_ok, btn_abbrechen);

        retranslateUi(Dialog_bearb_bohrung);

        QMetaObject::connectSlotsByName(Dialog_bearb_bohrung);
    } // setupUi

    void retranslateUi(QDialog *Dialog_bearb_bohrung)
    {
        Dialog_bearb_bohrung->setWindowTitle(QApplication::translate("Dialog_bearb_bohrung", "Dialog", nullptr));
        btn_ok->setText(QApplication::translate("Dialog_bearb_bohrung", "OK", nullptr));
        btn_abbrechen->setText(QApplication::translate("Dialog_bearb_bohrung", "Abbrechen", nullptr));
        label_11->setText(QApplication::translate("Dialog_bearb_bohrung", "Bezug", nullptr));
        label_5->setText(QApplication::translate("Dialog_bearb_bohrung", "Pos Y", nullptr));
        label_9->setText(QApplication::translate("Dialog_bearb_bohrung", "Zustellma\303\237", nullptr));
        label_3->setText(QApplication::translate("Dialog_bearb_bohrung", "Tiefe", nullptr));
        label_13->setText(QApplication::translate("Dialog_bearb_bohrung", "Werkzeugnummer", nullptr));
        label_12->setText(QApplication::translate("Dialog_bearb_bohrung", "Ausf\303\274hrbedingung", nullptr));
        label->setText(QApplication::translate("Dialog_bearb_bohrung", "Durchmesser", nullptr));
        label_6->setText(QApplication::translate("Dialog_bearb_bohrung", "Pos Z", nullptr));
        label_4->setText(QApplication::translate("Dialog_bearb_bohrung", "Pos X", nullptr));
        pushButton_wkzwahl->setText(QApplication::translate("Dialog_bearb_bohrung", "...", nullptr));
        pushButton_invert->setText(QApplication::translate("Dialog_bearb_bohrung", "HBE invertieren", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_bearb_bohrung: public Ui_Dialog_bearb_bohrung {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_BEARB_BOHRUNG_H
