#include <iostream>

#include <stdlib.h>

#include <time.h>

#include <sstream>

#include <windows.h>

#include <mmsystem.h>

#pragma comment(lib, "Winmm.lib")

using namespace std;
string corazones[13] = {
  "AS",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9",
  "10",
  "J",
  "Q",
  "K"
};
string rombos[13] = {
  "AS",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9",
  "10",
  "J",
  "Q",
  "K"
};
string picas[13] = {
  "AS",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9",
  "10",
  "J",
  "Q",
  "K"
};
string treboles[13] = {
  "AS",
  "2",
  "3",
  "4",
  "5",
  "6",
  "7",
  "8",
  "9",
  "10",
  "J",
  "Q",
  "K"
};
string cartasusuario[13];
string cartascroupier[13];
int puntosusuario = 0;
int puntoscroupier = 0;
stringstream ss;
int cu = 2;
int cc = 1;
int cu1 = 0;
int cc1 = 0;

void compruebapuntos() {
    cout << "Los puntos del usuario: " << puntosusuario << "\n";
    cout << "Los puntos del croupier: " << puntoscroupier << "\n";
}

string darcarta(string stringreceptor) {
    int n = (rand() % 4) + 1;
    int p = rand() % 13;
    string carta;
    bool repite = true;
    string palo;
    int contador = 1;
    int c1 = 0;

    while (repite) {
        switch (n) {

        case 1:
            palo = "corazones";

            while (corazones[p] == "repe") {
                int p = c1;
                c1++;
                contador++;
                if (contador == 13) {
                    n = rand() % 4 + 1;
                    break;
                }
            }
            if (contador == 13) {
                contador = 1;
                c1 = 0;
                break;
            }
            carta = corazones[p];
            corazones[p] = "repe";
            repite = false;
            break;

        case 2:
            palo = "rombos";
            while (rombos[p] == "repe") {
                int p = c1;
                c1++;
                contador++;
                if (contador == 13) {
                    n = rand() % 4 + 1;
                    c1 = 0;
                    break;
                }
            }
            if (contador == 13) {
                contador = 1;
                break;
            }
            carta = rombos[p];
            rombos[p] = "repe";
            repite = false;
            break;

        case 3:
            palo = "picas";
            while (picas[p] == "repe") {
                int p = c1;
                c1++;
                contador++;
                if (contador == 13) {
                    c1 = 0;
                    n = rand() % 4 + 1;
                    break;
                }
            }
            if (contador == 13) {
                contador = 1;
                break;
            }
            carta = picas[p];
            picas[p] = "repe";
            repite = false;
            break;

        case 4:
            palo = "treboles";
            while (treboles[p] == "repe") {
                int p = c1;
                c1++;
                contador++;
                if (contador == 13) {
                    n = rand() % 4 + 1;
                    c1 = 0;
                    break;
                }
            }
            if (contador == 13) {
                contador = 1;
                break;
            }
            carta = treboles[p];
            treboles[p] = "repe";
            repite = false;
            break;

        }

    }
    string aux = carta;
    if (stringreceptor == "croupier") {

        if (aux == "AS") {
            if (11 + puntoscroupier > 21) {
                aux = "1";
            }
            else {
                aux = "11";
            }
        }
        else if (aux == "Q" || aux == "K" || aux == "J") {
            aux = "10";
        }
        puntoscroupier += stoi(aux);
        cc1++;
    }
    else if (stringreceptor == "usuario") {
        if (aux == "AS") {
            string opcion = "";
            while (opcion != "1" && opcion != "11") {

                cout << "Salio el AS de "<< palo<<". Prefieres que valga 11[11] o 1[1] ? ";
                cin >> opcion;
            }
            if (opcion == "11") {
                aux = "11";
            }
            else {
                aux = "1";
            }
        }
        else if (aux == "Q" || aux == "K" || aux == "J") {
            aux = "10";
        }
        puntosusuario += stoi(aux);
        cu1++;
    }

    return (carta + " de " + palo);
}

void setter1() {
    for (int i = 0; i < 13; i++) {
        cartasusuario[i] = "VACIO";
        cartascroupier[i] = "VACIO";
    }
    cout << "El croupier te reparte 2 cartas y se reparte a el una sola carta.\n";
    
    cartasusuario[0] = darcarta("usuario");
    cartasusuario[1] = darcarta("usuario");
    cartascroupier[0] = darcarta("croupier");
    cout<< "Tus dos cartas son : \n[1] - "<<cartasusuario[0] << "\n[2] - " << cartasusuario[1] << "\n";

    cout << "La carta del croupier es el " << cartascroupier[0] << "\n";

}

void pedircartas() {
    bool pidiendo = true;
    while (pidiendo) {
        cout << "Quieres pedir mas cartas?\nSI-PEDIR MAS CARTAS \tNO-TURNO DE LA BANCA[DEFAULT]";
        string eleccion;
        cin >> eleccion;
        if (eleccion == "si" || eleccion == "SI") {
            cartasusuario[cu] = darcarta("usuario");
            cout << "La carta que has recibido es " << cartasusuario[cu] << "\n";
            cu++;
        }
        else {
            pidiendo = false;
        }
        compruebapuntos();

    }
    while (puntoscroupier < 21 && puntosusuario>puntoscroupier) {
        if (puntosusuario > 21 || puntoscroupier+1>21) {
            break;
        }
        cartascroupier[cc] = darcarta("croupier");
        cout << "La carta que ha recibido el croupier es " << cartascroupier[cc] << "\n";
        compruebapuntos();
        cc++;
    }
}

void finpartida() {
    if (puntosusuario > 21) {
        cout << "Perdiste la partida!" << "\n";
    }
    else {
        cout << "El croupier tiene " << puntoscroupier << "!\n";
        if (puntoscroupier > 21 || puntoscroupier < puntosusuario) {
            cout << "Ganaste la partida!\n";
        }
        else if (puntoscroupier == puntosusuario) {
            cout << "Hubo un empate...\n";
        }
        else if (puntoscroupier > puntosusuario) {
            cout << "El croupier gana!\n";
        }
    }
}

int main(void) {
    srand(time(NULL));
    setter1();
    compruebapuntos();
    pedircartas();
    finpartida();
}