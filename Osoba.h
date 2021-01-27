#pragma once
#include "Uzivatel.h"
class Osoba :
    public Uzivatel
{
protected:
    QString nazov;
    QString znacka;
    QString model;
    QString rocnik;
public:
    Osoba();
    void setUdaje(QString naz, QString zn, QString mod, QString rok);
    QString getmeno();
    QString getznac();
    QString getmod();
    QString getrok();
};

