#include <iostream>
#include "Personaje.h"
#include "bossfinal.h"
#include "heroe.h"
#include <cstdlib>
#include <stdlib.h>
#include <locale.h>
#include <Windows.h>
#include <chrono>
#include <thread>º
#include <time.h>
#include <mmsystem.h>
#include <conio.h>

using namespace std;

//VARIABLES TABLERO//
const int ROWS = 7;
const int COLS = 11;
char board[ROWS][COLS];

//JUEGO//
int estado = 0;
int salidacheck = 0;
int seve = 0;

//HEROE//
int vidas = 4;
string nombreheroe;
heroe usuario(40, 20, "Galadriel");

//ENEMIGOS NORMALES//
personajes p1("Ogro", 10, 10, rand() % 10 + 1, rand() % 6 + 1);
personajes p2("Goblin", 10, 10, rand() % 10 + 1, rand() % 6 + 1);
personajes p3("Gnomo", 10, 10, rand() % 10 + 1, rand() % 6 + 1);
personajes p4("Orco", 10, 10, rand() % 10 + 1, rand() % 6 + 1);
personajes salida("SALIDA", 0, 0, -1, -1);

//BOSS//
bossfinal boss(100, 20, "Skölfnir, portador de desdicha");
bool vidaboss = false;

void gamestarter() {
	p1.setPOS(rand() % 11, rand() % 4 + 1);
	p2.setPOS(rand() % 11, rand() % 4 + 1);
	p3.setPOS(rand() % 11, rand() % 4 + 1);
	p4.setPOS(rand() % 11, rand() % 4 + 1);
	setlocale(LC_ALL, "spanish");
	SetConsoleOutputCP(CP_UTF8);
	string bienvenida1 = "El heroe se despierta";
	string bienvenida2 = "Una sombra de lo que fue en otro tiempo";
	string bienvenida3 = "Nadie recuerda su nombre, pero la mayoria lo recuerda como";
	for (int i = 0; i < bienvenida1.length(); i++)
	{
		PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);
		cout << bienvenida1[i];
		this_thread::sleep_for(chrono::milliseconds(180));
		if (i == bienvenida1.length() - 1) {
			cout << ".";
			PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);
			this_thread::sleep_for(chrono::milliseconds(200));
			cout << ".";
			PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);
			this_thread::sleep_for(chrono::milliseconds(200));
			cout << ".";
			PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);

			this_thread::sleep_for(chrono::milliseconds(200));
		}
	}
	this_thread::sleep_for(chrono::milliseconds(2000));
	system("cls");
	for (int i = 0; i < bienvenida2.length(); i++)
	{
		cout << bienvenida2[i];
		PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);
		this_thread::sleep_for(chrono::milliseconds(180));
		if (i == bienvenida2.length() - 1) {
			cout << ".";
			PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);
			this_thread::sleep_for(chrono::milliseconds(200));
			cout << ".";
			PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);
			this_thread::sleep_for(chrono::milliseconds(200));
			cout << ".";
			PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);
			this_thread::sleep_for(chrono::milliseconds(200));
		}
	}
	this_thread::sleep_for(chrono::milliseconds(2000));
	system("cls");
	for (int i = 0; i < bienvenida3.length(); i++)
	{
		cout << bienvenida3[i];
		PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);
		this_thread::sleep_for(chrono::milliseconds(180));
		if (i == bienvenida3.length() - 1) {
			cout << ".";
			PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);
			this_thread::sleep_for(chrono::milliseconds(200));
			cout << ".";
			PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);
			this_thread::sleep_for(chrono::milliseconds(200));
			cout << ".";
			PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);
			this_thread::sleep_for(chrono::milliseconds(200));
		}
	}

	cout << endl;
	cout << "INTRODUCE EL NOMBRE DEL HEROE: ";
	cin >> nombreheroe;
	usuario.setNAME(nombreheroe);
	cout << endl;
	system("pause");
}

void barrasvida(bool quemuestra) {
	if (!quemuestra) {
		cout << "x:" << usuario.getPOSX() << " y: " << usuario.getPOSY();
		cout << endl;
		cout << p1.getNAME() << " || " << p1.getHP() << endl;
		cout << p2.getNAME() << " || " << p2.getHP() << endl;
		cout << p3.getNAME() << " || " << p3.getHP() << endl;
		cout << p4.getNAME() << " || " << p4.getHP() << endl;
	}
	else {
		cout << boss.getNAME() << " || " << boss.getHP() << endl;
	}

	cout << usuario.getNAME() << " || " << usuario.getHP();
}

