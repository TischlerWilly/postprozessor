/********************************************************************************
** Form generated from reading UI file 'dialog_bearb_pkopf.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_BEARB_PKOPF_H
#define UI_DIALOG_BEARB_PKOPF_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_bearb_pkopf
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit_kre;
    QLabel *label;
    QCheckBox *checkBox_use_ax;
    QLineEdit *lineEdit_b;
    QLabel *label_7;
    QLabel *label_5;
    QLineEdit *lineEdit_d;
    QLabel *label_6;
    QLineEdit *lineEdit_khi;
    QLineEdit *lineEdit_kli;
    QLineEdit *lineEdit_kvo;
    QLineEdit *lineEdit_l;
    QLabel *label_2;
    QCheckBox *checkBox_use_ay;
    QLabel *label_8;
    QLabel *label_9;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_abbrechen;

    void setupUi(QDialog *Dialog_bearb_pkopf)
    {
        if (Dialog_bearb_pkopf->objectName().isEmpty())
            Dialog_bearb_pkopf->setObjectName(QStringLiteral("Dialog_bearb_pkopf"));
        Dialog_bearb_pkopf->resize(443, 510);
        layoutWidget = new QWidget(Dialog_bearb_pkopf);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 421, 441));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        lineEdit_kre = new QLineEdit(layoutWidget);
        lineEdit_kre->setObjectName(QStringLiteral("lineEdit_kre"));

        gridLayout->addWidget(lineEdit_kre, 6, 1, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        checkBox_use_ax = new QCheckBox(layoutWidget);
        checkBox_use_ax->setObjectName(QStringLiteral("checkBox_use_ax"));

        gridLayout->addWidget(checkBox_use_ax, 7, 1, 1, 1);

        lineEdit_b = new QLineEdit(layoutWidget);
        lineEdit_b->setObjectName(QStringLiteral("lineEdit_b"));

        gridLayout->addWidget(lineEdit_b, 1, 1, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 6, 0, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        lineEdit_d = new QLineEdit(layoutWidget);
        lineEdit_d->setObjectName(QStringLiteral("lineEdit_d"));

        gridLayout->addWidget(lineEdit_d, 2, 1, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        lineEdit_khi = new QLineEdit(layoutWidget);
        lineEdit_khi->setObjectName(QStringLiteral("lineEdit_khi"));

        gridLayout->addWidget(lineEdit_khi, 4, 1, 1, 1);

        lineEdit_kli = new QLineEdit(layoutWidget);
        lineEdit_kli->setObjectName(QStringLiteral("lineEdit_kli"));

        gridLayout->addWidget(lineEdit_kli, 5, 1, 1, 1);

        lineEdit_kvo = new QLineEdit(layoutWidget);
        lineEdit_kvo->setObjectName(QStringLiteral("lineEdit_kvo"));

        gridLayout->addWidget(lineEdit_kvo, 3, 1, 1, 1);

        lineEdit_l = new QLineEdit(layoutWidget);
        lineEdit_l->setObjectName(QStringLiteral("lineEdit_l"));

        gridLayout->addWidget(lineEdit_l, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        checkBox_use_ay = new QCheckBox(layoutWidget);
        checkBox_use_ay->setObjectName(QStringLiteral("checkBox_use_ay"));

        gridLayout->addWidget(checkBox_use_ay, 8, 1, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 7, 0, 1, 1);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 8, 0, 1, 1);

        layoutWidget1 = new QWidget(Dialog_bearb_pkopf);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(90, 470, 261, 26));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_ok = new QPushButton(layoutWidget1);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        horizontalLayout->addWidget(pushButton_ok);

        pushButton_abbrechen = new QPushButton(layoutWidget1);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));

        horizontalLayout->addWidget(pushButton_abbrechen);

        QWidget::setTabOrder(lineEdit_l, lineEdit_b);
        QWidget::setTabOrder(lineEdit_b, lineEdit_d);
        QWidget::setTabOrder(lineEdit_d, lineEdit_kvo);
        QWidget::setTabOrder(lineEdit_kvo, lineEdit_khi);
        QWidget::setTabOrder(lineEdit_khi, lineEdit_kli);
        QWidget::setTabOrder(lineEdit_kli, lineEdit_kre);
        QWidget::setTabOrder(lineEdit_kre, pushButton_ok);
        QWidget::setTabOrder(pushButton_ok, pushButton_abbrechen);

        retranslateUi(Dialog_bearb_pkopf);

        QMetaObject::connectSlotsByName(Dialog_bearb_pkopf);
    } // setupUi

    void retranslateUi(QDialog *Dialog_bearb_pkopf)
    {
        Dialog_bearb_pkopf->setWindowTitle(QApplication::translate("Dialog_bearb_pkopf", "Dialog", nullptr));
        label_3->setText(QApplication::translate("Dialog_bearb_pkopf", "Dicke", nullptr));
        label_4->setText(QApplication::translate("Dialog_bearb_pkopf", "Kante vo", nullptr));
        label->setText(QApplication::translate("Dialog_bearb_pkopf", "L\303\244nge", nullptr));
        checkBox_use_ax->setText(QApplication::translate("Dialog_bearb_pkopf", "X-Versatz autoatisch ermitteln", nullptr));
        label_7->setText(QApplication::translate("Dialog_bearb_pkopf", "Kante re", nullptr));
        label_5->setText(QApplication::translate("Dialog_bearb_pkopf", "Kante hi", nullptr));
        label_6->setText(QApplication::translate("Dialog_bearb_pkopf", "Kante li", nullptr));
        label_2->setText(QApplication::translate("Dialog_bearb_pkopf", "Breite", nullptr));
        checkBox_use_ay->setText(QApplication::translate("Dialog_bearb_pkopf", "Y-Versatz automatisch ermitteln", nullptr));
        label_8->setText(QApplication::translate("Dialog_bearb_pkopf", "AX", nullptr));
        label_9->setText(QApplication::translate("Dialog_bearb_pkopf", "AY", nullptr));
        pushButton_ok->setText(QApplication::translate("Dialog_bearb_pkopf", "OK", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("Dialog_bearb_pkopf", "Abbrechen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_bearb_pkopf: public Ui_Dialog_bearb_pkopf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_BEARB_PKOPF_H
