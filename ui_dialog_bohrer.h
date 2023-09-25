/********************************************************************************
** Form generated from reading UI file 'dialog_bohrer.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_BOHRER_H
#define UI_DIALOG_BOHRER_H

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

class Ui_Dialog_bohrer
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QCheckBox *checkBox_hori;
    QLabel *label_nutzlaenge;
    QLineEdit *lineEdit_nutzlaenge;
    QLineEdit *lineEdit_nr;
    QLabel *label_nr;
    QCheckBox *checkBox_istdubo;
    QCheckBox *checkBox_ist_aktiv;
    QLabel *label_dm_real;
    QLineEdit *lineEdit_dm_cad;
    QLineEdit *lineEdit_dm_real;
    QLineEdit *lineEdit_zustmassvert;
    QLabel *label_dm_cad;
    QCheckBox *checkBox_verti;
    QLineEdit *lineEdit_zustmasshori;
    QLabel *label_zustmass;
    QLabel *label_zustmass_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_abbrechen;
    QPushButton *pushButton_ok;

    void setupUi(QDialog *Dialog_bohrer)
    {
        if (Dialog_bohrer->objectName().isEmpty())
            Dialog_bohrer->setObjectName(QStringLiteral("Dialog_bohrer"));
        Dialog_bohrer->resize(386, 362);
        Dialog_bohrer->setModal(true);
        layoutWidget = new QWidget(Dialog_bohrer);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 361, 311));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        checkBox_hori = new QCheckBox(layoutWidget);
        checkBox_hori->setObjectName(QStringLiteral("checkBox_hori"));

        gridLayout->addWidget(checkBox_hori, 9, 1, 1, 1);

        label_nutzlaenge = new QLabel(layoutWidget);
        label_nutzlaenge->setObjectName(QStringLiteral("label_nutzlaenge"));

        gridLayout->addWidget(label_nutzlaenge, 4, 0, 1, 1);

        lineEdit_nutzlaenge = new QLineEdit(layoutWidget);
        lineEdit_nutzlaenge->setObjectName(QStringLiteral("lineEdit_nutzlaenge"));

        gridLayout->addWidget(lineEdit_nutzlaenge, 4, 1, 1, 1);

        lineEdit_nr = new QLineEdit(layoutWidget);
        lineEdit_nr->setObjectName(QStringLiteral("lineEdit_nr"));

        gridLayout->addWidget(lineEdit_nr, 0, 1, 1, 1);

        label_nr = new QLabel(layoutWidget);
        label_nr->setObjectName(QStringLiteral("label_nr"));

        gridLayout->addWidget(label_nr, 0, 0, 1, 1);

        checkBox_istdubo = new QCheckBox(layoutWidget);
        checkBox_istdubo->setObjectName(QStringLiteral("checkBox_istdubo"));

        gridLayout->addWidget(checkBox_istdubo, 7, 1, 1, 1);

        checkBox_ist_aktiv = new QCheckBox(layoutWidget);
        checkBox_ist_aktiv->setObjectName(QStringLiteral("checkBox_ist_aktiv"));

        gridLayout->addWidget(checkBox_ist_aktiv, 11, 1, 1, 1);

        label_dm_real = new QLabel(layoutWidget);
        label_dm_real->setObjectName(QStringLiteral("label_dm_real"));

        gridLayout->addWidget(label_dm_real, 2, 0, 1, 1);

        lineEdit_dm_cad = new QLineEdit(layoutWidget);
        lineEdit_dm_cad->setObjectName(QStringLiteral("lineEdit_dm_cad"));

        gridLayout->addWidget(lineEdit_dm_cad, 1, 1, 1, 1);

        lineEdit_dm_real = new QLineEdit(layoutWidget);
        lineEdit_dm_real->setObjectName(QStringLiteral("lineEdit_dm_real"));

        gridLayout->addWidget(lineEdit_dm_real, 2, 1, 1, 1);

        lineEdit_zustmassvert = new QLineEdit(layoutWidget);
        lineEdit_zustmassvert->setObjectName(QStringLiteral("lineEdit_zustmassvert"));

        gridLayout->addWidget(lineEdit_zustmassvert, 5, 1, 1, 1);

        label_dm_cad = new QLabel(layoutWidget);
        label_dm_cad->setObjectName(QStringLiteral("label_dm_cad"));

        gridLayout->addWidget(label_dm_cad, 1, 0, 1, 1);

        checkBox_verti = new QCheckBox(layoutWidget);
        checkBox_verti->setObjectName(QStringLiteral("checkBox_verti"));

        gridLayout->addWidget(checkBox_verti, 8, 1, 1, 1);

        lineEdit_zustmasshori = new QLineEdit(layoutWidget);
        lineEdit_zustmasshori->setObjectName(QStringLiteral("lineEdit_zustmasshori"));

        gridLayout->addWidget(lineEdit_zustmasshori, 6, 1, 1, 1);

        label_zustmass = new QLabel(layoutWidget);
        label_zustmass->setObjectName(QStringLiteral("label_zustmass"));

        gridLayout->addWidget(label_zustmass, 6, 0, 1, 1);

        label_zustmass_2 = new QLabel(layoutWidget);
        label_zustmass_2->setObjectName(QStringLiteral("label_zustmass_2"));

        gridLayout->addWidget(label_zustmass_2, 5, 0, 1, 1);

        layoutWidget1 = new QWidget(Dialog_bohrer);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(160, 320, 211, 41));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_abbrechen = new QPushButton(layoutWidget1);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));

        horizontalLayout->addWidget(pushButton_abbrechen);

        pushButton_ok = new QPushButton(layoutWidget1);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        horizontalLayout->addWidget(pushButton_ok);

        QWidget::setTabOrder(lineEdit_nr, lineEdit_dm_cad);
        QWidget::setTabOrder(lineEdit_dm_cad, lineEdit_dm_real);
        QWidget::setTabOrder(lineEdit_dm_real, lineEdit_nutzlaenge);
        QWidget::setTabOrder(lineEdit_nutzlaenge, lineEdit_zustmassvert);
        QWidget::setTabOrder(lineEdit_zustmassvert, lineEdit_zustmasshori);
        QWidget::setTabOrder(lineEdit_zustmasshori, checkBox_istdubo);
        QWidget::setTabOrder(checkBox_istdubo, checkBox_verti);
        QWidget::setTabOrder(checkBox_verti, checkBox_hori);
        QWidget::setTabOrder(checkBox_hori, checkBox_ist_aktiv);
        QWidget::setTabOrder(checkBox_ist_aktiv, pushButton_ok);
        QWidget::setTabOrder(pushButton_ok, pushButton_abbrechen);

        retranslateUi(Dialog_bohrer);

        QMetaObject::connectSlotsByName(Dialog_bohrer);
    } // setupUi

    void retranslateUi(QDialog *Dialog_bohrer)
    {
        Dialog_bohrer->setWindowTitle(QApplication::translate("Dialog_bohrer", "Bohrer", nullptr));
        checkBox_hori->setText(QApplication::translate("Dialog_bohrer", "kann horizontal bohren", nullptr));
        label_nutzlaenge->setText(QApplication::translate("Dialog_bohrer", "<html><head/><body><p>Nutzl\303\244nge</p></body></html>", nullptr));
        label_nr->setText(QApplication::translate("Dialog_bohrer", "Werkzeugnummer", nullptr));
        checkBox_istdubo->setText(QApplication::translate("Dialog_bohrer", "ist Durchgangsbohrer", nullptr));
        checkBox_ist_aktiv->setText(QApplication::translate("Dialog_bohrer", "ist aktiv", nullptr));
        label_dm_real->setText(QApplication::translate("Dialog_bohrer", "Durchmesser export", nullptr));
        label_dm_cad->setText(QApplication::translate("Dialog_bohrer", "Durchmesser import", nullptr));
        checkBox_verti->setText(QApplication::translate("Dialog_bohrer", "kann vertikal bohren", nullptr));
        label_zustmass->setText(QApplication::translate("Dialog_bohrer", "Zustellma\303\237 horizontal", nullptr));
        label_zustmass_2->setText(QApplication::translate("Dialog_bohrer", "Zustellma\303\237 vertikal", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("Dialog_bohrer", "Abbrechen", nullptr));
        pushButton_ok->setText(QApplication::translate("Dialog_bohrer", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_bohrer: public Ui_Dialog_bohrer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_BOHRER_H
