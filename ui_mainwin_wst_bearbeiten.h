/********************************************************************************
** Form generated from reading UI file 'mainwin_wst_bearbeiten.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIN_WST_BEARBEITEN_H
#define UI_MAINWIN_WST_BEARBEITEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWin_wst_bearbeiten
{
public:
    QAction *actionMakeBohrung;
    QAction *actionMakeRTA;
    QAction *actionMakeNut;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionEntf;
    QAction *actionKopieren;
    QAction *actionEinfuegen;
    QAction *actionVerschieben;
    QAction *actionBearbeiten;
    QAction *actionDoppelteil_erzeugen;
    QWidget *centralwidget;
    QListWidget *listWidget_prgtext;
    QLabel *label_xypos;
    QMenuBar *menubar;
    QMenu *menuHallo_Welt;
    QMenu *menuBearbeiten;
    QMenu *menuManipulation;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWin_wst_bearbeiten)
    {
        if (MainWin_wst_bearbeiten->objectName().isEmpty())
            MainWin_wst_bearbeiten->setObjectName(QStringLiteral("MainWin_wst_bearbeiten"));
        MainWin_wst_bearbeiten->resize(789, 518);
        actionMakeBohrung = new QAction(MainWin_wst_bearbeiten);
        actionMakeBohrung->setObjectName(QStringLiteral("actionMakeBohrung"));
        actionMakeRTA = new QAction(MainWin_wst_bearbeiten);
        actionMakeRTA->setObjectName(QStringLiteral("actionMakeRTA"));
        actionMakeNut = new QAction(MainWin_wst_bearbeiten);
        actionMakeNut->setObjectName(QStringLiteral("actionMakeNut"));
        actionUndo = new QAction(MainWin_wst_bearbeiten);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionRedo = new QAction(MainWin_wst_bearbeiten);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        actionEntf = new QAction(MainWin_wst_bearbeiten);
        actionEntf->setObjectName(QStringLiteral("actionEntf"));
        actionKopieren = new QAction(MainWin_wst_bearbeiten);
        actionKopieren->setObjectName(QStringLiteral("actionKopieren"));
        actionEinfuegen = new QAction(MainWin_wst_bearbeiten);
        actionEinfuegen->setObjectName(QStringLiteral("actionEinfuegen"));
        actionVerschieben = new QAction(MainWin_wst_bearbeiten);
        actionVerschieben->setObjectName(QStringLiteral("actionVerschieben"));
        actionBearbeiten = new QAction(MainWin_wst_bearbeiten);
        actionBearbeiten->setObjectName(QStringLiteral("actionBearbeiten"));
        actionDoppelteil_erzeugen = new QAction(MainWin_wst_bearbeiten);
        actionDoppelteil_erzeugen->setObjectName(QStringLiteral("actionDoppelteil_erzeugen"));
        centralwidget = new QWidget(MainWin_wst_bearbeiten);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        listWidget_prgtext = new QListWidget(centralwidget);
        listWidget_prgtext->setObjectName(QStringLiteral("listWidget_prgtext"));
        listWidget_prgtext->setGeometry(QRect(570, 10, 211, 361));
        listWidget_prgtext->setSelectionMode(QAbstractItemView::ExtendedSelection);
        label_xypos = new QLabel(centralwidget);
        label_xypos->setObjectName(QStringLiteral("label_xypos"));
        label_xypos->setGeometry(QRect(566, 450, 191, 20));
        label_xypos->setAlignment(Qt::AlignCenter);
        MainWin_wst_bearbeiten->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWin_wst_bearbeiten);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 789, 21));
        menuHallo_Welt = new QMenu(menubar);
        menuHallo_Welt->setObjectName(QStringLiteral("menuHallo_Welt"));
        menuBearbeiten = new QMenu(menubar);
        menuBearbeiten->setObjectName(QStringLiteral("menuBearbeiten"));
        menuManipulation = new QMenu(menubar);
        menuManipulation->setObjectName(QStringLiteral("menuManipulation"));
        MainWin_wst_bearbeiten->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWin_wst_bearbeiten);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWin_wst_bearbeiten->setStatusBar(statusbar);

        menubar->addAction(menuHallo_Welt->menuAction());
        menubar->addAction(menuBearbeiten->menuAction());
        menubar->addAction(menuManipulation->menuAction());
        menuHallo_Welt->addAction(actionMakeBohrung);
        menuHallo_Welt->addAction(actionMakeRTA);
        menuHallo_Welt->addAction(actionMakeNut);
        menuBearbeiten->addAction(actionBearbeiten);
        menuBearbeiten->addSeparator();
        menuBearbeiten->addAction(actionUndo);
        menuBearbeiten->addAction(actionRedo);
        menuBearbeiten->addSeparator();
        menuBearbeiten->addAction(actionEntf);
        menuBearbeiten->addAction(actionKopieren);
        menuBearbeiten->addAction(actionEinfuegen);
        menuManipulation->addAction(actionVerschieben);
        menuManipulation->addAction(actionDoppelteil_erzeugen);

        retranslateUi(MainWin_wst_bearbeiten);

        QMetaObject::connectSlotsByName(MainWin_wst_bearbeiten);
    } // setupUi

    void retranslateUi(QMainWindow *MainWin_wst_bearbeiten)
    {
        MainWin_wst_bearbeiten->setWindowTitle(QApplication::translate("MainWin_wst_bearbeiten", "MainWin_wst_bearbeiten", nullptr));
        actionMakeBohrung->setText(QApplication::translate("MainWin_wst_bearbeiten", "Bohrung", nullptr));
        actionMakeRTA->setText(QApplication::translate("MainWin_wst_bearbeiten", "Rechtecktasche", nullptr));
        actionMakeNut->setText(QApplication::translate("MainWin_wst_bearbeiten", "Nut", nullptr));
        actionUndo->setText(QApplication::translate("MainWin_wst_bearbeiten", "R\303\274ckg\303\244ngig", nullptr));
#ifndef QT_NO_SHORTCUT
        actionUndo->setShortcut(QApplication::translate("MainWin_wst_bearbeiten", "Ctrl+Z", nullptr));
#endif // QT_NO_SHORTCUT
        actionRedo->setText(QApplication::translate("MainWin_wst_bearbeiten", "Wiederholen", nullptr));
#ifndef QT_NO_SHORTCUT
        actionRedo->setShortcut(QApplication::translate("MainWin_wst_bearbeiten", "Ctrl+Y", nullptr));
#endif // QT_NO_SHORTCUT
        actionEntf->setText(QApplication::translate("MainWin_wst_bearbeiten", "Entfernen", nullptr));
#ifndef QT_NO_SHORTCUT
        actionEntf->setShortcut(QApplication::translate("MainWin_wst_bearbeiten", "Del", nullptr));
#endif // QT_NO_SHORTCUT
        actionKopieren->setText(QApplication::translate("MainWin_wst_bearbeiten", "Kopieren", nullptr));
#ifndef QT_NO_SHORTCUT
        actionKopieren->setShortcut(QApplication::translate("MainWin_wst_bearbeiten", "Ctrl+C", nullptr));
#endif // QT_NO_SHORTCUT
        actionEinfuegen->setText(QApplication::translate("MainWin_wst_bearbeiten", "Einf\303\274gen", nullptr));
#ifndef QT_NO_SHORTCUT
        actionEinfuegen->setShortcut(QApplication::translate("MainWin_wst_bearbeiten", "Ctrl+V", nullptr));
#endif // QT_NO_SHORTCUT
        actionVerschieben->setText(QApplication::translate("MainWin_wst_bearbeiten", "Verschieben", nullptr));
#ifndef QT_NO_SHORTCUT
        actionVerschieben->setShortcut(QApplication::translate("MainWin_wst_bearbeiten", "Ctrl+M", nullptr));
#endif // QT_NO_SHORTCUT
        actionBearbeiten->setText(QApplication::translate("MainWin_wst_bearbeiten", "Bearbeiten", nullptr));
#ifndef QT_NO_SHORTCUT
        actionBearbeiten->setShortcut(QApplication::translate("MainWin_wst_bearbeiten", "Return", nullptr));
#endif // QT_NO_SHORTCUT
        actionDoppelteil_erzeugen->setText(QApplication::translate("MainWin_wst_bearbeiten", "Doppelteil erzeugen", nullptr));
        label_xypos->setText(QApplication::translate("MainWin_wst_bearbeiten", "TextLabel", nullptr));
        menuHallo_Welt->setTitle(QApplication::translate("MainWin_wst_bearbeiten", "Einf\303\274gen", nullptr));
        menuBearbeiten->setTitle(QApplication::translate("MainWin_wst_bearbeiten", "Bearbeiten", nullptr));
        menuManipulation->setTitle(QApplication::translate("MainWin_wst_bearbeiten", "Manipulation", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWin_wst_bearbeiten: public Ui_MainWin_wst_bearbeiten {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIN_WST_BEARBEITEN_H
