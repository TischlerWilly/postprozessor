/********************************************************************************
** Form generated from reading UI file 'dialog_einstellung_ganx.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_EINSTELLUNG_GANX_H
#define UI_DIALOG_EINSTELLUNG_GANX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog_einstellung_ganx
{
public:
    QCheckBox *checkBox_bezugskantenmass;
    QDoubleSpinBox *doubleSpinBox_bezugskantenmass;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_abbrechen;

    void setupUi(QDialog *Dialog_einstellung_ganx)
    {
        if (Dialog_einstellung_ganx->objectName().isEmpty())
            Dialog_einstellung_ganx->setObjectName(QStringLiteral("Dialog_einstellung_ganx"));
        Dialog_einstellung_ganx->resize(400, 300);
        Dialog_einstellung_ganx->setModal(true);
        checkBox_bezugskantenmass = new QCheckBox(Dialog_einstellung_ganx);
        checkBox_bezugskantenmass->setObjectName(QStringLiteral("checkBox_bezugskantenmass"));
        checkBox_bezugskantenmass->setGeometry(QRect(10, 10, 261, 21));
        doubleSpinBox_bezugskantenmass = new QDoubleSpinBox(Dialog_einstellung_ganx);
        doubleSpinBox_bezugskantenmass->setObjectName(QStringLiteral("doubleSpinBox_bezugskantenmass"));
        doubleSpinBox_bezugskantenmass->setGeometry(QRect(281, 10, 101, 22));
        doubleSpinBox_bezugskantenmass->setDecimals(1);
        doubleSpinBox_bezugskantenmass->setMaximum(100);
        pushButton_ok = new QPushButton(Dialog_einstellung_ganx);
        pushButton_ok->setObjectName(QStringLiteral("pushButton_ok"));
        pushButton_ok->setGeometry(QRect(110, 260, 75, 23));
        pushButton_abbrechen = new QPushButton(Dialog_einstellung_ganx);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));
        pushButton_abbrechen->setGeometry(QRect(200, 260, 75, 23));

        retranslateUi(Dialog_einstellung_ganx);

        QMetaObject::connectSlotsByName(Dialog_einstellung_ganx);
    } // setupUi

    void retranslateUi(QDialog *Dialog_einstellung_ganx)
    {
        Dialog_einstellung_ganx->setWindowTitle(QApplication::translate("Dialog_einstellung_ganx", "Grundeinstellungen ganx", nullptr));
#ifndef QT_NO_TOOLTIP
        checkBox_bezugskantenmass->setToolTip(QApplication::translate("Dialog_einstellung_ganx", "<html><head/><body><p>Ist in der Maschinensteuerung die Option &quot;Vermessen&quot; aktiviert so werden alle Bearbeitungen gem\303\244\303\237 ihrer Bezugskante verschoben anhand der nun erfolgenden L\303\244ngenmessung des Werkst\303\274ckes.</p><p>Wird dieser Haken im Postprozessor nicht gesetzt so werden alle Bearbeitungen mit Absolutma\303\237 ausgegeben (Bezugskante Nullpunkt).</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        checkBox_bezugskantenmass->setText(QApplication::translate("Dialog_einstellung_ganx", "Bezugskanten anhand Referenzma\303\237 setzen", nullptr));
        pushButton_ok->setText(QApplication::translate("Dialog_einstellung_ganx", "Speichern", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("Dialog_einstellung_ganx", "Abbrechen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_einstellung_ganx: public Ui_Dialog_einstellung_ganx {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_EINSTELLUNG_GANX_H
