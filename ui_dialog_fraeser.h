/********************************************************************************
** Form generated from reading UI file 'dialog_fraeser.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_FRAESER_H
#define UI_DIALOG_FRAESER_H

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

class Ui_Dialog_fraeser
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_abbrechen;
    QPushButton *pushButton_ok;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_dm;
    QCheckBox *checkBox_ist_hori;
    QCheckBox *checkBox_nur_direkt_zuweisbar;
    QLineEdit *lineEdit_alias;
    QLabel *label_nutzl;
    QLineEdit *lineEdit_zust_min;
    QLineEdit *lineEdit_zustmassvert;
    QLineEdit *lineEdit_nr;
    QLineEdit *lineEdit_spiegel;
    QLineEdit *lineEdit_voers;
    QLabel *label_zust_min;
    QLabel *label_vors;
    QLabel *label_zustm;
    QLabel *label_dm;
    QLabel *label_alias;
    QCheckBox *checkBox_ist_aktiv;
    QLineEdit *lineEdit_nutzl;
    QLabel *label_nr;
    QLabel *label_spiegel;
    QCheckBox *checkBox_ist_veti;
    QLineEdit *lineEdit_zustmasshori;
    QLabel *label_zustmass;

    void setupUi(QDialog *Dialog_fraeser)
    {
        if (Dialog_fraeser->objectName().isEmpty())
            Dialog_fraeser->setObjectName(QStringLiteral("Dialog_fraeser"));
        Dialog_fraeser->resize(400, 440);
        Dialog_fraeser->setModal(true);
        layoutWidget = new QWidget(Dialog_fraeser);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(160, 400, 231, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_abbrechen = new QPushButton(layoutWidget);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));

        horizontalLayout->addWidget(pushButton_abbrechen);

        pushButton_ok = new QPushButton(layoutWidget);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));

        horizontalLayout->addWidget(pushButton_ok);

        layoutWidget1 = new QWidget(Dialog_fraeser);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 10, 371, 381));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_dm = new QLineEdit(layoutWidget1);
        lineEdit_dm->setObjectName(QStringLiteral("lineEdit_dm"));

        gridLayout->addWidget(lineEdit_dm, 1, 1, 1, 1);

        checkBox_ist_hori = new QCheckBox(layoutWidget1);
        checkBox_ist_hori->setObjectName(QStringLiteral("checkBox_ist_hori"));

        gridLayout->addWidget(checkBox_ist_hori, 11, 1, 1, 1);

        checkBox_nur_direkt_zuweisbar = new QCheckBox(layoutWidget1);
        checkBox_nur_direkt_zuweisbar->setObjectName(QStringLiteral("checkBox_nur_direkt_zuweisbar"));

        gridLayout->addWidget(checkBox_nur_direkt_zuweisbar, 9, 1, 1, 1);

        lineEdit_alias = new QLineEdit(layoutWidget1);
        lineEdit_alias->setObjectName(QStringLiteral("lineEdit_alias"));

        gridLayout->addWidget(lineEdit_alias, 7, 1, 1, 1);

        label_nutzl = new QLabel(layoutWidget1);
        label_nutzl->setObjectName(QStringLiteral("label_nutzl"));

        gridLayout->addWidget(label_nutzl, 2, 0, 1, 1);

        lineEdit_zust_min = new QLineEdit(layoutWidget1);
        lineEdit_zust_min->setObjectName(QStringLiteral("lineEdit_zust_min"));

        gridLayout->addWidget(lineEdit_zust_min, 5, 1, 1, 1);

        lineEdit_zustmassvert = new QLineEdit(layoutWidget1);
        lineEdit_zustmassvert->setObjectName(QStringLiteral("lineEdit_zustmassvert"));

        gridLayout->addWidget(lineEdit_zustmassvert, 3, 1, 1, 1);

        lineEdit_nr = new QLineEdit(layoutWidget1);
        lineEdit_nr->setObjectName(QStringLiteral("lineEdit_nr"));

        gridLayout->addWidget(lineEdit_nr, 0, 1, 1, 1);

        lineEdit_spiegel = new QLineEdit(layoutWidget1);
        lineEdit_spiegel->setObjectName(QStringLiteral("lineEdit_spiegel"));

        gridLayout->addWidget(lineEdit_spiegel, 8, 1, 1, 1);

        lineEdit_voers = new QLineEdit(layoutWidget1);
        lineEdit_voers->setObjectName(QStringLiteral("lineEdit_voers"));

        gridLayout->addWidget(lineEdit_voers, 6, 1, 1, 1);

        label_zust_min = new QLabel(layoutWidget1);
        label_zust_min->setObjectName(QStringLiteral("label_zust_min"));

        gridLayout->addWidget(label_zust_min, 5, 0, 1, 1);

        label_vors = new QLabel(layoutWidget1);
        label_vors->setObjectName(QStringLiteral("label_vors"));

        gridLayout->addWidget(label_vors, 6, 0, 1, 1);

        label_zustm = new QLabel(layoutWidget1);
        label_zustm->setObjectName(QStringLiteral("label_zustm"));

        gridLayout->addWidget(label_zustm, 3, 0, 1, 1);

        label_dm = new QLabel(layoutWidget1);
        label_dm->setObjectName(QStringLiteral("label_dm"));

        gridLayout->addWidget(label_dm, 1, 0, 1, 1);

        label_alias = new QLabel(layoutWidget1);
        label_alias->setObjectName(QStringLiteral("label_alias"));

        gridLayout->addWidget(label_alias, 7, 0, 1, 1);

        checkBox_ist_aktiv = new QCheckBox(layoutWidget1);
        checkBox_ist_aktiv->setObjectName(QStringLiteral("checkBox_ist_aktiv"));

        gridLayout->addWidget(checkBox_ist_aktiv, 13, 1, 1, 1);

        lineEdit_nutzl = new QLineEdit(layoutWidget1);
        lineEdit_nutzl->setObjectName(QStringLiteral("lineEdit_nutzl"));

        gridLayout->addWidget(lineEdit_nutzl, 2, 1, 1, 1);

        label_nr = new QLabel(layoutWidget1);
        label_nr->setObjectName(QStringLiteral("label_nr"));

        gridLayout->addWidget(label_nr, 0, 0, 1, 1);

        label_spiegel = new QLabel(layoutWidget1);
        label_spiegel->setObjectName(QStringLiteral("label_spiegel"));

        gridLayout->addWidget(label_spiegel, 8, 0, 1, 1);

        checkBox_ist_veti = new QCheckBox(layoutWidget1);
        checkBox_ist_veti->setObjectName(QStringLiteral("checkBox_ist_veti"));

        gridLayout->addWidget(checkBox_ist_veti, 10, 1, 1, 1);

        lineEdit_zustmasshori = new QLineEdit(layoutWidget1);
        lineEdit_zustmasshori->setObjectName(QStringLiteral("lineEdit_zustmasshori"));

        gridLayout->addWidget(lineEdit_zustmasshori, 4, 1, 1, 1);

        label_zustmass = new QLabel(layoutWidget1);
        label_zustmass->setObjectName(QStringLiteral("label_zustmass"));

        gridLayout->addWidget(label_zustmass, 4, 0, 1, 1);

        QWidget::setTabOrder(lineEdit_nr, lineEdit_dm);
        QWidget::setTabOrder(lineEdit_dm, lineEdit_nutzl);
        QWidget::setTabOrder(lineEdit_nutzl, lineEdit_zustmassvert);
        QWidget::setTabOrder(lineEdit_zustmassvert, lineEdit_zustmasshori);
        QWidget::setTabOrder(lineEdit_zustmasshori, lineEdit_zust_min);
        QWidget::setTabOrder(lineEdit_zust_min, lineEdit_voers);
        QWidget::setTabOrder(lineEdit_voers, lineEdit_alias);
        QWidget::setTabOrder(lineEdit_alias, lineEdit_spiegel);
        QWidget::setTabOrder(lineEdit_spiegel, checkBox_nur_direkt_zuweisbar);
        QWidget::setTabOrder(checkBox_nur_direkt_zuweisbar, checkBox_ist_veti);
        QWidget::setTabOrder(checkBox_ist_veti, checkBox_ist_hori);
        QWidget::setTabOrder(checkBox_ist_hori, checkBox_ist_aktiv);
        QWidget::setTabOrder(checkBox_ist_aktiv, pushButton_ok);
        QWidget::setTabOrder(pushButton_ok, pushButton_abbrechen);

        retranslateUi(Dialog_fraeser);

        QMetaObject::connectSlotsByName(Dialog_fraeser);
    } // setupUi

    void retranslateUi(QDialog *Dialog_fraeser)
    {
        Dialog_fraeser->setWindowTitle(QApplication::translate("Dialog_fraeser", "Fraeser", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("Dialog_fraeser", "Abbrechen", nullptr));
        pushButton_ok->setText(QApplication::translate("Dialog_fraeser", "OK", nullptr));
        checkBox_ist_hori->setText(QApplication::translate("Dialog_fraeser", "kann horizontal fr\303\244sen", nullptr));
        checkBox_nur_direkt_zuweisbar->setText(QApplication::translate("Dialog_fraeser", "Nur direkt zuweisbar", nullptr));
#ifndef QT_NO_TOOLTIP
        lineEdit_alias->setToolTip(QApplication::translate("Dialog_fraeser", "<html><head/><body><p>Ein Alias-Name ist ein zweiter Name f\303\274r das selbe Werkzeug. Wird mehr als ein Alias-Name ben\303\266tigt, so kann das Werkzeug dupliziert werden und dem Duplikat ein anderer Alias-Name zugewiesen werden.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        label_nutzl->setText(QApplication::translate("Dialog_fraeser", "<html><head/><body><p>Nutzl\303\244nge</p></body></html>", nullptr));
        label_zust_min->setText(QApplication::translate("Dialog_fraeser", "Mind. Zustellung", nullptr));
        label_vors->setText(QApplication::translate("Dialog_fraeser", "Vorschub", nullptr));
        label_zustm->setText(QApplication::translate("Dialog_fraeser", "Zustellma\303\237 vertikal", nullptr));
        label_dm->setText(QApplication::translate("Dialog_fraeser", "Durchmesser", nullptr));
        label_alias->setText(QApplication::translate("Dialog_fraeser", "Alias-Name", nullptr));
        checkBox_ist_aktiv->setText(QApplication::translate("Dialog_fraeser", "ist aktiv", nullptr));
        label_nr->setText(QApplication::translate("Dialog_fraeser", "Werkzeugnummer", nullptr));
        label_spiegel->setText(QApplication::translate("Dialog_fraeser", "Spiegelwerkzeug", nullptr));
        checkBox_ist_veti->setText(QApplication::translate("Dialog_fraeser", "kann vertikal fr\303\244sen", nullptr));
        label_zustmass->setText(QApplication::translate("Dialog_fraeser", "Zustellma\303\237 horizontal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_fraeser: public Ui_Dialog_fraeser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_FRAESER_H
