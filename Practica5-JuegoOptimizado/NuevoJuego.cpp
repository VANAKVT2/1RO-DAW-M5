#include <iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

/*HEROE*/
int heroHP = 150;
int heroDMG;
int heroSPD = 2;
int heroAtt;
int c = 3;
int critico;
string heroName;

/*ENEMIGOS*/
int enemy1HP = 100;
int enemy2HP = 120;
int enemy1DMG = 130;
int enemy2DMG = 20;
int enemy1SPD = 1;
int enemy2SPD = 0;
string enemy1 = "Lotas el Espadachin";
string enemy2 = "Daraen el Caballero";

/*GENERAL*/
bool juego = true;

void INICIO() {
	srand(time(NULL));
	cout << "Introduce el nombre del heroe: ";
	cin >> heroName;
	heroName = heroName + " el Heroe";
	system("cls");
}

int ESTADOSVIDA() {
	if (heroHP <= 0) {
		return 3;
	}
	else if (enemy1HP <= 0 && enemy2HP <= 0) {
		return 4;
	}
	else if (enemy1HP >= 1 && enemy2HP <= 0) {
		cout << "El cadaver de " << enemy2 << " yace sobre el terreno de combate\n";
		enemy2HP = 0;
	}
	else if (enemy1HP <= 0 && enemy2HP >= 1) {
		cout << "El cadaver de " << enemy1 << " yace sobre el terreno de combate\n";
		enemy1HP = 0;
	}
	else if (enemy1HP >= 1 && enemy2HP >= 1) {
	}
	
}

int ESTADOSVEL() {
	int v1 = enemy1SPD;
	int v2 = enemy2SPD;
	int v0 = heroSPD;
	int x;
	if (v1 > v2 && v0) {
		enemy1SPD =0;
		enemy2SPD =2;
		heroSPD = 1;
		return 1;
	}
	else if (v2 > v1 && v0) {
		enemy1SPD = 1;
		enemy2SPD = 0;
		heroSPD = 2;
		return 2;
	}
	else if (v0 > v1 && v2) {
		enemy1SPD = 2;
		enemy2SPD = 1;
		heroSPD = 0;
		return 0;
	}

}

int SALIDA() {
	system("pause");
	system("cls");
	int ev = ESTADOSVIDA();
	if (ev == 3) {
		juego = false;
		cout << "EL JUEGO ACABO\n";
		cout << "El heroe fue derrotado.\n";
		return 1;
	}
	else if (ev == 4)  {
			cout << "El heroe vencio a los enemigos\n";
			return 1;
	}
	else {
		return 0;
	}
}

void GRAFICOS() {
	cout << enemy1 << "\t|| " << enemy1HP << " ||\n";
	cout << enemy2 << "\t|| " << enemy2HP << " ||\n";
	cout << heroName << "\t|| " << heroHP << " ||\n";
}

int SELECCIONENEMIGO() {
	int opcion;
	cout << "¿A que enemigo quieres atacar?\n";
	
		if (enemy1HP > 0) {
			cout << "[1]-" << enemy1<<"\n";
		}
		if (enemy2HP > 0) {
			cout << "[2]-" << enemy2 << "\n";
		}
		cin >> opcion;
		while (opcion < 0 || opcion>2) {
			cout << "Elige una opcion disponible";
			cin >> opcion;
			if (enemy1HP < 0 && opcion == 1) {
				opcion = -2;
			}
			if (enemy2HP < 0 && opcion == 2) {
				opcion == -2;
			}			
	}
		return opcion;
}

void ATAQUE(int& vidaentidadatacada, int danoentidadqueataca, string nombreentidadqueataca, string nombreentidadatacada) {
	cout << "¡Es " << nombreentidadqueataca << " quien blande su espada contra " << nombreentidadatacada << "! (" << danoentidadqueataca << " puntos de daño)\n";
	vidaentidadatacada = vidaentidadatacada - danoentidadqueataca;
}

void TIPOATAQUEHEROE() {
	int opcion=0;
	while ((opcion < 1 || opcion>3)) {
		cout << "Introduce el tipo de ataque que quieres realizar:\n[1]-Ataque Normal\n[2]-Ataque Especial ["<<c<<" usos disponibles]\n[3]-Golpe\n";
		cin >> opcion;
		if (c == 0 && opcion==2) {
			cout << "¡Ya no te quedan puntos de poder!";
			opcion = 0;
		}
	}
	if (opcion == 1) {
		heroDMG = 25;
	}
	else if (opcion == 2) {
		heroDMG = 40;
		critico = rand() % 20;
		int salecrit = rand() % 20;
		if (critico == salecrit) {
			heroDMG *= 1'5;
		}
		c--;
	}
	else if (opcion == 3) {
		heroDMG = 20;
	}
}

void PELEA(){
	int enemigo = SELECCIONENEMIGO();
	int vel = ESTADOSVEL();
	if (enemigo == 1) {
		if (vel == 0) {
			ATAQUE(enemy1HP, heroDMG, heroName, enemy1);
			ATAQUE(heroHP, enemy1DMG, enemy1, heroName);
			ATAQUE(heroHP, enemy2DMG, enemy2, heroName);
		}
		else if (vel == 1) {
			ATAQUE(heroHP, enemy1DMG, enemy1, heroName);
			ATAQUE(heroHP, enemy2DMG, enemy2, heroName);
			ATAQUE(enemy1HP, heroDMG, heroName, enemy1);
		}
		else if (vel == 2) {
			ATAQUE(heroHP, enemy2DMG, enemy2, heroName);
			ATAQUE(enemy1HP, heroDMG, heroName, enemy1);
			ATAQUE(heroHP, enemy1DMG, enemy1, heroName);
		}
	}	
	else if (enemigo == 2) {
		if (vel == 0) {
			ATAQUE(enemy2HP, heroDMG, heroName, enemy2);
			ATAQUE(heroHP, enemy1DMG, enemy1, heroName);
			ATAQUE(heroHP, enemy2DMG, enemy2, heroName);
		}
		else if (vel == 1) {
			ATAQUE(heroHP, enemy1DMG, enemy1, heroName);
			ATAQUE(heroHP, enemy2DMG, enemy2, heroName);
			ATAQUE(enemy2HP, heroDMG, heroName, enemy2);
		}
		else if (vel == 2) {
			ATAQUE(heroHP, enemy2DMG, enemy2, heroName);
			ATAQUE(enemy2HP, heroDMG, heroName, enemy2);
			ATAQUE(heroHP, enemy1DMG, enemy1, heroName);
		}
	}
}

int main() {
	INICIO();
	while (juego) {
		GRAFICOS();
		TIPOATAQUEHEROE();
		PELEA();
		int check=SALIDA();
		if (check == 1) {
			break;
		}
	}	
}