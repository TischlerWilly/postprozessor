#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pf.ordner_erstellen();
    tz = QDir::separator(); //Systemspezifischer Separator (Linux: Ordner/Unterordner/...)
    setup();
    set_prginfo();

    connect(this, SIGNAL(sendDialogDataWKZ(QString,text_zeilenweise)), \
            &dlg_wkz, SLOT(getDialogDataWKZ(QString,text_zeilenweise)) );
    connect(&dlg_wkz, SIGNAL(sendData_wkzmagazin(QString,text_zeilenweise)), \
            this, SLOT(getDialogDataWKZ(QString,text_zeilenweise))     );
    connect(this, SIGNAL(sendStdNamen(text_zeilenweise, text_zeilenweise)),\
            &dlg_stdnamen, SLOT(slot_setup(text_zeilenweise,text_zeilenweise)));
    connect(&dlg_stdnamen, SIGNAL(signal_sendData(text_zeilenweise,text_zeilenweise)),\
            this, SLOT(getStdNamen(text_zeilenweise,text_zeilenweise)));
    connect(this, SIGNAL(sendEinstellungPfade(einstellung)),\
            &dlg_Einstellung_pfade, SLOT(slot_einstellungen(einstellung)));
    connect(&dlg_Einstellung_pfade, SIGNAL(send_einstellungen(einstellung)),\
            this, SLOT(getEinstellung(einstellung)));
    connect(this, SIGNAL(sendEinstellungGANX(einstellung_ganx)),\
            &dlg_einstellung_ganx, SLOT(slot_einstellung(einstellung_ganx)));
    connect(&dlg_einstellung_ganx, SIGNAL(send_einstellung(einstellung_ganx)),\
            this, SLOT(getEinstellungGANX(einstellung_ganx )));
    connect(this, SIGNAL(sendEinstellungDxf(einstellung_dxf)),\
            &dlg_einstellung_dxf, SLOT(slot_einstellung(einstellung_dxf)));
    connect(&dlg_einstellung_dxf, SIGNAL(send_einstellung(einstellung_dxf)),\
            this, SLOT(getEinstellungDxf(einstellung_dxf )));
    connect(this, SIGNAL(sendEinstellungDxfKlassen(einstellung_dxf, einstellung_dxf_klassen)),\
            &dlg_einstellung_dxf_klassen, SLOT(slot_einstellung(einstellung_dxf, einstellung_dxf_klassen)));
    connect(&dlg_einstellung_dxf_klassen, SIGNAL(send_einstellung(einstellung_dxf_klassen)),\
            this, SLOT(getEinstellungDxfKlassen(einstellung_dxf_klassen )));
    connect(this, SIGNAL(sendVorschauAktualisieren(werkstueck,int)),\
            &vorschaufenster, SLOT(slot_aktualisieren(werkstueck,int)));
    connect(&dlg_prgtext, SIGNAL(signalIndexChange(int)),\
            &vorschaufenster, SLOT(slot_aktives_Element_einfaerben(int)));
    connect(&vorschaufenster, SIGNAL(sende_zeilennummer(uint, bool)),\
            &dlg_prgtext, SLOT(slot_zeilennummer(uint, bool)));
    connect(&vorschaufenster, SIGNAL(sende_maus_pos(QPoint)),\
             this, SLOT(getMausPosXY(QPoint)));
    connect(&vorschaufenster, SIGNAL(sende_wstmas(double,double,double)),\
             this, SLOT(getWSTMas(double,double,double)));
    connect(&vorschaufenster, SIGNAL(sende_drewi(QString)),\
             this, SLOT(getDrewi(QString)));
    connect(this, SIGNAL(sendProgrammtext(werkstueck*)),\
            &dlg_prgtext, SLOT(slot_wst(werkstueck*)));
    connect(this, SIGNAL(signal_exporte(text_zeilenweise)),\
            &dlg_exporte, SLOT(slot_wstnamen(text_zeilenweise)));
    connect(this, SIGNAL(signal_wstexport(QString,QString,bool)),\
            &dlg_exporte, SLOT(slot_wstexport(QString,QString,bool)));
    connect(this, SIGNAL(signal_wst_umbenennen(QString,QString)),\
            &dlg_exporte, SLOT(slot_wst_umbenennen(QString,QString)));
    connect(this, SIGNAL(signal_wst_ausblenden(QString,bool)),\
            &dlg_exporte, SLOT(slot_wst_ausblenden(QString,bool)));
    connect(&dlg_prgtext, SIGNAL(signalWstChanged(werkstueck*,int)),\
            this, SLOT(slotWstChanged(werkstueck*,int)));

    this->setWindowState(Qt::WindowMaximized);
    ui->lineEdit_projekt->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup()
{
    Projektpfad_stimmt = false;
    //Schauen ob alle Konfigurationsdateien vorhanden sind:
    bool inifile_gefunden           = false;    //user-Ordner
    bool wkz_ganx_gefunden          = false;    //user-Ordner
    bool wkz_fmc_gefunden           = false;    //user-Ordner
    bool wkz_ggf_gefunden           = false;    //user-Ordner
    bool namen_std_gefunden         = false;    //user-Ordner
    bool ini_ganx_gefunden          = false;    //user-Ordner
    bool ini_dxf_gefunden           = false;    //user-Ordner
    bool ini_dxf_klassen_gefunden   = false;    //user-Ordner
    QDir user_ordner(pf.path_user());
    QStringList ordnerinhalt;
    ordnerinhalt = user_ordner.entryList(QDir::Files);
    for(QStringList::iterator it = ordnerinhalt.begin() ; it!=ordnerinhalt.end() ; ++it)
    {
        QString name = *it;
        if(name.contains(pf.name_inifile()))
        {
            inifile_gefunden = true;
        }
        if(name.contains(pf.name_wkz_ganx()))
        {
            wkz_ganx_gefunden = true;
        }
        if(name.contains(pf.name_wkz_fmc()))
        {
            wkz_fmc_gefunden = true;
        }
        if(name.contains(pf.name_wkz_ggf()))
        {
            wkz_ggf_gefunden = true;
        }
        if(name.contains(pf.name_stdNamen()))
        {
            namen_std_gefunden = true;
        }
        if(name.contains(pf.name_ini_ganx()))
        {
            ini_ganx_gefunden = true;
        }
        if(name.contains(pf.name_ini_dxf()))
        {
            ini_dxf_gefunden = true;
        }
        if(name.contains(pf.name_ini_dxf_klassen()))
        {
            ini_dxf_klassen_gefunden = true;
        }
    }

    //Einstellungen aus Konfigurationsdateien übernehmen wo möglich:
    if(inifile_gefunden == false)
    {
        QFile file(pf.path_inifile());
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_inifile();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            file.write(Einstellung.text().toLatin1());
        }
        file.close();
    }else
    {
        QFile file(pf.path_inifile());
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_inifile();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            Einstellung.set_text(file.readAll());
            ui->actionEntwicklermodus->setChecked(Einstellung.entwicklermodus());
            ui->checkBox_quelldat_erhalt->setChecked(Einstellung.quelldateien_erhalten());
            ui->checkBox_std_namen_zuweisen->setChecked(Einstellung.std_dateinamen_verwenden());
            QString drehung = Einstellung.drehung_wst();
            if(drehung == "0")
            {
                ui->radioButton_drehung_0->setChecked(true);
            }else if(drehung == "90")
            {
                ui->radioButton_drehung_90->setChecked(true);
            }else if(drehung == "180")
            {
                ui->radioButton_drehung_180->setChecked(true);
            }else if(drehung == "270")
            {
                ui->radioButton_drehung_270->setChecked(true);
            }else
            {
                ui->radioButton_drehung_autom->setChecked(true);
            }
            if(Einstellung.tiefeneinst_fkon() == "orgi")
            {
                ui->radioButton_fkon_ti_quell->setChecked(true);
            }else
            {
                ui->radioButton_fkon_ti_wkz->setChecked(true);
            }
            ui->checkBox_geraden->setChecked(!Einstellung.kurze_geraden_importieren());
            ui->lineEdit_geraden_schwellenwert->setText(double_to_qstring(Einstellung.geraden_schwellwert()));
            ui->checkBox_formatierung_aufbrechen->setChecked(Einstellung.formartierungen_aufbrechen());
            ui->checkBox_fkon_kantenschonend->setChecked(Einstellung.fkon_kantenschonend());
            ui->lineEdit_zugabe_gehr->setText(double_to_qstring(Einstellung.gehrungen_zugabe()));
        }
        file.close();
    }

    if(namen_std_gefunden == false)
    {
        QFile file(pf.path_stdNamen());
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_stdNamen();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            file.write("Namen original");
            file.write(NAMEN_STD_INI_TZ_);
            file.write("Namen neu");
            namen_std_vor.zeile_anhaengen("Namen original");
            namen_std_nach.zeile_anhaengen("Namen neu");
        }
        file.close();
    }else
    {
        QFile file(pf.path_stdNamen());
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_stdNamen();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            while(!file.atEnd())
            {
                QString zeile = QLatin1String(  file.readLine()  );
                namen_std_vor.zeile_anhaengen(text_links(zeile,NAMEN_STD_INI_TZ_));
                namen_std_nach.zeile_anhaengen(text_rechts(zeile,NAMEN_STD_INI_TZ_));
            }
        }
        file.close();
    }

    if(ini_ganx_gefunden == false)
    {
        QFile file(pf.path_ini_ganx());
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_ini_ganx();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            file.write(Einstellung_ganx.text().toLatin1());
        }
        file.close();
    }else
    {
        QFile file(pf.path_ini_ganx());
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_ini_ganx();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            Einstellung_ganx.set_text(file.readAll());
        }
        file.close();
    }

    if(ini_dxf_gefunden == false)
    {
        QFile file(pf.path_ini_dxf());
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_ini_dxf();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            file.write(Einstellung_dxf.text().toLatin1());
        }
        file.close();
    }else
    {
        QFile file(pf.path_ini_dxf());
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_ini_dxf();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            Einstellung_dxf.set_text(file.readAll());
        }
        file.close();
    }

    if(ini_dxf_klassen_gefunden == false)
    {
        QFile file(pf.path_ini_dxf_klassen());
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_ini_dxf_klassen();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            file.write(Einstellung_dxf_klassen.text().toLatin1());
        }
        file.close();
    }else
    {
        QFile file(pf.path_ini_dxf_klassen());
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_ini_dxf_klassen();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            Einstellung_dxf_klassen.set_text(file.readAll());
        }
        file.close();
    }

    if(wkz_ganx_gefunden == false)
    {
        QFile file(pf.path_wkz_ganx());
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_wkz_ganx();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            werkzeugmagazin wm;
            file.write(wm.tabellenkopf().toUtf8());
            wkz_magazin_ganx.set_text(wm.tabellenkopf());
        }
        file.close();
    }else
    {
        QFile file(pf.path_wkz_ganx());
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_wkz_ganx();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            wkz_magazin_ganx.set_text(file.readAll());//alt
            //wkz_mag_ganx.set_text(file.readAll());//neu
        }
        file.close();
    }

    if(wkz_fmc_gefunden == false)
    {
        QFile file(pf.path_wkz_fmc());
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_wkz_fmc();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            werkzeugmagazin wm;
            file.write(wm.tabellenkopf().toUtf8());
            wkz_magazin_fmc.set_text(wm.tabellenkopf());
        }
        file.close();
    }else
    {
        QFile file(pf.path_wkz_fmc());
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_wkz_fmc();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            wkz_magazin_fmc.set_text(file.readAll());//alt
            //wkz_mag_fmc.set_text(file.readAll());//neu
        }
        file.close();
    }

    if(wkz_ggf_gefunden == false)
    {
        QFile file(pf.path_wkz_ggf());
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_wkz_ggf();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            //werkzeugmagazin wm;//alt
            wkz_magazin wm;//neu
            file.write(wm.text().toUtf8());
            wkz_magazin_ggf.set_text(wm.text());
        }
        file.close();
    }else
    {
        QFile file(pf.path_wkz_ggf());
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_wkz_ggf();
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            wkz_magazin_ggf.set_text(file.readAll());//alt
            wkz_mag_ggf.set_text(file.readAll());//neu
        }
        file.close();
    }

    //GUI ergänzen wenn inifile von alter Programmversion:
    if(ui->lineEdit_geraden_schwellenwert->text().isEmpty())
    {
        ui->lineEdit_geraden_schwellenwert->setText("2");
    }
    if(ui->lineEdit_zugabe_gehr->text().isEmpty())
    {
        ui->lineEdit_zugabe_gehr->setText("20");
    }
    ui->radioButton_vorschau_fmc->setChecked(true);
}
void MainWindow::schreibe_ini()
{
    QFile file(pf.path_inifile());
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString tmp = "Fehler beim Dateizugriff!\n";
        tmp += pf.path_inifile();
        tmp += "\n";
        tmp += "in der Funktioschreibe_ini";
        QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
    }else
    {
        file.write(Einstellung.text().toLatin1());
    }
    file.close();
    if(Einstellung.entwicklermodus())
    {
        ui->actionTestfunktion->setVisible(true);
    }else
    {
        ui->actionTestfunktion->setVisible(false);
    }
}
void MainWindow::resizeEvent(QResizeEvent *event)
{
    //linker Bereich (Einstellungen):
    ui->scrollArea_einstellungen->move(10,10);
    ui->scrollArea_einstellungen->setFixedHeight(this->height()-40);
    //rechter Bereich:
    ui->tabWidget_main->move(ui->scrollArea_einstellungen->width()+10, 10);
    ui->tabWidget_main->setFixedWidth(this->width()-ui->scrollArea_einstellungen->width()-20);
    ui->tabWidget_main->setFixedHeight(this->height()-40);
    //tab-(Schnell-Modus) Info:
    //---links:
    ui->plainTextEdit_eldungen->move(5,5);
    ui->plainTextEdit_eldungen->setFixedWidth(ui->tabWidget_main->width()-150);
    ui->plainTextEdit_eldungen->setFixedHeight(ui->tabWidget_main->height()-5);
    //---rechts:
    ui->pushButton_dateien_auflisten->move(ui->plainTextEdit_eldungen->x() \
                                           +ui->plainTextEdit_eldungen->width()+5, 5);
    ui->pushButton_dateien_auflisten->setFixedWidth(120);
    //tab(-Detail-Modus) Export:
    //---Projektpfad:
    rechteck3d r;
    r.set_bezugspunkt(OBEN_LINKS);
    r.set_einfuegepunkt(5,5,0);
    r.set_laenge(ui->tabWidget_main->width()-200-5);
    r.set_breite(50);
    double lx = r.l()/6 - 2;
    double ly = r.b()/2 - 1;
    ui->label_projekt->move(r.einfpunkt().x(), r.einfpunkt().y());
    ui->label_projekt->setFixedSize(lx,ly);
    ui->lineEdit_projekt->move(r.einfpunkt().x() + lx*1 + 2*1, r.einfpunkt().y());
    ui->lineEdit_projekt->setFixedSize(lx, ly);
    ui->label_pos->move(r.einfpunkt().x() + lx*2 + 2*2, r.einfpunkt().y());
    ui->label_pos->setFixedSize(lx,ly);
    ui->lineEdit_pos->move(r.einfpunkt().x() + lx*3 + 2*3, r.einfpunkt().y());
    ui->lineEdit_pos->setFixedSize(lx, ly);
    ui->label_baugruppe->move(r.einfpunkt().x() + lx*4 + 2*4, r.einfpunkt().y());
    ui->label_baugruppe->setFixedSize(lx,ly);
    ui->lineEdit_baugruppe->move(r.einfpunkt().x() + lx*5 + 2*5, r.einfpunkt().y());
    ui->lineEdit_baugruppe->setFixedSize(lx, ly);
    ui->lineEdit_projektpfad->move(r.einfpunkt().x(), r.einfpunkt().y() + ly*1 + 2*1);
    ui->lineEdit_projektpfad->setFixedSize(r.l(),ly);
    //---Vorschaufenster:
    ui->label_warnungen->move(5,r.einfpunkt().y()+r.b());
    ui->label_warnungen->setFixedWidth(ui->tabWidget_main->width()-200);
    vorschaufenster.setParent(ui->tab_detail);
    vorschaufenster.move(5,72);
    vorschaufenster.setFixedWidth(ui->tabWidget_main->width()-200);
    vorschaufenster.setFixedHeight(ui->tabWidget_main->height()-100);
    //---rechter Bereich:
    ui->pushButton_import->move(ui->tabWidget_main->width()-190,5);
    ui->pushButton_import->setFixedWidth(180);
    ui->listWidget_wste->move(ui->pushButton_import->x(),\
                              ui->pushButton_import->y()+ui->pushButton_import->height()+5);
    ui->listWidget_wste->setFixedWidth(180);
    ui->listWidget_wste->setFixedHeight(this->height()-320);
    ui->groupBox_vorschauformat->move(ui->pushButton_import->x(),\
                                      ui->listWidget_wste->y()+ui->listWidget_wste->height()+5);
    ui->groupBox_vorschauformat->setFixedWidth(180);
    ui->pushButton_einzelexport->move(ui->pushButton_import->x(),\
                                      ui->groupBox_vorschauformat->y() + \
                                      ui->groupBox_vorschauformat->height()+5);
    ui->pushButton_einzelexport->setFixedWidth(180);
    ui->pushButton_umbenennen->move(ui->pushButton_import->x(),\
                                      ui->pushButton_einzelexport->y() + \
                                      ui->pushButton_einzelexport->height()+5);
    ui->pushButton_umbenennen->setFixedWidth(180);
    ui->label_xypos->move(ui->pushButton_import->x(),\
                          ui->pushButton_umbenennen->y() + \
                          ui->pushButton_umbenennen->height()+5);
    ui->label_xypos->setFixedWidth(180);
    ui->label_wstmas->move(ui->pushButton_import->x(),\
                           ui->label_xypos->y() + \
                           ui->label_xypos->height()+5);
    ui->label_wstmas->setFixedWidth(180);
    //-----
    ui->checkBox_fkon_kantenschonend->setDisabled(true);
    QMainWindow::resizeEvent(event);
}
//-----------------------------------------------------------------------public slots:
void MainWindow::getDialogDataWKZ(QString fenstertitel, text_zeilenweise werkzeugmagazin)
{
    if(fenstertitel.contains("GANX"))
    {
        QFile file(pf.path_wkz_ganx());
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_wkz_ganx();
            tmp += "\n";
            tmp += "in der Funktion getDialogDataWKZ";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            wkz_magazin_ganx = werkzeugmagazin;
            file.write(werkzeugmagazin.text().toUtf8());
        }
        file.close();
    }else if(fenstertitel.contains("FMC"))
    {
        QFile file(pf.path_wkz_fmc());
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_wkz_fmc();
            tmp += "\n";
            tmp += "in der Funktion getDialogDataWKZ";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            wkz_magazin_fmc = werkzeugmagazin;
            file.write(werkzeugmagazin.text().toUtf8());
        }
        file.close();
    }else if(fenstertitel.contains("GGF"))
    {
        QFile file(pf.path_wkz_ggf());
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += pf.path_wkz_ggf();
            tmp += "\n";
            tmp += "in der Funktion getDialogDataWKZ";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            wkz_magazin_ggf = werkzeugmagazin;
            file.write(werkzeugmagazin.text().toUtf8());
        }
        file.close();
    }
}
void MainWindow::getStdNamen(text_zeilenweise namen_vor, text_zeilenweise namen_nach)
{
    namen_std_vor = namen_vor;
    namen_std_nach = namen_nach;

    QFile file(pf.path_stdNamen());
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString tmp = "Fehler beim Dateizugriff!\n";
        tmp += pf.path_stdNamen();
        tmp += "\n";
        tmp += "in der Funktion getStdNamen";
        QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
    }else
    {
        text_zeilenweise namen;
        for(uint i=1; i<=namen_std_vor.zeilenanzahl() ;i++)
        {
            QString zeile;
            zeile  = namen_std_vor.zeile(i);
            zeile += NAMEN_STD_INI_TZ_;
            zeile += namen_std_nach.zeile(i);
            namen.zeile_anhaengen(zeile);
        }
        file.write(namen.text().toUtf8());
    }
    file.close();
}
void MainWindow::getEinstellung(einstellung e)
{
    Einstellung = e;
    schreibe_ini();
}
void MainWindow::getEinstellungGANX(einstellung_ganx e)
{
    Einstellung_ganx = e;

    QFile file(pf.path_ini_ganx());
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString tmp = "Fehler beim Dateizugriff!\n";
        tmp += pf.path_ini_ganx();
        tmp += "\n";
        tmp += "in der Funktion getEinstellungGANX";
        QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
    }else
    {
        file.write(Einstellung_ganx.text().toLatin1());
    }
    file.close();
}
void MainWindow::getEinstellungDxf(einstellung_dxf e)
{
    Einstellung_dxf = e;

    QFile file(pf.path_ini_dxf());
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString tmp = "Fehler beim Dateizugriff!\n";
        tmp += pf.path_ini_dxf();
        tmp += "\n";
        tmp += "in der Funktion getEinstellungDxf";
        QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
    }else
    {
        file.write(Einstellung_dxf.text().toLatin1());
    }
    file.close();
}
void MainWindow::getEinstellungDxfKlassen(einstellung_dxf_klassen e)
{
    Einstellung_dxf_klassen = e;

    QFile file(pf.path_ini_dxf_klassen());
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString tmp = "Fehler beim Dateizugriff!\n";
        tmp += pf.path_ini_dxf_klassen();
        tmp += "\n";
        tmp += "in der Funktion getEinstellungDxfKlassen";
        QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
    }else
    {
        file.write(Einstellung_dxf_klassen.text().toLatin1());
    }
    file.close();
}
void MainWindow::getMausPosXY(QPoint p)
{
    if(ui->listWidget_wste->selectedItems().count())
    {
        QString x = int_to_qstring(p.x());
        QString y = int_to_qstring(p.y());
        QString msg;
        msg  = "X: ";
        msg += x;
        msg += " / Y: ";
        msg += y;
        ui->label_xypos->setText(msg);
    }else
    {
        QString msg;
        msg  = "X: ";
        msg += "?";
        msg += " / Y: ";
        msg += "?";
        ui->label_xypos->setText(msg);
    }
}
void MainWindow::getCADFehler(QString w)
{
    if(ui->listWidget_wste->selectedItems().count())
    {
        ui->label_warnungen->setText(w);
        ui->label_warnungen->setToolTip(w);        
    }else
    {
        ui->label_warnungen->clear();
        ui->label_warnungen->toolTip().clear();        
    }
    if(!w.isEmpty())
    {
        ui->label_warnungen->setStyleSheet("QLabel { background-color : red; color : black; }");
    }else
    {
        ui->label_warnungen->setStyleSheet("QLabel { background-color : white; color : black; }");
    }
}
void MainWindow::getWarnungen(QString w)
{
    ui->pushButton_einzelexport->setToolTip(w);
    if(!w.isEmpty())
    {
        ui->pushButton_einzelexport->setStyleSheet("border:3px solid #ff0000;");
    }else
    {
        ui->pushButton_einzelexport->setStyleSheet(ui->pushButton_umbenennen->styleSheet());
    }
}
void MainWindow::getWSTMas(double l, double b, double d)
{
    QString mas;
    mas  = "L: ";
    mas += double_to_qstring(l);
    mas += " / ";
    mas += "B: ";
    mas += double_to_qstring(b);
    mas += " / ";
    mas += "D: ";
    mas += double_to_qstring(d);
    ui->label_wstmas->setText(mas);
}
void MainWindow::getDrewi(QString w)
{
    ui->radioButton_drehung_autom->setToolTip(w);
}
void MainWindow::slotWstChanged(werkstueck *w, int index)
{
    //int index = ui->listWidget_wste->currentRow();
    //on_listWidget_wste_currentRowChanged(index);
    sendVorschauAktualisieren(*w, index);
}
//-----------------------------------------------------------------------LineEdits:
void MainWindow::on_lineEdit_geraden_schwellenwert_editingFinished()
{
    QString eingabe = ui->lineEdit_geraden_schwellenwert->text();
    eingabe.replace(",",".");
    ui->lineEdit_geraden_schwellenwert->setText(eingabe);
    Einstellung.set_geraden_schwellwert(eingabe.toDouble());
    schreibe_ini();
}
void MainWindow::on_lineEdit_zugabe_gehr_editingFinished()
{
    QString eingabe = ui->lineEdit_zugabe_gehr->text();
    eingabe.replace(",",".");
    if(eingabe.toDouble() >= 0)
    {
        ui->lineEdit_zugabe_gehr->setText(eingabe);
        Einstellung.set_gehrungen_zugabe(eingabe.toDouble());
        schreibe_ini();
    }else
    {
        QMessageBox::warning(this,"Fehler" ,"Eingaben kleiner als Nulle sind hier nicht erlaubt!",QMessageBox::Ok);
        ui->lineEdit_zugabe_gehr->setText(double_to_qstring(Einstellung.gehrungen_zugabe()));
    }
}
void MainWindow::on_lineEdit_projekt_editingFinished()
{
    set_projektpfad();
}
void MainWindow::on_lineEdit_pos_editingFinished()
{    
    QString eingabe = ui->lineEdit_pos->text();
    eingabe.replace(",", ".");
    double eingabe_double = eingabe.toDouble();
    QString tmp = double_to_qstring(eingabe_double);
    if(eingabe.isEmpty() | (eingabe == tmp && eingabe_double <= 9999))
    {
        eingabe.replace(".", ",");
        Projektposition = eingabe;
        ui->lineEdit_pos->setText(Projektposition);
        set_projektpfad();
    }else
    {
        QString msg;
        msg += "\"";
        msg += ui->lineEdit_pos->text();
        msg += "\"";
        msg += " ist keine gültige Positionsnummer!";
        if(eingabe_double > 9999)
        {
            msg += "\n";
            msg += "Positionsnummer ist zu hoch.";
        }
        QMessageBox mb;
        mb.setText(msg);
        mb.exec();
        ui->lineEdit_pos->setText(Projektposition);
        set_projektpfad();
    }
}
void MainWindow::on_lineEdit_baugruppe_editingFinished()
{
    set_projektpfad();
}
void MainWindow::set_projektpfad()
{
    if(ui->listWidget_wste->selectedItems().count())
    {
        Projektpfad_stimmt = false;
        QString pfad;
        QString dateiname;
        QString pfad_lokal;
        QString format;
        pfad_lokal = Einstellung.verzeichnis_ziel_lokal();
        pfad_lokal += QDir::separator();
        pfad_lokal += "DetailModus";
        if(ui->radioButton_vorschau_fmc->isChecked())
        {
            pfad_lokal += QDir::separator();
            format = "fmc";
            pfad_lokal += format;
        }else if(ui->radioButton_vorschau_ganx->isChecked())
        {
            pfad_lokal += QDir::separator();
            format = "ganx";
            pfad_lokal += format;
        }else if(ui->radioButton_vorschau_ggf->isChecked())
        {
            pfad_lokal += QDir::separator();
            format = "ggf";
            pfad_lokal += format;
        }else //eigen
        {
            pfad_lokal += QDir::separator();
            format = "eigen";
            pfad_lokal += format;
        }

        if(ui->radioButton_vorschau_fmc->isChecked())
        {
            QDir d(Einstellung.verzeichnis_root_fmc());
            if(d.exists())
            {
                pfad = Einstellung.verzeichnis_root_fmc();
                pfad += QDir::separator();
            }else
            {
                pfad = pfad_lokal;
                pfad += QDir::separator();
            }
        }else if(ui->radioButton_vorschau_ganx->isChecked())
        {
            QDir d(Einstellung.verzeichnis_root_ganx());
            if(d.exists())
            {
                pfad = Einstellung.verzeichnis_root_ganx();
                pfad += QDir::separator();
            }else
            {
                pfad = pfad_lokal;
                pfad += QDir::separator();
            }
        }else
        {
            pfad = pfad_lokal;
            pfad += QDir::separator();
        }
        if(!ui->lineEdit_projekt->text().isEmpty())
        {
            pfad += ui->lineEdit_projekt->text();
            if(!ui->lineEdit_pos->text().isEmpty())
            {
                QString tmp = ui->lineEdit_pos->text();
                QString barcode;
                if(tmp.contains(","))
                {
                    QString li = text_links(tmp, ",");
                    QString re = text_rechts(tmp, ",");
                    if(li.length()==4)
                    {
                        barcode += tmp;
                    }else if(li.length()==3)
                    {
                        barcode += "0";
                        barcode += li;
                        barcode += ",";
                        barcode += re;
                    }else if(li.length()==2)
                    {
                        barcode += "00";
                        barcode += li;
                        barcode += ",";
                        barcode += re;
                    }else if(li.length()==1)
                    {
                        barcode += "000";
                        barcode += li;
                        barcode += ",";
                        barcode += re;
                    }
                }else
                {
                    if(tmp.length()==4)
                    {
                        barcode += tmp;
                    }else if(tmp.length()==3)
                    {
                        barcode += "0";
                        barcode += tmp;
                    }else if(tmp.length()==2)
                    {
                        barcode += "00";
                        barcode += tmp;
                    }else if(tmp.length()==1)
                    {
                        barcode += "000";
                        barcode += tmp;
                    }
                }
                pfad += QDir::separator();
                pfad += barcode;
                Projektpfad_stimmt = true;
                if(!ui->lineEdit_baugruppe->text().isEmpty())
                {
                    pfad += QDir::separator();
                    pfad += ui->lineEdit_baugruppe->text();
                }
                if(ui->listWidget_wste->selectedItems().count() && ui->listWidget_wste->currentItem())
                {
                    if(!ui->listWidget_wste->currentItem()->text().isEmpty())
                    {
                        dateiname = ui->listWidget_wste->currentItem()->text();
                        if(ui->radioButton_vorschau_fmc->isChecked())
                        {
                            dateiname += ".fmc";
                        }else if(ui->radioButton_vorschau_ganx->isChecked())
                        {
                            dateiname += ".ganx";
                        }else if(ui->radioButton_vorschau_ggf->isChecked())
                        {
                            dateiname += ".ggf";
                        }else //eigen == ".ppf"
                        {
                            dateiname += ".ppf";
                        }
                    }
                }
            }else
            {
                pfad.clear();
            }
        }else
        {
            pfad.clear();
        }
        pfad.replace("\\", QDir::separator());
        pfad.replace("/", QDir::separator());
        //QString pfad_mit_dateinamen;
        if(!pfad.isEmpty() && !dateiname.isEmpty())
        {
            Pfad_mit_dateinamen = pfad + QDir::separator() + dateiname;
            ui->lineEdit_projektpfad->setText(Pfad_mit_dateinamen);
        }else
        {
            ui->lineEdit_projektpfad->setText(pfad);
        }


        //lineEdit einfärben:
        if(!Pfad_mit_dateinamen.isEmpty())
        {
            QFile f(Pfad_mit_dateinamen);
            if(f.exists())
            {
                QPalette palette;
                palette.setColor(QPalette::Base,Qt::green);
                //palette.setColor(QPalette::Text,Qt::black);
                ui->lineEdit_projektpfad->setPalette(palette);
                signal_wstexport(dateiname, format, true);
                dlg_exporte.setWindowTitle(fenstertitel_exportuebersicht());

                QFileInfo fi(Pfad_mit_dateinamen);
                QDateTime fi_lastMod = fi.lastModified();
                QDateTime heute = QDateTime::currentDateTime();
                QString zeitstempel = "\t";
                if(fi_lastMod.date() == heute.date())
                {
                    zeitstempel += "(Heute ";
                    zeitstempel += fi_lastMod.time().toString("hh:mm)");
                }else
                {
                    zeitstempel += fi_lastMod.toString("(yyyy.MM.dd / hh:mm)");
                }
                ui->lineEdit_projektpfad->setText(Pfad_mit_dateinamen + zeitstempel);

            }else if(!pfad.isEmpty())
            {
                QDir d(pfad);
                if(d.exists())
                {
                    QPalette palette;
                    palette.setColor(QPalette::Base,Qt::yellow);
                    //palette.setColor(QPalette::Text,Qt::black);
                    ui->lineEdit_projektpfad->setPalette(palette);
                }else
                {
                    QPalette palette;
                    palette.setColor(QPalette::Base,Qt::white);
                    //palette.setColor(QPalette::Text,Qt::black);
                    ui->lineEdit_projektpfad->setPalette(palette);
                }
            }
        }else if(!pfad.isEmpty())
        {
            QDir d(pfad);
            if(d.exists())
            {
                QPalette palette;
                palette.setColor(QPalette::Base,Qt::yellow);
                //palette.setColor(QPalette::Text,Qt::black);
                ui->lineEdit_projektpfad->setPalette(palette);
            }else
            {
                QPalette palette;
                palette.setColor(QPalette::Base,Qt::white);
                //palette.setColor(QPalette::Text,Qt::black);
                ui->lineEdit_projektpfad->setPalette(palette);
            }
        }else
        {
            QPalette palette;
            palette.setColor(QPalette::Base,Qt::white);
            //palette.setColor(QPalette::Text,Qt::black);
            ui->lineEdit_projektpfad->setPalette(palette);
        }
    }
}
QString MainWindow::fenstertitel_exportuebersicht()
{
    QString titel = "Exportübersicht ";
    if(!ui->lineEdit_projekt->text().isEmpty() && !ui->lineEdit_pos->text().isEmpty())
    {
        titel += ui->lineEdit_projekt->text();
        titel += " Pos: ";
        titel += ui->lineEdit_pos->text();
        if(!ui->lineEdit_baugruppe->text().isEmpty())
        {
            titel += " / ";
            titel += ui->lineEdit_baugruppe->text();
        }
    }
    return titel;
}
//-----------------------------------------------------------------------Checkboxen:
void MainWindow::on_checkBox_quelldat_erhalt_stateChanged()
{
    Einstellung.set_quelldateien_erhalten(ui->checkBox_quelldat_erhalt->isChecked());
    schreibe_ini();
}
void MainWindow::on_checkBox_std_namen_zuweisen_stateChanged()
{
    Einstellung.set_std_dateinamen_verwenden(ui->checkBox_std_namen_zuweisen->isChecked());
    schreibe_ini();
}
void MainWindow::on_checkBox_geraden_stateChanged()
{
    Einstellung.set_kurze_geraden_importieren(!ui->checkBox_geraden->isChecked());//invertiert weil im ui anders herum
    schreibe_ini();
}
void MainWindow::on_checkBox_formatierung_aufbrechen_stateChanged()
{
    Einstellung.set_formartierungen_aufbrechen(ui->checkBox_formatierung_aufbrechen->isChecked());
    schreibe_ini();
}
void MainWindow::on_checkBox_fkon_kantenschonend_stateChanged()
{
    QMessageBox mb;
    mb.setText("Diese Funktion ist derzeit leider noch nicht fertig!");
    mb.exec();

    Einstellung.set_fkon_kantenschonend(ui->checkBox_fkon_kantenschonend->isChecked());
    schreibe_ini();
}
//-----------------------------------------------------------------------Radio-Buttons:
void MainWindow::on_radioButton_drehung_0_toggled(bool checked)
{
    if(checked)
    {
        Einstellung.set_drehung_wst("0");
        if(ui->tab_detail->isVisible() && ui->listWidget_wste->count()>0)
        {
            on_listWidget_wste_currentRowChanged(ui->listWidget_wste->currentRow());
        }
    }
    schreibe_ini();
}
void MainWindow::on_radioButton_drehung_90_toggled(bool checked)
{
    if(checked)
    {
        Einstellung.set_drehung_wst("90");
        if(ui->tab_detail->isVisible() && ui->listWidget_wste->count()>0)
        {
            on_listWidget_wste_currentRowChanged(ui->listWidget_wste->currentRow());
        }
    }
    schreibe_ini();
}
void MainWindow::on_radioButton_drehung_180_toggled(bool checked)
{
    if(checked)
    {
        Einstellung.set_drehung_wst("180");
        if(ui->tab_detail->isVisible() && ui->listWidget_wste->count()>0)
        {
            on_listWidget_wste_currentRowChanged(ui->listWidget_wste->currentRow());
        }
    }
    schreibe_ini();
}
void MainWindow::on_radioButton_drehung_270_toggled(bool checked)
{
    if(checked)
    {
        Einstellung.set_drehung_wst("270");
        if(ui->tab_detail->isVisible() && ui->listWidget_wste->count()>0)
        {
            on_listWidget_wste_currentRowChanged(ui->listWidget_wste->currentRow());
        }
    }
    schreibe_ini();
}
void MainWindow::on_radioButton_drehung_autom_toggled(bool checked)
{
    if(checked)
    {
        Einstellung.set_drehung_wst("AUTO");
        if(ui->tab_detail->isVisible() && ui->listWidget_wste->count()>0)
        {
            on_listWidget_wste_currentRowChanged(ui->listWidget_wste->currentRow());
        }
    }
    schreibe_ini();
}

