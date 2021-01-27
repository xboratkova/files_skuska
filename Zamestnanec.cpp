#include "Zamestnanec.h"
Zamestnanec::Zamestnanec() {
	meno = " ";
	heslo = " ";
	pozicia = " ";
	nazov = " ";
}

void Zamestnanec::setUdaje(QString poz, QString naz) {
	pozicia = poz;
	nazov = naz;
}

QString Zamestnanec::getpozicia() {
	return pozicia;
}
QString Zamestnanec::getmeno() {
	return nazov;
}