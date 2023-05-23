#include "personajes.h"
#include <string>;
#include <iostream>
#include <cstdlib>
using namespace std;
personajes::personajes(string nombree, int HP, int ATK, int posx, int posy) {
	nombre = nombree;
	vida = HP;
	ataque = ATK;
	posX = posx;
	posY = posy;
}
int personajes::getHP() {
	return vida;
}
int personajes::getATK() {
	return ataque;
}

int personajes::getPOSY() {
	return posY;
}

int personajes::getPOSX() {
	return posX;
}

string personajes::getNAME() {
	return nombre;
}
bool personajes::operator==(const personajes& otro) const {
	return (nombre == otro.nombre && vida == otro.vida && ataque == otro.ataque && posX == otro.posX && posY == otro.posY);
}

bool personajes::operator!=(const personajes& otro) const {
	return !(*this == otro);
}

void personajes::setHP(int newvida) {
	vida = newvida;
}
void personajes::setATK(int newataque) {
	ataque = newataque;
}
void personajes::setNAME(string newnombre) {
	nombre = newnombre;
}
void personajes::setPOS(int newposX, int newposY) {
	posX = newposX;
	posY = newposY;
}
void personajes::ataquenormal(personajes pataca, personajes& percibe, int estado) {
	if (estado == 0) {
		cout << pataca.getNAME() << " ataca a " << percibe.getNAME() << "!" << endl;
	}
	int nueva_vida = percibe.getHP() - pataca.getATK();
	percibe.setHP(nueva_vida);
	cout << percibe.getNAME() << " recibe " << pataca.getATK() << " puntos de daño!"<<endl;
}