void MainWindow::on_radioButton_fkon_ti_quell_toggled(bool checked)
{
    if(checked)
    {
        Einstellung.set_tiefeneinstellung_fkon("orgi");
    }
    schreibe_ini();
}
void MainWindow::on_radioButton_fkon_ti_wkz_toggled(bool checked)
{
    if(checked)
    {
        Einstellung.set_tiefeneinstellung_fkon("wkz");
    }
    schreibe_ini();
}

void MainWindow::on_radioButton_vorschau_eigen_clicked(bool checked)
{
    if(checked == true)
    {
        if(ui->listWidget_wste->selectedItems().count())
        {
            on_listWidget_wste_currentRowChanged(ui->listWidget_wste->currentRow());
            set_projektpfad();
        }        
    }
}
void MainWindow::on_radioButton_vorschau_ganx_clicked(bool checked)
{
    if(checked == true)
    {
        if(ui->listWidget_wste->selectedItems().count())
        {
            on_listWidget_wste_currentRowChanged(ui->listWidget_wste->currentRow());
            set_projektpfad();
        }        
    }
}
void MainWindow::on_radioButton_vorschau_fmc_clicked(bool checked)
{
    if(checked == true)
    {
        if(ui->listWidget_wste->selectedItems().count())
        {
            on_listWidget_wste_currentRowChanged(ui->listWidget_wste->currentRow());
            set_projektpfad();
        }        
    }
}
void MainWindow::on_radioButton_vorschau_ggf_clicked(bool checked)
{
    if(checked == true)
    {
        if(ui->listWidget_wste->selectedItems().count())
        {
            on_listWidget_wste_currentRowChanged(ui->listWidget_wste->currentRow());
            set_projektpfad();
        }
    }
}

