#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup()
{
    bool inifile_gefunden = false;
    bool wkz_ganx_gefunden = false;
    bool wkz_fmc_gefunden = false;
    bool namen_std_gefunden = false;
    QDir programmordner("./");
    QStringList ordnerinhalt;
    ordnerinhalt = programmordner.entryList(QDir::Files);
    for(QStringList::iterator it = ordnerinhalt.begin() ; it!=ordnerinhalt.end() ; ++it)
    {
        QString name = *it;
        if(name.contains(INIFILE))
        {
            inifile_gefunden = true;
        }
        if(name.contains(WERKZEUGDATEI_GANX))
        {
            wkz_ganx_gefunden = true;
        }
        if(name.contains(WERKZEUGDATEI_FMC))
        {
            wkz_fmc_gefunden = true;
        }
        if(name.contains(NAMEN_STD_INI))
        {
            namen_std_gefunden = true;
        }
    }
    if(inifile_gefunden == false)
    {
        QFile file(INIFILE);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += INIFILE;
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            file.write("verzeichnis_quelle:");
            file.write("\n");

            file.write("verzeichnis_ziel:");
            file.write("\n");

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

            ui->checkBox_af_eigen->setChecked(false);
            file.write("erzeuge_eigen:nein");
            file.write("\n");

        }
        file.close();
    }else
    {
        QFile file(INIFILE);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += INIFILE;
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
                }else if(zeile.contains("verzeichnis_ziel:"))
                {
                    verzeichnis_ziel = text_mitte(zeile, "verzeichnis_ziel:", "\n");
                    ui->lineEdit_ziel->setText(verzeichnis_ziel);
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
                }
            }
        }
        file.close();
    }

    if(namen_std_gefunden == false)
    {
        QFile file(NAMEN_STD_INI);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += NAMEN_STD_INI;
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            file.write("Namen original");
            file.write(NAMEN_STD_INI_TZ_);
            file.write("Namen neu");
        }
        file.close();
    }else
    {
        QFile file(NAMEN_STD_INI);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += NAMEN_STD_INI;
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

    if(wkz_ganx_gefunden == false)
    {
        QFile file(WERKZEUGDATEI_GANX);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += WERKZEUGDATEI_GANX;
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            //----------------------------------------------Tabellenkopf:
            werkzeugmagazin wm;
            file.write(wm.get_tabellenkopf().toUtf8());
            /*
            file.write("Typ");
            file.write("\t");
            file.write("Nummer");
            file.write("\t");
            file.write("Durchmesser");
            file.write("\t");
            file.write("Nutzlaenge");
            file.write("\t");
            file.write("Vorschub");
            file.write("\t");
            file.write("Zustellmass");
            file.write("\t");
            file.write("DM_CAD");
            file.write("\t");
            file.write("Ist Durchgangsbohrer");
            file.write("\t");
            file.write(" ");
            */
            //file.write("\n");
        }
        file.close();
    }else
    {
        QFile file(WERKZEUGDATEI_GANX);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += WERKZEUGDATEI_GANX;
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
        QFile file(WERKZEUGDATEI_FMC);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += WERKZEUGDATEI_FMC;
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            //----------------------------------------------Tabellenkopf:
            werkzeugmagazin wm;
            file.write(wm.get_tabellenkopf().toUtf8());
            /*
            file.write("Typ");
            file.write("\t");
            file.write("Nummer");
            file.write("\t");
            file.write("Durchmesser");
            file.write("\t");
            file.write("Nutzlaenge");
            file.write("\t");
            file.write("Vorschub");
            file.write("\t");
            file.write("Zustellmass");
            file.write("\t");
            file.write("DM_CAD");
            file.write("\t");
            file.write("Ist Durchgangsbohrer");
            file.write("\t");
            file.write(" ");
            */
            //file.write("\n");
        }
        file.close();
    }else
    {
        QFile file(WERKZEUGDATEI_FMC);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += WERKZEUGDATEI_FMC;
            tmp += "\n";
            tmp += "in der Funktion setup";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            wkz_magazin_fmc.set_text(file.readAll());
        }
        file.close();
    }
}

void MainWindow::schreibe_ini()
{
    QFile file(INIFILE);
    file.remove();
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString tmp = "Fehler beim Dateizugriff!\n";
        tmp += INIFILE;
        tmp += "\n";
        tmp += "in der Funktion schreibe_ini";
        QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
    }else
    {
        //-------------------------------------------Verzeichnisse:
        file.write("verzeichnis_quelle:");
        file.write(verzeichnis_quelle.toUtf8());
        file.write("\n");

        file.write("verzeichnis_ziel:");
        file.write(verzeichnis_ziel.toUtf8());
        file.write("\n");

        //-------------------------------------------Checkboxen:
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

        file.write("erzeuge_eigen:");
        file.write(erzeuge_eigenes_format.toUtf8());
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
        QFile file(WERKZEUGDATEI_GANX);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += WERKZEUGDATEI_GANX;
            tmp += "\n";
            tmp += "in der Funktion getDialogDataWKZ";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            wkz_magazin_ganx = werkzeugmagazin;
            file.write(werkzeugmagazin.get_text().toUtf8());
        }
        file.close();
    }else if(fenstertitel.contains("FMC"))
    {
        QFile file(WERKZEUGDATEI_FMC);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QString tmp = "Fehler beim Dateizugriff!\n";
            tmp += WERKZEUGDATEI_FMC;
            tmp += "\n";
            tmp += "in der Funktion getDialogDataWKZ";
            QMessageBox::warning(this,"Fehler",tmp,QMessageBox::Ok);
        }else
        {
            wkz_magazin_fmc = werkzeugmagazin;
            file.write(werkzeugmagazin.get_text().toUtf8());
        }
        file.close();
    }
}

