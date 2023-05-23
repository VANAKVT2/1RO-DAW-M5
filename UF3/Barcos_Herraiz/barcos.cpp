#include "barcos.h"
#include <iostream>
using namespace std;
//constructor
barcos::barcos(int vel, string name, int c_distancia, int c_nitro) {
	velocidad = vel;
	distancia = c_distancia;
	nitro = c_nitro;
	drivername = name;
	}
//getters
int barcos::getvel() {
	return velocidad;
}
int barcos::getdist() {
	return distancia;
}
int barcos::nitrostate() {
	return nitro;
}
string barcos::getname() {
	return drivername;
}
//setters 
void barcos::setvel(int newvel) {
	velocidad = newvel;
}
void barcos::setnitrostate(int newnitrostate){
	nitro = newnitrostate;
}
void barcos::setname(string newname) {
	drivername = newname;
}
void barcos::setdist(int newdist) {
	distancia = newdist;
}
void barcos::checkdist() {
	cout << "El barco " << getname() << " se encuentra actualmente a " << getdist() << " metros del puerto!\n";
}