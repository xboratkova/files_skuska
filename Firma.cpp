#include "Firma.h"
Firma::Firma() {
	meno = " ";
	heslo = " ";
	ico = " ";
	dph = " ";
	nazov = " ";
	znacka = " ";
	model = " ";
	rocnik = " ";
}

void Firma::setUdaje(QString ic, QString dp, QString naz, QString zn, QString mod, QString rok) {
	ico = ic;
	dph = dp;
	nazov = naz;
	znacka = zn;
	model = mod;
	rocnik = rok;
}

QString Firma::getdph() {
	return dph;
}

QString Firma::getico() {
	return ico;
}