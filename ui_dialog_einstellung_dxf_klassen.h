/********************************************************************************
** Form generated from reading UI file 'dialog_einstellung_dxf_klassen.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_EINSTELLUNG_DXF_KLASSEN_H
#define UI_DIALOG_EINSTELLUNG_DXF_KLASSEN_H

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

class Ui_Dialog_einstellung_dxf_klassen
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_17;
    QLabel *label_14;
    QLabel *label_19;
    QLabel *label_16;
    QLabel *label_12;
    QLabel *label_11;
    QLineEdit *lineEdit_bohr_hori_beispiel;
    QLabel *label_18;
    QLabel *label_7;
    QLineEdit *lineEdit_rta_beispiel;
    QLineEdit *lineEdit_rta;
    QLineEdit *lineEdit_wst;
    QLabel *label;
    QLineEdit *lineEdit_bohr_vert_beispiel;
    QLabel *label_5;
    QLineEdit *lineEdit_nut_vert;
    QLabel *label_6;
    QLineEdit *lineEdit_kta;
    QLineEdit *lineEdit_fraes_vert_beispiel1;
    QLineEdit *lineEdit_wst_beispiel;
    QLineEdit *lineEdit_kta_beispiel;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *lineEdit_bohr_vert;
    QLabel *label_15;
    QLabel *label_4;
    QLineEdit *lineEdit_kta_beispiel2;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_10;
    QLineEdit *lineEdit_fraes_vert;
    QLineEdit *lineEdit_nut_vert_beispiel;
    QLineEdit *lineEdit_bohr_hori;
    QLineEdit *lineEdit_fraes_vert_beispiel2;
    QLabel *label_13;
    QLineEdit *lineEdit_rta_beispiel2;
    QLabel *label_20;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_speichern;
    QPushButton *pushButton_abbrechen;

    void setupUi(QDialog *Dialog_einstellung_dxf_klassen)
    {
        if (Dialog_einstellung_dxf_klassen->objectName().isEmpty())
            Dialog_einstellung_dxf_klassen->setObjectName(QStringLiteral("Dialog_einstellung_dxf_klassen"));
        Dialog_einstellung_dxf_klassen->resize(568, 416);
        layoutWidget = new QWidget(Dialog_einstellung_dxf_klassen);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 541, 326));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_17 = new QLabel(layoutWidget);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout->addWidget(label_17, 3, 2, 1, 1);

        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout->addWidget(label_14, 10, 0, 1, 4);

        label_19 = new QLabel(layoutWidget);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout->addWidget(label_19, 6, 2, 1, 1);

        label_16 = new QLabel(layoutWidget);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout->addWidget(label_16, 7, 0, 1, 1);

        label_12 = new QLabel(layoutWidget);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 11, 2, 1, 1);

        label_11 = new QLabel(layoutWidget);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout->addWidget(label_11, 9, 0, 1, 1);

        lineEdit_bohr_hori_beispiel = new QLineEdit(layoutWidget);
        lineEdit_bohr_hori_beispiel->setObjectName(QStringLiteral("lineEdit_bohr_hori_beispiel"));
        lineEdit_bohr_hori_beispiel->setReadOnly(true);

        gridLayout->addWidget(lineEdit_bohr_hori_beispiel, 3, 3, 1, 1);

        label_18 = new QLabel(layoutWidget);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout->addWidget(label_18, 7, 2, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        lineEdit_rta_beispiel = new QLineEdit(layoutWidget);
        lineEdit_rta_beispiel->setObjectName(QStringLiteral("lineEdit_rta_beispiel"));
        lineEdit_rta_beispiel->setReadOnly(true);

        gridLayout->addWidget(lineEdit_rta_beispiel, 7, 3, 1, 1);

        lineEdit_rta = new QLineEdit(layoutWidget);
        lineEdit_rta->setObjectName(QStringLiteral("lineEdit_rta"));

        gridLayout->addWidget(lineEdit_rta, 7, 1, 1, 1);

        lineEdit_wst = new QLineEdit(layoutWidget);
        lineEdit_wst->setObjectName(QStringLiteral("lineEdit_wst"));

        gridLayout->addWidget(lineEdit_wst, 1, 1, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 1, 1, 1);

        lineEdit_bohr_vert_beispiel = new QLineEdit(layoutWidget);
        lineEdit_bohr_vert_beispiel->setObjectName(QStringLiteral("lineEdit_bohr_vert_beispiel"));
        lineEdit_bohr_vert_beispiel->setReadOnly(true);

        gridLayout->addWidget(lineEdit_bohr_vert_beispiel, 2, 3, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        lineEdit_nut_vert = new QLineEdit(layoutWidget);
        lineEdit_nut_vert->setObjectName(QStringLiteral("lineEdit_nut_vert"));

        gridLayout->addWidget(lineEdit_nut_vert, 4, 1, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        lineEdit_kta = new QLineEdit(layoutWidget);
        lineEdit_kta->setObjectName(QStringLiteral("lineEdit_kta"));

        gridLayout->addWidget(lineEdit_kta, 5, 1, 1, 1);

        lineEdit_fraes_vert_beispiel1 = new QLineEdit(layoutWidget);
        lineEdit_fraes_vert_beispiel1->setObjectName(QStringLiteral("lineEdit_fraes_vert_beispiel1"));
        lineEdit_fraes_vert_beispiel1->setReadOnly(true);

        gridLayout->addWidget(lineEdit_fraes_vert_beispiel1, 11, 3, 1, 1);

        lineEdit_wst_beispiel = new QLineEdit(layoutWidget);
        lineEdit_wst_beispiel->setObjectName(QStringLiteral("lineEdit_wst_beispiel"));
        lineEdit_wst_beispiel->setReadOnly(true);

        gridLayout->addWidget(lineEdit_wst_beispiel, 1, 3, 1, 1);

        lineEdit_kta_beispiel = new QLineEdit(layoutWidget);
        lineEdit_kta_beispiel->setObjectName(QStringLiteral("lineEdit_kta_beispiel"));
        lineEdit_kta_beispiel->setReadOnly(true);

        gridLayout->addWidget(lineEdit_kta_beispiel, 5, 3, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 5, 2, 1, 1);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 4, 0, 1, 1);

        lineEdit_bohr_vert = new QLineEdit(layoutWidget);
        lineEdit_bohr_vert->setObjectName(QStringLiteral("lineEdit_bohr_vert"));

        gridLayout->addWidget(lineEdit_bohr_vert, 2, 1, 1, 1);

        label_15 = new QLabel(layoutWidget);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout->addWidget(label_15, 5, 0, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 2, 1, 1);

        lineEdit_kta_beispiel2 = new QLineEdit(layoutWidget);
        lineEdit_kta_beispiel2->setObjectName(QStringLiteral("lineEdit_kta_beispiel2"));
        lineEdit_kta_beispiel2->setReadOnly(true);

        gridLayout->addWidget(lineEdit_kta_beispiel2, 6, 3, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 2, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 0, 2, 1, 2);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 4, 2, 1, 1);

        lineEdit_fraes_vert = new QLineEdit(layoutWidget);
        lineEdit_fraes_vert->setObjectName(QStringLiteral("lineEdit_fraes_vert"));

        gridLayout->addWidget(lineEdit_fraes_vert, 9, 1, 1, 1);

        lineEdit_nut_vert_beispiel = new QLineEdit(layoutWidget);
        lineEdit_nut_vert_beispiel->setObjectName(QStringLiteral("lineEdit_nut_vert_beispiel"));
        lineEdit_nut_vert_beispiel->setReadOnly(true);

        gridLayout->addWidget(lineEdit_nut_vert_beispiel, 4, 3, 1, 1);

        lineEdit_bohr_hori = new QLineEdit(layoutWidget);
        lineEdit_bohr_hori->setObjectName(QStringLiteral("lineEdit_bohr_hori"));

        gridLayout->addWidget(lineEdit_bohr_hori, 3, 1, 1, 1);

        lineEdit_fraes_vert_beispiel2 = new QLineEdit(layoutWidget);
        lineEdit_fraes_vert_beispiel2->setObjectName(QStringLiteral("lineEdit_fraes_vert_beispiel2"));
        lineEdit_fraes_vert_beispiel2->setReadOnly(true);

        gridLayout->addWidget(lineEdit_fraes_vert_beispiel2, 12, 3, 1, 1);

        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 12, 2, 1, 1);

        lineEdit_rta_beispiel2 = new QLineEdit(layoutWidget);
        lineEdit_rta_beispiel2->setObjectName(QStringLiteral("lineEdit_rta_beispiel2"));
        lineEdit_rta_beispiel2->setReadOnly(true);

        gridLayout->addWidget(lineEdit_rta_beispiel2, 8, 3, 1, 1);

        label_20 = new QLabel(layoutWidget);
        label_20->setObjectName(QStringLiteral("label_20"));

        gridLayout->addWidget(label_20, 8, 2, 1, 1);

        layoutWidget1 = new QWidget(Dialog_einstellung_dxf_klassen);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(220, 380, 261, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_speichern = new QPushButton(layoutWidget1);
        pushButton_speichern->setObjectName(QStringLiteral("pushButton_speichern"));

        horizontalLayout->addWidget(pushButton_speichern);

        pushButton_abbrechen = new QPushButton(layoutWidget1);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));

        horizontalLayout->addWidget(pushButton_abbrechen);

        QWidget::setTabOrder(lineEdit_wst, lineEdit_bohr_vert);
        QWidget::setTabOrder(lineEdit_bohr_vert, lineEdit_bohr_hori);
        QWidget::setTabOrder(lineEdit_bohr_hori, lineEdit_nut_vert);
        QWidget::setTabOrder(lineEdit_nut_vert, lineEdit_kta);
        QWidget::setTabOrder(lineEdit_kta, lineEdit_rta);
        QWidget::setTabOrder(lineEdit_rta, lineEdit_fraes_vert);
        QWidget::setTabOrder(lineEdit_fraes_vert, lineEdit_wst_beispiel);
        QWidget::setTabOrder(lineEdit_wst_beispiel, lineEdit_bohr_vert_beispiel);
        QWidget::setTabOrder(lineEdit_bohr_vert_beispiel, lineEdit_bohr_hori_beispiel);
        QWidget::setTabOrder(lineEdit_bohr_hori_beispiel, lineEdit_nut_vert_beispiel);
        QWidget::setTabOrder(lineEdit_nut_vert_beispiel, lineEdit_kta_beispiel);
        QWidget::setTabOrder(lineEdit_kta_beispiel, lineEdit_rta_beispiel);
        QWidget::setTabOrder(lineEdit_rta_beispiel, lineEdit_fraes_vert_beispiel1);
        QWidget::setTabOrder(lineEdit_fraes_vert_beispiel1, lineEdit_fraes_vert_beispiel2);
        QWidget::setTabOrder(lineEdit_fraes_vert_beispiel2, pushButton_speichern);
        QWidget::setTabOrder(pushButton_speichern, pushButton_abbrechen);

        retranslateUi(Dialog_einstellung_dxf_klassen);

        QMetaObject::connectSlotsByName(Dialog_einstellung_dxf_klassen);
    } // setupUi

    void retranslateUi(QDialog *Dialog_einstellung_dxf_klassen)
    {
        Dialog_einstellung_dxf_klassen->setWindowTitle(QApplication::translate("Dialog_einstellung_dxf_klassen", "Klasseneinstellungen DXF", nullptr));
        label_17->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "14,2mm tief", nullptr));
        label_14->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "Beispiel jeweil mit Werkzeug 601 mit Radiuskorrektur links bei einem Bauteil mit 19mm Dicke:", nullptr));
        label_19->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "mit WKZ", nullptr));
        label_16->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "Rechtecktaschen", nullptr));
        label_12->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "durchgefr\303\244st 2mm", nullptr));
        label_11->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "Fr\303\244ser vertikal", nullptr));
        label_18->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "14,2mm tief", nullptr));
        label_7->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "Bohrung horizontal", nullptr));
        label->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "Klassenname", nullptr));
        label_5->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "Bauteil", nullptr));
        label_6->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "Bohrung vertikal", nullptr));
        label_8->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "14,2mm tief", nullptr));
        label_9->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "Nut vertikal", nullptr));
        label_15->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "Kreistaschen", nullptr));
        label_4->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "14,2mm tief", nullptr));
        label_3->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "19,6mm Dick", nullptr));
        label_2->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "Anwendungsbeispiel", nullptr));
        label_10->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "8,5mm breit", nullptr));
        label_13->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "5mm tief eingefr\303\244st", nullptr));
        label_20->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "mit WKZ", nullptr));
        pushButton_speichern->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "Speichern", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("Dialog_einstellung_dxf_klassen", "Abbrechen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_einstellung_dxf_klassen: public Ui_Dialog_einstellung_dxf_klassen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_EINSTELLUNG_DXF_KLASSEN_H
