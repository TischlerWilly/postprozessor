/********************************************************************************
** Form generated from reading UI file 'dialog_einstellung_wkz_pp.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_EINSTELLUNG_WKZ_PP_H
#define UI_DIALOG_EINSTELLUNG_WKZ_PP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_einstellung_wkz_pp
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QCheckBox *checkBox_wkz_fr_fmc;
    QCheckBox *checkBox_wkz_fr_ganx;
    QCheckBox *checkBox_wkz_fr_cix;
    QCheckBox *checkBox_wkz_fr_ggf;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_abbrechen;

    void setupUi(QDialog *Dialog_einstellung_wkz_pp)
    {
        if (Dialog_einstellung_wkz_pp->objectName().isEmpty())
            Dialog_einstellung_wkz_pp->setObjectName(QStringLiteral("Dialog_einstellung_wkz_pp"));
        Dialog_einstellung_wkz_pp->resize(401, 192);
        Dialog_einstellung_wkz_pp->setModal(true);
        layoutWidget = new QWidget(Dialog_einstellung_wkz_pp);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 382, 107));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        checkBox_wkz_fr_fmc = new QCheckBox(layoutWidget);
        checkBox_wkz_fr_fmc->setObjectName(QStringLiteral("checkBox_wkz_fr_fmc"));

        verticalLayout->addWidget(checkBox_wkz_fr_fmc);

        checkBox_wkz_fr_ganx = new QCheckBox(layoutWidget);
        checkBox_wkz_fr_ganx->setObjectName(QStringLiteral("checkBox_wkz_fr_ganx"));

        verticalLayout->addWidget(checkBox_wkz_fr_ganx);

        checkBox_wkz_fr_cix = new QCheckBox(layoutWidget);
        checkBox_wkz_fr_cix->setObjectName(QStringLiteral("checkBox_wkz_fr_cix"));

        verticalLayout->addWidget(checkBox_wkz_fr_cix);

        checkBox_wkz_fr_ggf = new QCheckBox(layoutWidget);
        checkBox_wkz_fr_ggf->setObjectName(QStringLiteral("checkBox_wkz_fr_ggf"));

        verticalLayout->addWidget(checkBox_wkz_fr_ggf);

        layoutWidget1 = new QWidget(Dialog_einstellung_wkz_pp);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(80, 150, 191, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_ok = new QPushButton(layoutWidget1);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        horizontalLayout->addWidget(pushButton_ok);

        pushButton_abbrechen = new QPushButton(layoutWidget1);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));

        horizontalLayout->addWidget(pushButton_abbrechen);


        retranslateUi(Dialog_einstellung_wkz_pp);

        QMetaObject::connectSlotsByName(Dialog_einstellung_wkz_pp);
    } // setupUi

    void retranslateUi(QDialog *Dialog_einstellung_wkz_pp)
    {
        Dialog_einstellung_wkz_pp->setWindowTitle(QApplication::translate("Dialog_einstellung_wkz_pp", "Werkzeug Postprozessor", nullptr));
        label->setText(QApplication::translate("Dialog_einstellung_wkz_pp", "folgende Werkzeugmagazine f\303\274r die Bearbeitung von Werkst\303\274cken verwenden:", nullptr));
        checkBox_wkz_fr_fmc->setText(QApplication::translate("Dialog_einstellung_wkz_pp", "Werkzeug fmc", nullptr));
        checkBox_wkz_fr_ganx->setText(QApplication::translate("Dialog_einstellung_wkz_pp", "Werkzeug ganx", nullptr));
        checkBox_wkz_fr_cix->setText(QApplication::translate("Dialog_einstellung_wkz_pp", "Werkzeug cix", nullptr));
        checkBox_wkz_fr_ggf->setText(QApplication::translate("Dialog_einstellung_wkz_pp", "Werkzeug ggf", nullptr));
        pushButton_ok->setText(QApplication::translate("Dialog_einstellung_wkz_pp", "OK", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("Dialog_einstellung_wkz_pp", "Abbrechen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_einstellung_wkz_pp: public Ui_Dialog_einstellung_wkz_pp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_EINSTELLUNG_WKZ_PP_H
