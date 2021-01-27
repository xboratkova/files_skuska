#include "Autoserviskb.h"

Autoserviskb::Autoserviskb(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void Autoserviskb::openUserFile(QString s) {
    QString fileName = s;
    QString data;
    QFile importedCSV(fileName);
    QStringList rowOfData;
    QStringList rowData;
    rowOfData.clear();
    rowData.clear();

    if (importedCSV.open(QFile::ReadOnly))
    {
        data = importedCSV.readAll();
        rowOfData = data.split("\n");
        importedCSV.close();
    }

    for (int x = 0; x < rowOfData.size(); x++)
    {
        rowData = rowOfData.at(x).split(";");
        ui.uzivatelia_2->addItem(rowData.at(0));
    }
}

void Autoserviskb::importCSVFile() {
    QString fileName = "sluzby/Sluzby.csv"; ///QFileDialog::getOpenFileName(this, ("Open File"), "sluzby", ("csv File(*.csv)"));
    QFile importedCSV(fileName);

    if (importedCSV.open(QFile::ReadOnly))
    {
        QTextStream in(&importedCSV);
        while (!in.atEnd())
        {
            Produkty sluzba;
            sluzba.napln(in.readLine());
            sluzbyvektor.append(sluzba);
        }
        importedCSV.close();
    }
    ui.sluzby->setRowCount(sluzbyvektor.size());
    ui.sluzby->setColumnCount(3);

    for (int x = 0; x < sluzbyvektor.size(); x++)
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText(sluzbyvektor[x].getnazov());

        QTableWidgetItem* item2 = new QTableWidgetItem();
        item2->setText(sluzbyvektor[x].getcena());

        QTableWidgetItem* item3 = new QTableWidgetItem();
        item3->setText(sluzbyvektor[x].getcenabez());
        ui.sluzby->setItem(x, 0, item);
        ui.sluzby->setItem(x, 1, item2);
        ui.sluzby->setItem(x, 2, item3);
    }
}

void Autoserviskb::getPassword(QString s) {
    QString fileName = s;
    QString data;
    QFile importedCSV(fileName);
    QStringList rowOfData;
    QStringList rowData;
    rowOfData.clear();
    rowData.clear();

    if (importedCSV.open(QFile::ReadOnly))
    {
        data = importedCSV.readAll();
        rowOfData = data.split("\n");
        importedCSV.close();
    }

    int x = ui.uzivatelia_2->currentIndex();
    rowData = rowOfData.at(x).split(";");
    if (stav == 1) {
        admin->setPrihlasUdaje(rowData.at(0), rowData.at(1));

    }
    if (stav == 2) {
        zamestnanec->setPrihlasUdaje(rowData.at(0), rowData.at(1));
    }
    if (stav == 3) {
        firma->setPrihlasUdaje(rowData.at(0), rowData.at(1));
    }
    if (stav == 4) {
        osoba->setPrihlasUdaje(rowData.at(0), rowData.at(1));
    }
    importedCSV.close();
}

void Autoserviskb::on_admin_2_clicked() {
    openUserFile("users/userlistAdmin.csv");
    stav = 1;
    admin = new Uzivatel();
    ui.admin_2->setEnabled(false);
    ui.osoba_2->setEnabled(false);
    ui.firma_2->setEnabled(false);
    ui.zamestnanec_2->setEnabled(false);
    
}

void Autoserviskb::on_zamestnanec_2_clicked()  {
    openUserFile("users/userlistZam.csv");
    stav = 2;
    zamestnanec = new Zamestnanec();
    ui.admin_2->setEnabled(false);
    ui.osoba_2->setEnabled(false);
    ui.firma_2->setEnabled(false);
    ui.zamestnanec_2->setEnabled(false);
}

void Autoserviskb::on_firma_2_clicked() {
    openUserFile("users/userlistFirmy.csv");
    stav = 3;
    firma = new Firma();
    ui.admin_2->setEnabled(false);
    ui.osoba_2->setEnabled(false);
    ui.firma_2->setEnabled(false);
    ui.zamestnanec_2->setEnabled(false);
}

