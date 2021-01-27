#pragma once

#include <QtWidgets>
#include <ui_Autoserviskb.h>
#include "Firma.h"
#include "Osoba.h"
#include "Uzivatel.h"
#include "Produkty.h"
#include "Zamestnanec.h"

class Autoserviskb : public QMainWindow
{
    Q_OBJECT

public:
    Autoserviskb(QWidget *parent = Q_NULLPTR);

private:
    Ui::AutoserviskbClass ui;
    int stav;
    Uzivatel* admin;
    Zamestnanec* zamestnanec;
    Osoba* osoba;
    Firma* firma;
    QVector<Produkty> sluzbyvektor;
    QVector<Produkty> objednane;
    QVector<Produkty> potvrdene;
    void importCSVFile();
    void openUserFile(QString s);
    void getPassword(QString s);
    void vytvorSubor();
    void vytvorOsUdaje();
    void loadVybrane();
    void ulozVybrane();
    void potvrdVybrane();
    void ulozOs();
    void loadVybraneZam();
    void loadUserfileZam(QString s);
    void loadPotvrdene();
    void loadPotvrdeneZam();
    void vytlacFakturu();
    void openUserFileEdit(QString s);
    void nacitajOsUj();
    void loadVektor();

private slots:
    void on_prihlas_2_clicked();
    void on_vybrat_clicked();
    void on_admin_2_clicked();
    void on_firma_2_clicked();
    void on_osoba_2_clicked();
    void on_zamestnanec_2_clicked();
    void on_vytvor_2_clicked();
    void on_actionNahrat_triggered();
    void on_zmenitOs_clicked();
    void on_odhlasit_clicked();
    void on_uzivateliaUloz_currentTextChanged();
    void on_potvdObj_clicked();
    void on_faktura_clicked();
    void on_edit_2_clicked();
    void on_editPush_2_clicked();
    void on_vymaz_2_clicked();
    void on_vymazat_clicked();
};