//-----------------------------------------------------------------------Menüs:
void MainWindow::on_actionTestfunktion_triggered()
{

    //Test für text_zw:
    QString msg;
    //msg += "Zeile 0\n";
    //msg += "Zeile 1\n";
    //msg += "Zeile 2\n";
    //msg += "Zeile 3\n";
    //msg += "Zeile 4";
    //text_zw test(msg);
    text_zw test;
    QMessageBox mb;
    //mb.setText(test.zeile(2));
    //mb.setText(test.zeilen(2,2));
    //test.add_vo("davor\n123");
    //test.add_hi("");
    //test.add_hi("danach\n123");
    //test.add_mi(19 ,"danach\n123");
    //test.edit(5, "getauscht");
    //test.entf(2,3);
    mb.setText(test.text());
    mb.setWindowTitle(int_to_qstring(test.count()));
    mb.exec();

}
void MainWindow::set_prginfo()
{
    QString tmp;
    tmp = "Postprozessor ";
    tmp += PROGRAMMVERSION;
    this->setWindowTitle(tmp);
    //----------------------------------------------------------
    tmp =  "Autor:";
    tmp += "\t";
    tmp += "Oliver Schuft";
    tmp += "\n";
    tmp += "source:";
    tmp += "\t";
    tmp += "https://github.com/TischlerWilly/postprozessor.git";
    tmp += "\n\n";

    tmp += "Mögliche Importformate:\n";
    tmp += "  *.FMC (IMAWOP4)\n";
    tmp += "  *.fmc  (IMAWOP4)\n";
    tmp += "  *.DXF mit Versionskennung AC1009\n";
    tmp += "  *.dxf mit Versionskennung AC1009\n";
    tmp += "\n";

    tmp += "Hinweis zum GANX-Export:\n";
    tmp += "  Fräskonturen werden nicht ausgegeben.\n";

    tmp += "\n\n";
    tmp += "--- Leistungsumfang ----\n\n";
    tmp += "Import von fmc:\n";
    tmp += "- Werkstückgröße [PGKOPF40]\n";
    tmp += "- Kanteninformation (über Kommentare)\n";
    tmp += "- Gehrung [ZYSCHN40]\n";
    tmp += "- Einzelbohrung vertikal [VBDMES40]\n";
    tmp += "- HBE x+ [HBXPLU40]\n";
    tmp += "- HBE x- [HBXMIN40]\n";
    tmp += "- HBE y+ [HBYPLU40]\n";
    tmp += "- HBE y- [HBYMIN40]\n";
    tmp += "- Bohrbild in X [VBX_40]\n";
    tmp += "- Bohrbild in Y [VBY_40]\n";
    tmp += "- Lochreihe Anfang-Ende [VBLAEN40]\n";
    tmp += "- Lochreihe Mitte-Anfang [VBLMIT40]\n";
    tmp += "- Topfbandbohrung [VBTOPF41]\n";
    tmp += "- Kreistasche [ZYKTFR40]\n";
    tmp += "- Rechtecktasche [ZYRTFR40]\n";
    tmp += "- Nut [ZYSNUT40]\n";
    tmp += "- Falz [ZYFALZ40]\n";
    tmp += "- Aufruf Fräser [KAFRAE40]\n";
    tmp += "- Gerade Fräsbahn [G1]\n";
    tmp += "- Bogen fräsen im UZS [G2]\n";
    tmp += "- Bogen fräsen im GUZS [G3]\n";
    tmp += "- Stulp [ZYSTUL40]";
    tmp += "\n";
    tmp += "\n";
    tmp += "Import von dxf:\n";
    tmp += "- Werkstückgröße (Polilinie)\n";
    tmp += "- Einzelbohrung vertikal (Kreis)\n";
    tmp += "- Einzelbohrung horizontal (2 Linien)\n";
    tmp += "- Nut vertikal (2 oder 4 Linien)\n";
    tmp += "- Kreistasche vertikal (Kreis)\n";
    tmp += "- Rechtecktasche vertikal (4 Linien)\n";
    tmp += "- Fräsung vertikal (Linien, Bögen)\n";
    tmp += "\n";
    tmp += "\n";
    tmp += "Bearbeitungsoptimierungen:\n";
    tmp += "- Drehen AUTO\n";
    tmp += "- Borraster-Erkennung\n";
    tmp += "- Durchgangsbohungen splitten\n";
    tmp += "- Automatische Werkzeugzuweisung\n";
    tmp += "- Plausibilitätsprüfung (Warnungen)\n";
    tmp += "\n";
    tmp += "\n";
    tmp += "Weiteren Funktionen:\n";
    tmp += "- Doppelte (identische) Bohrungen werden beim Import ignoriert\n";
    tmp += "- Werkzeugmagazin für jedes Exportformat\n";
    tmp += "- Werkstücke beim Import automatisch benennen\n";
    tmp += "- Werkstücke dem Namen nach sortieren (bei Import)\n";
    tmp += "- Werkstücke umbenennen\n";
    tmp += "- Exportübersicht\n";
    tmp += "- Werkstücke bearbeiten\n";
    tmp += "  ->Werkstückgröße ändern\n";
    tmp += "  ->Bearbeitungen einfügen\n";
    tmp += "  ->Bearbeitungen ändern\n";
    tmp += "  ->Bearbeitungen verschieben (mehrere gleichzeitig möglich)\n";
    tmp += "  ->Verwenden der Platzhalter L B und D möglch\n";
    tmp += "- Kurze Geraden ignorieren mit Angabe des Schwellenwertes (fmc)\n";
    tmp += "- Formartierungen aufbrechen (fmc)\n";
    tmp += "- Werkstück vergrößern als Zugabe für Gehrungen (fmc)\n";
    tmp += "- Werkstücke ausblenden\n";
    tmp += "- Export in hierarchischen Projekt-Unterordnern\n";

    ui->plainTextEdit_eldungen->setPlainText(tmp);
}
void MainWindow::on_actionInfo_triggered()
{
    ui->tabWidget_main->setCurrentIndex(0);
    set_prginfo();
}
void MainWindow::on_actionEntwicklermodus_triggered(bool checked)
{
    Einstellung.set_entwicklermodus(checked);
    schreibe_ini();
}
void MainWindow::on_actionWerkzeug_ganx_anzeigen_triggered()
{
    emit sendDialogDataWKZ("Werkzeug GANX", wkz_magazin_ganx);
}
void MainWindow::on_actionWerkzeug_fmc_anzeigen_triggered()
{
    emit sendDialogDataWKZ("Werkzeug FMC", wkz_magazin_fmc);
}
void MainWindow::on_actionWerkzeug_ggf_anzeigen_triggered()
{
    //emit sendDialogDataWKZ("Werkzeug GGF", wkz_magazin_ggf);//alt
    //neu:
    dlg_wkzmag.setWindowTitle("Werkzeugmagazin ggf");
    dlg_wkzmag.set_wkzmag(wkz_mag_ggf);
    dlg_wkzmag.show();
}
void MainWindow::on_actionEinstellung_pfade_triggered()
{
    emit sendEinstellungPfade(Einstellung);
}
void MainWindow::on_actionStandard_Namen_anzeigen_triggered()
{
    emit sendStdNamen(namen_std_vor, namen_std_nach);
}
void MainWindow::on_actionEinstellung_ganx_triggered()
{
    emit sendEinstellungGANX(Einstellung_ganx);
}
void MainWindow::on_actionEinstellung_dxf_triggered()
{
    emit sendEinstellungDxf(Einstellung_dxf);
}
void MainWindow::on_actionEinstellung_dxf_klassen_triggered()
{
    emit sendEinstellungDxfKlassen(Einstellung_dxf, Einstellung_dxf_klassen);
}
void MainWindow::on_actionExportUebersicht_triggered()
{
    dlg_exporte.show();
}
void MainWindow::on_actionWST_ausblenden_triggered()
{
    if(ui->listWidget_wste->selectedItems().count())
    {
        if(!ui->listWidget_wste->currentItem()->text().isEmpty())
        {
            ui->listWidget_wste->currentItem()->setHidden(true);
            signal_wst_ausblenden(ui->listWidget_wste->currentItem()->text(), true);
            for(int index = ui->listWidget_wste->currentRow() ; index > 0 ; index--)
            {
                if(!ui->listWidget_wste->item(index)->isHidden())
                {
                    ui->listWidget_wste->setCurrentRow(index);
                    index = 0;
                }
            }
            if(ui->listWidget_wste->currentItem()->isHidden())
            {
                for(int index = 0 ; index < ui->listWidget_wste->count() ; index++)
                {
                    if(!ui->listWidget_wste->item(index)->isHidden())
                    {
                        ui->listWidget_wste->setCurrentRow(index);
                        index = ui->listWidget_wste->count();
                    }
                }
            }
        }
    }
}
void MainWindow::on_actionWST_bearbeiten_triggered()
{
    if(ui->listWidget_wste->selectedItems().count())
    {
        const int wstindex = ui->listWidget_wste->currentRow()+1;
        werkstueck *w = wste.wst(wstindex);
        dlg_wst_bearbeiten.setWindowTitle(w->name());
        dlg_wst_bearbeiten.set_wst(w);
        dlg_wst_bearbeiten.show();
    }
}
//-----------------------------------------------------------------------Buttons:
void MainWindow::on_pushButton_dateien_auflisten_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    if(Einstellung.verzeichnis_quelle().isEmpty())
    {
        QMessageBox::warning(this,"Abbruch","Quellverzeichniss nicht angegeben!",QMessageBox::Ok);
        return;
    }
    dateien_erfassen();
    QString vortext = int_to_qstring(dateien_alle.zeilenanzahl()) + " Dateien gefunden:\n";
    vortext += dateien_alle.text();
    ui->plainTextEdit_eldungen->setPlainText(vortext);
    QApplication::restoreOverrideCursor();
}
void MainWindow::on_pushButton_import_clicked()
{
    import();
    werkstueck w;//leeres wst
    sendVorschauAktualisieren(w, 0);//leeres wst an vorschau schicken
    ui->listWidget_wste->clear();
    for(uint i=1; i<=wste.anzahl() ;i++)
    {
        ui->listWidget_wste->addItem(wste.wst(i)->name());
    }
    signal_exporte(wste.namen_tz());
}
void MainWindow::on_pushButton_einzelexport_clicked()
{
    QString pfad = Pfad_mit_dateinamen;
    bool exportieren = false;
    if(!pfad.isEmpty())
    {
        if(ui->listWidget_wste->selectedItems().count())
        {
            if(!ui->listWidget_wste->currentItem()->text().isEmpty())
            {
                QString dateiname = ui->listWidget_wste->currentItem()->text();
                if(ui->radioButton_vorschau_fmc->isChecked())
                {
                    dateiname += ".fmc";
                }else if(ui->radioButton_vorschau_ganx->isChecked())
                {
                    dateiname += ".ganx";
                }else if(ui->radioButton_vorschau_ggf->isChecked())
                {
                    dateiname += ".ggf";
                }else //eigen
                {
                    dateiname += ".ppf";
                }
                QDir exportdir(text_links(pfad, dateiname));
                exportdir.mkpath(text_links(pfad, dateiname));
                QFile f(pfad);
                if(f.exists())
                {
                    QString msg;
                    msg  = "Die Datei existiert bereits!\n";
                    msg += "Soll sie überschrieben werden?";
                    QMessageBox mb;
                    mb.setWindowTitle("Datei überschreiben?");
                    mb.setText(msg);
                    mb.setStandardButtons(QMessageBox::Yes);
                    mb.addButton(QMessageBox::No);
                    mb.setDefaultButton(QMessageBox::No);

                    int mb_returnwert = mb.exec();
                    if(mb_returnwert == QMessageBox::Yes)
                    {
                        exportieren = true;
                    }else if(mb_returnwert == QMessageBox::No)
                    {
                        ;//nichts tun = nicht speichern
                    }
                }else
                {
                    exportieren = true;
                }
            }else
            {
                QString msg;
                msg = "Bauteil hat keinen Namen!";
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
            }
        }else
        {
            QString msg;
            msg = "Es ist kein Bauteil ausgewählt!";
            QMessageBox mb;
            mb.setText(msg);
            mb.setWindowTitle("Programm exportieren");
            mb.exec();
        }
    }else
    {
        QString msg;
        msg = "Bitte Projekt und Positionsnummer angeben!";
        QMessageBox mb;
        mb.setText(msg);
        mb.setWindowTitle("Programm exportieren");
        mb.exec();
    }
    if(exportieren == true)
    {
        QApplication::setOverrideCursor(Qt::WaitCursor);        
        //Exportieren:
        QFile f(pfad);
        bool foauf;
        if(Einstellung.formartierungen_aufbrechen())
        {
            foauf = true;
        }else
        {
            foauf = false;
        }
        bool fkonkanschon;
        if(Einstellung.fkon_kantenschonend())
        {
            fkonkanschon = true;
        }else
        {
            fkonkanschon = false;
        }
        if(ui->radioButton_vorschau_fmc->isChecked())
        {
            int i = ui->listWidget_wste->currentRow()+1;
            if(wste.wst(i)->zustand().export_moeglich())
            {
                if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QString tmp = "Fehler beim Dateizugriff!\n";
                    tmp += pfad;
                    tmp += "\n";
                    tmp += "in der Funktion on_pushButton_einzelexport_clicked";
                    QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
                }else
                {
                    f.write(wste.wst(i)->zustand().exporttext().toUtf8());
                    schreibe_in_zwischenablage(pfad);
                    speichere_ausgabepfad_fmc(pfad);
                }
                f.close();
            }else
            {
                QString msg;
                msg = "Export nicht möglich!";
                msg += "\n";
                msg += wste.wst(i)->zustand().exporttext();
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
            }
        }else if(ui->radioButton_vorschau_ganx->isChecked())
        {
            int i = ui->listWidget_wste->currentRow()+1;
            if(wste.wst(i)->zustand().export_moeglich())
            {
                if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QString tmp = "Fehler beim Dateizugriff!\n";
                    tmp += pfad;
                    tmp += "\n";
                    tmp += "in der Funktion on_pushButton_einzelexport_clicked";
                    QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
                }else
                {
                    f.write(wste.wst(i)->zustand().exporttext().toUtf8());
                }
                f.close();
            }else
            {
                QString msg;
                msg = "Export nicht möglich!";
                msg += "\n";
                msg += wste.wst(i)->zustand().exporttext();
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
            }
        }else if(ui->radioButton_vorschau_ggf->isChecked())
        {
            int i = ui->listWidget_wste->currentRow()+1;
            if(wste.wst(i)->zustand().export_moeglich())
            {
                if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QString tmp = "Fehler beim Dateizugriff!\n";
                    tmp += pfad;
                    tmp += "\n";
                    tmp += "in der Funktion on_pushButton_einzelexport_clicked";
                    QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
                }else
                {

                    f.write(wste.wst(i)->zustand().exporttext().toUtf8());
                }
                f.close();
            }else
            {
                QString msg;
                msg = "Export nicht möglich!";
                msg += "\n";
                msg += wste.wst(i)->zustand().exporttext();
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
            }
        }else //eigen
        {
            int i = ui->listWidget_wste->currentRow()+1;
            if(wste.wst(i)->zustand().export_moeglich())
            {
                if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    QString tmp = "Fehler beim Dateizugriff!\n";
                    tmp += pfad;
                    tmp += "\n";
                    tmp += "in der Funktion on_pushButton_einzelexport_clicked";
                    QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
                }else
                {
                    f.write(wste.wst(i)->zustand().exporttext().toUtf8());
                }
                f.close();
            }else
            {
                QString msg;
                msg = "Export nicht möglich!";
                msg += "\n";
                msg += wste.wst(i)->zustand().exporttext();
                QMessageBox mb;
                mb.setText(msg);
                mb.exec();
            }
        }
        QApplication::restoreOverrideCursor();
    }
    set_projektpfad();//Farbänderung
}
void MainWindow::on_pushButton_umbenennen_clicked()
{
    if(ui->listWidget_wste->selectedItems().count())
    {
        QString name = ui->listWidget_wste->currentItem()->text();
        if(!name.isEmpty())
        {
            bool ok;
            QString fenstertitel = "umbenennen";
            QString hinweistext  = "Neuer Name:";
            QString vorgebewert  = name;
            QString neuer_name = QInputDialog::getText(this, fenstertitel,
                                                       hinweistext, QLineEdit::Normal,
                                                       name, &ok);
            if (ok && !neuer_name.isEmpty())
            {
                if(wste.ist_bekannt(neuer_name))
                {
                    QString msg;
                    msg  = "Das Bauteil kann nicht umbenannt werden.";
                    msg += "\n";
                    msg += "Es gibt bereits ein Bauteil mit dem Namen ";
                    msg += neuer_name;
                    msg += ".";
                    QMessageBox mb;
                    mb.setText(msg);
                    mb.exec();
                }else
                {
                    int row = ui->listWidget_wste->currentRow();
                    ui->listWidget_wste->item(row)->setText(neuer_name);
                    wste.set_name(row+1, neuer_name);//Namensliste in wste
                    wste.wst(row+1)->set_name(neuer_name);//name des konkreten wst
                    signal_wst_umbenennen(name, neuer_name);//gui
                    on_listWidget_wste_currentRowChanged(ui->listWidget_wste->currentRow());
                }
            }
        }else
        {
            QString msg;
            msg = "Bauteil hat keinen Namen!";
            QMessageBox mb;
            mb.setText(msg);
            mb.setWindowTitle("Werkstück umbenennen");
            mb.exec();
        }
    }else
    {
        QString msg;
        msg = "Es ist kein Bauteil ausgewählt!";
        QMessageBox mb;
        mb.setText(msg);
        mb.setWindowTitle("Werkstück umbenennen");
        mb.exec();
    }
}
//-----------------------------------------------------------------------ListeWidgets:
void MainWindow::on_listWidget_wste_currentRowChanged(int currentRow)
{
    if(ui->listWidget_wste->selectedItems().count())
    {
        const int wstindex = currentRow+1;
        if(ui->radioButton_vorschau_eigen->isChecked())
        {            
            wste.wst(wstindex)->set_einstellung_ganx(Einstellung_ganx);
            //->set_einstellung_fmc
            //->set_einstellung_eigen
            wste.wst(wstindex)->set_zugabe_gehrungen(Einstellung.gehrungen_zugabe());
            wste.wst(wstindex)->set_zustand("eigen", wkz_magazin_fmc, Einstellung.drehung_wst(), \
                                               Einstellung.formartierungen_aufbrechen(), Einstellung.tiefeneinst_fkon());
            sendVorschauAktualisieren(*wste.wst(wstindex), 0);
            getCADFehler(wste.wst(wstindex)->cad_fehler(true));
            getWarnungen(wste.wst(wstindex)->zustand().warnungen());
            //hier übergebe ich der wkz von fmc weil wkz übergeben werden muss es aber keines gibt.
        }else if(ui->radioButton_vorschau_ganx->isChecked())
        {            
            wste.wst(wstindex)->set_einstellung_ganx(Einstellung_ganx);
            //->set_einstellung_fmc
            //->set_einstellung_eigen
            wste.wst(wstindex)->set_zugabe_gehrungen(Einstellung.gehrungen_zugabe());
            wste.wst(wstindex)->set_zustand("ganx", wkz_magazin_ganx, Einstellung.drehung_wst(), \
                                               Einstellung.formartierungen_aufbrechen(), Einstellung.tiefeneinst_fkon());
            sendVorschauAktualisieren(*wste.wst(wstindex), 0);
            getCADFehler(wste.wst(wstindex)->cad_fehler(true));
            getWarnungen(wste.wst(wstindex)->zustand().warnungen());
        }else if(ui->radioButton_vorschau_fmc->isChecked())
        {
            wste.wst(wstindex)->set_einstellung_ganx(Einstellung_ganx);
            //->set_einstellung_fmc
            //->set_einstellung_eigen
            wste.wst(wstindex)->set_zugabe_gehrungen(Einstellung.gehrungen_zugabe());
            wste.wst(wstindex)->set_zustand("fmc", wkz_magazin_fmc, Einstellung.drehung_wst(), \
                                               Einstellung.formartierungen_aufbrechen(), Einstellung.tiefeneinst_fkon());
            sendVorschauAktualisieren(*wste.wst(wstindex), 0);
            getCADFehler(wste.wst(wstindex)->cad_fehler(true));
            getWarnungen(wste.wst(wstindex)->zustand().warnungen());
        }else if(ui->radioButton_vorschau_ggf->isChecked())
        {
            wste.wst(wstindex)->set_einstellung_ganx(Einstellung_ganx);
            //->set_einstellung_fmc
            //->set_einstellung_eigen
            wste.wst(wstindex)->set_zugabe_gehrungen(Einstellung.gehrungen_zugabe());
            wste.wst(wstindex)->set_zustand("ggf", wkz_magazin_ggf, Einstellung.drehung_wst(), \
                                               Einstellung.formartierungen_aufbrechen(), Einstellung.tiefeneinst_fkon());
            sendVorschauAktualisieren(*wste.wst(wstindex), 0);
            getCADFehler(wste.wst(wstindex)->cad_fehler(true));
            getWarnungen(wste.wst(wstindex)->zustand().warnungen());
        }
        if(dlg_prgtext.isVisible())
        {
            on_listWidget_wste_itemDoubleClicked();
        }
        ui->radioButton_drehung_autom->setToolTip(wste.wst(wstindex)->zustand().drehung());
        set_projektpfad();
        if(dlg_wst_bearbeiten.isVisible())
        {
            on_actionWST_bearbeiten_triggered();
        }
    }
}
void MainWindow::on_listWidget_wste_itemSelectionChanged()
{
    if(ui->listWidget_wste->selectedItems().count())
    {
        on_listWidget_wste_currentRowChanged(ui->listWidget_wste->currentRow());
    }
}
void MainWindow::on_listWidget_wste_itemDoubleClicked()
{
    emit sendProgrammtext(wste.wst(ui->listWidget_wste->currentRow()+1));
}
void MainWindow::on_listWidget_wste_itemClicked(QListWidgetItem *item)
{
    on_listWidget_wste_currentRowChanged(ui->listWidget_wste->currentRow());
}
//-----------------------------------------------------------------------
void MainWindow::dateien_erfassen()
{
    QDir ordner(Einstellung.verzeichnis_quelle());
    QStringList ordnerinhalt;
    ordnerinhalt = ordner.entryList(QDir::Files);
    text_zeilenweise tz;
    for(QStringList::iterator it = ordnerinhalt.begin() ; it!=ordnerinhalt.end() ; ++it)
    {
        QString name = *it;
        tz.zeile_anhaengen(name);
    }
    dateien_alle = tz;
}
void MainWindow::import()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    wste.clear();
    wste.set_einstellung_dxf(Einstellung_dxf);
    wste.set_einstellung_dxf_klassen(Einstellung_dxf_klassen);
    dateien_erfassen();
    QString fmc = FMC;
    QString fmcA = FMC_PRGA;
    QString fmcB = FMC_PRGB;
    QString dxf = DXF;

    //Dateien einlesen:
    for(uint i=1; i<=dateien_alle.zeilenanzahl() ;i++)
    {

        if(dateien_alle.zeile(i).right(fmc.length()) == FMC  || \
           dateien_alle.zeile(i).right(fmc.length()) == FMC_     )
        {
            QString nam_ohn_end = dateien_alle.zeile(i).left(dateien_alle.zeile(i).length()-fmc.length());

            if(nam_ohn_end.right(fmcA.length()) == FMC_PRGA)
            {
                QString nam_ohn_pref = nam_ohn_end.left(nam_ohn_end.length()-fmcA.length());
                if(wste.neu(nam_ohn_pref, FMC))//Wenn es das Wst bereits gibt
                {
                    //Bearbeitungen auf der Wst-Unterseite importieren
                    QString pfad = Einstellung.verzeichnis_quelle() + QDir::separator() + dateien_alle.zeile(i);
                    QFile datei(pfad);
                    if(!datei.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        QString tmp = "Fehler beim Dateizugriff!\n";
                        tmp += pfad;
                        tmp += "\n";
                        tmp += "in der Funktion on_pushButton_start_clicked";
                        QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
                    }else
                    {
                        QString inhalt = datei.readAll();
                        wste.import_fmc_unterseite(nam_ohn_pref, inhalt);
                        datei.close();
                        if(Einstellung.quelldateien_erhalten() == false)
                        {
                            QFile originaldatei(pfad);
                            originaldatei.remove();
                        }
                    }
                }else //Das Wst gab es noch nicht, es ist jetzt jungfräulich angelegt
                {
                    //Bearbeitungen auf der Wst-Obererseite importieren
                    QString pfad = Einstellung.verzeichnis_quelle() + QDir::separator() + dateien_alle.zeile(i);
                    QFile datei(pfad);
                    if(!datei.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        QString tmp = "Fehler beim Dateizugriff!\n";
                        tmp += pfad;
                        tmp += "\n";
                        tmp += "in der Funktion on_pushButton_start_clicked";
                        QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
                    }else
                    {
                        QString inhalt = datei.readAll();
                        wste.import_fmc_oberseite(nam_ohn_pref, inhalt);
                        datei.close();
                        if(Einstellung.quelldateien_erhalten() == false)
                        {
                            QFile originaldatei(pfad);
                            originaldatei.remove();
                        }
                    }
                }
            }else if(nam_ohn_end.right(fmcB.length()) == FMC_PRGB)
            {
                QString nam_ohn_pref = nam_ohn_end.left(nam_ohn_end.length()-fmcB.length());
                if(wste.neu(nam_ohn_pref, FMC))//Wenn es das Wst bereits gibt
                {
                    //Bearbeitungen auf der Wst-Unterseite importieren
                    QString pfad = Einstellung.verzeichnis_quelle() + QDir::separator() + dateien_alle.zeile(i);
                    QFile datei(pfad);
                    if(!datei.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        QString tmp = "Fehler beim Dateizugriff!\n";
                        tmp += pfad;
                        tmp += "\n";
                        tmp += "in der Funktion on_pushButton_start_clicked";
                        QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
                    }else
                    {
                        QString inhalt = datei.readAll();
                        wste.import_fmc_unterseite(nam_ohn_pref, inhalt);
                        datei.close();
                        if(Einstellung.quelldateien_erhalten() == false)
                        {
                            QFile originaldatei(pfad);
                            originaldatei.remove();
                        }
                    }
                }else//Das Wst gab es noch nicht, es ist jetzt jungfräulich angelegt
                {
                    //Bearbeitungen auf der Wst-Obererseite importieren
                    QString pfad = Einstellung.verzeichnis_quelle() + QDir::separator() + dateien_alle.zeile(i);
                    QFile datei(pfad);
                    if(!datei.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        QString tmp = "Fehler beim Dateizugriff!\n";
                        tmp += pfad;
                        tmp += "\n";
                        tmp += "in der Funktion on_pushButton_start_clicked";
                        QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
                    }else
                    {
                        QString inhalt = datei.readAll();
                        wste.import_fmc_oberseite(nam_ohn_pref, inhalt);
                        datei.close();
                        if(Einstellung.quelldateien_erhalten() == false)
                        {
                            QFile originaldatei(pfad);
                            originaldatei.remove();
                        }
                    }
                }
            }else //Ober und Unterseite sind bereits in einem Programm zusammengeführt
            {
                //Import von händisch geschriebenen Programmen:
                QString nam_ohn_pref = nam_ohn_end;
                if(wste.neu(nam_ohn_pref, FMC))//Wenn es das Wst bereits gibt
                {
                    //Bearbeitungen auf der Wst-Unterseite importieren
                    QString pfad = Einstellung.verzeichnis_quelle() + QDir::separator() + dateien_alle.zeile(i);
                    QFile datei(pfad);
                    if(!datei.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        QString tmp = "Fehler beim Dateizugriff!\n";
                        tmp += pfad;
                        tmp += "\n";
                        tmp += "in der Funktion on_pushButton_start_clicked";
                        QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
                    }else
                    {
                        QString inhalt = datei.readAll();
                        wste.import_fmc_unterseite(nam_ohn_pref, inhalt);
                        if(Einstellung.quelldateien_erhalten() == false)
                        {
                            QFile originaldatei(pfad);
                            originaldatei.remove();
                        }
                    }
                }else //Das Wst gab es noch nicht, es ist jetzt jungfräulich angelegt
                {
                    //Bearbeitungen auf der Wst-Obererseite importieren
                    QString pfad = Einstellung.verzeichnis_quelle() + QDir::separator() + dateien_alle.zeile(i);
                    QFile datei(pfad);
                    if(!datei.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        QString tmp = "Fehler beim Dateizugriff!\n";
                        tmp += pfad;
                        tmp += "\n";
                        tmp += "in der Funktion on_pushButton_start_clicked";
                        QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
                    }else
                    {
                        QString inhalt = datei.readAll();
                        wste.import_fmc_oberseite(nam_ohn_pref, inhalt);
                        datei.close();
                        if(Einstellung.quelldateien_erhalten() == false)
                        {
                            QFile originaldatei(pfad);
                            originaldatei.remove();
                        }
                    }
                }
            }
        }else if(dateien_alle.zeile(i).right(fmc.length()) == DXF  || \
                 dateien_alle.zeile(i).right(fmc.length()) == DXF_     )
        {
            QString nam_ohn_end = dateien_alle.zeile(i).left(dateien_alle.zeile(i).length()-dxf.length());
            QString kenOb = Einstellung_dxf.kenObsei();
            QString kenUn = Einstellung_dxf.kenUnsei();
            QString nam_ohn_pref;
            bool ist_oberseite = true;
            if(nam_ohn_end.right(kenOb.length()) == kenOb)
            {
                nam_ohn_pref = nam_ohn_end.left(nam_ohn_end.length()-kenOb.length());
                ist_oberseite = true;
            }else if(nam_ohn_end.right(kenUn.length()) == kenUn)
            {
                nam_ohn_pref = nam_ohn_end.left(nam_ohn_end.length()-kenUn.length());
                ist_oberseite = false;
            }else
            {
                nam_ohn_pref = nam_ohn_end;
                ist_oberseite = true;
            }
            wste.neu(nam_ohn_pref, DXF);;//Wst wird nur angelegt wenn es nicht schon existiert

            QString pfad = Einstellung.verzeichnis_quelle() + QDir::separator() + dateien_alle.zeile(i);
            QFile datei(pfad);
            if(!datei.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QString tmp = "Fehler beim Dateizugriff!\n";
                tmp += pfad;
                tmp += "\n";
                tmp += "in der Funktion on_pushButton_start_clicked";
                QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
            }else
            {
                QString inhalt = datei.readAll();
                wste.import_dxf(nam_ohn_pref, inhalt, ist_oberseite);
                datei.close();
                if(Einstellung.quelldateien_erhalten() == false)
                {
                    QFile originaldatei(pfad);
                    originaldatei.remove();
                }
            }
        }
    }
    //Std-Wst-Namen:
    if(Einstellung.std_dateinamen_verwenden())
    {
        QString baugruppe = wste.stdnamen(namen_std_vor, namen_std_nach);
        ui->lineEdit_baugruppe->setText(baugruppe);
    }
    //wst-Sortieren:
    wste.sortieren();

    QApplication::restoreOverrideCursor();
}
QString MainWindow::verzeichnis_ziel()
{
    QDir d(Einstellung.verzeichnis_ziel_server());
    if(d.exists())
    {
        Einstellung.set_verzeichnis_ziel_auswahl(Einstellung.verzeichnis_ziel_server());
        return Einstellung.verzeichnis_ziel_server();
    }else
    {
        Einstellung.set_verzeichnis_ziel_auswahl(Einstellung.verzeichnis_ziel_lokal());
        return Einstellung.verzeichnis_ziel_lokal();
    }
}
void MainWindow::zielordner_leeren()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QString pfad = verzeichnis_ziel() + QDir::separator() + "eigen";
    QDir dir_eigen(pfad);
    if(dir_eigen.exists())
    {
        QStringList ordnerinhalt;
        ordnerinhalt = dir_eigen.entryList(QDir::Files);
        for(QStringList::iterator it = ordnerinhalt.begin() ; it!=ordnerinhalt.end() ; ++it)
        {
            QString name = *it;
            QFile tmp(pfad + QDir::separator() + name);
            tmp.remove();
        }
    }

    pfad = verzeichnis_ziel() + QDir::separator() + "fmc";
    QDir dir_fmc(pfad);
    if(dir_fmc.exists())
    {
        QStringList ordnerinhalt;
        ordnerinhalt = dir_fmc.entryList(QDir::Files);
        for(QStringList::iterator it = ordnerinhalt.begin() ; it!=ordnerinhalt.end() ; ++it)
        {
            QString name = *it;
            QFile tmp(pfad + QDir::separator() + name);
            tmp.remove();
        }
    }

    pfad = verzeichnis_ziel() + QDir::separator() + "ggf";
    QDir dir_ggf(pfad);
    if(dir_ggf.exists())
    {
        QStringList ordnerinhalt;
        ordnerinhalt = dir_ggf.entryList(QDir::Files);
        for(QStringList::iterator it = ordnerinhalt.begin() ; it!=ordnerinhalt.end() ; ++it)
        {
            QString name = *it;
            QFile tmp(pfad + QDir::separator() + name);
            tmp.remove();
        }
    }

    pfad = verzeichnis_ziel() + QDir::separator() + "ganx";
    QDir dir_ganx(pfad);
    if(dir_ganx.exists())
    {
        QStringList ordnerinhalt;
        ordnerinhalt = dir_ganx.entryList(QDir::Files);
        for(QStringList::iterator it = ordnerinhalt.begin() ; it!=ordnerinhalt.end() ; ++it)
        {
            QString name = *it;
            QFile tmp(pfad + QDir::separator() + name);
            tmp.remove();
        }
    }
    ui->plainTextEdit_eldungen->setPlainText("Zielordner wurden geleert.");
    QApplication::restoreOverrideCursor();
}
void MainWindow::closeEvent(QCloseEvent *ce)
{
    //if(irgendwas == true)
    //{
    //    ce->ignore();
    //}else
    //{
    //    ce->accept();
    //}
    dlg_prgtext.close();
    dlg_exporte.close();
    ce->accept();
}
void MainWindow::speichere_ausgabepfad(QString pfad)
{
    if(!pfad.isEmpty())
    {
        if(pfad.contains(".fmc") | pfad.contains(".ganx") | pfad.contains(".ggf") | pfad.contains(".eigen"))
        {
            QString pfad_neu = text_links(pfad, QDir::separator());;
            pfad_neu += QDir::separator();
            QString restpfad = text_rechts(pfad, pfad_neu);
            for(int i=1; i<pfad.count(QDir::separator()) ;i++)
            {
                QString tmp;
                tmp += text_links(restpfad, QDir::separator());
                if(i != pfad.count(QDir::separator())-1)
                {
                    tmp += QDir::separator();
                }
                pfad_neu += tmp;
                restpfad = text_rechts(restpfad, tmp);
            }
            pfad = pfad_neu;
        }
        Einstellung.set_verzeichnis_ziel_auswahl(pfad);
        schreibe_ini();
    }
}
void MainWindow::speichere_ausgabepfad_fmc(QString pfad)
{
    if(!pfad.isEmpty())
    {
        if(pfad.contains(".fmc"))
        {
            QString pfad_neu = text_links(pfad, QDir::separator());;
            pfad_neu += QDir::separator();
            QString restpfad = text_rechts(pfad, pfad_neu);
            for(int i=1; i<pfad.count(QDir::separator()) ;i++)
            {
                QString tmp;
                tmp += text_links(restpfad, QDir::separator());
                if(i != pfad.count(QDir::separator())-1)
                {
                    tmp += QDir::separator();
                }
                pfad_neu += tmp;
                restpfad = text_rechts(restpfad, tmp);
            }
            pfad = pfad_neu;
        }
        Einstellung.set_verzeichnis_ziel_auswahl(pfad);
        schreibe_ini();
    }
}
void MainWindow::schreibe_in_zwischenablage(QString s)
{
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(s);
}





































































































