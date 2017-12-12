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
    }
    if(inifile_gefunden == false)
    {
        QFile file(INIFILE);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
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

            ui->checkBox_af_ganx->setChecked(false);
            file.write("erzeuge_ganx:nein");
            file.write("\n");

            ui->checkBox_af_fmc->setChecked(false);
            file.write("erzeuge_fmc:nein");
            file.write("\n");

        }
        file.close();
    }else
    {
        QFile file(INIFILE);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
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
                }
            }
        }
        file.close();
    }
    if(wkz_ganx_gefunden == false)
    {
        QFile file(WERKZEUGDATEI_GANX);
        if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
        }else
        {
            //----------------------------------------------Tabellenkopf:
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
            file.write(" ");

            //file.write("\n");
        }
        file.close();
    }else
    {
        QFile file(WERKZEUGDATEI_GANX);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
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
            QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
        }else
        {
            //----------------------------------------------Tabellenkopf:
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
            file.write(" ");

            //file.write("\n");
        }
        file.close();
    }else
    {
        QFile file(WERKZEUGDATEI_FMC);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
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
        QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
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

        //-------------------------------------------Radio-Buttons:
        file.write("drehung_des_bauteils:");
        file.write(drehung_des_bauteils.toUtf8());
        file.write("\n");

    }
    file.close();
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

//-----------------------------------------------------------------------Menüs:
void MainWindow::on_actionInfo_triggered()
{
    QString tmp;
    tmp = "Postprozessor";
    tmp += "\t\tProgrammversion: ";
    tmp += PROGRAMMVERSION;

    ui->plainTextEdit_eldungen->setPlainText(tmp);
}
void MainWindow::on_actionWerkzeug_ganx_anzeigen_triggered()
{
    ui->plainTextEdit_eldungen->setPlainText(wkz_magazin_ganx.get_text());
}
void MainWindow::on_actionWerkzeug_fmc_anzeigen_triggered()
{
    ui->plainTextEdit_eldungen->setPlainText(wkz_magazin_fmc.get_text());
}

//-----------------------------------------------------------------------Buttons:
void MainWindow::on_pushButton_dateien_auflisten_clicked()
{
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
    QString vortext = "-----------------gefundene Dateien:\n";
    vortext += dateien_alle.get_text();
/*
    QString nachtext;
    if(std_namen == "ja")
    {
        nachtext += "\n-----------------Standard-Dateinamen:\n";
        for(uint i=1;i<=postfixe.zeilenanzahl();i++)
        {
            nachtext += postfixe.zeile(i);
            nachtext += "      -->      ";
            nachtext += namen_durch_std_namen_tauschen(postfixe.zeile(i));
            nachtext += "\n";
        }
    }
*/
    ui->plainTextEdit_eldungen->setPlainText(vortext);
}
void MainWindow::on_pushButton_start_clicked()
{
    wste.clear();
    dateien_erfassen();
    QString fmc = FMC;
    QString fmcA = FMC_PRGA;
    QString fmcB = FMC_PRGB;

    //Dateien einlesen:
    for(uint i=1; i<=dateien_alle.zeilenanzahl() ;i++)
    {
        if(dateien_alle.zeile(i).right(fmc.length()) == FMC)
        {
            QString nam_ohn_end = dateien_alle.zeile(i).left(dateien_alle.zeile(i).length()-fmc.length());

            if(nam_ohn_end.right(fmcA.length()) == FMC_PRGA)
            {
                QString nam_ohn_pref = nam_ohn_end.left(nam_ohn_end.length()-fmcA.length());
                if(wste.neu(nam_ohn_pref, FMC))//Wenn es das Wst bereits gibt
                {
                    QMessageBox mb;
                    mb.setText("Das Teil gibt es bereits");
                    mb.exec();
                    //Bearbeitungen auf der Wst-Unterseite importieren



                }else //Das Wst gab es noch nicht, es ist jetzt jungfräulich angelegt
                {
                    //Bearbeitungen auf der Wst-Obererseite importieren
                    QString pfad = ui->lineEdit_quelle->text() + QDir::separator() + dateien_alle.zeile(i);
                    QFile datei(pfad);
                    if(!datei.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
                    }else
                    {
                        QString inhalt = datei.readAll();
                        wste.import_fmc_oberseite(nam_ohn_pref, inhalt);


                    }
                }
            }else if(nam_ohn_end.right(fmcB.length()) == FMC_PRGB)
            {
                QString nam_ohn_pref = nam_ohn_end.left(nam_ohn_end.length()-fmcB.length());
                if(wste.neu(nam_ohn_pref, FMC))//Wenn es das Wst bereits gibt
                {
                    QMessageBox mb;
                    mb.setText("Das Teil gibt es bereits");
                    mb.exec();
                    //Bearbeitungen auf der Wst-Unterseite importieren



                }else//Das Wst gab es noch nicht, es ist jetzt jungfräulich angelegt
                {
                    //Bearbeitungen auf der Wst-Obererseite importieren
                    QString pfad = ui->lineEdit_quelle->text() + QDir::separator() + dateien_alle.zeile(i);
                    QFile datei(pfad);
                    if(!datei.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
                    }else
                    {
                        QString inhalt = datei.readAll();
                        wste.import_fmc_oberseite(nam_ohn_pref, inhalt);

                        //ui->plainTextEdit_eldungen->setPlainText(pfad);//nur erst einmal zum Testen
                        //ui->plainTextEdit_eldungen->setPlainText(inhalt);//nur erst einmal zum Testen
                    }
                }
            }else //Ober und Unterseite sind bereits in einem Programm zusammengeführt
            {
                //Dieser Fall wird vorerst nicht berücksichtigt
            }
        }
    }

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
    for(uint i=1; i<=wste.anzahl() ;i++)
    {
        if(erzeuge_ganx == "ja")
        {
            QString teilname = wste.get_name(i);
            teilname += GANX;

            QFile datei(pfad_ganx + QDir::separator() + teilname);
            if(!datei.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
            }else
            {
                QString tmp = wste.get_wst(i).get_ganx(wkz_magazin_ganx, drehung_des_bauteils);
                datei.write(tmp.toUtf8());
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
                QMessageBox::warning(this,"Fehler","Fehler beim Dateizugriff!",QMessageBox::Ok);
            }else
            {
                QString tmp = wste.get_wst(i).get_fmc(wkz_magazin_fmc, drehung_des_bauteils);
                datei.write(tmp.toUtf8());
            }
            datei.close();
        }
    }
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






































