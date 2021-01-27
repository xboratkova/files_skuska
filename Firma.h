#pragma once
#include "Osoba.h"
class Firma :
    public Osoba
{
private:
    QString ico;
    QString dph;
public:
    Firma();
    void setUdaje(QString ic, QString dp, QString naz, QString zn, QString mod, QString rok);
    QString getico();
    QString getdph();
};

