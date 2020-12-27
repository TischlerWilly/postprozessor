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
    on_actionInfo_triggered();

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup()
{
    //Schauen ob alle Konfigurationsdateien vorhanden sind:
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
            ui->checkBox_af_ganx->setChecked(Einstellung.export_ganx());
            ui->checkBox_af_fmc->setChecked(Einstellung.export_fmc());
            ui->checkBox_af_ggf->setChecked(Einstellung.export_ggf());
            ui->checkBox_af_eigen->setChecked(Einstellung.export_eigen());
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
}
//-----------------------------------------------------------------------poblic slots:
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
void MainWindow::on_checkBox_af_ganx_stateChanged()
{
    Einstellung.set_export_ganx(ui->checkBox_af_ganx->isChecked());
    schreibe_ini();
}
void MainWindow::on_checkBox_af_fmc_stateChanged()
{
    Einstellung.set_export_fmc(ui->checkBox_af_fmc->isChecked());
    schreibe_ini();
}
void MainWindow::on_checkBox_af_ggf_stateChanged()
{
    Einstellung.set_export_ggf(ui->checkBox_af_ggf->isChecked());schreibe_ini();
}
void MainWindow::on_checkBox_af_eigen_stateChanged()
{
    Einstellung.set_export_eigen(ui->checkBox_af_eigen->isChecked());
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
    }
    schreibe_ini();
}
void MainWindow::on_radioButton_drehung_90_toggled(bool checked)
{
    if(checked)
    {
        Einstellung.set_drehung_wst("90");
    }
    schreibe_ini();
}
void MainWindow::on_radioButton_drehung_180_toggled(bool checked)
{
    if(checked)
    {
        Einstellung.set_drehung_wst("180");
    }
    schreibe_ini();
}
void MainWindow::on_radioButton_drehung_270_toggled(bool checked)
{
    if(checked)
    {
        Einstellung.set_drehung_wst("270");
    }
    schreibe_ini();
}
void MainWindow::on_radioButton_drehung_autom_toggled(bool checked)
{
    if(checked)
    {
        Einstellung.set_drehung_wst("AUTO");
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
        }
    }

    if(Einstellung.std_dateinamen_verwenden())
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
    QString pfad_ganx = verzeichnis_ziel() + QDir::separator() + "ganx";
    if(Einstellung.export_ganx())
    {
        dir_ganx.mkpath(pfad_ganx);
    }

    QDir dir_fmc;
    QString pfad_fmc = verzeichnis_ziel() + QDir::separator() + "fmc";
    if(Einstellung.export_fmc())
    {
        dir_fmc.mkpath(pfad_fmc);
    }

    QDir dir_eigen;
    QString pfad_eigen = verzeichnis_ziel() + QDir::separator() + "eigen";
    if(Einstellung.export_eigen())
    {
        dir_eigen.mkpath(pfad_eigen);
    }

    QDir dir_ggf;
    QString pfad_ggf = verzeichnis_ziel() + QDir::separator() + "ggf";
    if(Einstellung.export_ggf())
    {
        dir_eigen.mkpath(pfad_ggf);
    }

    for(uint i=1; i<=wste.anzahl() ;i++)
    {
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

        if(Einstellung.export_ganx())
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
                QString tmp = wste.wst(i).ganx(wkz_magazin_ganx, info, Einstellung.drehung_wst(), Einstellung_ganx);
                datei.write(tmp.toUtf8());
                QString output;
                output = teilname;
                //output += "\n";
                output += info;
                ui->plainTextEdit_eldungen->setPlainText(ui->plainTextEdit_eldungen->toPlainText() + output);
            }
            datei.close();
        }
        if(Einstellung.export_fmc())
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
                QString tmp = wste.wst(i).fmc(wkz_magazin_fmc, info, Einstellung.drehung_wst(), \
                                                      Einstellung.tiefeneinst_fkon(), foauf,fkonkanschon);
                datei.write(tmp.toUtf8());
                QString output;
                output = teilname;
                //output += "\n";
                output += info;
                ui->plainTextEdit_eldungen->setPlainText(ui->plainTextEdit_eldungen->toPlainText() + output);
            }
            datei.close();
        }
        if(Einstellung.export_ggf())
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
                QString tmp = wste.wst(i).ggf(wkz_magazin_ggf, info, Einstellung.drehung_wst());
                datei.write(tmp.toUtf8());
                QString output;
                output = teilname;                
                output += info;
                output += "\n";
                ui->plainTextEdit_eldungen->setPlainText(ui->plainTextEdit_eldungen->toPlainText() + output);
            }
            datei.close();
        }
        if(Einstellung.export_eigen())
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
                if(Einstellung.export_fmc()  &&  !Einstellung.export_ganx())
                {
                    tmp = wste.wst(i).eigenses_format(Einstellung.drehung_wst(), FMC, \
                                                              wkz_magazin_fmc, foauf, fkonkanschon);
                }else if(!Einstellung.export_fmc()  &&  Einstellung.export_ganx())
                {
                    tmp = wste.wst(i).eigenses_format(Einstellung.drehung_wst(), GANX, \
                                                              wkz_magazin_ganx, foauf, fkonkanschon);
                }else
                {
                    text_zeilenweise wkz_eigen;//leeres werkzeugmagazin
                    tmp = wste.wst(i).eigenses_format(Einstellung.drehung_wst(), EIGENES_FORMAT, \
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
    ui->plainTextEdit_zusatzinfo->clear();
    QApplication::restoreOverrideCursor();
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

QString MainWindow::verzeichnis_ziel()
{
    QDir d(Einstellung.verzeichnis_ziel_server());
    if(d.exists())
    {
        return Einstellung.verzeichnis_ziel_server();
    }else
    {
        return Einstellung.verzeichnis_ziel_lokal();
    }
}





































