void Autoserviskb::on_osoba_2_clicked() {
    openUserFile("users/userlistOsoby.csv");
    stav = 4;
    osoba = new Osoba();
    ui.admin_2->setEnabled(false);
    ui.osoba_2->setEnabled(false);
    ui.firma_2->setEnabled(false);
    ui.zamestnanec_2->setEnabled(false);
}

void Autoserviskb::on_prihlas_2_clicked() {
    importCSVFile();

    if (stav == 1) {

        getPassword("users/userlistAdmin.csv");

        QString heslo = ui.heslo_2->text();
        QString sHeslo = QCryptographicHash::hash(heslo.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
        qDebug() << sHeslo;
        if (sHeslo != admin->getHeslo()) {
            QMessageBox msgbox;
            msgbox.setText("Nespravne heslo");
            msgbox.exec();
            return;
        }
        else {
            ui.groupBox_9->setEnabled(true);
            ui.menuAdmin->setEnabled(true);
            ui.groupBox_7->setEnabled(false);
        }

    }
    if (stav == 2) {
        getPassword("users/userlistZam.csv");

        QString heslo = ui.heslo_2->text();
        QString sHeslo = QCryptographicHash::hash(heslo.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
        if (sHeslo != zamestnanec->getHeslo()) {
            QMessageBox msgbox;
            msgbox.setText("Nespravne heslo");
            msgbox.exec();
            return;
        }
        else {
            ui.groupBox_5->setEnabled(true);
            loadUserfileZam("users/userlistFirmy.csv");
            loadUserfileZam("users/userlistOsoby.csv");
            nacitajOsUj();
            ui.lineEdit_4->setEnabled(false);
            ui.lineEdit_5->setEnabled(false);
            ui.lineEdit_6->setEnabled(false);
            ui.lineEdit_7->setEnabled(false);
            ui.lineEdit_8->setEnabled(false);

        }
    }
    if (stav == 3) {
        getPassword("users/userlistFirmy.csv");

        QString heslo = ui.heslo_2->text();
        QString sHeslo = QCryptographicHash::hash(heslo.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
        if (sHeslo != firma->getHeslo()) {
            QMessageBox msgbox;
            msgbox.setText("Nespravne heslo");
            msgbox.exec();
            return;
        }
        else {
            loadVybrane();
            loadPotvrdene();
            nacitajOsUj();
            ui.lineEdit_9->setEnabled(false);
        }
    }
    if (stav == 4) {
        getPassword("users/userlistOsoby.csv");
        QString heslo = ui.heslo_2->text();
        QString sHeslo = QCryptographicHash::hash(heslo.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
        if (sHeslo != osoba->getHeslo()) {
            QMessageBox msgbox;
            msgbox.setText("Nespravne heslo");
            msgbox.exec();
            return;
        }
        else {
            loadVybrane();
            loadPotvrdene();
            nacitajOsUj();
            ui.lineEdit_7->setEnabled(false);
            ui.lineEdit_8->setEnabled(false);
            ui.lineEdit_9->setEnabled(false);
        }

    }
}

void Autoserviskb::on_vytvor_2_clicked() {
    qDebug() << "kliknute na vytvor";
    if (ui.zamestnanecRadio_2->isChecked()) {
        QString fileName = "users/userlistZam.csv";
        QFile importedCSV(fileName);
        if (importedCSV.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&importedCSV);
            QString heslo = ui.noveheslo_2->text();
            QString sifHeslo = QCryptographicHash::hash(heslo.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
            out << ui.novemeno_2->text() << ";" << sifHeslo << ";" << "\n";
        }
        importedCSV.close();
        vytvorSubor();
        vytvorOsUdaje();
    }
    if (ui.osobaRadio_2->isChecked()) {
        QString fileName = "users/userlistOsoby.csv";
        QFile importedCSV(fileName);
        if (importedCSV.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&importedCSV);
            QString heslo = ui.noveheslo_2->text();
            QString sifHeslo = QCryptographicHash::hash(heslo.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
            out << ui.novemeno_2->text() << ";" << sifHeslo << ";" << "\n";
        }
        importedCSV.close();
        vytvorSubor();
        vytvorOsUdaje();
    }
    if (ui.frimaRadio_2->isChecked()) {
        QString fileName = "users/userlistFirmy.csv";
        QFile importedCSV(fileName);
        if (importedCSV.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&importedCSV);
            QString heslo = ui.noveheslo_2->text();
            QString sifHeslo = QCryptographicHash::hash(heslo.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
            out << ui.novemeno_2->text() << ";" << sifHeslo << ";" << "\n";
        }
        importedCSV.close();
        vytvorSubor();
        vytvorOsUdaje();
    }
}

void Autoserviskb::on_vybrat_clicked() {
    int b = ui.sluzby->currentRow();
    objednane.append(sluzbyvektor[b]);
    for (int i = 0; i < ui.vybrane->rowCount(); i++) {
        ui.vybrane->removeRow(i);
    }
    loadVektor();
}

void Autoserviskb::vytvorSubor() {
    QString fileName = "subory/" + ui.novemeno_2->text() + ".csv";
    qDebug() << fileName;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    file.close();
}

void Autoserviskb::vytvorOsUdaje() {
    QString fileName = "osudaje/" + ui.novemeno_2->text() + ".csv";
    qDebug() << fileName;
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);
    stream << "Meno/firma" << ";" << "none" << ";" << "\n";
    stream << "Znaèka" << ";" << "none" << ";" << "\n";
    stream << "Model" << ";" << "none" << ";" << "\n";
    stream << "Rok výroby" << ";" << "none" << ";" << "\n";
    if (ui.frimaRadio_2->isChecked()) {
        stream << "IÈO" << ";" << "none" << ";" << "\n";
        stream << "Platca DPH" << ";" << "none" << ";" << "\n";
    }
    if (ui.zamestnanecRadio_2->isChecked()) {
        stream << "Pozicia" << ";" << "none" << ";" << "\n";
    }

    file.close();
}

void Autoserviskb::loadVektor() {
    ui.vybrane->setRowCount(objednane.size());
    ui.vybrane->setColumnCount(3);

    for (int x = 0; x < objednane.size(); x++)
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText(objednane[x].getnazov());

        QTableWidgetItem* item2 = new QTableWidgetItem();
        item2->setText(objednane[x].getcena());

        QTableWidgetItem* item3 = new QTableWidgetItem();
        item3->setText(objednane[x].getcenabez());
        ui.vybrane->setItem(x, 0, item);
        ui.vybrane->setItem(x, 1, item2);
        ui.vybrane->setItem(x, 2, item3);
    }
}

void Autoserviskb::loadVybrane() {
    QString meno = ui.uzivatelia_2->currentText();
    QString fileName1 = "subory/" + meno + ".csv"; ///QFileDialog::getOpenFileName(this, ("Open File"), "sluzby", ("csv File(*.csv)"));
    QFile importedCSV1(fileName1);
    if (importedCSV1.open(QFile::ReadOnly))
    {
        QTextStream in(&importedCSV1);
        in.setCodec("UTF-8");
        while (!in.atEnd())
        {
            Produkty sluzba;
            sluzba.napln(in.readLine());
            objednane.append(sluzba);
        }
        importedCSV1.close();
    }
    ui.vybrane->setRowCount(objednane.size());
    ui.vybrane->setColumnCount(3);

    for (int x = 0; x < objednane.size(); x++)
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText(objednane[x].getnazov());

        QTableWidgetItem* item2 = new QTableWidgetItem();
        item2->setText(objednane[x].getcena());

        QTableWidgetItem* item3 = new QTableWidgetItem();
        item3->setText(objednane[x].getcenabez());
        ui.vybrane->setItem(x, 0, item);
        ui.vybrane->setItem(x, 1, item2);
        ui.vybrane->setItem(x, 2, item3);
    }


}

void Autoserviskb::ulozVybrane() {
    QString meno = ui.uzivatelia_2->currentText();
    QString fileName = "subory/" + meno + ".csv";
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        for (int x = 0; x < ui.vybrane->rowCount(); x++) {

            QString s = ui.vybrane->item(x, 0)->text();

            QString s1 = ui.vybrane->item(x, 1)->text();

            QString s2 = ui.vybrane->item(x, 2)->text();
            stream.setCodec("UTF-8");
            stream << s << ";" << s1 << ";" << s2 << "\n";
        }
        file.close();
    }

}

