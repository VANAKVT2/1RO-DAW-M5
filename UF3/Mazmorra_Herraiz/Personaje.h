#pragma once
#include <string>

using namespace std;

class Personaje
{
private:
	int vida, ataque;
	string nombre;
public: 
	int getHP() {
		return vida;
	}
	int getATK() {
		return ataque;
	}
	string getNAME() {
		return nombre;
	}
};