//-----------------------------------------------------------------------Pfade:
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
void MainWindow::on_lineEdit_ziel_editingFinished()
{
    QString eingabe = ui->lineEdit_ziel->text();
    if(!QDir(eingabe).exists())
    {
        QMessageBox::warning(this,"Fehler","Verzeichniss \"" + eingabe + "\" nicht gefunden!",QMessageBox::Ok);
        ui->lineEdit_ziel->setText(verzeichnis_ziel);
    }else
    {
        verzeichnis_ziel = eingabe;
        schreibe_ini();
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
void MainWindow::on_pushButton_ziel_clicked()
{
    if(verzeichnis_ziel.isEmpty())
    {
        verzeichnis_ziel = "./";
    }
    QString tmp = QFileDialog::getExistingDirectory(this, tr("Zielverzeichniss"), verzeichnis_ziel);
    if(!tmp.isEmpty())
    {
        verzeichnis_ziel = tmp;
        ui->lineEdit_ziel->setText(verzeichnis_ziel);
        schreibe_ini();
    }
}

//-----------------------------------------------------------------------Checkboxen:
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
    tmp = "Postprozessor";
    tmp += "\t\tProgrammversion: ";
    tmp += PROGRAMMVERSION;
    tmp += "\n\n";

    tmp += "Moegliche Importformate:\n";
    tmp += "  *.FMC / *.fmc (IMAWOP4)\n";
    tmp += "\n";

    tmp += "Hinweis zum GANX-Export:\n";
    tmp += "  Fraeskonturen werden ignoriert.";

    ui->plainTextEdit_eldungen->setPlainText(tmp);

    //----------------------------------------------------------

    tmp  = "Der Postpozessor versucht fehlerhaft ausgegebene Bauteile zu erkennen.\n";
    tmp += "In diesem Textfeld werden die gefundenen Auffaelligkeiten aufgelistet.";

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
void MainWindow::on_actionStandard_Namen_anzeigen_triggered()
{
    QString msg = "";
    //Längsten Namen finden:
    int anz_zeichen = 0;
    for(uint i=1; i<=namen_std_vor.zeilenanzahl() ;i++)
    {
        if(namen_std_vor.zeile(i).count() > anz_zeichen)
        {
            anz_zeichen = namen_std_vor.zeile(i).count();
        }
    }
    //Allen Namen die gleiche Länge geben:
    text_zeilenweise tz;
    for(uint i=1; i<=namen_std_vor.zeilenanzahl() ;i++)
    {
        QString tmp = namen_std_vor.zeile(i);
        while(tmp.count() < anz_zeichen)
        {
            tmp += " ";
        }
        tz.zeile_anhaengen(tmp);
    }
    //Auflistung erstellen:
    for(uint i=1; i<=namen_std_vor.zeilenanzahl() ;i++)
    {
        //msg += namen_std_vor.zeile(i);
        msg += tz.zeile(i);
        msg += "\t";
        msg += namen_std_nach.zeile(i);
        msg += "\n";
    }
    ui->plainTextEdit_eldungen->setPlainText(msg);
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
    vortext += dateien_alle.get_text();
    ui->plainTextEdit_eldungen->setPlainText(vortext);
    ui->plainTextEdit_zusatzinfo->clear();

    QApplication::restoreOverrideCursor();
}
void MainWindow::on_pushButton_start_clicked()
{
    on_pushButton_zielordner_leeren_clicked();

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
    msg = int_to_qstring(wste.get_namen_tz().zeilenanzahl()) + " eingelesene Dateien\n\n";
    msg += "------------------\n";
    ui->plainTextEdit_eldungen->setPlainText(msg);
    ui->plainTextEdit_zusatzinfo->setPlainText(wste.suche_cad_fehler());

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

    for(uint i=1; i<=wste.anzahl() ;i++)
    {
        if(erzeuge_ganx == "ja")
        {
            QString teilname = wste.get_name(i);
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
                QString tmp = wste.get_wst(i).get_ganx(wkz_magazin_ganx, info, drehung_des_bauteils);
                datei.write(tmp.toUtf8());
                QString output;
                output = teilname;
                output += "\n";
                output += info;
                ui->plainTextEdit_eldungen->setPlainText(ui->plainTextEdit_eldungen->toPlainText() + output);
            }
            datei.close();
        }
        if(erzeuge_fmc == "ja")
        {
            QString teilname = wste.get_name(i);
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
                QString tmp = wste.get_wst(i).get_fmc(wkz_magazin_fmc, info, drehung_des_bauteils, option_fkon_ti);
                datei.write(tmp.toUtf8());
                QString output;
                output = teilname;
                output += "\n";
                output += info;
                ui->plainTextEdit_eldungen->setPlainText(ui->plainTextEdit_eldungen->toPlainText() + output);
            }
            datei.close();
        }
        if(erzeuge_eigenes_format == "ja")
        {
            QString teilname = wste.get_name(i);
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
                QString info = "";
                QString tmp = wste.get_wst(i).get_eigenses_format(drehung_des_bauteils);
                datei.write(tmp.toUtf8());
                QString output;
                output = teilname;
                output += "\n";
                ui->plainTextEdit_eldungen->setPlainText(ui->plainTextEdit_eldungen->toPlainText() + output);
            }
            datei.close();

        }
    }

    QApplication::restoreOverrideCursor();
}
void MainWindow::on_pushButton_zielordner_leeren_clicked()
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














































