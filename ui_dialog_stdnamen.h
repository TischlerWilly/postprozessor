/********************************************************************************
** Form generated from reading UI file 'dialog_stdnamen.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_STDNAMEN_H
#define UI_DIALOG_STDNAMEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog_stdnamen
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_neu;
    QPushButton *pushButton_edit;
    QPushButton *pushButton_entf;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_abbrechen;
    QTableWidget *tableWidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_up;
    QPushButton *pushButton_down;

    void setupUi(QDialog *Dialog_stdnamen)
    {
        if (Dialog_stdnamen->objectName().isEmpty())
            Dialog_stdnamen->setObjectName(QStringLiteral("Dialog_stdnamen"));
        Dialog_stdnamen->resize(451, 550);
        Dialog_stdnamen->setModal(true);
        layoutWidget = new QWidget(Dialog_stdnamen);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 430, 431, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_neu = new QPushButton(layoutWidget);
        pushButton_neu->setObjectName(QStringLiteral("pushButton_neu"));

        horizontalLayout->addWidget(pushButton_neu);

        pushButton_edit = new QPushButton(layoutWidget);
        pushButton_edit->setObjectName(QStringLiteral("pushButton_edit"));

        horizontalLayout->addWidget(pushButton_edit);

        pushButton_entf = new QPushButton(layoutWidget);
        pushButton_entf->setObjectName(QStringLiteral("pushButton_entf"));

        horizontalLayout->addWidget(pushButton_entf);

        layoutWidget1 = new QWidget(Dialog_stdnamen);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(230, 506, 211, 41));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_ok = new QPushButton(layoutWidget1);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        horizontalLayout_2->addWidget(pushButton_ok);

        pushButton_abbrechen = new QPushButton(layoutWidget1);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));

        horizontalLayout_2->addWidget(pushButton_abbrechen);

        tableWidget = new QTableWidget(Dialog_stdnamen);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 10, 431, 411));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setAlternatingRowColors(false);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->verticalHeader()->setVisible(false);
        widget = new QWidget(Dialog_stdnamen);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(17, 470, 121, 71));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_up = new QPushButton(widget);
        pushButton_up->setObjectName(QStringLiteral("pushButton_up"));

        horizontalLayout_3->addWidget(pushButton_up);

        pushButton_down = new QPushButton(widget);
        pushButton_down->setObjectName(QStringLiteral("pushButton_down"));

        horizontalLayout_3->addWidget(pushButton_down);

        QWidget::setTabOrder(pushButton_ok, pushButton_abbrechen);
        QWidget::setTabOrder(pushButton_abbrechen, pushButton_neu);
        QWidget::setTabOrder(pushButton_neu, pushButton_entf);

        retranslateUi(Dialog_stdnamen);

        QMetaObject::connectSlotsByName(Dialog_stdnamen);
    } // setupUi

    void retranslateUi(QDialog *Dialog_stdnamen)
    {
        Dialog_stdnamen->setWindowTitle(QApplication::translate("Dialog_stdnamen", "Standard-Namen", nullptr));
        pushButton_neu->setText(QApplication::translate("Dialog_stdnamen", "Neu", nullptr));
        pushButton_edit->setText(QApplication::translate("Dialog_stdnamen", "Bearbeiten", nullptr));
        pushButton_entf->setText(QApplication::translate("Dialog_stdnamen", "Entfernen", nullptr));
        pushButton_ok->setText(QApplication::translate("Dialog_stdnamen", "OK", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("Dialog_stdnamen", "Abbrechen", nullptr));
        pushButton_up->setText(QApplication::translate("Dialog_stdnamen", "hoch", nullptr));
        pushButton_down->setText(QApplication::translate("Dialog_stdnamen", "runter", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_stdnamen: public Ui_Dialog_stdnamen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_STDNAMEN_H
