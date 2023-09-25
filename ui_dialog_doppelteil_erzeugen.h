/********************************************************************************
** Form generated from reading UI file 'dialog_doppelteil_erzeugen.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_DOPPELTEIL_ERZEUGEN_H
#define UI_DIALOG_DOPPELTEIL_ERZEUGEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_doppelteil_erzeugen
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QFrame *line_2;
    QRadioButton *radioButton_re;
    QRadioButton *radioButton_hi;
    QFrame *line_4;
    QRadioButton *radioButton_li;
    QRadioButton *radioButton_vo;
    QFrame *line;
    QFrame *line_3;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioButton_drehen;
    QRadioButton *radioButton_spiegeln;
    QWidget *widget2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_abbrechen;
    QWidget *widget3;
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_alt_la;
    QLabel *label_3;
    QLineEdit *lineEdit_neu_br;
    QLineEdit *lineEdit_alt_br;
    QLineEdit *lineEdit_neu_la;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;

    void setupUi(QDialog *Dialog_doppelteil_erzeugen)
    {
        if (Dialog_doppelteil_erzeugen->objectName().isEmpty())
            Dialog_doppelteil_erzeugen->setObjectName(QStringLiteral("Dialog_doppelteil_erzeugen"));
        Dialog_doppelteil_erzeugen->resize(413, 256);
        Dialog_doppelteil_erzeugen->setModal(true);
        widget = new QWidget(Dialog_doppelteil_erzeugen);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 188, 107));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);

        verticalLayout->addWidget(label_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);

        gridLayout->addWidget(label, 2, 2, 1, 1);

        line_2 = new QFrame(widget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 0, 1, 1, 3);

        radioButton_re = new QRadioButton(widget);
        radioButton_re->setObjectName(QStringLiteral("radioButton_re"));

        gridLayout->addWidget(radioButton_re, 2, 3, 1, 1);

        radioButton_hi = new QRadioButton(widget);
        radioButton_hi->setObjectName(QStringLiteral("radioButton_hi"));

        gridLayout->addWidget(radioButton_hi, 1, 2, 1, 1);

        line_4 = new QFrame(widget);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_4, 1, 4, 3, 1);

        radioButton_li = new QRadioButton(widget);
        radioButton_li->setObjectName(QStringLiteral("radioButton_li"));

        gridLayout->addWidget(radioButton_li, 2, 1, 1, 1);

        radioButton_vo = new QRadioButton(widget);
        radioButton_vo->setObjectName(QStringLiteral("radioButton_vo"));
        radioButton_vo->setChecked(true);

        gridLayout->addWidget(radioButton_vo, 3, 2, 1, 1);

        line = new QFrame(widget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 4, 1, 1, 3);

        line_3 = new QFrame(widget);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 1, 0, 3, 1);


        verticalLayout->addLayout(gridLayout);

        widget1 = new QWidget(Dialog_doppelteil_erzeugen);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(240, 40, 125, 42));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        radioButton_drehen = new QRadioButton(widget1);
        radioButton_drehen->setObjectName(QStringLiteral("radioButton_drehen"));
        radioButton_drehen->setChecked(true);

        verticalLayout_2->addWidget(radioButton_drehen);

        radioButton_spiegeln = new QRadioButton(widget1);
        radioButton_spiegeln->setObjectName(QStringLiteral("radioButton_spiegeln"));

        verticalLayout_2->addWidget(radioButton_spiegeln);

        widget2 = new QWidget(Dialog_doppelteil_erzeugen);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(100, 220, 221, 25));
        horizontalLayout = new QHBoxLayout(widget2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_ok = new QPushButton(widget2);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        horizontalLayout->addWidget(pushButton_ok);

        pushButton_abbrechen = new QPushButton(widget2);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));

        horizontalLayout->addWidget(pushButton_abbrechen);

        widget3 = new QWidget(Dialog_doppelteil_erzeugen);
        widget3->setObjectName(QStringLiteral("widget3"));
        widget3->setGeometry(QRect(19, 140, 381, 67));
        gridLayout_2 = new QGridLayout(widget3);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        lineEdit_alt_la = new QLineEdit(widget3);
        lineEdit_alt_la->setObjectName(QStringLiteral("lineEdit_alt_la"));
        lineEdit_alt_la->setEnabled(false);

        gridLayout_2->addWidget(lineEdit_alt_la, 1, 1, 1, 1);

        label_3 = new QLabel(widget3);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 1, 0, 1, 1);

        lineEdit_neu_br = new QLineEdit(widget3);
        lineEdit_neu_br->setObjectName(QStringLiteral("lineEdit_neu_br"));

        gridLayout_2->addWidget(lineEdit_neu_br, 2, 2, 1, 1);

        lineEdit_alt_br = new QLineEdit(widget3);
        lineEdit_alt_br->setObjectName(QStringLiteral("lineEdit_alt_br"));
        lineEdit_alt_br->setEnabled(false);

        gridLayout_2->addWidget(lineEdit_alt_br, 2, 1, 1, 1);

        lineEdit_neu_la = new QLineEdit(widget3);
        lineEdit_neu_la->setObjectName(QStringLiteral("lineEdit_neu_la"));

        gridLayout_2->addWidget(lineEdit_neu_la, 1, 2, 1, 1);

        label_4 = new QLabel(widget3);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        label_5 = new QLabel(widget3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_5, 0, 1, 1, 1);

        label_6 = new QLabel(widget3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_6, 0, 2, 1, 1);

        QWidget::setTabOrder(radioButton_vo, radioButton_hi);
        QWidget::setTabOrder(radioButton_hi, radioButton_li);
        QWidget::setTabOrder(radioButton_li, radioButton_re);
        QWidget::setTabOrder(radioButton_re, radioButton_drehen);
        QWidget::setTabOrder(radioButton_drehen, radioButton_spiegeln);
        QWidget::setTabOrder(radioButton_spiegeln, lineEdit_alt_la);
        QWidget::setTabOrder(lineEdit_alt_la, lineEdit_alt_br);
        QWidget::setTabOrder(lineEdit_alt_br, lineEdit_neu_la);
        QWidget::setTabOrder(lineEdit_neu_la, lineEdit_neu_br);
        QWidget::setTabOrder(lineEdit_neu_br, pushButton_ok);
        QWidget::setTabOrder(pushButton_ok, pushButton_abbrechen);

        retranslateUi(Dialog_doppelteil_erzeugen);

        QMetaObject::connectSlotsByName(Dialog_doppelteil_erzeugen);
    } // setupUi

    void retranslateUi(QDialog *Dialog_doppelteil_erzeugen)
    {
        Dialog_doppelteil_erzeugen->setWindowTitle(QApplication::translate("Dialog_doppelteil_erzeugen", "Doppelteil erzeugen", nullptr));
        label_2->setText(QApplication::translate("Dialog_doppelteil_erzeugen", "Bezugskante/Fixkante", nullptr));
        label->setText(QApplication::translate("Dialog_doppelteil_erzeugen", "Draufsicht", nullptr));
        radioButton_re->setText(QApplication::translate("Dialog_doppelteil_erzeugen", "rechts", nullptr));
        radioButton_hi->setText(QApplication::translate("Dialog_doppelteil_erzeugen", "hinten", nullptr));
        radioButton_li->setText(QApplication::translate("Dialog_doppelteil_erzeugen", "links", nullptr));
        radioButton_vo->setText(QApplication::translate("Dialog_doppelteil_erzeugen", "vorne", nullptr));
        radioButton_drehen->setText(QApplication::translate("Dialog_doppelteil_erzeugen", "Bearbeitung drehen", nullptr));
        radioButton_spiegeln->setText(QApplication::translate("Dialog_doppelteil_erzeugen", "Bearbeitung spiegeln", nullptr));
        pushButton_ok->setText(QApplication::translate("Dialog_doppelteil_erzeugen", "OK", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("Dialog_doppelteil_erzeugen", "Abbrechen", nullptr));
        label_3->setText(QApplication::translate("Dialog_doppelteil_erzeugen", "L\303\244nge", nullptr));
        label_4->setText(QApplication::translate("Dialog_doppelteil_erzeugen", "Breite", nullptr));
        label_5->setText(QApplication::translate("Dialog_doppelteil_erzeugen", "vorher", nullptr));
        label_6->setText(QApplication::translate("Dialog_doppelteil_erzeugen", "neue Ma\303\237e", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_doppelteil_erzeugen: public Ui_Dialog_doppelteil_erzeugen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_DOPPELTEIL_ERZEUGEN_H
