#include "Produkty.h"
Produkty::Produkty() {
	nazov = " ";
	cena = " ";
	cenabez = " ";
}

void Produkty::setProd(QString naz, QString cen, QString cenb) {
	nazov = naz;
	cena = cen;
	cenabez = cenb;
}
void Produkty::napln(QString s) {
	QStringList list = s.split(";");
	setProd(list[0], list[1], list[2]);
}
QString Produkty::getnazov() {
	return nazov;
}

QString Produkty::getcena() {
	return cena;
}

QString Produkty::getcenabez() {
	return cenabez;
}