void Autoserviskb::potvrdVybrane() {
    QString meno = ui.uzivateliaUloz->currentText();
    QString fileName1 = "subory/" + meno + ".csv";
    QString fileName2 = "vybavene/" + meno + ".csv";
    QFile file1(fileName1);
    QFile file2(fileName2);

    QStringList rowOfData;
    rowOfData.clear();
    QString data;
    if (file1.open(QFile::ReadOnly))
    {
        data = file1.readAll();
        rowOfData = data.split("\n");
        file1.close();
    }
    if (file2.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file2);
        for (int x = 0; x < rowOfData.size() - 1; x++) {
            stream.setCodec("UTF-8");
            stream << rowOfData.at(x) << "\n";
        }
        file2.close();
    }

    file1.resize(0);
}

void Autoserviskb::on_actionNahrat_triggered() {
    QString filename = QFileDialog::getOpenFileName(this, ("Open File"), "sluzby", ("csv File(*.csv)")); //Predpoklada sa ze novy subor bude mat rovnaky nazov ako povodny
    qDebug() << filename;
    QFile file(filename);
    file.rename(filename, "sluzby/Sluzby.csv");
}

void Autoserviskb::on_zmenitOs_clicked() {
    if (stav == 2) {
        zamestnanec->setUdaje(ui.lineEdit_9->text(), ui.lineEdit_3->text());
    }
    if (stav == 3) {
        firma->setUdaje(ui.lineEdit_7->text(), ui.lineEdit_8->text(), ui.lineEdit_3->text(), ui.lineEdit_4->text(), ui.lineEdit_5->text(), ui.lineEdit_6->text());
    }
    if (stav == 4) {
        osoba->setUdaje(ui.lineEdit_3->text(), ui.lineEdit_4->text(), ui.lineEdit_5->text(), ui.lineEdit_6->text());
    }

}

