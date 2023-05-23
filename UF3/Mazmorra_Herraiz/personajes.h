#pragma once
#include <string>
using namespace std;
class personajes
{
private:
	int vida, ataque, posX, posY;
	string nombre = "";
public:
	personajes(string nombree, int vida, int ataque, int posX, int posY);

	personajes() {
		nombre = "Ogro";
		ataque = 10;
		vida = 30;
		posX = 0;
		posY = 0;
	}
	
	int getHP();

	string getNAME();

	bool operator==(const personajes& otro) const;
	bool operator!=(const personajes& otro) const;


	void ataquenormal(personajes pataca, personajes& percibe, int estado);

	int getATK();

	int getPOSY();

	int getPOSX();

	void setHP(int newvida);

	void setATK(int newataque);

	void setNAME(string newnombre);

	void setPOS(int newposX, int newposY);

};

