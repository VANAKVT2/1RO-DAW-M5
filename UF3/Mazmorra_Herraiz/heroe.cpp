#include "heroe.h"
#include <string>;
#include <iostream>
using namespace std;

void heroe::ataqueespecial(personajes& personajerecibe) {
	personajerecibe.setPOS(-1, -1);
}

void heroe::ataqueheroe(personajes& personajequerecibedaño, int dañoheroe, heroe& personaje)
{
	cout << "Atacas al enemigo " << personajequerecibedaño.getNAME() << "!\n";
	int savedaño = personaje.getHP();
	int embestidaheroica = dañoheroe * 1.35;
	if (turnoscd == 0) {
		cout << "¿Quieres usar la embestida heroica?('s' para confirmar)\n";
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
	personaje.ataquenormal(personaje, personajequerecibedaño, 1);
	personaje.setATK(savedaño);
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
