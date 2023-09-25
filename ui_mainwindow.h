/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionWerkzeug_ganx_anzeigen;
    QAction *actionInfo;
    QAction *actionWerkzeug_fmc_anzeigen;
    QAction *actionStandard_Namen_anzeigen;
    QAction *actionWerkzeug_ggf_anzeigen;
    QAction *actionEinstellung_ganx;
    QAction *actionEinstellung_pfade;
    QAction *actionExportUebersicht;
    QAction *actionWST_ausblenden;
    QAction *actionEinstellung_dxf_klassen;
    QAction *actionEinstellung_dxf;
    QAction *actionWST_bearbeiten;
    QAction *actionEntwicklermodus;
    QAction *actionTestfunktion;
    QAction *actionEinstellung_fmc;
    QAction *actionWerkzeug_cix_anzeigen;
    QAction *actionWerkzeug_Postprozessor;
    QWidget *centralWidget;
    QScrollArea *scrollArea_einstellungen;
    QWidget *scrollAreaWidgetContents;
    QCheckBox *checkBox_quelldat_erhalt;
    QCheckBox *checkBox_std_namen_zuweisen;
    QFrame *line;
    QLabel *label_2;
    QFrame *line_2;
    QLabel *label_fkon_tiefe;
    QFrame *line_3;
    QCheckBox *checkBox_geraden;
    QLabel *label;
    QLineEdit *lineEdit_geraden_schwellenwert;
    QFrame *line_4;
    QCheckBox *checkBox_formatierung_aufbrechen;
    QCheckBox *checkBox_fkon_kantenschonend;
    QFrame *line_5;
    QLabel *label_3;
    QLineEdit *lineEdit_zugabe_gehr;
    QFrame *line_6;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QRadioButton *radioButton_drehung_0;
    QRadioButton *radioButton_drehung_270;
    QRadioButton *radioButton_drehung_autom;
    QRadioButton *radioButton_drehung_90;
    QRadioButton *radioButton_drehung_180;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton_fkon_ti_quell;
    QRadioButton *radioButton_fkon_ti_wkz;
    QTabWidget *tabWidget_main;
    QWidget *tab_quick;
    QPlainTextEdit *plainTextEdit_eldungen;
    QPushButton *pushButton_dateien_auflisten;
    QWidget *tab_detail;
    QPushButton *pushButton_import;
    QListWidget *listWidget_wste;
    QGroupBox *groupBox_vorschauformat;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButton_vorschau_fmc;
    QRadioButton *radioButton_vorschau_ganx;
    QRadioButton *radioButton_vorschau_cix;
    QRadioButton *radioButton_vorschau_ggf;
    QRadioButton *radioButton_vorschau_eigen;
    QLabel *label_projekt;
    QLabel *label_pos;
    QLabel *label_baugruppe;
    QLineEdit *lineEdit_projekt;
    QLineEdit *lineEdit_pos;
    QLineEdit *lineEdit_baugruppe;
    QLineEdit *lineEdit_projektpfad;
    QPushButton *pushButton_einzelexport;
    QPushButton *pushButton_umbenennen;
    QLabel *label_xypos;
    QLabel *label_warnungen;
    QLabel *label_wstmas;
    QMenuBar *menuBar;
    QMenu *menuWerkzeug;
    QMenu *menuExtras;
    QMenu *menuEinstellungen;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(896, 722);
        actionWerkzeug_ganx_anzeigen = new QAction(MainWindow);
        actionWerkzeug_ganx_anzeigen->setObjectName(QStringLiteral("actionWerkzeug_ganx_anzeigen"));
        actionInfo = new QAction(MainWindow);
        actionInfo->setObjectName(QStringLiteral("actionInfo"));
        actionWerkzeug_fmc_anzeigen = new QAction(MainWindow);
        actionWerkzeug_fmc_anzeigen->setObjectName(QStringLiteral("actionWerkzeug_fmc_anzeigen"));
        actionStandard_Namen_anzeigen = new QAction(MainWindow);
        actionStandard_Namen_anzeigen->setObjectName(QStringLiteral("actionStandard_Namen_anzeigen"));
        actionWerkzeug_ggf_anzeigen = new QAction(MainWindow);
        actionWerkzeug_ggf_anzeigen->setObjectName(QStringLiteral("actionWerkzeug_ggf_anzeigen"));
        actionEinstellung_ganx = new QAction(MainWindow);
        actionEinstellung_ganx->setObjectName(QStringLiteral("actionEinstellung_ganx"));
        actionEinstellung_pfade = new QAction(MainWindow);
        actionEinstellung_pfade->setObjectName(QStringLiteral("actionEinstellung_pfade"));
        actionExportUebersicht = new QAction(MainWindow);
        actionExportUebersicht->setObjectName(QStringLiteral("actionExportUebersicht"));
        actionWST_ausblenden = new QAction(MainWindow);
        actionWST_ausblenden->setObjectName(QStringLiteral("actionWST_ausblenden"));
        actionEinstellung_dxf_klassen = new QAction(MainWindow);
        actionEinstellung_dxf_klassen->setObjectName(QStringLiteral("actionEinstellung_dxf_klassen"));
        actionEinstellung_dxf = new QAction(MainWindow);
        actionEinstellung_dxf->setObjectName(QStringLiteral("actionEinstellung_dxf"));
        actionWST_bearbeiten = new QAction(MainWindow);
        actionWST_bearbeiten->setObjectName(QStringLiteral("actionWST_bearbeiten"));
        actionEntwicklermodus = new QAction(MainWindow);
        actionEntwicklermodus->setObjectName(QStringLiteral("actionEntwicklermodus"));
        actionEntwicklermodus->setCheckable(true);
        actionTestfunktion = new QAction(MainWindow);
        actionTestfunktion->setObjectName(QStringLiteral("actionTestfunktion"));
        actionEinstellung_fmc = new QAction(MainWindow);
        actionEinstellung_fmc->setObjectName(QStringLiteral("actionEinstellung_fmc"));
        actionWerkzeug_cix_anzeigen = new QAction(MainWindow);
        actionWerkzeug_cix_anzeigen->setObjectName(QStringLiteral("actionWerkzeug_cix_anzeigen"));
        actionWerkzeug_Postprozessor = new QAction(MainWindow);
        actionWerkzeug_Postprozessor->setObjectName(QStringLiteral("actionWerkzeug_Postprozessor"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        scrollArea_einstellungen = new QScrollArea(centralWidget);
        scrollArea_einstellungen->setObjectName(QStringLiteral("scrollArea_einstellungen"));
        scrollArea_einstellungen->setGeometry(QRect(10, 10, 191, 671));
        scrollArea_einstellungen->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea_einstellungen->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 189, 669));
        checkBox_quelldat_erhalt = new QCheckBox(scrollAreaWidgetContents);
        checkBox_quelldat_erhalt->setObjectName(QStringLiteral("checkBox_quelldat_erhalt"));
        checkBox_quelldat_erhalt->setGeometry(QRect(11, 11, 126, 17));
        checkBox_std_namen_zuweisen = new QCheckBox(scrollAreaWidgetContents);
        checkBox_std_namen_zuweisen->setObjectName(QStringLiteral("checkBox_std_namen_zuweisen"));
        checkBox_std_namen_zuweisen->setGeometry(QRect(11, 34, 128, 17));
        line = new QFrame(scrollAreaWidgetContents);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(11, 57, 161, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(11, 66, 101, 16));
        line_2 = new QFrame(scrollAreaWidgetContents);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(11, 156, 161, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_fkon_tiefe = new QLabel(scrollAreaWidgetContents);
        label_fkon_tiefe->setObjectName(QStringLiteral("label_fkon_tiefe"));
        label_fkon_tiefe->setGeometry(QRect(11, 165, 120, 16));
        line_3 = new QFrame(scrollAreaWidgetContents);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(11, 232, 161, 16));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        checkBox_geraden = new QCheckBox(scrollAreaWidgetContents);
        checkBox_geraden->setObjectName(QStringLiteral("checkBox_geraden"));
        checkBox_geraden->setGeometry(QRect(11, 241, 144, 17));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(11, 264, 73, 16));
        lineEdit_geraden_schwellenwert = new QLineEdit(scrollAreaWidgetContents);
        lineEdit_geraden_schwellenwert->setObjectName(QStringLiteral("lineEdit_geraden_schwellenwert"));
        lineEdit_geraden_schwellenwert->setGeometry(QRect(11, 283, 133, 20));
        line_4 = new QFrame(scrollAreaWidgetContents);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(11, 309, 161, 16));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        checkBox_formatierung_aufbrechen = new QCheckBox(scrollAreaWidgetContents);
        checkBox_formatierung_aufbrechen->setObjectName(QStringLiteral("checkBox_formatierung_aufbrechen"));
        checkBox_formatierung_aufbrechen->setGeometry(QRect(11, 318, 161, 17));
        checkBox_fkon_kantenschonend = new QCheckBox(scrollAreaWidgetContents);
        checkBox_fkon_kantenschonend->setObjectName(QStringLiteral("checkBox_fkon_kantenschonend"));
        checkBox_fkon_kantenschonend->setGeometry(QRect(11, 341, 156, 17));
        line_5 = new QFrame(scrollAreaWidgetContents);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(11, 364, 161, 16));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(11, 373, 96, 16));
        lineEdit_zugabe_gehr = new QLineEdit(scrollAreaWidgetContents);
        lineEdit_zugabe_gehr->setObjectName(QStringLiteral("lineEdit_zugabe_gehr"));
        lineEdit_zugabe_gehr->setGeometry(QRect(11, 392, 133, 20));
        line_6 = new QFrame(scrollAreaWidgetContents);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(11, 418, 161, 16));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        layoutWidget = new QWidget(scrollAreaWidgetContents);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 85, 141, 65));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        radioButton_drehung_0 = new QRadioButton(layoutWidget);
        radioButton_drehung_0->setObjectName(QStringLiteral("radioButton_drehung_0"));

        gridLayout->addWidget(radioButton_drehung_0, 0, 1, 1, 1);

        radioButton_drehung_270 = new QRadioButton(layoutWidget);
        radioButton_drehung_270->setObjectName(QStringLiteral("radioButton_drehung_270"));

        gridLayout->addWidget(radioButton_drehung_270, 1, 0, 1, 1);

        radioButton_drehung_autom = new QRadioButton(layoutWidget);
        radioButton_drehung_autom->setObjectName(QStringLiteral("radioButton_drehung_autom"));

        gridLayout->addWidget(radioButton_drehung_autom, 1, 1, 1, 1);

        radioButton_drehung_90 = new QRadioButton(layoutWidget);
        radioButton_drehung_90->setObjectName(QStringLiteral("radioButton_drehung_90"));

        gridLayout->addWidget(radioButton_drehung_90, 1, 2, 1, 1);

        radioButton_drehung_180 = new QRadioButton(layoutWidget);
        radioButton_drehung_180->setObjectName(QStringLiteral("radioButton_drehung_180"));

        gridLayout->addWidget(radioButton_drehung_180, 2, 1, 1, 1);

        layoutWidget1 = new QWidget(scrollAreaWidgetContents);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(11, 184, 148, 42));
        verticalLayout = new QVBoxLayout(layoutWidget1);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        radioButton_fkon_ti_quell = new QRadioButton(layoutWidget1);
        radioButton_fkon_ti_quell->setObjectName(QStringLiteral("radioButton_fkon_ti_quell"));

        verticalLayout->addWidget(radioButton_fkon_ti_quell);

        radioButton_fkon_ti_wkz = new QRadioButton(layoutWidget1);
        radioButton_fkon_ti_wkz->setObjectName(QStringLiteral("radioButton_fkon_ti_wkz"));

        verticalLayout->addWidget(radioButton_fkon_ti_wkz);

        scrollArea_einstellungen->setWidget(scrollAreaWidgetContents);
        tabWidget_main = new QTabWidget(centralWidget);
        tabWidget_main->setObjectName(QStringLiteral("tabWidget_main"));
        tabWidget_main->setGeometry(QRect(210, 10, 681, 671));
        tab_quick = new QWidget();
        tab_quick->setObjectName(QStringLiteral("tab_quick"));
        plainTextEdit_eldungen = new QPlainTextEdit(tab_quick);
        plainTextEdit_eldungen->setObjectName(QStringLiteral("plainTextEdit_eldungen"));
        plainTextEdit_eldungen->setGeometry(QRect(10, 10, 531, 501));
        plainTextEdit_eldungen->setLineWrapMode(QPlainTextEdit::NoWrap);
        plainTextEdit_eldungen->setReadOnly(true);
        pushButton_dateien_auflisten = new QPushButton(tab_quick);
        pushButton_dateien_auflisten->setObjectName(QStringLiteral("pushButton_dateien_auflisten"));
        pushButton_dateien_auflisten->setGeometry(QRect(570, 200, 89, 23));
        tabWidget_main->addTab(tab_quick, QString());
        tab_detail = new QWidget();
        tab_detail->setObjectName(QStringLiteral("tab_detail"));
        pushButton_import = new QPushButton(tab_detail);
        pushButton_import->setObjectName(QStringLiteral("pushButton_import"));
        pushButton_import->setGeometry(QRect(540, 10, 75, 23));
        listWidget_wste = new QListWidget(tab_detail);
        listWidget_wste->setObjectName(QStringLiteral("listWidget_wste"));
        listWidget_wste->setGeometry(QRect(525, 40, 141, 151));
        groupBox_vorschauformat = new QGroupBox(tab_detail);
        groupBox_vorschauformat->setObjectName(QStringLiteral("groupBox_vorschauformat"));
        groupBox_vorschauformat->setGeometry(QRect(530, 200, 131, 141));
        layoutWidget2 = new QWidget(groupBox_vorschauformat);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(20, 20, 84, 111));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        radioButton_vorschau_fmc = new QRadioButton(layoutWidget2);
        radioButton_vorschau_fmc->setObjectName(QStringLiteral("radioButton_vorschau_fmc"));

        verticalLayout_3->addWidget(radioButton_vorschau_fmc);

        radioButton_vorschau_ganx = new QRadioButton(layoutWidget2);
        radioButton_vorschau_ganx->setObjectName(QStringLiteral("radioButton_vorschau_ganx"));

        verticalLayout_3->addWidget(radioButton_vorschau_ganx);

        radioButton_vorschau_cix = new QRadioButton(layoutWidget2);
        radioButton_vorschau_cix->setObjectName(QStringLiteral("radioButton_vorschau_cix"));

        verticalLayout_3->addWidget(radioButton_vorschau_cix);

        radioButton_vorschau_ggf = new QRadioButton(layoutWidget2);
        radioButton_vorschau_ggf->setObjectName(QStringLiteral("radioButton_vorschau_ggf"));

        verticalLayout_3->addWidget(radioButton_vorschau_ggf);

        radioButton_vorschau_eigen = new QRadioButton(layoutWidget2);
        radioButton_vorschau_eigen->setObjectName(QStringLiteral("radioButton_vorschau_eigen"));

        verticalLayout_3->addWidget(radioButton_vorschau_eigen);

        label_projekt = new QLabel(tab_detail);
        label_projekt->setObjectName(QStringLiteral("label_projekt"));
        label_projekt->setGeometry(QRect(1, 1, 38, 16));
        label_pos = new QLabel(tab_detail);
        label_pos->setObjectName(QStringLiteral("label_pos"));
        label_pos->setGeometry(QRect(169, 1, 21, 16));
        label_baugruppe = new QLabel(tab_detail);
        label_baugruppe->setObjectName(QStringLiteral("label_baugruppe"));
        label_baugruppe->setGeometry(QRect(320, 1, 56, 16));
        lineEdit_projekt = new QLineEdit(tab_detail);
        lineEdit_projekt->setObjectName(QStringLiteral("lineEdit_projekt"));
        lineEdit_projekt->setGeometry(QRect(45, 1, 118, 20));
        lineEdit_pos = new QLineEdit(tab_detail);
        lineEdit_pos->setObjectName(QStringLiteral("lineEdit_pos"));
        lineEdit_pos->setGeometry(QRect(196, 1, 118, 20));
        lineEdit_baugruppe = new QLineEdit(tab_detail);
        lineEdit_baugruppe->setObjectName(QStringLiteral("lineEdit_baugruppe"));
        lineEdit_baugruppe->setGeometry(QRect(382, 1, 118, 20));
        lineEdit_projektpfad = new QLineEdit(tab_detail);
        lineEdit_projektpfad->setObjectName(QStringLiteral("lineEdit_projektpfad"));
        lineEdit_projektpfad->setGeometry(QRect(45, 27, 451, 20));
        pushButton_einzelexport = new QPushButton(tab_detail);
        pushButton_einzelexport->setObjectName(QStringLiteral("pushButton_einzelexport"));
        pushButton_einzelexport->setGeometry(QRect(550, 350, 111, 23));
        pushButton_umbenennen = new QPushButton(tab_detail);
        pushButton_umbenennen->setObjectName(QStringLiteral("pushButton_umbenennen"));
        pushButton_umbenennen->setGeometry(QRect(550, 380, 111, 23));
        label_xypos = new QLabel(tab_detail);
        label_xypos->setObjectName(QStringLiteral("label_xypos"));
        label_xypos->setGeometry(QRect(560, 410, 91, 16));
        label_xypos->setLayoutDirection(Qt::LeftToRight);
        label_xypos->setAlignment(Qt::AlignCenter);
        label_warnungen = new QLabel(tab_detail);
        label_warnungen->setObjectName(QStringLiteral("label_warnungen"));
        label_warnungen->setGeometry(QRect(20, 60, 121, 16));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_warnungen->setFont(font);
        label_warnungen->setFrameShape(QFrame::NoFrame);
        label_warnungen->setAlignment(Qt::AlignCenter);
        label_wstmas = new QLabel(tab_detail);
        label_wstmas->setObjectName(QStringLiteral("label_wstmas"));
        label_wstmas->setGeometry(QRect(550, 430, 111, 20));
        label_wstmas->setAlignment(Qt::AlignCenter);
        tabWidget_main->addTab(tab_detail, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 896, 21));
        menuWerkzeug = new QMenu(menuBar);
        menuWerkzeug->setObjectName(QStringLiteral("menuWerkzeug"));
        menuExtras = new QMenu(menuBar);
        menuExtras->setObjectName(QStringLiteral("menuExtras"));
        menuEinstellungen = new QMenu(menuBar);
        menuEinstellungen->setObjectName(QStringLiteral("menuEinstellungen"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuWerkzeug->menuAction());
        menuBar->addAction(menuEinstellungen->menuAction());
        menuBar->addAction(menuExtras->menuAction());
        menuWerkzeug->addAction(actionWerkzeug_Postprozessor);
        menuWerkzeug->addAction(actionWerkzeug_ganx_anzeigen);
        menuWerkzeug->addAction(actionWerkzeug_fmc_anzeigen);
        menuWerkzeug->addAction(actionWerkzeug_ggf_anzeigen);
        menuWerkzeug->addAction(actionWerkzeug_cix_anzeigen);
        menuExtras->addAction(actionInfo);
        menuExtras->addAction(actionExportUebersicht);
        menuExtras->addAction(actionWST_ausblenden);
        menuExtras->addAction(actionWST_bearbeiten);
        menuExtras->addSeparator();
        menuExtras->addAction(actionTestfunktion);
        menuEinstellungen->addAction(actionEntwicklermodus);
        menuEinstellungen->addAction(actionEinstellung_pfade);
        menuEinstellungen->addAction(actionStandard_Namen_anzeigen);
        menuEinstellungen->addAction(actionEinstellung_fmc);
        menuEinstellungen->addAction(actionEinstellung_ganx);
        menuEinstellungen->addAction(actionEinstellung_dxf);
        menuEinstellungen->addAction(actionEinstellung_dxf_klassen);

        retranslateUi(MainWindow);

        tabWidget_main->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Postprozessor", nullptr));
        actionWerkzeug_ganx_anzeigen->setText(QApplication::translate("MainWindow", "Werkzeug ganx bearbeiten", nullptr));
        actionInfo->setText(QApplication::translate("MainWindow", "Info", nullptr));
        actionWerkzeug_fmc_anzeigen->setText(QApplication::translate("MainWindow", "Werkzeug fmc bearbeiten", nullptr));
        actionStandard_Namen_anzeigen->setText(QApplication::translate("MainWindow", "Standard-Namen", nullptr));
        actionWerkzeug_ggf_anzeigen->setText(QApplication::translate("MainWindow", "Werkzeug ggf bearbeiten", nullptr));
        actionEinstellung_ganx->setText(QApplication::translate("MainWindow", "GANX-Grundeinstellung", nullptr));
        actionEinstellung_pfade->setText(QApplication::translate("MainWindow", "Pfade", nullptr));
        actionExportUebersicht->setText(QApplication::translate("MainWindow", "Export\303\274bersicht", nullptr));
#ifndef QT_NO_SHORTCUT
        actionExportUebersicht->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", nullptr));
#endif // QT_NO_SHORTCUT
        actionWST_ausblenden->setText(QApplication::translate("MainWindow", "WST ausblenden", nullptr));
#ifndef QT_NO_SHORTCUT
        actionWST_ausblenden->setShortcut(QApplication::translate("MainWindow", "Del", nullptr));
#endif // QT_NO_SHORTCUT
        actionEinstellung_dxf_klassen->setText(QApplication::translate("MainWindow", "DXF-Klasseneinstellung", nullptr));
        actionEinstellung_dxf->setText(QApplication::translate("MainWindow", "DXF-Grundeinstellungen", nullptr));
        actionWST_bearbeiten->setText(QApplication::translate("MainWindow", "WST bearbeiten", nullptr));
#ifndef QT_NO_SHORTCUT
        actionWST_bearbeiten->setShortcut(QApplication::translate("MainWindow", "F3", nullptr));
#endif // QT_NO_SHORTCUT
        actionEntwicklermodus->setText(QApplication::translate("MainWindow", "Entwicklermodus", nullptr));
        actionTestfunktion->setText(QApplication::translate("MainWindow", "Testfunktion", nullptr));
        actionEinstellung_fmc->setText(QApplication::translate("MainWindow", "FMC-Grundeinstellung", nullptr));
        actionWerkzeug_cix_anzeigen->setText(QApplication::translate("MainWindow", "Werkzeug cix bearbeiten", nullptr));
        actionWerkzeug_Postprozessor->setText(QApplication::translate("MainWindow", "Werkzeug Postprozessor", nullptr));
#ifndef QT_NO_TOOLTIP
        checkBox_quelldat_erhalt->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Die Quelldateien werden beim Import in den Postprozessor nicht gel\303\266scht</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        checkBox_quelldat_erhalt->setText(QApplication::translate("MainWindow", "Quelldateien erhalten", nullptr));
#ifndef QT_NO_TOOLTIP
        checkBox_std_namen_zuweisen->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Die importierten Dateien werden mit ver\303\244nderten Dateinamen exportiert. Die vorangestellte Schranknummer wird wenn m\303\266glich entfernt.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        checkBox_std_namen_zuweisen->setText(QApplication::translate("MainWindow", "Standard-Dateinamen", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Drehung der Bauteile", nullptr));
        label_fkon_tiefe->setText(QApplication::translate("MainWindow", "Tiefe der Fraeskonturen:", nullptr));
        checkBox_geraden->setText(QApplication::translate("MainWindow", "kurze Geraden ignorieren", nullptr));
        label->setText(QApplication::translate("MainWindow", "Schwellenwert:", nullptr));
        checkBox_formatierung_aufbrechen->setText(QApplication::translate("MainWindow", "Formartierungen aufbrechen", nullptr));
        checkBox_fkon_kantenschonend->setText(QApplication::translate("MainWindow", "Fr\303\244sungen kantenschonend", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Zugabe Gehrungen:", nullptr));
#ifndef QT_NO_TOOLTIP
        lineEdit_zugabe_gehr->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Es wird keine keine Zugabe gegeben wenn die Gehrung bekantet ist</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        radioButton_drehung_0->setToolTip(QApplication::translate("MainWindow", "8", nullptr));
#endif // QT_NO_TOOLTIP
        radioButton_drehung_0->setText(QApplication::translate("MainWindow", "0", nullptr));
#ifndef QT_NO_SHORTCUT
        radioButton_drehung_0->setShortcut(QApplication::translate("MainWindow", "8", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        radioButton_drehung_270->setToolTip(QApplication::translate("MainWindow", "4", nullptr));
#endif // QT_NO_TOOLTIP
        radioButton_drehung_270->setText(QApplication::translate("MainWindow", "270", nullptr));
#ifndef QT_NO_SHORTCUT
        radioButton_drehung_270->setShortcut(QApplication::translate("MainWindow", "4", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        radioButton_drehung_autom->setToolTip(QApplication::translate("MainWindow", "0", nullptr));
#endif // QT_NO_TOOLTIP
        radioButton_drehung_autom->setText(QApplication::translate("MainWindow", "AUTO", nullptr));
#ifndef QT_NO_SHORTCUT
        radioButton_drehung_autom->setShortcut(QApplication::translate("MainWindow", "5", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        radioButton_drehung_90->setToolTip(QApplication::translate("MainWindow", "6", nullptr));
#endif // QT_NO_TOOLTIP
        radioButton_drehung_90->setText(QApplication::translate("MainWindow", "90", nullptr));
#ifndef QT_NO_SHORTCUT
        radioButton_drehung_90->setShortcut(QApplication::translate("MainWindow", "6", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        radioButton_drehung_180->setToolTip(QApplication::translate("MainWindow", "2", nullptr));
#endif // QT_NO_TOOLTIP
        radioButton_drehung_180->setText(QApplication::translate("MainWindow", "180", nullptr));
#ifndef QT_NO_SHORTCUT
        radioButton_drehung_180->setShortcut(QApplication::translate("MainWindow", "2", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        radioButton_fkon_ti_quell->setToolTip(QApplication::translate("MainWindow", "Tiefe der Fr\303\244skontur bleibt unver\303\244ndert, so wie in der Quelldatei angegeben, erhalten", nullptr));
#endif // QT_NO_TOOLTIP
        radioButton_fkon_ti_quell->setText(QApplication::translate("MainWindow", "gem Quelldatei", nullptr));
#ifndef QT_NO_TOOLTIP
        radioButton_fkon_ti_wkz->setToolTip(QApplication::translate("MainWindow", "ggf. wird die Fr\303\244sbahn mehrfach ausgegeben mit unterschiedlichen Zustelltiefen, bis die Gesamttiefe erreicht ist", nullptr));
#endif // QT_NO_TOOLTIP
        radioButton_fkon_ti_wkz->setText(QApplication::translate("MainWindow", "gem Zustellung Werkzeug", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButton_dateien_auflisten->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Listet die im Importverzeichnis gefundenen Dateien auf.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        pushButton_dateien_auflisten->setText(QApplication::translate("MainWindow", "Dateien auflisten", nullptr));
        tabWidget_main->setTabText(tabWidget_main->indexOf(tab_quick), QApplication::translate("MainWindow", "Info", nullptr));
#ifndef QT_NO_TOOLTIP
        pushButton_import->setToolTip(QApplication::translate("MainWindow", "I", nullptr));
#endif // QT_NO_TOOLTIP
        pushButton_import->setText(QApplication::translate("MainWindow", "importieren", nullptr));
#ifndef QT_NO_SHORTCUT
        pushButton_import->setShortcut(QApplication::translate("MainWindow", "I", nullptr));
#endif // QT_NO_SHORTCUT
        groupBox_vorschauformat->setTitle(QApplication::translate("MainWindow", "Vorschau anzeigen f\303\274r:", nullptr));
#ifndef QT_NO_TOOLTIP
        radioButton_vorschau_fmc->setToolTip(QApplication::translate("MainWindow", "Strg+F", nullptr));
#endif // QT_NO_TOOLTIP
        radioButton_vorschau_fmc->setText(QApplication::translate("MainWindow", "fmc", nullptr));
#ifndef QT_NO_SHORTCUT
        radioButton_vorschau_fmc->setShortcut(QApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        radioButton_vorschau_ganx->setToolTip(QApplication::translate("MainWindow", "Strg+G", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        radioButton_vorschau_ganx->setStatusTip(QApplication::translate("MainWindow", "Strg+G", nullptr));
#endif // QT_NO_STATUSTIP
        radioButton_vorschau_ganx->setText(QApplication::translate("MainWindow", "ganx", nullptr));
#ifndef QT_NO_SHORTCUT
        radioButton_vorschau_ganx->setShortcut(QApplication::translate("MainWindow", "Ctrl+G", nullptr));
#endif // QT_NO_SHORTCUT
        radioButton_vorschau_cix->setText(QApplication::translate("MainWindow", "cix", nullptr));
        radioButton_vorschau_ggf->setText(QApplication::translate("MainWindow", "ggf", nullptr));
        radioButton_vorschau_eigen->setText(QApplication::translate("MainWindow", "eigen", nullptr));
        label_projekt->setText(QApplication::translate("MainWindow", "Projekt:", nullptr));
        label_pos->setText(QApplication::translate("MainWindow", "Pos:", nullptr));
        label_baugruppe->setText(QApplication::translate("MainWindow", "Baugruppe:", nullptr));
#ifndef QT_NO_TOOLTIP
        lineEdit_projektpfad->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Hintergrundfarben:</p><p>wei\303\237: Ordner oder Datei existieren nicht</p><p>gelb: Ordner existiert bereits</p><p>gr\303\274n: CNC-Programm existiert bereits, hinter dem Dateipfad wird Datum der letzten \303\204nderung angezeigt</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        pushButton_einzelexport->setToolTip(QApplication::translate("MainWindow", "E", nullptr));
#endif // QT_NO_TOOLTIP
        pushButton_einzelexport->setText(QApplication::translate("MainWindow", "exportieren", nullptr));
#ifndef QT_NO_SHORTCUT
        pushButton_einzelexport->setShortcut(QApplication::translate("MainWindow", "E", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        pushButton_umbenennen->setToolTip(QApplication::translate("MainWindow", "F2", nullptr));
#endif // QT_NO_TOOLTIP
        pushButton_umbenennen->setText(QApplication::translate("MainWindow", "umbenennen", nullptr));
#ifndef QT_NO_SHORTCUT
        pushButton_umbenennen->setShortcut(QApplication::translate("MainWindow", "F2", nullptr));
#endif // QT_NO_SHORTCUT
        label_xypos->setText(QApplication::translate("MainWindow", "X: / Y:", nullptr));
        label_warnungen->setText(QApplication::translate("MainWindow", "Warnungen", nullptr));
        label_wstmas->setText(QApplication::translate("MainWindow", "L x B x D", nullptr));
        tabWidget_main->setTabText(tabWidget_main->indexOf(tab_detail), QApplication::translate("MainWindow", "Export", nullptr));
        menuWerkzeug->setTitle(QApplication::translate("MainWindow", "Werkzeug", nullptr));
        menuExtras->setTitle(QApplication::translate("MainWindow", "Extras", nullptr));
        menuEinstellungen->setTitle(QApplication::translate("MainWindow", "Einstellungen", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