void Autoserviskb::ulozOs() {
    QString meno = ui.uzivatelia_2->currentText();
    QString fileName = "osudaje/" + meno + ".csv";
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QTextStream stream(&file);
        stream << "Meno/firma" << ";" << ui.lineEdit_3->text() << ";" << "\n";
        stream << "Znaèka" << ";" << ui.lineEdit_4->text() << ";" << "\n";
        stream << "Model" << ";" << ui.lineEdit_5->text() << ";" << "\n";
        stream << "Rok výroby" << ";" << ui.lineEdit_6->text() << ";" << "\n";
        if (stav == 3) {
            stream << "IÈO" << ";" << ui.lineEdit_7->text() << ";" << "\n";
            stream << "Platca DPH" << ";" << ui.lineEdit_8->text() << ";" << "\n";
        }
        if (stav == 2) {
            stream << "Pozicia" << ";" << ui.lineEdit_9->text() << ";" << "\n";
        }
    }
    file.close();
}

void Autoserviskb::loadPotvrdene() {
    QString meno = ui.uzivatelia_2->currentText();
    QString fileName2 = "vybavene/" + meno + ".csv"; ///QFileDialog::getOpenFileName(this, ("Open File"), "sluzby", ("csv File(*.csv)"));
    QFile importedCSV1(fileName2);
    if (importedCSV1.open(QFile::ReadOnly))
    {
        QTextStream in(&importedCSV1);
        in.setCodec("UTF-8");
        while (!in.atEnd())
        {
            Produkty sluzba;
            sluzba.napln(in.readLine());
            potvrdene.append(sluzba);
        }
        importedCSV1.close();
    }
    ui.potvrdene->setRowCount(potvrdene.size());
    ui.potvrdene->setColumnCount(3);

    for (int x = 0; x < potvrdene.size(); x++)
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText(potvrdene[x].getnazov());

        QTableWidgetItem* item2 = new QTableWidgetItem();
        item2->setText(potvrdene[x].getcena());

        QTableWidgetItem* item3 = new QTableWidgetItem();
        item3->setText(potvrdene[x].getcenabez());
        ui.potvrdene->setItem(x, 0, item);
        ui.potvrdene->setItem(x, 1, item2);
        ui.potvrdene->setItem(x, 2, item3);
    }


}

void Autoserviskb::on_odhlasit_clicked() {
    ulozVybrane();
    ulozOs();
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());

}

