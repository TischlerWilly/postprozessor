/********************************************************************************
** Form generated from reading UI file 'dialog_einstellung_fmc.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_EINSTELLUNG_FMC_H
#define UI_DIALOG_EINSTELLUNG_FMC_H

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

class Ui_Dialog_einstellung_fmc
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QComboBox *comboBox_drehdypUnterseite;
    QLineEdit *lineEdit_KennungOberseite;
    QLineEdit *lineEdit_KennungUnterseite;
    QLabel *label_2;
    QLabel *label_4;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_abbrechen;

    void setupUi(QDialog *Dialog_einstellung_fmc)
    {
        if (Dialog_einstellung_fmc->objectName().isEmpty())
            Dialog_einstellung_fmc->setObjectName(QStringLiteral("Dialog_einstellung_fmc"));
        Dialog_einstellung_fmc->resize(404, 365);
        Dialog_einstellung_fmc->setModal(true);
        layoutWidget = new QWidget(Dialog_einstellung_fmc);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 11, 381, 256));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        comboBox_drehdypUnterseite = new QComboBox(layoutWidget);
        comboBox_drehdypUnterseite->setObjectName(QStringLiteral("comboBox_drehdypUnterseite"));

        gridLayout->addWidget(comboBox_drehdypUnterseite, 2, 1, 1, 1);

        lineEdit_KennungOberseite = new QLineEdit(layoutWidget);
        lineEdit_KennungOberseite->setObjectName(QStringLiteral("lineEdit_KennungOberseite"));

        gridLayout->addWidget(lineEdit_KennungOberseite, 0, 1, 1, 1);

        lineEdit_KennungUnterseite = new QLineEdit(layoutWidget);
        lineEdit_KennungUnterseite->setObjectName(QStringLiteral("lineEdit_KennungUnterseite"));

        gridLayout->addWidget(lineEdit_KennungUnterseite, 1, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        layoutWidget_2 = new QWidget(Dialog_einstellung_fmc);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(170, 320, 221, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_ok = new QPushButton(layoutWidget_2);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        horizontalLayout->addWidget(pushButton_ok);

        pushButton_abbrechen = new QPushButton(layoutWidget_2);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));

        horizontalLayout->addWidget(pushButton_abbrechen);


        retranslateUi(Dialog_einstellung_fmc);

        QMetaObject::connectSlotsByName(Dialog_einstellung_fmc);
    } // setupUi

    void retranslateUi(QDialog *Dialog_einstellung_fmc)
    {
        Dialog_einstellung_fmc->setWindowTitle(QApplication::translate("Dialog_einstellung_fmc", "Grundeinstellungen fmc", nullptr));
        label_3->setText(QApplication::translate("Dialog_einstellung_fmc", "Kennung Datei f\303\274r Unterseite", nullptr));
        label_2->setText(QApplication::translate("Dialog_einstellung_fmc", "Kennung Datei f\303\274r Oberseite", nullptr));
        label_4->setText(QApplication::translate("Dialog_einstellung_fmc", "Unterseite ist gedreht um", nullptr));
        pushButton_ok->setText(QApplication::translate("Dialog_einstellung_fmc", "OK", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("Dialog_einstellung_fmc", "Abbrechen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_einstellung_fmc: public Ui_Dialog_einstellung_fmc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_EINSTELLUNG_FMC_H
