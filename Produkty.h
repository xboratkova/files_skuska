#pragma once
#include <QtWidgets>

class Produkty
{
private:
	QString nazov;
	QString cena;
	QString cenabez;
public:
	Produkty();
	void setProd(QString naz, QString cen, QString cenb);
	void napln(QString s);
	QString getnazov();
	QString getcena();
	QString getcenabez();
};