int dado() {
	return (rand() % 6) + 1;
}

void lanzadado(int& num) {
	num = 0;
	while (num != dado()) {
		num = rand() % 6 + 1;
		cout << "\rTirando dado... " << num;
		this_thread::sleep_for(chrono::milliseconds(200));
	}
	cout << endl;
}

bool mostrarenemigos(personajes enemigo) {
	if ((
		(enemigo.getPOSX() - 1 == usuario.getPOSX() || enemigo.getPOSX() + 1 == usuario.getPOSX()) && (enemigo.getPOSY() == usuario.getPOSY() || enemigo.getPOSY() - 1 == usuario.getPOSY() || enemigo.getPOSY() + 1 == usuario.getPOSY())
		) ||
		(enemigo.getPOSY() - 1 == usuario.getPOSY() || enemigo.getPOSY() + 1 == usuario.getPOSY()) && (enemigo.getPOSX() == usuario.getPOSX() || enemigo.getPOSX() - 1 == usuario.getPOSX() || enemigo.getPOSX() + 1 == usuario.getPOSX())
		) {
		return true;
	}
	else {
		return false;
	}
}

void check2() {
	if (salidacheck == 0 && p1.getHP() <= 0 && p2.getHP() <= 0 && p3.getHP() <= 0 && p4.getHP() <= 0) {
		int posx = rand() % 11;
		salidacheck++;
		if (posx == usuario.getPOSX() && usuario.getPOSY() == 11) {
			posx = rand() % 11;
		}
		salida.setPOS(posx, 6);
	}
	if (usuario.getHP() < 1) {
		estado = 1;
		PlaySound(TEXT("heroemuere.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	else if (boss.getHP() < 1) {
		estado = 2;

	}
}

void combate(personajes enemigo) {
	usuario.setATK(15);
	cout << "INICIA EL COMBATE CONTRA EL ENEMIGO " << enemigo.getNAME() << "!" << endl;
	cout << "Lanza un dado para decidir quien ataca primero!" << endl;
	system("pause");
	system("cls");
	cout << "INICIA EL COMBATE CONTRA EL ENEMIGO " << enemigo.getNAME() << "!" << endl;
	int num = 0;
	lanzadado(num);
	if (num > 2) {
		usuario.ataqueheroe(enemigo, usuario.getATK(), usuario);
		if (enemigo.getNAME() == "Ogro") {
			usuario.ataqueespecial(p1);
			p1.setHP(p1.getHP() - usuario.getATK());
		}
		else if (enemigo.getNAME() == "Goblin") {
			usuario.ataqueespecial(p2);
			p2.setHP(p2.getHP() - usuario.getATK());
		}
		else if (enemigo.getNAME() == "Gnomo") {
			usuario.ataqueespecial(p3);
			p3.setHP(p3.getHP() - usuario.getATK());
		}
		else if (enemigo.getNAME() == "Orco") {
			p4.setHP(p4.getHP() - usuario.getATK());
			usuario.ataqueespecial(p4);
		}
	}
	else {
		usuario.setPOS(usuario.getPOSX(), usuario.getPOSY() - 1);
		enemigo.ataquenormal(enemigo, usuario, 0);
	}
}

void iniciobatallafinal() {
	system("cls");
	int suspensecount = 3;
	string suspense = "...";
	string bossataca = "Ves como frente a ti aparece un hombre musculoso blandiendo dos hachas";
	string bossataca2 = "COMIENZA EL COMBATE";
	do {

		if (suspensecount == 2)
		{
			for (int i = 0; i < bossataca.length(); i++)
			{
				PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);
				cout << bossataca[i];
				this_thread::sleep_for(chrono::milliseconds(100));

			}
		}
		else if (suspensecount == 1)
		{
			for (int i = 0; i < bossataca2.length(); i++)
			{
				PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);
				cout << bossataca2[i];
				this_thread::sleep_for(chrono::milliseconds(100));

			}
		}
		if (suspensecount != (1 && 2)) {
			for (int i = 0; i < suspense.length(); i++)
			{
				PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);
				cout << suspense[i];
				this_thread::sleep_for(chrono::milliseconds(500));

			}
			this_thread::sleep_for(chrono::milliseconds(500));
		}
		system("cls");
		suspensecount -= 1;
	} while (suspensecount != 0);

}

