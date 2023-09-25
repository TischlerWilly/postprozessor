/********************************************************************************
** Form generated from reading UI file 'dialog_saege.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_SAEGE_H
#define UI_DIALOG_SAEGE_H

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

class Ui_Dialog_saege
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_zustm;
    QLineEdit *lineEdit_nr;
    QLabel *label_zustm;
    QLineEdit *lineEdit_breite;
    QLineEdit *lineEdit_dm;
    QLabel *label_breite;
    QLabel *label_nr;
    QCheckBox *checkBox_ist_aktiv;
    QCheckBox *checkBox_hori;
    QLabel *label_dm;
    QCheckBox *checkBox_vert;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_abbrechen;
    QPushButton *pushButton_ok;

    void setupUi(QDialog *Dialog_saege)
    {
        if (Dialog_saege->objectName().isEmpty())
            Dialog_saege->setObjectName(QStringLiteral("Dialog_saege"));
        Dialog_saege->resize(400, 302);
        Dialog_saege->setModal(true);
        layoutWidget = new QWidget(Dialog_saege);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 371, 251));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_zustm = new QLineEdit(layoutWidget);
        lineEdit_zustm->setObjectName(QStringLiteral("lineEdit_zustm"));

        gridLayout->addWidget(lineEdit_zustm, 2, 1, 1, 1);

        lineEdit_nr = new QLineEdit(layoutWidget);
        lineEdit_nr->setObjectName(QStringLiteral("lineEdit_nr"));

        gridLayout->addWidget(lineEdit_nr, 0, 1, 1, 1);

        label_zustm = new QLabel(layoutWidget);
        label_zustm->setObjectName(QStringLiteral("label_zustm"));

        gridLayout->addWidget(label_zustm, 2, 0, 1, 1);

        lineEdit_breite = new QLineEdit(layoutWidget);
        lineEdit_breite->setObjectName(QStringLiteral("lineEdit_breite"));

        gridLayout->addWidget(lineEdit_breite, 3, 1, 1, 1);

        lineEdit_dm = new QLineEdit(layoutWidget);
        lineEdit_dm->setObjectName(QStringLiteral("lineEdit_dm"));

        gridLayout->addWidget(lineEdit_dm, 1, 1, 1, 1);

        label_breite = new QLabel(layoutWidget);
        label_breite->setObjectName(QStringLiteral("label_breite"));

        gridLayout->addWidget(label_breite, 3, 0, 1, 1);

        label_nr = new QLabel(layoutWidget);
        label_nr->setObjectName(QStringLiteral("label_nr"));

        gridLayout->addWidget(label_nr, 0, 0, 1, 1);

        checkBox_ist_aktiv = new QCheckBox(layoutWidget);
        checkBox_ist_aktiv->setObjectName(QStringLiteral("checkBox_ist_aktiv"));

        gridLayout->addWidget(checkBox_ist_aktiv, 7, 1, 1, 1);

        checkBox_hori = new QCheckBox(layoutWidget);
        checkBox_hori->setObjectName(QStringLiteral("checkBox_hori"));

        gridLayout->addWidget(checkBox_hori, 5, 1, 1, 1);

        label_dm = new QLabel(layoutWidget);
        label_dm->setObjectName(QStringLiteral("label_dm"));

        gridLayout->addWidget(label_dm, 1, 0, 1, 1);

        checkBox_vert = new QCheckBox(layoutWidget);
        checkBox_vert->setObjectName(QStringLiteral("checkBox_vert"));

        gridLayout->addWidget(checkBox_vert, 4, 1, 1, 1);

        layoutWidget1 = new QWidget(Dialog_saege);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(167, 270, 221, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_abbrechen = new QPushButton(layoutWidget1);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));

        horizontalLayout->addWidget(pushButton_abbrechen);

        pushButton_ok = new QPushButton(layoutWidget1);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        horizontalLayout->addWidget(pushButton_ok);

        QWidget::setTabOrder(lineEdit_nr, lineEdit_dm);
        QWidget::setTabOrder(lineEdit_dm, lineEdit_zustm);
        QWidget::setTabOrder(lineEdit_zustm, lineEdit_breite);
        QWidget::setTabOrder(lineEdit_breite, checkBox_vert);
        QWidget::setTabOrder(checkBox_vert, checkBox_hori);
        QWidget::setTabOrder(checkBox_hori, checkBox_ist_aktiv);
        QWidget::setTabOrder(checkBox_ist_aktiv, pushButton_ok);
        QWidget::setTabOrder(pushButton_ok, pushButton_abbrechen);

        retranslateUi(Dialog_saege);

        QMetaObject::connectSlotsByName(Dialog_saege);
    } // setupUi

    void retranslateUi(QDialog *Dialog_saege)
    {
        Dialog_saege->setWindowTitle(QApplication::translate("Dialog_saege", "Saege", nullptr));
        label_zustm->setText(QApplication::translate("Dialog_saege", "<html><head/><body><p>Zustellma\303\237</p></body></html>", nullptr));
        label_breite->setText(QApplication::translate("Dialog_saege", "Schnittbreite", nullptr));
        label_nr->setText(QApplication::translate("Dialog_saege", "Werkzeugnummer", nullptr));
        checkBox_ist_aktiv->setText(QApplication::translate("Dialog_saege", "ist aktiv", nullptr));
        checkBox_hori->setText(QApplication::translate("Dialog_saege", "Horizontal", nullptr));
        label_dm->setText(QApplication::translate("Dialog_saege", "Durchmesser", nullptr));
        checkBox_vert->setText(QApplication::translate("Dialog_saege", "Vertikal", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("Dialog_saege", "Abbrechen", nullptr));
        pushButton_ok->setText(QApplication::translate("Dialog_saege", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_saege: public Ui_Dialog_saege {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_SAEGE_H
