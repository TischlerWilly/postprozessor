#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pf.ordner_erstellen();
    verzeichnis_quelle  = "";
    verzeichnis_ziel    = "";
    drehung_des_bauteils = "0";
    tz = QDir::separator(); //Systemspezifischer Separator (Linux: Ordner/Unterordner/...)
    setup();
    on_actionInfo_triggered();

    connect(this, SIGNAL(sendDialogDataWKZ(QString,text_zeilenweise)), \
            &dlg_wkz, SLOT(getDialogDataWKZ(QString,text_zeilenweise)) );
    connect(&dlg_wkz, SIGNAL(sendData_wkzmagazin(QString,text_zeilenweise)), \
            this, SLOT(getDialogDataWKZ(QString,text_zeilenweise))     );
    connect(this, SIGNAL(sendStdNamen(text_zeilenweise, text_zeilenweise)),\
            &dlg_stdnamen, SLOT(slot_setup(text_zeilenweise,text_zeilenweise)));
    connect(&dlg_stdnamen, SIGNAL(signal_sendData(text_zeilenweise,text_zeilenweise)),\
            this, SLOT(getStdNamen(text_zeilenweise,text_zeilenweise)));
    connect(this, SIGNAL(sendEinstellungGANX(einstellung_ganx)),\
            &dlg_einstellung_ganx, SLOT(slot_einstellung(einstellung_ganx)));
    connect(&dlg_einstellung_ganx, SIGNAL(send_einstellung(einstellung_ganx)),\
            this, SLOT(getEinstellungGANX(einstellung_ganx )));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup()
{
    bool inifile_gefunden = false;      //user-Ordner
    bool wkz_ganx_gefunden = false;     //user-Ordner
    bool wkz_fmc_gefunden = false;      //user-Ordner
    bool wkz_ggf_gefunden = false;      //user-Ordner
    bool namen_std_gefunden = false;    //user-Ordner
    bool ini_ganx_gefunden = false;     //user-Ordner
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
    }
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
            file.write("verzeichnis_quelle:");
            file.write("\n");

            file.write("verzeichnis_ziel:");
            file.write("\n");

            file.write("geraden_schwellenwert:1");
            file.write("\n");
            geraden_schwellenwert = "1";
            ui->lineEdit_geraden_schwellenwert->setText(geraden_schwellenwert);
            wste.set_fkon_gerade_laenge(geraden_schwellenwert.toDouble());

            file.write("zugabe_gehrungen:20");
            file.write("\n");
            zugabe_gehrungen = "20";
            ui->lineEdit_zugabe_gehr->setText(zugabe_gehrungen);
            wste.set_zugabe_gehrungen(zugabe_gehrungen.toDouble());

            ui->checkBox_quelldat_erhalt->setChecked(true);
            file.write("quelldateien_erhalten:ja");
            file.write("\n");

            ui->checkBox_std_namen_zuweisen->setChecked(false);
            file.write("std_namen:nein");
            file.write("\n");

            ui->radioButton_drehung_0->setChecked(true);
            file.write("drehung_des_bauteils:0");
            file.write("\n");

            ui->radioButton_fkon_ti_quell->setChecked(true);
            file.write("tiefenzustellung_fkon:orgi");
            file.write("\n");

            ui->checkBox_af_ganx->setChecked(false);
            file.write("erzeuge_ganx:nein");
            file.write("\n");

            ui->checkBox_af_fmc->setChecked(false);
            file.write("erzeuge_fmc:nein");
            file.write("\n");

            ui->checkBox_af_ggf->setChecked(false);
            file.write("erzeuge_ggf:nein");
            file.write("\n");

            ui->checkBox_af_eigen->setChecked(false);
            file.write("erzeuge_eigen:nein");
            file.write("\n");

            ui->checkBox_geraden->setChecked(true);
            file.write("kurze_geraden_weglassen:ja");
            file.write("\n");
            wste.set_kurze_geraden_importieren(false);

            ui->checkBox_formatierung_aufbrechen->setChecked(false);
            file.write("formatierung_aufbrechen:nein");
            file.write("\n");

            ui->checkBox_fkon_kantenschonend->setChecked(false);
            file.write("fkon_kantenschonend:nein");
            file.write("\n");

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
            while(!file.atEnd())
            {
                QString zeile = QLatin1String(  file.readLine()  );
                if(zeile.contains("verzeichnis_quelle:"))
                {
                    verzeichnis_quelle = text_mitte(zeile, "verzeichnis_quelle:", "\n");
                    ui->lineEdit_quelle->setText(verzeichnis_quelle);
                }else if(zeile.contains("verzeichnis_zielA:"))
                {
                    verzeichnis_zielA = text_mitte(zeile, "verzeichnis_zielA:", "\n");
                    ui->lineEdit_zielA->setText(verzeichnis_zielA);
                }else if(zeile.contains("verzeichnis_zielB:"))
                {
                    verzeichnis_zielB = text_mitte(zeile, "verzeichnis_zielB:", "\n");
                    ui->lineEdit_zielB->setText(verzeichnis_zielB);
                }else if(zeile.contains("geraden_schwellenwert:"))
                {
                    geraden_schwellenwert = text_mitte(zeile, "geraden_schwellenwert:", "\n");
                    ui->lineEdit_geraden_schwellenwert->setText(geraden_schwellenwert);
                    wste.set_fkon_gerade_laenge(geraden_schwellenwert.toDouble());
                }else if(zeile.contains("zugabe_gehrungen:"))
                {
                    zugabe_gehrungen = text_mitte(zeile, "zugabe_gehrungen:", "\n");
                    ui->lineEdit_zugabe_gehr->setText(zugabe_gehrungen);
                    wste.set_zugabe_gehrungen(zugabe_gehrungen.toDouble());
                }else if(zeile.contains("use_zielB:"))
                {
                    use_zielB = text_mitte(zeile, "use_zielB:", "\n");
                    if(use_zielB == "ja")
                    {
                        ui->checkBox_use_ZielB->setChecked(true);
                        on_checkBox_use_ZielB_stateChanged();
                    }else
                    {
                        ui->checkBox_use_ZielB->setChecked(false);
                        on_checkBox_use_ZielB_stateChanged();
                    }
                }else if(zeile.contains("quelldateien_erhalten:"))
                {
                    quelldateien_erhalten = text_mitte(zeile, "quelldateien_erhalten:", "\n");
                    if(quelldateien_erhalten == "ja")
                    {
                        ui->checkBox_quelldat_erhalt->setChecked(true);
                    }else
                    {
                        ui->checkBox_quelldat_erhalt->setChecked(false);
                    }
                }else if(zeile.contains("std_namen:"))
                {
                    std_namen = text_mitte(zeile, "std_namen:", "\n");
                    if(std_namen == "ja")
                    {
                        ui->checkBox_std_namen_zuweisen->setChecked(true);
                    }else
                    {
                        ui->checkBox_std_namen_zuweisen->setChecked(false);
                    }
                }else if(zeile.contains("erzeuge_ganx:"))
                {
                    erzeuge_ganx = text_mitte(zeile, "erzeuge_ganx:", "\n");
                    if(erzeuge_ganx == "ja")
                    {
                        ui->checkBox_af_ganx->setChecked(true);
                    }else
                    {
                        ui->checkBox_af_ganx->setChecked(false);
                    }
                }else if(zeile.contains("erzeuge_fmc:"))
                {
                    erzeuge_fmc = text_mitte(zeile, "erzeuge_fmc:", "\n");
                    if(erzeuge_fmc == "ja")
                    {
                        ui->checkBox_af_fmc->setChecked(true);
                    }else
                    {
                        ui->checkBox_af_fmc->setChecked(false);
                    }
                }else if(zeile.contains("erzeuge_ggf:"))
                {
                    erzeuge_ggf = text_mitte(zeile, "erzeuge_ggf:", "\n");
                    if(erzeuge_ggf == "ja")
                    {
                        ui->checkBox_af_ggf->setChecked(true);
                    }else
                    {
                        ui->checkBox_af_ggf->setChecked(false);
                    }
                }else if(zeile.contains("erzeuge_eigen:"))
                {
                    erzeuge_eigenes_format = text_mitte(zeile, "erzeuge_eigen:", "\n");
                    if(erzeuge_eigenes_format == "ja")
                    {
                        ui->checkBox_af_eigen->setChecked(true);
                    }else
                    {
                        ui->checkBox_af_eigen->setChecked(false);
                    }
                }else if(zeile.contains("kurze_geraden_weglassen:"))
                {
                    kurze_geraden_weglassen = text_mitte(zeile, "kurze_geraden_weglassen:", "\n");
                    if(kurze_geraden_weglassen == "ja")
                    {
                        ui->checkBox_geraden->setChecked(true);
                        wste.set_kurze_geraden_importieren(false);
                    }else
                    {
                        ui->checkBox_geraden->setChecked(false);
                        wste.set_kurze_geraden_importieren(true);
                    }
                }else if(zeile.contains("drehung_des_bauteils:"))
                {
                    drehung_des_bauteils = text_mitte(zeile, "drehung_des_bauteils:", "\n");
                    if(drehung_des_bauteils == "0")
                    {
                        ui->radioButton_drehung_0->setChecked(true);
                    }else if(drehung_des_bauteils == "90")
                    {
                        ui->radioButton_drehung_90->setChecked(true);
                    }else if(drehung_des_bauteils == "180")
                    {
                        ui->radioButton_drehung_180->setChecked(true);
                    }else if(drehung_des_bauteils == "270")
                    {
                        ui->radioButton_drehung_270->setChecked(true);
                    }else if(drehung_des_bauteils == "AUTO")
                    {
                        ui->radioButton_drehung_autom->setChecked(true);
                    }
                }else if(zeile.contains("tiefenzustellung_fkon:"))
                {
                    option_fkon_ti = text_mitte(zeile, "tiefenzustellung_fkon:", "\n");
                    if(option_fkon_ti == "orgi")
                    {
                        ui->radioButton_fkon_ti_quell->setChecked(true);
                    }else if(option_fkon_ti == "wkz")
                    {
                        ui->radioButton_fkon_ti_wkz->setChecked(true);
                    }
                }else if(zeile.contains("formartierungen_aufbrechen:"))
                {
                    formartierungen_aufbrechen = text_mitte(zeile, "formartierungen_aufbrechen:", "\n");
                    if(formartierungen_aufbrechen == "ja")
                    {
                        ui->checkBox_formatierung_aufbrechen->setChecked(true);
                    }else
                    {
                        ui->checkBox_formatierung_aufbrechen->setChecked(false);
                    }
                }else if(zeile.contains("fkon_kantenschonend:"))
                {
                    fkon_kantenschonend = text_mitte(zeile, "fkon_kantenschonend:", "\n");
                    if(fkon_kantenschonend == "ja")
                    {
                        ui->checkBox_fkon_kantenschonend->setChecked(true);
                    }else
                    {
                        ui->checkBox_fkon_kantenschonend->setChecked(false);
                    }
                }
            }
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
            wkz_magazin_ganx.set_text(file.readAll());
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
            wkz_magazin_fmc.set_text(file.readAll());
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
            werkzeugmagazin wm;
            file.write(wm.tabellenkopf().toUtf8());
            wkz_magazin_ggf.set_text(wm.tabellenkopf());
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
            wkz_magazin_ggf.set_text(file.readAll());
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
}