void batallafinal() {
	system("cls");
	iniciobatallafinal();
	system("pause");
	usuario.setHP(75);
	while (estado == 4) {
		int random = rand() % 100;
		usuario.setATK(15);
		system("cls");
		vidaboss = true;
		barrasvida(vidaboss);
		cout << endl;
		cout << "--------------------------------------------------------------";
		cout << endl;
		int num;
		lanzadado(num);
		if (num >= 3) {
			usuario.ataqueheroe(boss, usuario.getATK(), usuario);
		}
		else {
			boss.ataqueboss(usuario, boss.getATK(), boss, random);
		}
		check2();
	}

}

void colision(personajes& enemigo, personajes& usuarioo) {

	if (salida != enemigo && usuario.getPOSY() == enemigo.getPOSY() && usuario.getPOSX() == enemigo.getPOSX() && enemigo.getNAME() != salida.getNAME()) {
		PlaySound(TEXT("enemigoencontrado.wav"), NULL, SND_FILENAME | SND_ASYNC);
		system("cls");
		PlaySound(TEXT("combate.wav"), NULL, SND_FILENAME | SND_ASYNC);
		combate(enemigo);
		if (enemigo.getPOSX() == -1) {
			PlaySound(TEXT("golpe.wav"), NULL, SND_FILENAME | SND_ASYNC);
			this_thread::sleep_for(chrono::milliseconds(300));
			PlaySound(TEXT("monstruomuere.wav"), NULL, SND_FILENAME | SND_ASYNC);
		}
		else {
			PlaySound(TEXT("golpe.wav"), NULL, SND_FILENAME | SND_ASYNC);

		}
		system("pause");
		PlaySound(TEXT("musicadefault.wav"), NULL, SND_FILENAME | SND_ASYNC);
	}
	else if (salida.getPOSY() == usuario.getPOSY() && salida.getPOSX() == usuario.getPOSX() && estado == 0) {
		estado = 4;
		batallafinal();
	}

}

void ccheck() {
	colision(p1, usuario);
	colision(p2, usuario);
	colision(p3, usuario);
	colision(p4, usuario);
	colision(salida, usuario);
}

void lastmove(int posX, int posY) {
	if (posX >= 10) {
		usuario.setPOS(10, usuario.getPOSY());
	}
	else if (posX <= -1) {
		usuario.setPOS(0, usuario.getPOSY());
	}
	if (posY >= 7) {
		usuario.setPOS(usuario.getPOSX(), 6);
	}
	if (posY <= -1) {
		usuario.setPOS(usuario.getPOSX(), 0);
	}
}

void movimientousuario() {

	char ch;
	int x = usuario.getPOSX();
	int y = usuario.getPOSY();
	ch = _getch();
	switch (ch) {

	case 'w':
		usuario.setPOS(x, y - 1);
		break;

	case 's':
		usuario.setPOS(x, y + 1);
		break;

	case 'a':
		usuario.setPOS(x - 1, y);
		break;

		case 'd'
			:
				usuario.setPOS(x + 1, y);
				break;

		default:

			break;
	}
	lastmove(usuario.getPOSX(), usuario.getPOSY());
	ccheck();
}

