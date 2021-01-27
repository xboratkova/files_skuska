#include "Uzivatel.h"
Uzivatel::Uzivatel() {
	meno = " ";
	heslo = " ";
}

void Uzivatel::setPrihlasUdaje(QString m, QString h) {
	meno = m;
	heslo = h;
}