void Autoserviskb::loadVybraneZam() {
    for (int i = 0; i < ui.vybrane->rowCount()+1; i++) {
        ui.vybrane->removeRow(i);
    }
    objednane.clear();
    QString meno = ui.uzivateliaUloz->currentText();
    QString fileName = "subory/" + meno + ".csv"; ///QFileDialog::getOpenFileName(this, ("Open File"), "sluzby", ("csv File(*.csv)"));
    QFile importedCSV1(fileName);
    if (importedCSV1.open(QFile::ReadOnly))
    {
        QTextStream in(&importedCSV1);
        in.setCodec("UTF-8");
        while (!in.atEnd())
        {
            Produkty sluzba1;
            sluzba1.napln(in.readLine());
            objednane.append(sluzba1);
        }
        importedCSV1.close();
    }
    ui.vybrane->setRowCount(objednane.size());
    ui.vybrane->setColumnCount(3);

    for (int x = 0; x < objednane.size(); x++)
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText(objednane[x].getnazov());

        QTableWidgetItem* item2 = new QTableWidgetItem();
        item2->setText(objednane[x].getcena());

        QTableWidgetItem* item3 = new QTableWidgetItem();
        item3->setText(objednane[x].getcenabez());
        ui.vybrane->setItem(x, 0, item);
        ui.vybrane->setItem(x, 1, item2);
        ui.vybrane->setItem(x, 2, item3);
    }


}

void Autoserviskb::loadPotvrdeneZam() {
    for (int i = 0; i < ui.potvrdene->rowCount()+1; i++) {
        ui.potvrdene->removeRow(i);
    }
    potvrdene.clear();
    QString meno = ui.uzivateliaUloz->currentText();
    QString fileName = "vybavene/" + meno + ".csv"; ///QFileDialog::getOpenFileName(this, ("Open File"), "sluzby", ("csv File(*.csv)"));
    QFile importedCSV1(fileName);
    if (importedCSV1.open(QFile::ReadOnly))
    {
        QTextStream in(&importedCSV1);
        in.setCodec("UTF-8");
        while (!in.atEnd())
        {
            Produkty sluzba;
            sluzba.napln(in.readLine());
            potvrdene.append(sluzba);
        }
        importedCSV1.close();
    }
    ui.potvrdene->setRowCount(potvrdene.size());
    ui.potvrdene->setColumnCount(3);

    for (int x = 0; x < potvrdene.size(); x++)
    {
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setText(potvrdene[x].getnazov());

        QTableWidgetItem* item2 = new QTableWidgetItem();
        item2->setText(potvrdene[x].getcena());

        QTableWidgetItem* item3 = new QTableWidgetItem();
        item3->setText(potvrdene[x].getcenabez());
        ui.potvrdene->setItem(x, 0, item);
        ui.potvrdene->setItem(x, 1, item2);
        ui.potvrdene->setItem(x, 2, item3);
    }


}

void Autoserviskb::on_uzivateliaUloz_currentTextChanged() {
    loadVybraneZam();
    loadPotvrdeneZam();
}

void Autoserviskb::loadUserfileZam(QString s) {
    QString fileName = s;
    QString data;
    QFile importedCSV(fileName);
    QStringList rowOfData;
    QStringList rowData;
    rowOfData.clear();
    rowData.clear();

    if (importedCSV.open(QFile::ReadOnly))
    {
        data = importedCSV.readAll();
        rowOfData = data.split("\n");
        importedCSV.close();
    }

    for (int x = 0; x < rowOfData.size(); x++)
    {
        rowData = rowOfData.at(x).split(";");
        ui.uzivateliaUloz->addItem(rowData.at(0));
    }
}