void MainWindow::schreibe_ini()
{
    QFile file(pf.path_inifile());
    file.remove();
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString tmp = "Fehler beim Dateizugriff!\n";
        tmp += pf.path_inifile();
        tmp += "\n";
        tmp += "in der Funktion schreibe_ini";
        QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
    }else
    {
        //-------------------------------------------LineEdits:
        file.write("verzeichnis_quelle:");
        file.write(verzeichnis_quelle.toUtf8());
        file.write("\n");

        file.write("verzeichnis_zielA:");
        file.write(verzeichnis_zielA.toUtf8());
        file.write("\n");

        file.write("verzeichnis_zielB:");
        file.write(verzeichnis_zielB.toUtf8());
        file.write("\n");

        file.write("geraden_schwellenwert:");
        file.write(geraden_schwellenwert.toUtf8());
        file.write("\n");
        wste.set_fkon_gerade_laenge(geraden_schwellenwert.toDouble());

        file.write("zugabe_gehrungen:");
        file.write(zugabe_gehrungen.toUtf8());
        file.write("\n");
        wste.set_zugabe_gehrungen(zugabe_gehrungen.toDouble());

        //-------------------------------------------Checkboxen:
        file.write("use_zielB:");
        file.write(use_zielB.toUtf8());
        file.write("\n");

        file.write("quelldateien_erhalten:");
        file.write(quelldateien_erhalten.toUtf8());
        file.write("\n");

        file.write("std_namen:");
        file.write(std_namen.toUtf8());
        file.write("\n");

        file.write("erzeuge_ganx:");
        file.write(erzeuge_ganx.toUtf8());
        file.write("\n");

        file.write("erzeuge_fmc:");
        file.write(erzeuge_fmc.toUtf8());
        file.write("\n");

        file.write("erzeuge_ggf:");
        file.write(erzeuge_ggf.toUtf8());
        file.write("\n");

        file.write("erzeuge_eigen:");
        file.write(erzeuge_eigenes_format.toUtf8());
        file.write("\n");

        file.write("kurze_geraden_weglassen:");
        file.write(kurze_geraden_weglassen.toUtf8());
        file.write("\n");
        if(kurze_geraden_weglassen == "ja")
        {
            wste.set_kurze_geraden_importieren(false);
        }else
        {
            wste.set_kurze_geraden_importieren(true);
        }

        file.write("formartierungen_aufbrechen:");
        file.write(formartierungen_aufbrechen.toUtf8());
        file.write("\n");

        file.write("fkon_kantenschonend:");
        file.write(fkon_kantenschonend.toUtf8());
        file.write("\n");

        //-------------------------------------------Radio-Buttons:
        file.write("drehung_des_bauteils:");
        file.write(drehung_des_bauteils.toUtf8());
        file.write("\n");

        file.write("tiefenzustellung_fkon:");
        file.write(option_fkon_ti.toUtf8());
        file.write("\n");
    }
    file.close();
}

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
//-----------------------------------------------------------------------LineEdits:
void MainWindow::on_lineEdit_quelle_editingFinished()
{
    QString eingabe = ui->lineEdit_quelle->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_quelle->setText(verzeichnis_quelle);
    }else
    {
        verzeichnis_quelle = eingabe;
        schreibe_ini();
    }
}
void MainWindow::on_lineEdit_zielA_editingFinished()
{
    QString eingabe = ui->lineEdit_zielA->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_zielA->setText(verzeichnis_ziel);
    }else
    {
        verzeichnis_zielA = eingabe;
        schreibe_ini();
    }
}
void MainWindow::on_lineEdit_zielB_editingFinished()
{
    QString eingabe = ui->lineEdit_zielB->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_zielB->setText(verzeichnis_ziel);
    }else
    {
        verzeichnis_zielB = eingabe;
        schreibe_ini();
    }
}
void MainWindow::on_lineEdit_geraden_schwellenwert_editingFinished()
{
    QString eingabe = ui->lineEdit_geraden_schwellenwert->text();
    eingabe.replace(",",".");
    ui->lineEdit_geraden_schwellenwert->setText(eingabe);
    geraden_schwellenwert = eingabe;
    schreibe_ini();
}
void MainWindow::on_lineEdit_zugabe_gehr_editingFinished()
{
    QString eingabe = ui->lineEdit_zugabe_gehr->text();
    eingabe.replace(",",".");
    if(eingabe.toDouble() >= 0)
    {
        ui->lineEdit_zugabe_gehr->setText(eingabe);
        zugabe_gehrungen = eingabe;
        schreibe_ini();
    }else
    {
        QMessageBox::warning(this,"Fehler" ,"Eingaben kleiner als Nulle sind hier nicht erlaubt!",QMessageBox::Ok);
        ui->lineEdit_zugabe_gehr->setText(zugabe_gehrungen);
    }
}
//-----------------------------------------------------------------------Pfad-Buttons:
void MainWindow::on_pushButton__quelle_clicked()
{
    if(verzeichnis_quelle.isEmpty())
    {
        verzeichnis_quelle = "./";
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Quellverzeichniss"), verzeichnis_quelle);
    if(!tmp.isEmpty())
    {
        verzeichnis_quelle = tmp;
        ui->lineEdit_quelle->setText(verzeichnis_quelle);
        schreibe_ini();
    }
}
void MainWindow::on_pushButton_zielA_clicked()
{
    if(verzeichnis_zielA.isEmpty())
    {
        verzeichnis_zielA = "./";
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Zielverzeichniss"), verzeichnis_zielA);
    if(!tmp.isEmpty())
    {
        verzeichnis_zielA = tmp;
        ui->lineEdit_zielA->setText(verzeichnis_zielA);
        schreibe_ini();
    }
}
void MainWindow::on_pushButton_zielB_clicked()
{
    if(verzeichnis_zielB.isEmpty())
    {
        verzeichnis_zielB = "./";
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Zielverzeichniss"), verzeichnis_zielB);
    if(!tmp.isEmpty())
    {
        verzeichnis_zielB = tmp;
        ui->lineEdit_zielB->setText(verzeichnis_zielB);
        schreibe_ini();
    }
}

//-----------------------------------------------------------------------Checkboxen:
void MainWindow::on_checkBox_use_ZielB_stateChanged()
{
    if(ui->checkBox_use_ZielB->isChecked() == true)
    {
        use_zielB = "ja";
        verzeichnis_ziel = verzeichnis_zielB;
        ui->lineEdit_zielA->setDisabled(true);
        ui->lineEdit_zielB->setEnabled(true);
    }else
    {
        use_zielB = "nein";
        verzeichnis_ziel = verzeichnis_zielA;
        ui->lineEdit_zielB->setDisabled(true);
        ui->lineEdit_zielA->setEnabled(true);
    }
    schreibe_ini();
}
void MainWindow::on_checkBox_quelldat_erhalt_stateChanged()
{
    if(ui->checkBox_quelldat_erhalt->isChecked() == true)
    {
        quelldateien_erhalten = "ja";
    }else
    {
        quelldateien_erhalten = "nein";
    }
    schreibe_ini();
}
void MainWindow::on_checkBox_std_namen_zuweisen_stateChanged()
{
    if(ui->checkBox_std_namen_zuweisen->isChecked() == true)
    {
        std_namen = "ja";
    }else
    {
        std_namen = "nein";
    }
    schreibe_ini();
}
void MainWindow::on_checkBox_af_ganx_stateChanged()
{
    if(ui->checkBox_af_ganx->isChecked() == true)
    {
        erzeuge_ganx = "ja";
    }else
    {
        erzeuge_ganx = "nein";
    }
    schreibe_ini();
}
void MainWindow::on_checkBox_af_fmc_stateChanged()
{
    if(ui->checkBox_af_fmc->isChecked() == true)
    {
        erzeuge_fmc = "ja";
    }else
    {
        erzeuge_fmc = "nein";
    }
    schreibe_ini();
}
void MainWindow::on_checkBox_af_ggf_stateChanged()
{
    if(ui->checkBox_af_ggf->isChecked() == true)
    {
        erzeuge_ggf = "ja";
    }else
    {
        erzeuge_ggf = "nein";
    }
    schreibe_ini();
}
void MainWindow::on_checkBox_af_eigen_stateChanged()
{
    if(ui->checkBox_af_eigen->isChecked() == true)
    {
        erzeuge_eigenes_format = "ja";
    }else
    {
        erzeuge_eigenes_format = "nein";
    }
    schreibe_ini();
}
void MainWindow::on_checkBox_geraden_stateChanged()
{
    if(ui->checkBox_geraden->isChecked() == true)
    {
        kurze_geraden_weglassen = "ja";
    }else
    {
        kurze_geraden_weglassen = "nein";
    }
    schreibe_ini();
}
void MainWindow::on_checkBox_formatierung_aufbrechen_stateChanged()
{
    if(ui->checkBox_formatierung_aufbrechen->isChecked() == true)
    {
        formartierungen_aufbrechen = "ja";
    }else
    {
        formartierungen_aufbrechen = "nein";
    }
    schreibe_ini();
}
void MainWindow::on_checkBox_fkon_kantenschonend_stateChanged()
{
    QMessageBox mb;
    mb.setText("Diese Funktion ist derzeit leider noch nicht fertig!");
    mb.exec();

    if(ui->checkBox_fkon_kantenschonend->isChecked() == true)
    {
        fkon_kantenschonend = "ja";
    }else
    {
        fkon_kantenschonend = "nein";
    }
    schreibe_ini();
}
//-----------------------------------------------------------------------Radio-Buttons:
void MainWindow::on_radioButton_drehung_0_toggled(bool checked)
{
    if(checked)
    {
        drehung_des_bauteils = "0";
    }
    schreibe_ini();
}
void MainWindow::on_radioButton_drehung_90_toggled(bool checked)
{
    if(checked)
    {
        drehung_des_bauteils = "90";
    }
    schreibe_ini();
}
void MainWindow::on_radioButton_drehung_180_toggled(bool checked)
{
    if(checked)
    {
        drehung_des_bauteils = "180";
    }
    schreibe_ini();
}
void MainWindow::on_radioButton_drehung_270_toggled(bool checked)
{
    if(checked)
    {
        drehung_des_bauteils = "270";
    }
    schreibe_ini();
}
void MainWindow::on_radioButton_drehung_autom_toggled(bool checked)
{
    if(checked)
    {
        drehung_des_bauteils = "AUTO";
    }
    schreibe_ini();
}

void MainWindow::on_radioButton_fkon_ti_quell_toggled(bool checked)
{
    if(checked)
    {
        option_fkon_ti = "orgi";
    }
    schreibe_ini();
}
void MainWindow::on_radioButton_fkon_ti_wkz_toggled(bool checked)
{
    if(checked)
    {
        option_fkon_ti = "wkz";
    }
    schreibe_ini();
}

//-----------------------------------------------------------------------Menüs:
void MainWindow::on_actionInfo_triggered()
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
    tmp += "\n";

    tmp += "Hinweis zum GANX-Export:\n";
    tmp += "  Fräskonturen werden nicht ausgegeben.\n";

    ui->plainTextEdit_eldungen->setPlainText(tmp);

    //----------------------------------------------------------

    tmp  = "Der Postpozessor versucht fehlerhaft ausgegebene Bauteile zu erkennen.\n";
    tmp += "In diesem Textfeld werden die gefundenen Auffälligkeiten aufgelistet.";

    ui->plainTextEdit_zusatzinfo->setPlainText(tmp);
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
    emit sendDialogDataWKZ("Werkzeug GGF", wkz_magazin_ggf);
}
void MainWindow::on_actionStandard_Namen_anzeigen_triggered()
{
    emit sendStdNamen(namen_std_vor, namen_std_nach);
}
void MainWindow::on_actionEinstellung_ganx_triggered()
{
    emit sendEinstellungGANX(Einstellung_ganx);
}

//-----------------------------------------------------------------------Buttons:
void MainWindow::on_pushButton_dateien_auflisten_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    if(verzeichnis_quelle.isEmpty())
    {
        QMessageBox::warning(this,"Abbruch","Quellverzeichniss nicht angegeben!",QMessageBox::Ok);
        return;
    }
    if(verzeichnis_ziel.isEmpty())
    {
        QMessageBox::warning(this,"Abbruch","Zielverzeichniss nicht angegeben!",QMessageBox::Ok);
        return;
    }
    dateien_erfassen();
    QString vortext = int_to_qstring(dateien_alle.zeilenanzahl()) + " Dateien gefunden:\n";
    vortext += dateien_alle.text();
    ui->plainTextEdit_eldungen->setPlainText(vortext);
    ui->plainTextEdit_zusatzinfo->clear();

    QApplication::restoreOverrideCursor();
}
void MainWindow::on_pushButton_start_clicked()
{
    zielordner_leeren();

    QApplication::setOverrideCursor(Qt::WaitCursor);

    wste.clear();
    dateien_erfassen();
    QString fmc = FMC;
    QString fmcA = FMC_PRGA;
    QString fmcB = FMC_PRGB;

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
                    QString pfad = ui->lineEdit_quelle->text() + QDir::separator() + dateien_alle.zeile(i);
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
                        if(quelldateien_erhalten.contains("nein"))
                        {
                            QFile originaldatei(pfad);
                            originaldatei.remove();
                        }
                    }
                }else //Das Wst gab es noch nicht, es ist jetzt jungfräulich angelegt
                {
                    //Bearbeitungen auf der Wst-Obererseite importieren
                    QString pfad = ui->lineEdit_quelle->text() + QDir::separator() + dateien_alle.zeile(i);
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
                        if(quelldateien_erhalten.contains("nein"))
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
                    QString pfad = ui->lineEdit_quelle->text() + QDir::separator() + dateien_alle.zeile(i);
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
                        if(quelldateien_erhalten.contains("nein"))
                        {
                            QFile originaldatei(pfad);
                            originaldatei.remove();
                        }
                    }
                }else//Das Wst gab es noch nicht, es ist jetzt jungfräulich angelegt
                {
                    //Bearbeitungen auf der Wst-Obererseite importieren
                    QString pfad = ui->lineEdit_quelle->text() + QDir::separator() + dateien_alle.zeile(i);
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
                        if(quelldateien_erhalten.contains("nein"))
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
                    QString pfad = ui->lineEdit_quelle->text() + QDir::separator() + dateien_alle.zeile(i);
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
                        if(quelldateien_erhalten == "nein")
                        {
                            QFile originaldatei(pfad);
                            originaldatei.remove();
                        }
                    }
                }else //Das Wst gab es noch nicht, es ist jetzt jungfräulich angelegt
                {
                    //Bearbeitungen auf der Wst-Obererseite importieren
                    QString pfad = ui->lineEdit_quelle->text() + QDir::separator() + dateien_alle.zeile(i);
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
                        if(quelldateien_erhalten.contains("nein"))
                        {
                            QFile originaldatei(pfad);
                            originaldatei.remove();
                        }
                    }
                }
            }
        }
    }

    if(std_namen == "ja")
    {
        wste.stdnamen(namen_std_vor, namen_std_nach);
    }

    QString msg;
    msg = int_to_qstring(wste.namen_tz().zeilenanzahl()) + " eingelesene Dateien\n\n";
    msg += "------------------\n";
    ui->plainTextEdit_eldungen->setPlainText(msg);
    ui->plainTextEdit_zusatzinfo->setPlainText(wste.cad_fehler());

    //Einstellungen auf Werkstücke übertragen:
    //for(uint i=1; i<=wste.anzahl() ;i++)
    //{
    //    wste.wst(i).set_einstellung_ganx(Einstellung_ganx);
    //}

    //Datein exportieren:
    QDir dir_ganx;
    QString pfad_ganx = verzeichnis_ziel + QDir::separator() + "ganx";
    if(erzeuge_ganx == "ja")
    {
        dir_ganx.mkpath(pfad_ganx);
    }

    QDir dir_fmc;
    QString pfad_fmc = verzeichnis_ziel + QDir::separator() + "fmc";
    if(erzeuge_fmc == "ja")
    {
        dir_fmc.mkpath(pfad_fmc);
    }

    QDir dir_eigen;
    QString pfad_eigen = verzeichnis_ziel + QDir::separator() + "eigen";
    if(erzeuge_eigenes_format == "ja")
    {
        dir_eigen.mkpath(pfad_eigen);
    }

    QDir dir_ggf;
    QString pfad_ggf = verzeichnis_ziel + QDir::separator() + "ggf";
    if(erzeuge_ggf == "ja")
    {
        dir_eigen.mkpath(pfad_ggf);
    }

    for(uint i=1; i<=wste.anzahl() ;i++)
    {
        bool foauf;
        if(formartierungen_aufbrechen == "ja")
        {
            foauf = true;
        }else
        {
            foauf = false;
        }
        bool fkonkanschon;
        if(fkon_kantenschonend == "ja")
        {
            fkonkanschon = true;
        }else
        {
            fkonkanschon = false;
        }

        if(erzeuge_ganx == "ja")
        {
            QString teilname = wste.name(i);
            teilname += GANX;

            QFile datei(pfad_ganx + QDir::separator() + teilname);
            if(!datei.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QString tmp = "Fehler beim Dateizugriff!\n";
                tmp += pfad_ganx + QDir::separator() + teilname;
                tmp += "\n";
                tmp += "in der Funktion on_pushButton_start_clicked";
                QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
            }else
            {
                QString info = "";
                QString tmp = wste.wst(i).ganx(wkz_magazin_ganx, info, drehung_des_bauteils, Einstellung_ganx);
                datei.write(tmp.toUtf8());
                QString output;
                output = teilname;
                //output += "\n";
                output += info;
                ui->plainTextEdit_eldungen->setPlainText(ui->plainTextEdit_eldungen->toPlainText() + output);
            }
            datei.close();
        }
        if(erzeuge_fmc == "ja")
        {
            QString teilname = wste.name(i);
            teilname += FMC;

            QFile datei(pfad_fmc + QDir::separator() + teilname);
            if(!datei.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QString tmp = "Fehler beim Dateizugriff!\n";
                tmp += pfad_fmc + QDir::separator() + teilname;
                tmp += "\n";
                tmp += "in der Funktion on_pushButton_start_clicked";
                QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
            }else
            {
                QString info = "";                
                QString tmp = wste.wst(i).fmc(wkz_magazin_fmc, info, drehung_des_bauteils, \
                                                      option_fkon_ti, foauf,fkonkanschon);
                datei.write(tmp.toUtf8());
                QString output;
                output = teilname;
                //output += "\n";
                output += info;
                ui->plainTextEdit_eldungen->setPlainText(ui->plainTextEdit_eldungen->toPlainText() + output);
            }
            datei.close();
        }
        if(erzeuge_ggf == "ja")
        {
            QString teilname = wste.name(i);
            teilname += GGF;

            QFile datei(pfad_ggf + QDir::separator() + teilname);
            if(!datei.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QString tmp = "Fehler beim Dateizugriff!\n";
                tmp += pfad_fmc + QDir::separator() + teilname;
                tmp += "\n";
                tmp += "in der Funktion on_pushButton_start_clicked";
                QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
            }else
            {
                QString info = "";
                QString tmp = wste.wst(i).ggf(wkz_magazin_ggf, info, drehung_des_bauteils);
                datei.write(tmp.toUtf8());
                QString output;
                output = teilname;                
                output += info;
                output += "\n";
                ui->plainTextEdit_eldungen->setPlainText(ui->plainTextEdit_eldungen->toPlainText() + output);
            }
            datei.close();
        }
        if(erzeuge_eigenes_format == "ja")
        {
            QString teilname = wste.name(i);
            teilname += EIGENES_FORMAT;

            QFile datei(pfad_eigen + QDir::separator() + teilname);
            if(!datei.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QString tmp = "Fehler beim Dateizugriff!\n";
                tmp += pfad_eigen + QDir::separator() + teilname;
                tmp += "\n";
                tmp += "in der Funktion on_pushButton_start_clicked";
                QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
            }else
            {
                QString tmp;
                if(erzeuge_fmc  == "ja"  &&  erzeuge_ganx != "ja")
                {
                    tmp = wste.wst(i).eigenses_format(drehung_des_bauteils, FMC, \
                                                              wkz_magazin_fmc, foauf, fkonkanschon);
                }else if(erzeuge_fmc  != "ja"  &&  erzeuge_ganx == "ja")
                {
                    tmp = wste.wst(i).eigenses_format(drehung_des_bauteils, GANX, \
                                                              wkz_magazin_ganx, foauf, fkonkanschon);
                }else
                {
                    text_zeilenweise wkz_eigen;//leeres werkzeugmagazin
                    tmp = wste.wst(i).eigenses_format(drehung_des_bauteils, EIGENES_FORMAT, \
                                                              wkz_eigen, foauf, fkonkanschon);
                }
                datei.write(tmp.toUtf8());
                QString output;
                output = teilname;
                output += "\n";
                ui->plainTextEdit_eldungen->setPlainText(ui->plainTextEdit_eldungen->toPlainText() + output);
            }
            datei.close();
        }


    }

    QString slist; //Stückliste
    slist += "\n";
    slist += "----------------------------Stückliste----------------------------";
    slist += "\n";
    slist += "Bezeichnung";
    slist += "\t";
    slist += "Länge";
    slist += "\t";
    slist += "Breite";
    slist += "\t";
    slist += "Dicke";
    slist += "\n";
    for(uint i=1; i<=wste.anzahl() ;i++)
    {
        slist += wste.wst(i).name();
        slist += "\t";
        slist += wste.wst(i).laenge_qstring();
        slist += "\t";
        slist += wste.wst(i).breite_qstring();
        slist += "\t";
        slist += wste.wst(i).dicke_qstring();
        slist += "\n";
    }
    ui->plainTextEdit_eldungen->setPlainText(ui->plainTextEdit_eldungen->toPlainText() + slist);

    QApplication::restoreOverrideCursor();
}
void MainWindow::zielordner_leeren()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QString pfad = verzeichnis_ziel + QDir::separator() + "eigen";
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

    pfad = verzeichnis_ziel + QDir::separator() + "fmc";
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

    pfad = verzeichnis_ziel + QDir::separator() + "ggf";
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

    pfad = verzeichnis_ziel + QDir::separator() + "ganx";
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
    ui->plainTextEdit_zusatzinfo->clear();
    QApplication::restoreOverrideCursor();
}

//-----------------------------------------------------------------------
void MainWindow::dateien_erfassen()
{
    QDir ordner(verzeichnis_quelle);
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





































































