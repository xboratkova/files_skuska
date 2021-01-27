#pragma once
#include <QtWidgets>

class Uzivatel
{
protected:
	QString meno;
	QString heslo;
public:
	Uzivatel();
	QString getHeslo() {
		return heslo;
	}
	QString getMeno() {
		return meno;
	}
	void setPrihlasUdaje(QString m, QString h);
};

