#include "bossfinal.h"

void bossfinal::ataqueboss(personajes& elpersonajequerecibe, int ataque, personajes& elqueataca, int random) {
	int saveda�o = elqueataca.getATK();
	int ataquedefinitivo = elqueataca.getATK() * 1.75;
	int ataquedefinitivo2 = elqueataca.getATK() * 2;
	cout << elqueataca.getNAME() << "\n";
	if (turnoscd2 == 0 && (random > 75)) {
		elqueataca.setATK(ataquedefinitivo);
		turnoscd2 = 4;
		cout << "Sk�lfnir ha preparado un golpe de berserker!";
	}
	else if (turnoscd3 == 0 && random > 90) {
		elqueataca.setATK(ataquedefinitivo2);
		cout << "El cuerpo de Sk�lfnir parece hacer vibrar el aire a su alrededor!";
		turnoscd3 = 4;
	}
	if (turnoscd3 > 0) {
		turnoscd3--;
	}if (turnoscd2 > 0) {
		turnoscd2--;
	}
	cout << endl;
	cout << "Sk�lfnir lanza su ataque!";
	elpersonajequerecibe.setHP(elpersonajequerecibe.getHP() - ataque);
	elqueataca.setATK(saveda�o);
	cout << endl;
	system("pause");
}

bossfinal::bossfinal(int vida, int ataque, string nombre)
{
	setATK(ataque);
	setHP(vida);
	setNAME(nombre);
}
