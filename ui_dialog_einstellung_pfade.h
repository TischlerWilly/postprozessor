/********************************************************************************
** Form generated from reading UI file 'dialog_einstellung_pfade.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_EINSTELLUNG_PFADE_H
#define UI_DIALOG_EINSTELLUNG_PFADE_H

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

class Ui_Dialog_Einstellung_pfade
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_root_ganx;
    QLabel *label_2;
    QLabel *label_5;
    QLineEdit *lineEdit_ziel_server;
    QPushButton *pushButton_root_ganx;
    QLabel *label;
    QPushButton *pushButton_root_fmc;
    QLineEdit *lineEdit_quelle;
    QPushButton *pushButton_ziel_server;
    QLabel *label_4;
    QLineEdit *lineEdit_ziel_lokal;
    QLabel *label_3;
    QPushButton *pushButton_ziel_lokal;
    QLineEdit *lineEdit_root_fmc;
    QPushButton *pushButton_quelle;
    QLabel *label_6;
    QLineEdit *lineEdit_root_cix;
    QPushButton *pushButton_root_cix;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_abbrechen;

    void setupUi(QDialog *Dialog_Einstellung_pfade)
    {
        if (Dialog_Einstellung_pfade->objectName().isEmpty())
            Dialog_Einstellung_pfade->setObjectName(QStringLiteral("Dialog_Einstellung_pfade"));
        Dialog_Einstellung_pfade->resize(823, 246);
        Dialog_Einstellung_pfade->setModal(true);
        layoutWidget = new QWidget(Dialog_Einstellung_pfade);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 791, 181));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_root_ganx = new QLineEdit(layoutWidget);
        lineEdit_root_ganx->setObjectName(QStringLiteral("lineEdit_root_ganx"));

        gridLayout->addWidget(lineEdit_root_ganx, 3, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        lineEdit_ziel_server = new QLineEdit(layoutWidget);
        lineEdit_ziel_server->setObjectName(QStringLiteral("lineEdit_ziel_server"));

        gridLayout->addWidget(lineEdit_ziel_server, 1, 1, 1, 1);

        pushButton_root_ganx = new QPushButton(layoutWidget);
        pushButton_root_ganx->setObjectName(QStringLiteral("pushButton_root_ganx"));

        gridLayout->addWidget(pushButton_root_ganx, 3, 2, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        pushButton_root_fmc = new QPushButton(layoutWidget);
        pushButton_root_fmc->setObjectName(QStringLiteral("pushButton_root_fmc"));

        gridLayout->addWidget(pushButton_root_fmc, 4, 2, 1, 1);

        lineEdit_quelle = new QLineEdit(layoutWidget);
        lineEdit_quelle->setObjectName(QStringLiteral("lineEdit_quelle"));

        gridLayout->addWidget(lineEdit_quelle, 0, 1, 1, 1);

        pushButton_ziel_server = new QPushButton(layoutWidget);
        pushButton_ziel_server->setObjectName(QStringLiteral("pushButton_ziel_server"));

        gridLayout->addWidget(pushButton_ziel_server, 1, 2, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        lineEdit_ziel_lokal = new QLineEdit(layoutWidget);
        lineEdit_ziel_lokal->setObjectName(QStringLiteral("lineEdit_ziel_lokal"));

        gridLayout->addWidget(lineEdit_ziel_lokal, 2, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        pushButton_ziel_lokal = new QPushButton(layoutWidget);
        pushButton_ziel_lokal->setObjectName(QStringLiteral("pushButton_ziel_lokal"));

        gridLayout->addWidget(pushButton_ziel_lokal, 2, 2, 1, 1);

        lineEdit_root_fmc = new QLineEdit(layoutWidget);
        lineEdit_root_fmc->setObjectName(QStringLiteral("lineEdit_root_fmc"));

        gridLayout->addWidget(lineEdit_root_fmc, 4, 1, 1, 1);

        pushButton_quelle = new QPushButton(layoutWidget);
        pushButton_quelle->setObjectName(QStringLiteral("pushButton_quelle"));

        gridLayout->addWidget(pushButton_quelle, 0, 2, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        lineEdit_root_cix = new QLineEdit(layoutWidget);
        lineEdit_root_cix->setObjectName(QStringLiteral("lineEdit_root_cix"));

        gridLayout->addWidget(lineEdit_root_cix, 5, 1, 1, 1);

        pushButton_root_cix = new QPushButton(layoutWidget);
        pushButton_root_cix->setObjectName(QStringLiteral("pushButton_root_cix"));

        gridLayout->addWidget(pushButton_root_cix, 5, 2, 1, 1);

        layoutWidget1 = new QWidget(Dialog_Einstellung_pfade);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(260, 210, 261, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_ok = new QPushButton(layoutWidget1);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        horizontalLayout->addWidget(pushButton_ok);

        pushButton_abbrechen = new QPushButton(layoutWidget1);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));

        horizontalLayout->addWidget(pushButton_abbrechen);

        QWidget::setTabOrder(lineEdit_quelle, lineEdit_ziel_server);
        QWidget::setTabOrder(lineEdit_ziel_server, lineEdit_ziel_lokal);
        QWidget::setTabOrder(lineEdit_ziel_lokal, lineEdit_root_ganx);
        QWidget::setTabOrder(lineEdit_root_ganx, lineEdit_root_fmc);
        QWidget::setTabOrder(lineEdit_root_fmc, pushButton_ok);
        QWidget::setTabOrder(pushButton_ok, pushButton_abbrechen);
        QWidget::setTabOrder(pushButton_abbrechen, pushButton_quelle);
        QWidget::setTabOrder(pushButton_quelle, pushButton_ziel_server);
        QWidget::setTabOrder(pushButton_ziel_server, pushButton_ziel_lokal);
        QWidget::setTabOrder(pushButton_ziel_lokal, pushButton_root_ganx);
        QWidget::setTabOrder(pushButton_root_ganx, pushButton_root_fmc);

        retranslateUi(Dialog_Einstellung_pfade);

        QMetaObject::connectSlotsByName(Dialog_Einstellung_pfade);
    } // setupUi

    void retranslateUi(QDialog *Dialog_Einstellung_pfade)
    {
        Dialog_Einstellung_pfade->setWindowTitle(QApplication::translate("Dialog_Einstellung_pfade", "Einstellung Pfade", nullptr));
        label_2->setText(QApplication::translate("Dialog_Einstellung_pfade", "Zielverzeichnis Server", nullptr));
        label_5->setText(QApplication::translate("Dialog_Einstellung_pfade", "Wurzelverzeichniss fmc", nullptr));
        pushButton_root_ganx->setText(QApplication::translate("Dialog_Einstellung_pfade", "...", nullptr));
        label->setText(QApplication::translate("Dialog_Einstellung_pfade", "Quellverzeichnis", nullptr));
        pushButton_root_fmc->setText(QApplication::translate("Dialog_Einstellung_pfade", "...", nullptr));
        pushButton_ziel_server->setText(QApplication::translate("Dialog_Einstellung_pfade", "...", nullptr));
        label_4->setText(QApplication::translate("Dialog_Einstellung_pfade", "Wurzelverzeichnis ganx", nullptr));
        label_3->setText(QApplication::translate("Dialog_Einstellung_pfade", "Zielverzeichnis lokal", nullptr));
        pushButton_ziel_lokal->setText(QApplication::translate("Dialog_Einstellung_pfade", "...", nullptr));
        pushButton_quelle->setText(QApplication::translate("Dialog_Einstellung_pfade", "...", nullptr));
        label_6->setText(QApplication::translate("Dialog_Einstellung_pfade", "Wurzelverzeichniss cix", nullptr));
        pushButton_root_cix->setText(QApplication::translate("Dialog_Einstellung_pfade", "...", nullptr));
        pushButton_ok->setText(QApplication::translate("Dialog_Einstellung_pfade", "OK", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("Dialog_Einstellung_pfade", "Abbrechen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_Einstellung_pfade: public Ui_Dialog_Einstellung_pfade {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_EINSTELLUNG_PFADE_H
