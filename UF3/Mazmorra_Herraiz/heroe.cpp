#include "heroe.h"
#include <string>;
#include <iostream>
using namespace std;

void heroe::ataqueespecial(personajes& personajerecibe) {
	personajerecibe.setPOS(-1, -1);
}

void heroe::ataqueheroe(personajes& personajequerecibeda�o, int da�oheroe, heroe& personaje)
{
	cout << "Atacas al enemigo " << personajequerecibeda�o.getNAME() << "!\n";
	int saveda�o = personaje.getHP();
	int embestidaheroica = da�oheroe * 1.35;
	if (turnoscd == 0) {
		cout << "�Quieres usar la embestida heroica?('s' para confirmar)\n";
		char opcion = 'p';
		cin >> opcion;
		if (opcion == 's') {
			personaje.setATK(embestidaheroica);
			turnoscd = 2;
		}
	}
	else if (turnoscd > 0) {
		cout << "No puedes utilizar tu habilidad especial todavia!" << endl;
		turnoscd -= 1;
	}
	personaje.ataquenormal(personaje, personajequerecibeda�o, 1);
	personaje.setATK(saveda�o);
}

heroe::heroe(int vidaa, int ataquee, string nombree)
{
	setHP(vidaa);
	setATK(ataquee);
	setNAME(nombree);
	setPOS(5, 0);
}
heroe::heroe() {
	setHP(70);
	setATK(20);
	setNAME("Galadriel");
}