void drawboard(personajes p1, personajes p2, personajes p3, personajes p4) {
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			board[i][j] = ' ';
		}
	}
	for (int i = 0; i < ROWS; i++) {
		cout << "+";
		for (int j = 0; j < COLS; j++) {
			cout << "----+";
		}
		cout << endl;
		for (int j = 0; j < COLS; j++) {
			cout << "|";
			for (int l = 0; l < 4; l++) {
				bool print = true;
				int contador = 0;
				int contador2 = 0;
				while (print) {
					if (j == p1.getPOSX() && i == p1.getPOSY() && l == 0 && p1.getPOSX() && mostrarenemigos(p1)) {
						cout << "\033[31m" << char(219) << "\033[37m";
						if (seve == 0) {
							PlaySound(TEXT("enemyappear.wav"), NULL, SND_FILENAME | SND_ASYNC);
							seve++;
						}
						print = false;
					}
					else if (j == p2.getPOSX() && i == p2.getPOSY() && l == 1 && mostrarenemigos(p2)) {
						cout << "\033[31m" << char(219) << "\033[37m";
						if (seve == 0) {
							PlaySound(TEXT("enemyappear.wav"), NULL, SND_FILENAME | SND_ASYNC);
							seve++;
						}
						print = false;
					}
					else if (j == p3.getPOSX() && i == p3.getPOSY() && l == 2 && mostrarenemigos(p3)) {
						cout << "\033[31m" << char(219) << "\033[37m";
						if (seve == 0) {
							PlaySound(TEXT("enemyappear.wav"), NULL, SND_FILENAME | SND_ASYNC);
							seve++;
						}
						print = false;

					}
					else if (j == p4.getPOSX() && i == p4.getPOSY() && l == 3 && mostrarenemigos(p4)) {
						cout << "\033[31m" << char(219) << "\033[37m";
						if (seve == 0) {
							PlaySound(TEXT("enemyappear.wav"), NULL, SND_FILENAME | SND_ASYNC);
							seve++;
						}
						print = false;
					}

					else if (j == salida.getPOSX() && i == salida.getPOSY()) {
						cout << "\033[34m" << char(219) << "\033[37m";
						if (seve == 0) {
							PlaySound(TEXT("enemyappear.wav"), NULL, SND_FILENAME | SND_ASYNC);
							seve++;
						}
						print = false;
					}

					else if (j == usuario.getPOSX() && i == usuario.getPOSY()) {
						if (l == 0) {
							for (int k = 0; k < usuario.getHP() / 10; k++) {
								if (usuario.getHP() / 10 == 4) {
									cout << "\033[32m";
								}
								else if (usuario.getHP() / 10 == 3 || usuario.getHP() / 10 == 2) {
									cout << "\033[33m";
								}
								else if (usuario.getHP() / 10 == 1) {
									cout << "\033[91m";
								}
								cout << char(219) << "\033[37m";
							}
						}
						else if (l == 3) {
							if (usuario.getHP() / 10 == 3) {
								cout << " ";
							}
							else if (usuario.getHP() / 10 == 2) {
								cout << "  ";
							}
							else if (usuario.getHP() / 10 == 1) {
								cout << "   ";
							}
						}

						print = false;
					}
					contador++;
					if (contador == 5) {
						break;
					}
				}
				if (print) {
					cout << " ";
					contador = 0;
				}
			}
		}
		cout << "|" << endl;
	}
	cout << "+";
	for (int j = 0; j < COLS; j++) {
		cout << "----+";
	}
	cout << endl;
	cout << seve;
	barrasvida(vidaboss = false);
	if (!mostrarenemigos(p1) && !mostrarenemigos(p2) && !mostrarenemigos(p3) && !mostrarenemigos(p4)) {
		seve = 0;
	}
}

void endgame(int estado) {

	if (estado == 1) {
		string end1 = "El heroe ha caido en combate";
		string end2 = "FIN DE LA PARTIDA";
		PlaySound(TEXT("musicadefault.wav"), NULL, SND_FILENAME | SND_ASYNC);
		for (int i = 0; i < end1.length(); i++) {
			cout << end1[i];
			this_thread::sleep_for(chrono::milliseconds(180));
			if (i == end1.length() - 1) {
				cout << ".";
				this_thread::sleep_for(chrono::milliseconds(200));
				cout << ".";
				this_thread::sleep_for(chrono::milliseconds(200));
				cout << ".";
				this_thread::sleep_for(chrono::milliseconds(200));
			}
		}
	}
	else if (estado == 2) {
		string end1 = "El heroe finalizó con exito su cometido!";
		string end2 = "FIN DE LA PARTIDA";
		for (int i = 0; i < end1.length(); i++) {
			cout << end1[i];
			PlaySound(TEXT("escribe.wav"), NULL, SND_FILENAME | SND_ASYNC);
			this_thread::sleep_for(chrono::milliseconds(180));
			if (i == end1.length() - 1) {
				cout << ".";
				this_thread::sleep_for(chrono::milliseconds(200));
				cout << ".";
				this_thread::sleep_for(chrono::milliseconds(200));
				cout << ".";
				this_thread::sleep_for(chrono::milliseconds(200));
			}
		}
	}
}

int main() {
	srand(time(NULL));
	gamestarter();
	PlaySound(TEXT("musicadefault.wav"), NULL, SND_FILENAME | SND_ASYNC);
	while (estado == 0) {
		drawboard(p1, p2, p3, p4);
		movimientousuario();
		system("cls");
		check2();
	}
	endgame(estado);
}