void Autoserviskb::vytlacFakturu() {
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "faktury", "Text files (*.txt)");
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream stream(&file);
        stream.setCodec("UTF-8");
        ui.vybrane->removeRow(ui.vybrane->rowCount() - 1);
        for (int x = 0; x < ui.vybrane->rowCount(); x++) {

            QString s = ui.vybrane->item(x, 0)->text();

            QString s1 = ui.vybrane->item(x, 1)->text();

            QString s2 = ui.vybrane->item(x, 2)->text();
            stream << s << " " << s1 << " " << s2 << "\n";
        }
        float cenasdph = 0;
        float cenabez = 0;
        for (int x = 0; x < ui.vybrane->rowCount(); x++) {

            float s = ui.vybrane->item(x, 1)->text().toFloat();

            float a = ui.vybrane->item(x, 2)->text().toFloat();
            cenasdph = cenasdph + s;
            cenabez = cenabez + a;
        }
        QString cenad = QString::number(cenasdph);
        QString cenab = QString::number(cenabez);

        
        
        if (stav == 3) {
            if (firma->getdph() == "n") {
                stream << "Celkova cena bez DPH: " << cenab << "\n";
            }
            else {
                stream << "Celkova cena s DPH: " << cenad << "\n";
            }
        }
        else {
            stream << "Celkova cena s DPH: " << cenad << "\n";
        }

        file.close();
    }
}

void Autoserviskb::on_potvdObj_clicked() {
    potvrdVybrane();
    loadVybraneZam();
    loadPotvrdeneZam();

}

void Autoserviskb::on_faktura_clicked() {
    vytlacFakturu();
}

