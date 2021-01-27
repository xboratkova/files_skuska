#pragma once
#include "Uzivatel.h"

class Zamestnanec :
    public Uzivatel
    {
    private:
        QString pozicia;
        QString nazov;
    public:
        Zamestnanec();
        void setUdaje(QString poz, QString naz);
        QString getpozicia();
        QString getmeno();
};

