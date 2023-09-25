/********************************************************************************
** Form generated from reading UI file 'dialog_bearb_faufruf.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_BEARB_FAUFRUF_H
#define UI_DIALOG_BEARB_FAUFRUF_H

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

class Ui_Dialog_bearb_faufruf
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_z;
    QLineEdit *lineEdit_x;
    QPushButton *pushButton_wkzwahl;
    QLabel *label_11;
    QLabel *label_13;
    QLabel *label_5;
    QLineEdit *lineEdit_afb;
    QLabel *label_12;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox_kor;
    QLabel *label_6;
    QComboBox *comboBox_bezug;
    QLabel *label_7;
    QLabel *label;
    QLineEdit *lineEdit_ti;
    QLabel *label_4;
    QLabel *label_10;
    QLineEdit *lineEdit_y;
    QLineEdit *lineEdit_wkz;
    QLabel *label_8;
    QLineEdit *lineEdit_anweg;
    QLineEdit *lineEdit_abweg;
    QComboBox *comboBox_antyp;
    QComboBox *comboBox_abtyp;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *btn_ok;
    QPushButton *btn_abbrechen;

    void setupUi(QDialog *Dialog_bearb_faufruf)
    {
        if (Dialog_bearb_faufruf->objectName().isEmpty())
            Dialog_bearb_faufruf->setObjectName(QStringLiteral("Dialog_bearb_faufruf"));
        Dialog_bearb_faufruf->resize(492, 582);
        layoutWidget = new QWidget(Dialog_bearb_faufruf);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 471, 491));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_z = new QLineEdit(layoutWidget);
        lineEdit_z->setObjectName(QStringLiteral("lineEdit_z"));
        lineEdit_z->setEnabled(true);

        gridLayout->addWidget(lineEdit_z, 3, 1, 1, 2);

        lineEdit_x = new QLineEdit(layoutWidget);
        lineEdit_x->setObjectName(QStringLiteral("lineEdit_x"));
        lineEdit_x->setEnabled(true);

        gridLayout->addWidget(lineEdit_x, 1, 1, 1, 2);

        pushButton_wkzwahl = new QPushButton(layoutWidget);
        pushButton_wkzwahl->setObjectName(QStringLiteral("pushButton_wkzwahl"));

        gridLayout->addWidget(pushButton_wkzwahl, 8, 2, 1, 1);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 6, 0, 1, 1);

        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 8, 0, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        lineEdit_afb = new QLineEdit(layoutWidget);
        lineEdit_afb->setObjectName(QStringLiteral("lineEdit_afb"));

        gridLayout->addWidget(lineEdit_afb, 7, 1, 1, 2);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 7, 0, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 10, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 4, 0, 1, 1);

        comboBox_kor = new QComboBox(layoutWidget);
        comboBox_kor->setObjectName(QStringLiteral("comboBox_kor"));

        gridLayout->addWidget(comboBox_kor, 5, 1, 1, 2);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 3, 0, 1, 1);

        comboBox_bezug = new QComboBox(layoutWidget);
        comboBox_bezug->setObjectName(QStringLiteral("comboBox_bezug"));
        comboBox_bezug->setEnabled(true);

        gridLayout->addWidget(comboBox_bezug, 6, 1, 1, 2);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 11, 0, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 9, 0, 1, 1);

        lineEdit_ti = new QLineEdit(layoutWidget);
        lineEdit_ti->setObjectName(QStringLiteral("lineEdit_ti"));

        gridLayout->addWidget(lineEdit_ti, 4, 1, 1, 2);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 5, 0, 1, 1);

        lineEdit_y = new QLineEdit(layoutWidget);
        lineEdit_y->setObjectName(QStringLiteral("lineEdit_y"));
        lineEdit_y->setEnabled(true);

        gridLayout->addWidget(lineEdit_y, 2, 1, 1, 2);

        lineEdit_wkz = new QLineEdit(layoutWidget);
        lineEdit_wkz->setObjectName(QStringLiteral("lineEdit_wkz"));

        gridLayout->addWidget(lineEdit_wkz, 8, 1, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 12, 0, 1, 1);

        lineEdit_anweg = new QLineEdit(layoutWidget);
        lineEdit_anweg->setObjectName(QStringLiteral("lineEdit_anweg"));

        gridLayout->addWidget(lineEdit_anweg, 11, 1, 1, 1);

        lineEdit_abweg = new QLineEdit(layoutWidget);
        lineEdit_abweg->setObjectName(QStringLiteral("lineEdit_abweg"));

        gridLayout->addWidget(lineEdit_abweg, 12, 1, 1, 1);

        comboBox_antyp = new QComboBox(layoutWidget);
        comboBox_antyp->setObjectName(QStringLiteral("comboBox_antyp"));

        gridLayout->addWidget(comboBox_antyp, 9, 1, 1, 2);

        comboBox_abtyp = new QComboBox(layoutWidget);
        comboBox_abtyp->setObjectName(QStringLiteral("comboBox_abtyp"));

        gridLayout->addWidget(comboBox_abtyp, 10, 1, 1, 2);

        layoutWidget_2 = new QWidget(Dialog_bearb_faufruf);
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

        QWidget::setTabOrder(lineEdit_x, lineEdit_y);
        QWidget::setTabOrder(lineEdit_y, lineEdit_z);
        QWidget::setTabOrder(lineEdit_z, lineEdit_ti);
        QWidget::setTabOrder(lineEdit_ti, comboBox_kor);
        QWidget::setTabOrder(comboBox_kor, comboBox_bezug);
        QWidget::setTabOrder(comboBox_bezug, lineEdit_afb);
        QWidget::setTabOrder(lineEdit_afb, lineEdit_wkz);
        QWidget::setTabOrder(lineEdit_wkz, comboBox_antyp);
        QWidget::setTabOrder(comboBox_antyp, comboBox_abtyp);
        QWidget::setTabOrder(comboBox_abtyp, lineEdit_anweg);
        QWidget::setTabOrder(lineEdit_anweg, lineEdit_abweg);
        QWidget::setTabOrder(lineEdit_abweg, btn_ok);
        QWidget::setTabOrder(btn_ok, btn_abbrechen);
        QWidget::setTabOrder(btn_abbrechen, pushButton_wkzwahl);

        retranslateUi(Dialog_bearb_faufruf);

        QMetaObject::connectSlotsByName(Dialog_bearb_faufruf);
    } // setupUi

    void retranslateUi(QDialog *Dialog_bearb_faufruf)
    {
        Dialog_bearb_faufruf->setWindowTitle(QApplication::translate("Dialog_bearb_faufruf", "Dialog", nullptr));
        pushButton_wkzwahl->setText(QApplication::translate("Dialog_bearb_faufruf", "...", nullptr));
        label_11->setText(QApplication::translate("Dialog_bearb_faufruf", "Bezug", nullptr));
        label_13->setText(QApplication::translate("Dialog_bearb_faufruf", "Werkzeugnummer", nullptr));
        label_5->setText(QApplication::translate("Dialog_bearb_faufruf", "Pos Y", nullptr));
        label_12->setText(QApplication::translate("Dialog_bearb_faufruf", "Ausf\303\274hrbedingung", nullptr));
        label_2->setText(QApplication::translate("Dialog_bearb_faufruf", "Abfahrtyp", nullptr));
        label_3->setText(QApplication::translate("Dialog_bearb_faufruf", "Eintauch-Tiefe", nullptr));
        label_6->setText(QApplication::translate("Dialog_bearb_faufruf", "Pos Z", nullptr));
        label_7->setText(QApplication::translate("Dialog_bearb_faufruf", "Anfahrweg", nullptr));
        label->setText(QApplication::translate("Dialog_bearb_faufruf", "Anfahrtyp", nullptr));
        label_4->setText(QApplication::translate("Dialog_bearb_faufruf", "Pos X", nullptr));
        label_10->setText(QApplication::translate("Dialog_bearb_faufruf", "Korrektur", nullptr));
        label_8->setText(QApplication::translate("Dialog_bearb_faufruf", "abfahrweg", nullptr));
        btn_ok->setText(QApplication::translate("Dialog_bearb_faufruf", "OK", nullptr));
        btn_abbrechen->setText(QApplication::translate("Dialog_bearb_faufruf", "Abbrechen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_bearb_faufruf: public Ui_Dialog_bearb_faufruf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_BEARB_FAUFRUF_H
