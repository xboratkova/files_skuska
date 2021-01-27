#include "Osoba.h"
Osoba::Osoba() {
	meno = " ";
	heslo = " ";
	nazov = " ";
	znacka = " ";
	model = " ";
	rocnik = " ";
}

void Osoba::setUdaje(QString naz, QString zn, QString mod, QString rok) {
	nazov = naz;
	znacka = zn;
	model = mod;
	rocnik = rok;
}

QString Osoba::getmeno() {
	return nazov;
}
QString Osoba::getmod() {
	return model;
}

QString Osoba::getznac() {
	return znacka;
}

QString Osoba::getrok() {
	return rocnik;
}