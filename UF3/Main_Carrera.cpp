#include <iostream>
#include "barcos.h"
#include <algorithm>
#include <sstream>
#include <time.h>
#include <string>
using namespace std;

//VARIABLES
// 
	//COMPROBACION DEL GANADOR DE LA CARRERA
		string ganador="";
		int maxdist=0;

	//NOMBRE DEL BARCO PARA EL JUGADOR
		string nombre_barco="";

	//CANTIDAD DE BARCOS EN LA COMPETICION
		int numerobarcosenemigos=0;

	//CALCULO DE TURNOS
		int turno = 0;

	//VARIABLES DE VELOCIDAD
		
		//USO DEL NITRO
			char nitrouse='b';

		//DADO DE 6 CARAS PARA CALCULO DE VELOCIDAD
			int Dd6=0;

		//DADO DE 2 CARAS PARA CALCULO DE NITRO
			int Dd2=0;
//OBJETOS 
	//CREO LOS BARCOS. UNO PARA EL JUGADOR, EL RESTO PARA LA IA
		barcos barco1(0, nombre_barco);
		barcos barco2(0, "El Galeon Dorado");
		barcos barco3(0, "La Perla Negra");
		barcos barco4(0, "El Nautilus");
		barcos barco5(0, "El holandes Errante");
		barcos barco6(0, "El Endurance");

	//CREO UN ARRAY PARA ALMACENAR TODOS LOS BARCOS ENEMIGOS
		barcos barcosenemigos[5] = {barco2, barco3, barco4, barco5, barco6};
	//CREO UN ARRAY PARA ALMACENAR TODAS LAS DISTANCIAS
		int distancias[6];
	//CREO UN ARRAY PARA LA TABLA DE PUNTUACIONES
		string podio[4][2] = { 
			{barco1.getname(),to_string(barco1.getdist())} ,
			{barco2.getname(),to_string(barco2.getdist())} ,
			{barco3.getname(),to_string(barco3.getdist())} ,
			{barco4.getname(),to_string(barco4.getdist())} };
	//CREO UN ARRAY PARA EL USO DE TODOS LOS NITROS DE LOS BARCOS
		int nitrouses[6] ={1, 1, 1, 1, 1, 1};

//FUNCIONES
	void gamestarter() {
		cout << "\n";
		//INTRODUCCION DEL NOMBRE DE BARCO PARA EL USUARIO
			srand(time(NULL));
			cout << "Introduce el nombre del tu barco: ";
			cin >> nombre_barco;
			barco1.setname(nombre_barco);
			podio[0][0] = barco1.getname();
			cout << "\n";

		//SE ESTABLECE LA CANTIDAD DE BARCOS CONTRA LOS QUE SE COMPITEN
			while (numerobarcosenemigos > 4 || numerobarcosenemigos < 1) {
				cout << "Introduce la cantidad de barcos a los que te quieres enfrentar en la carrera (1-4)\n";
				cin >> numerobarcosenemigos;
			}
	}
	//VARIABLE DEL USO DEL NITRO POR PARTE DEL USUARIO
	void nitrousage(barcos& nombrebarco, int numbarco) {
		if (nitrouses[numbarco] == 1) {
			if (numbarco == 0) {
				while (nitrouse != 's' && nitrouse != 'n' && nitrouse != 'S' && nitrouse != 'N') {
					cout << "¿Quieres usar el nitro?\n";
					cin >> nitrouse;
				}
				if (nitrouse == 's') {
					Dd2 = int(rand() % 2);
					if (Dd2 == 1) {
						nombrebarco.setvel(nombrebarco.getvel() * 2);
						nitrouses[numbarco] = 0;
						cout << "Perfecto, salió uno en el dado, la velocidad de tu barco se multiplica por dos!\n";
					}
					else if (Dd2==0) {
						nombrebarco.setvel(nombrebarco.getvel() / 2);
						nitrouses[numbarco] = 0;
						cout << "Lástima... Sacas un cero en la tirada del dado. La velocidad de tu barco se divide a la mitad.\n";
					}
				}
			}
			else {
				if (Dd2 == 1 && Dd6 >3 ) {
					cout << "El barco " << nombrebarco.getname() << " activa el turbo!\n";
					nombrebarco.setvel(nombrebarco.getvel() * 2);
					nitrouses[numbarco] = 0;
				}
				else {
					cout << "El motor del barco " << nombrebarco.getname() << " se cala!\n";
				}
			}
		}
	}
	void turn(barcos& nombrebarco, int numbarco) {
		cout << "\n";
		//SE LANZA EL DADO DE 6 CARAS PARA DETERMINAR LA VELOCIDAD
			Dd6 = int(rand() % 6 + 1);
			cout << "El barco " << nombrebarco.getname() << " aumenta su velocidad en " << Dd6 << " unidades! Su velocidad pasa de " << nombrebarco.getvel();
			nombrebarco.setvel(nombrebarco.getvel()+Dd6);
			cout << " a " << nombrebarco.getvel()<<"\n";
			system("pause");

		//SE COMPRUEBA EL NITRO DE TODOS Y CADA UNO DE LOS BARCOS
			nitrousage(nombrebarco, numbarco);

		//Y SE COMPRUEBA LA DISTANCIA RECORRIDA DEL BARCO
			distancias[numbarco-1] = nombrebarco.getdist()+nombrebarco.getvel() * 100;
			nombrebarco.setdist(distancias[numbarco-1]);
			nombrebarco.checkdist();
			if (nombrebarco.getdist() > maxdist) {
				maxdist = nombrebarco.getdist();
				ganador = nombrebarco.getname();
			}
			for (int i = 0; i<numerobarcosenemigos; i++)
			{
				if (barcosenemigos[i].getname() == nombrebarco.getname()) {
					barcosenemigos[i].setdist(nombrebarco.getdist());
					break;
				}
			}
	}

	// DECLARO LA FUNCION DE DETERMINACIÓN DEL GANADOR
	void checkwinner() {
		cout << "\n";
		cout << "El ganador de la carrera es " << ganador << "\n";
		if (barco1.getname() == ganador) {
			cout << "Felicidades!\n";
		}
		else {
			cout << "Lastima...\n";
		}
		for (int i = 0; i<=numerobarcosenemigos; i++)
		{
			if (i == 0) {
				cout << barco1.getname() << "\t-\t-\t" << barco1.getdist() << "\n";
			}
			else {
				cout << barcosenemigos[i].getname() << "\t-\t-\t" << barcosenemigos[i].getdist() << "\n";
			}
		}
	}

	void turnos() {
		//TURNO DEL JUGADOR 1
		turn(barco1, 0);
		//TURNO DE LAS IAS
		for (int i = 1; i <= numerobarcosenemigos; i++)
		{
			turn(barcosenemigos[i], i);
		}
		system("pause");
		system("cls");
		if (turno == 4) {
			//SE COMPRUEBA EL GANADOR DE CARRERA
			checkwinner();
		}
	}

//MAIN
	int main() {
		//SE INICIA EL JUEGO
		gamestarter();
		for (turno=0;turno<5; turno++){
			//SE REALIZAN 5 TURNOS
			turnos();
		}	
		system("pause");
	}