void Autoserviskb::on_edit_2_clicked() {
    if (ui.zamestnanecRadio_2->isChecked()) {
        QString fileName = "users/userlistZam.csv";
        QFile zamestnanci(fileName);
        QStringList nove;
        QString staremeno = ui.comboBox_2->currentText();
        QString novemeno = ui.novemeno_2->text();
        QString heslo = ui.heslo_2->text();
        QString sifHeslo = QCryptographicHash::hash(heslo.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
        if (zamestnanci.open(QIODevice::ReadOnly)) {
            QStringList rowOfData;
            QString data;
            data.clear();
            rowOfData.clear();

            data = zamestnanci.readAll();
            rowOfData = data.split("\n");
            int x = ui.comboBox_2->currentIndex();


            rowOfData[x] = novemeno + ";" + sifHeslo + ";";
            zamestnanci.close();
            nove = rowOfData;
        }

        if (zamestnanci.open(QIODevice::WriteOnly)) {
            for (int y = 0; y < nove.size(); y++) {
                QTextStream stream(&zamestnanci);
                stream << nove[y] << "\n";
            }
        }
        QString filename1 = "subory/" + staremeno + ".csv";
        QString filename2 = "osudaje/" + staremeno + ".csv";
        QString filename3 = "vybavene/" + staremeno + ".csv";
        QString filename1nove = "subory/" + novemeno + ".csv";
        QString filename2nove = "osudaje/" + novemeno + ".csv";
        QString filename3nove = "vybavene/" + novemeno + ".csv";
        QFile file1(filename1);
        QFile file2(filename2);
        QFile file3(filename3);
        file1.rename(filename1, filename1nove);
        file2.rename(filename2, filename2nove);
        file3.rename(filename3, filename3nove);
    }
    if (ui.osobaRadio_2->isChecked()) {
        QString fileName = "users/userlistOsoby.csv";
        QFile zamestnanci(fileName);
        QStringList nove;
        QString staremeno = ui.comboBox_2->currentText();
        QString novemeno = ui.novemeno_2->text();
        QString heslo = ui.heslo_2->text();
        QString sifHeslo = QCryptographicHash::hash(heslo.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
        if (zamestnanci.open(QIODevice::ReadOnly)) {
            QStringList rowOfData;
            QString data;
            data.clear();
            rowOfData.clear();

            data = zamestnanci.readAll();
            rowOfData = data.split("\n");
            int x = ui.comboBox_2->currentIndex();

            rowOfData[x] = novemeno + ";" + sifHeslo + ";";
            zamestnanci.close();
            nove = rowOfData;
        }

        if (zamestnanci.open(QIODevice::WriteOnly)) {
            for (int y = 0; y < nove.size(); y++) {
                QTextStream stream(&zamestnanci);
                stream << nove[y] << "\n";
            }
        }
        QString filename1 = "subory/" + staremeno + ".csv";
        QString filename2 = "osudaje/" + staremeno + ".csv";
        QString filename3 = "vybavene/" + staremeno + ".csv";
        QString filename1nove = "subory/" + novemeno + ".csv";
        QString filename2nove = "osudaje/" + novemeno + ".csv";
        QString filename3nove = "vybavene/" + novemeno + ".csv";
        QFile file1(filename1);
        QFile file2(filename2);
        QFile file3(filename3);
        file1.rename(filename1, filename1nove);
        file2.rename(filename2, filename2nove);
        file3.rename(filename3, filename3nove);
    }
    if (ui.frimaRadio_2->isChecked()) {
        QString fileName = "users/userlistFirmy.csv";
        QFile zamestnanci(fileName);
        QStringList nove;
        QString staremeno = ui.comboBox_2->currentText();
        QString novemeno = ui.novemeno_2->text();
        QString heslo = ui.heslo_2->text();
        QString sifHeslo = QCryptographicHash::hash(heslo.toStdString().c_str(), QCryptographicHash::Sha1).toHex();
        if (zamestnanci.open(QIODevice::ReadOnly)) {
            QStringList rowOfData;
            QString data;
            data.clear();
            rowOfData.clear();

            data = zamestnanci.readAll();
            rowOfData = data.split("\n");
            int x = ui.comboBox_2->currentIndex();

            rowOfData[x] = novemeno + ";" + sifHeslo + ";";
            zamestnanci.close();
            nove = rowOfData;
        }

        if (zamestnanci.open(QIODevice::WriteOnly)) {
            for (int y = 0; y < nove.size(); y++) {
                QTextStream stream(&zamestnanci);
                stream << nove[y] << "\n";
            }
        }
        QString filename1 = "subory/" + staremeno + ".csv";
        QString filename2 = "osudaje/" + staremeno + ".csv";
        QString filename3 = "vybavene/" + staremeno + ".csv";
        QString filename1nove = "subory/" + novemeno + ".csv";
        QString filename2nove = "osudaje/" + novemeno + ".csv";
        QString filename3nove = "vybavene/" + novemeno + ".csv";
        QFile file1(filename1);
        QFile file2(filename2);
        QFile file3(filename3);
        file1.rename(filename1, filename1nove);
        file2.rename(filename2, filename2nove);
        file3.rename(filename3, filename3nove);
    }
}

void Autoserviskb::on_editPush_2_clicked() {
    if (ui.zamestnanecRadio_2->isChecked()) {
        openUserFileEdit("users/userlistZam.csv");
    }
    if (ui.osobaRadio_2->isChecked()) {
        openUserFileEdit("users/userlistOsoby.csv");
    }
    if (ui.frimaRadio_2->isChecked()) {
        openUserFileEdit("users/userlistFirmy.csv");

    }
}

void Autoserviskb::openUserFileEdit(QString s) {
    QString fileName = s;
    QString data;
    QFile importedCSV(fileName);
    QStringList rowOfData;
    QStringList rowData;
    rowOfData.clear();
    rowData.clear();

    if (importedCSV.open(QFile::ReadOnly))
    {
        data = importedCSV.readAll();
        rowOfData = data.split("\n");
        importedCSV.close();
    }

    for (int x = 0; x < rowOfData.size(); x++)
    {
        rowData = rowOfData.at(x).split(";");
        ui.comboBox_2->addItem(rowData.at(0));
    }
}

void Autoserviskb::on_vymaz_2_clicked() {
    if (ui.zamestnanecRadio_2->isChecked()) {
        QString fileName = "users/userlistZam.csv";
        QFile zamestnanci(fileName);
        QStringList nove;
        if (zamestnanci.open(QIODevice::ReadOnly)) {
            QStringList rowOfData;
            QString data;
            data.clear();
            rowOfData.clear();

            data = zamestnanci.readAll();
            rowOfData = data.split("\n");
            int x = ui.comboBox_2->currentIndex();
            rowOfData.removeAt(x);
            zamestnanci.close();
            nove = rowOfData;
        }

        if (zamestnanci.open(QIODevice::WriteOnly)) {
            for (int y = 0; y < nove.size(); y++) {
                QTextStream stream(&zamestnanci);
                stream << nove[y];
            }
        }
    }
    if (ui.osobaRadio_2->isChecked()) {
        QString fileName = "users/userlistOsoby.csv";
        QFile zamestnanci(fileName);
        QStringList nove;
        if (zamestnanci.open(QIODevice::ReadOnly)) {
            QStringList rowOfData;
            QString data;
            data.clear();
            rowOfData.clear();

            data = zamestnanci.readAll();
            rowOfData = data.split("\n");
            int x = ui.comboBox_2->currentIndex();
            rowOfData.removeAt(x);
            zamestnanci.close();
            nove = rowOfData;
        }

        if (zamestnanci.open(QIODevice::WriteOnly)) {
            for (int y = 0; y < nove.size(); y++) {
                QTextStream stream(&zamestnanci);
                stream << nove[y] << "\n";
            }
        }
    }
    if (ui.frimaRadio_2->isChecked()) {
        QString fileName = "users/userlistFirmy.csv";
        QFile zamestnanci(fileName);
        QStringList nove;
        if (zamestnanci.open(QIODevice::ReadOnly)) {
            QStringList rowOfData;
            QString data;
            data.clear();
            rowOfData.clear();

            data = zamestnanci.readAll();
            rowOfData = data.split("\n");
            int x = ui.comboBox_2->currentIndex();
            rowOfData.removeAt(x);
            zamestnanci.close();
            nove = rowOfData;
        }

        if (zamestnanci.open(QIODevice::WriteOnly)) {
            for (int y = 0; y < nove.size(); y++) {
                QTextStream stream(&zamestnanci);
                stream << nove[y] << "\n";
            }
        }
    }
}

void Autoserviskb::on_vymazat_clicked() {
    int a = ui.vybrane->currentRow();
    objednane.remove(a);
    loadVektor();
}

void Autoserviskb::nacitajOsUj() {
    QString meno = ui.uzivatelia_2->currentText();
    QString fileName = "osudaje/" + meno + ".csv";
    QString data;
    QFile importedCSV(fileName);
    QStringList rowOfData;
    QStringList rowDatameno;
    QStringList rowDataznacka;
    QStringList rowDatamodel;
    QStringList rowDatarok;
    QStringList rowDataico;
    QStringList rowDatadph;
    QStringList rowDatapozicia;
    int tempint = 0;
    data.clear();
    rowOfData.clear();

    if (importedCSV.open(QFile::ReadOnly))
    {
        data = importedCSV.readAll();
        rowOfData = data.split("\n");
        importedCSV.close();
    }


    rowDatameno = rowOfData.at(0).split(";");
    QString menofirma = rowDatameno.at(1);
    
    rowDataznacka = rowOfData.at(1).split(";");
    QString znacka = rowDataznacka.at(1);
    
    rowDatamodel = rowOfData.at(2).split(";");
    QString model = rowDatamodel.at(1);
    
    rowDatarok = rowOfData.at(3).split(";");
    QString rok = rowDatarok.at(1);
    
    if (stav == 4) {
        osoba->setUdaje(menofirma, znacka, model, rok);
        ui.lineEdit_3->setText(osoba->getmeno());
        ui.lineEdit_4->setText(osoba->getznac());
        ui.lineEdit_5->setText(osoba->getmod());
        ui.lineEdit_6->setText(osoba->getrok());
    }
    if (stav == 3) {
        rowDataico = rowOfData.at(4).split(";");
        QString ico = rowDataico.at(1);
        
        rowDatadph = rowOfData.at(5).split(";");
        QString dph = rowDatadph.at(1);
        
        firma->setUdaje(ico, dph, menofirma, znacka, model, rok);
        ui.lineEdit_3->setText(firma->getmeno());
        ui.lineEdit_4->setText(firma->getznac());
        ui.lineEdit_5->setText(firma->getmod());
        ui.lineEdit_6->setText(firma->getrok());
        ui.lineEdit_7->setText(firma->getico());
        ui.lineEdit_8->setText(firma->getdph());
    }
    if (stav == 2) {
        rowDatapozicia = rowOfData.at(4).split(";");
        QString pozicia = rowDatapozicia.at(1);
        zamestnanec->setUdaje(pozicia, menofirma);

        ui.lineEdit_3->setText(zamestnanec->getmeno());
        ui.lineEdit_9->setText(zamestnanec->getpozicia());
    }






}