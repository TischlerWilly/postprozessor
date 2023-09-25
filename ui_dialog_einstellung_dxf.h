/********************************************************************************
** Form generated from reading UI file 'dialog_einstellung_dxf.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_EINSTELLUNG_DXF_H
#define UI_DIALOG_EINSTELLUNG_DXF_H

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

class Ui_Dialog_einstellung_dxf
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_5;
    QLineEdit *lineEdit_KennungOberseite;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *label_dezimaltrenner;
    QLabel *label_6;
    QLineEdit *lineEdit_parametertrenner;
    QLabel *label_8;
    QLineEdit *lineEdit_KennungRadKorRe;
    QLineEdit *lineEdit_KennungRadKorLi;
    QLineEdit *lineEdit_KennungWKZnr;
    QComboBox *comboBox_drehdypUnterseite;
    QLabel *label_4;
    QLineEdit *lineEdit_KennungRadKorMi;
    QLineEdit *lineEdit_dezimaltrenner;
    QLineEdit *lineEdit_KennungUnterseite;
    QLabel *label_9;
    QComboBox *comboBox_bezugTiFkon;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_abbrechen;

    void setupUi(QDialog *Dialog_einstellung_dxf)
    {
        if (Dialog_einstellung_dxf->objectName().isEmpty())
            Dialog_einstellung_dxf->setObjectName(QStringLiteral("Dialog_einstellung_dxf"));
        Dialog_einstellung_dxf->resize(400, 363);
        layoutWidget = new QWidget(Dialog_einstellung_dxf);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 11, 381, 256));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        lineEdit_KennungOberseite = new QLineEdit(layoutWidget);
        lineEdit_KennungOberseite->setObjectName(QStringLiteral("lineEdit_KennungOberseite"));

        gridLayout->addWidget(lineEdit_KennungOberseite, 2, 1, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 7, 0, 1, 1);

        label_dezimaltrenner = new QLabel(layoutWidget);
        label_dezimaltrenner->setObjectName(QStringLiteral("label_dezimaltrenner"));

        gridLayout->addWidget(label_dezimaltrenner, 1, 0, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        lineEdit_parametertrenner = new QLineEdit(layoutWidget);
        lineEdit_parametertrenner->setObjectName(QStringLiteral("lineEdit_parametertrenner"));

        gridLayout->addWidget(lineEdit_parametertrenner, 0, 1, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 8, 0, 1, 1);

        lineEdit_KennungRadKorRe = new QLineEdit(layoutWidget);
        lineEdit_KennungRadKorRe->setObjectName(QStringLiteral("lineEdit_KennungRadKorRe"));

        gridLayout->addWidget(lineEdit_KennungRadKorRe, 8, 1, 1, 1);

        lineEdit_KennungRadKorLi = new QLineEdit(layoutWidget);
        lineEdit_KennungRadKorLi->setObjectName(QStringLiteral("lineEdit_KennungRadKorLi"));

        gridLayout->addWidget(lineEdit_KennungRadKorLi, 6, 1, 1, 1);

        lineEdit_KennungWKZnr = new QLineEdit(layoutWidget);
        lineEdit_KennungWKZnr->setObjectName(QStringLiteral("lineEdit_KennungWKZnr"));

        gridLayout->addWidget(lineEdit_KennungWKZnr, 5, 1, 1, 1);

        comboBox_drehdypUnterseite = new QComboBox(layoutWidget);
        comboBox_drehdypUnterseite->setObjectName(QStringLiteral("comboBox_drehdypUnterseite"));

        gridLayout->addWidget(comboBox_drehdypUnterseite, 4, 1, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        lineEdit_KennungRadKorMi = new QLineEdit(layoutWidget);
        lineEdit_KennungRadKorMi->setObjectName(QStringLiteral("lineEdit_KennungRadKorMi"));

        gridLayout->addWidget(lineEdit_KennungRadKorMi, 7, 1, 1, 1);

        lineEdit_dezimaltrenner = new QLineEdit(layoutWidget);
        lineEdit_dezimaltrenner->setObjectName(QStringLiteral("lineEdit_dezimaltrenner"));

        gridLayout->addWidget(lineEdit_dezimaltrenner, 1, 1, 1, 1);

        lineEdit_KennungUnterseite = new QLineEdit(layoutWidget);
        lineEdit_KennungUnterseite->setObjectName(QStringLiteral("lineEdit_KennungUnterseite"));

        gridLayout->addWidget(lineEdit_KennungUnterseite, 3, 1, 1, 1);

        label_9 = new QLabel(layoutWidget);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 9, 0, 1, 1);

        comboBox_bezugTiFkon = new QComboBox(layoutWidget);
        comboBox_bezugTiFkon->setObjectName(QStringLiteral("comboBox_bezugTiFkon"));

        gridLayout->addWidget(comboBox_bezugTiFkon, 9, 1, 1, 1);

        layoutWidget1 = new QWidget(Dialog_einstellung_dxf);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(170, 320, 221, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_ok = new QPushButton(layoutWidget1);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        horizontalLayout->addWidget(pushButton_ok);

        pushButton_abbrechen = new QPushButton(layoutWidget1);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));

        horizontalLayout->addWidget(pushButton_abbrechen);

        QWidget::setTabOrder(lineEdit_parametertrenner, lineEdit_dezimaltrenner);
        QWidget::setTabOrder(lineEdit_dezimaltrenner, lineEdit_KennungOberseite);
        QWidget::setTabOrder(lineEdit_KennungOberseite, lineEdit_KennungUnterseite);
        QWidget::setTabOrder(lineEdit_KennungUnterseite, comboBox_drehdypUnterseite);
        QWidget::setTabOrder(comboBox_drehdypUnterseite, pushButton_ok);
        QWidget::setTabOrder(pushButton_ok, pushButton_abbrechen);

        retranslateUi(Dialog_einstellung_dxf);

        QMetaObject::connectSlotsByName(Dialog_einstellung_dxf);
    } // setupUi

    void retranslateUi(QDialog *Dialog_einstellung_dxf)
    {
        Dialog_einstellung_dxf->setWindowTitle(QApplication::translate("Dialog_einstellung_dxf", "Grundeinstellungen DXF", nullptr));
        label_2->setText(QApplication::translate("Dialog_einstellung_dxf", "Kennung Datei f\303\274r Oberseite", nullptr));
        label_5->setText(QApplication::translate("Dialog_einstellung_dxf", "Kennung Werkzeugnummer", nullptr));
        label->setText(QApplication::translate("Dialog_einstellung_dxf", "Trennzeichen von Parametern im Klassennamen", nullptr));
        label_3->setText(QApplication::translate("Dialog_einstellung_dxf", "Kennung Datei f\303\274r Unterseite", nullptr));
        label_7->setText(QApplication::translate("Dialog_einstellung_dxf", "Kennung Radiuskorrektur mitte", nullptr));
        label_dezimaltrenner->setText(QApplication::translate("Dialog_einstellung_dxf", "Dezimalzeichen in Klassennamen", nullptr));
        label_6->setText(QApplication::translate("Dialog_einstellung_dxf", "Kennung Radiuskorrektur links", nullptr));
        label_8->setText(QApplication::translate("Dialog_einstellung_dxf", "Kennung Radiuskorrektur rechts", nullptr));
        label_4->setText(QApplication::translate("Dialog_einstellung_dxf", "Unterseite ist gedreht um", nullptr));
        label_9->setText(QApplication::translate("Dialog_einstellung_dxf", "Angabe Fr\303\244stiefe hat Bezug", nullptr));
        pushButton_ok->setText(QApplication::translate("Dialog_einstellung_dxf", "OK", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("Dialog_einstellung_dxf", "Abbrechen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_einstellung_dxf: public Ui_Dialog_einstellung_dxf {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_EINSTELLUNG_DXF_H
