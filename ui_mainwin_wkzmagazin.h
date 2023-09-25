/********************************************************************************
** Form generated from reading UI file 'mainwin_wkzmagazin.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIN_WKZMAGAZIN_H
#define UI_MAINWIN_WKZMAGAZIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mainwin_wkzmagazin
{
public:
    QAction *actionFraeser_anlegen;
    QAction *actionBohrer_anlegen;
    QAction *actionSaege_anlegen;
    QAction *actionHoch;
    QAction *actionRunter;
    QAction *actionL_schen;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionDuplizieren;
    QWidget *centralwidget;
    QListWidget *listWidget;
    QPushButton *pushButton_speichern;
    QPushButton *pushButton_abbrechen;
    QTableWidget *tableWidget_info;
    QMenuBar *menubar;
    QMenu *menuneues_Werkzeug;
    QMenu *menuBearbeiten;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *mainwin_wkzmagazin)
    {
        if (mainwin_wkzmagazin->objectName().isEmpty())
            mainwin_wkzmagazin->setObjectName(QStringLiteral("mainwin_wkzmagazin"));
        mainwin_wkzmagazin->resize(590, 642);
        actionFraeser_anlegen = new QAction(mainwin_wkzmagazin);
        actionFraeser_anlegen->setObjectName(QStringLiteral("actionFraeser_anlegen"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/toolbaricons/toolbaricons/Fraese 100x100.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFraeser_anlegen->setIcon(icon);
        actionBohrer_anlegen = new QAction(mainwin_wkzmagazin);
        actionBohrer_anlegen->setObjectName(QStringLiteral("actionBohrer_anlegen"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/new/toolbaricons/toolbaricons/drill.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionBohrer_anlegen->setIcon(icon1);
        actionSaege_anlegen = new QAction(mainwin_wkzmagazin);
        actionSaege_anlegen->setObjectName(QStringLiteral("actionSaege_anlegen"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/new/toolbaricons/toolbaricons/saw.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSaege_anlegen->setIcon(icon2);
        actionHoch = new QAction(mainwin_wkzmagazin);
        actionHoch->setObjectName(QStringLiteral("actionHoch"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/new/toolbaricons/toolbaricons/up.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHoch->setIcon(icon3);
        actionRunter = new QAction(mainwin_wkzmagazin);
        actionRunter->setObjectName(QStringLiteral("actionRunter"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/new/toolbaricons/toolbaricons/down.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRunter->setIcon(icon4);
        actionL_schen = new QAction(mainwin_wkzmagazin);
        actionL_schen->setObjectName(QStringLiteral("actionL_schen"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/new/toolbaricons/toolbaricons/trash.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionL_schen->setIcon(icon5);
        actionUndo = new QAction(mainwin_wkzmagazin);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/new/toolbaricons/toolbaricons/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon6);
        actionRedo = new QAction(mainwin_wkzmagazin);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/new/toolbaricons/toolbaricons/redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon7);
        actionDuplizieren = new QAction(mainwin_wkzmagazin);
        actionDuplizieren->setObjectName(QStringLiteral("actionDuplizieren"));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/new/toolbaricons/toolbaricons/kopieren.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDuplizieren->setIcon(icon8);
        centralwidget = new QWidget(mainwin_wkzmagazin);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(10, 10, 256, 541));
        pushButton_speichern = new QPushButton(centralwidget);
        pushButton_speichern->setObjectName(QStringLiteral("pushButton_speichern"));
        pushButton_speichern->setGeometry(QRect(350, 520, 75, 23));
        pushButton_abbrechen = new QPushButton(centralwidget);
        pushButton_abbrechen->setObjectName(QStringLiteral("pushButton_abbrechen"));
        pushButton_abbrechen->setGeometry(QRect(440, 520, 75, 23));
        tableWidget_info = new QTableWidget(centralwidget);
        tableWidget_info->setObjectName(QStringLiteral("tableWidget_info"));
        tableWidget_info->setEnabled(false);
        tableWidget_info->setGeometry(QRect(270, 320, 301, 192));
        tableWidget_info->horizontalHeader()->setVisible(false);
        tableWidget_info->verticalHeader()->setVisible(false);
        mainwin_wkzmagazin->setCentralWidget(centralwidget);
        menubar = new QMenuBar(mainwin_wkzmagazin);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 590, 21));
        menuneues_Werkzeug = new QMenu(menubar);
        menuneues_Werkzeug->setObjectName(QStringLiteral("menuneues_Werkzeug"));
        menuBearbeiten = new QMenu(menubar);
        menuBearbeiten->setObjectName(QStringLiteral("menuBearbeiten"));
        mainwin_wkzmagazin->setMenuBar(menubar);
        statusbar = new QStatusBar(mainwin_wkzmagazin);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        mainwin_wkzmagazin->setStatusBar(statusbar);
        toolBar = new QToolBar(mainwin_wkzmagazin);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setMovable(false);
        toolBar->setIconSize(QSize(35, 35));
        mainwin_wkzmagazin->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuneues_Werkzeug->menuAction());
        menubar->addAction(menuBearbeiten->menuAction());
        menuneues_Werkzeug->addAction(actionFraeser_anlegen);
        menuneues_Werkzeug->addAction(actionBohrer_anlegen);
        menuneues_Werkzeug->addAction(actionSaege_anlegen);
        menuBearbeiten->addAction(actionUndo);
        menuBearbeiten->addAction(actionRedo);
        menuBearbeiten->addSeparator();
        menuBearbeiten->addAction(actionHoch);
        menuBearbeiten->addAction(actionRunter);
        menuBearbeiten->addSeparator();
        menuBearbeiten->addAction(actionL_schen);
        menuBearbeiten->addSeparator();
        menuBearbeiten->addAction(actionDuplizieren);
        toolBar->addAction(actionHoch);
        toolBar->addAction(actionRunter);
        toolBar->addSeparator();
        toolBar->addAction(actionDuplizieren);
        toolBar->addSeparator();
        toolBar->addAction(actionL_schen);
        toolBar->addSeparator();
        toolBar->addAction(actionFraeser_anlegen);
        toolBar->addAction(actionBohrer_anlegen);
        toolBar->addAction(actionSaege_anlegen);
        toolBar->addSeparator();
        toolBar->addAction(actionUndo);
        toolBar->addAction(actionRedo);

        retranslateUi(mainwin_wkzmagazin);

        QMetaObject::connectSlotsByName(mainwin_wkzmagazin);
    } // setupUi

    void retranslateUi(QMainWindow *mainwin_wkzmagazin)
    {
        mainwin_wkzmagazin->setWindowTitle(QApplication::translate("mainwin_wkzmagazin", "mainwin_wkzmagazin", nullptr));
        actionFraeser_anlegen->setText(QApplication::translate("mainwin_wkzmagazin", "Fr\303\244ser anlegen", nullptr));
        actionBohrer_anlegen->setText(QApplication::translate("mainwin_wkzmagazin", "Bohrer anlegen", nullptr));
        actionSaege_anlegen->setText(QApplication::translate("mainwin_wkzmagazin", "S\303\244ge anlegen", nullptr));
        actionHoch->setText(QApplication::translate("mainwin_wkzmagazin", "Hoch", nullptr));
        actionRunter->setText(QApplication::translate("mainwin_wkzmagazin", "Runter", nullptr));
        actionL_schen->setText(QApplication::translate("mainwin_wkzmagazin", "L\303\266schen", nullptr));
#ifndef QT_NO_SHORTCUT
        actionL_schen->setShortcut(QApplication::translate("mainwin_wkzmagazin", "Del", nullptr));
#endif // QT_NO_SHORTCUT
        actionUndo->setText(QApplication::translate("mainwin_wkzmagazin", "R\303\274ckg\303\244ngig", nullptr));
#ifndef QT_NO_SHORTCUT
        actionUndo->setShortcut(QApplication::translate("mainwin_wkzmagazin", "Ctrl+Z", nullptr));
#endif // QT_NO_SHORTCUT
        actionRedo->setText(QApplication::translate("mainwin_wkzmagazin", "Wiederholen", nullptr));
#ifndef QT_NO_SHORTCUT
        actionRedo->setShortcut(QApplication::translate("mainwin_wkzmagazin", "Ctrl+Y", nullptr));
#endif // QT_NO_SHORTCUT
        actionDuplizieren->setText(QApplication::translate("mainwin_wkzmagazin", "Duplizieren", nullptr));
        pushButton_speichern->setText(QApplication::translate("mainwin_wkzmagazin", "Speichern", nullptr));
        pushButton_abbrechen->setText(QApplication::translate("mainwin_wkzmagazin", "Abbrechen", nullptr));
        menuneues_Werkzeug->setTitle(QApplication::translate("mainwin_wkzmagazin", "neues Werkzeug", nullptr));
        menuBearbeiten->setTitle(QApplication::translate("mainwin_wkzmagazin", "Bearbeiten", nullptr));
        toolBar->setWindowTitle(QApplication::translate("mainwin_wkzmagazin", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class mainwin_wkzmagazin: public Ui_mainwin_wkzmagazin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIN_WKZMAGAZIN_H
