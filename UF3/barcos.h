#pragma once
#include <iostream>
using namespace std;

class barcos{
	//variables
private:
	int velocidad;
	int distancia;
	int nitro;
	string drivername;

public:
	//constructor
	barcos(int vel, string name, int c_distancia=0, int c_nitro=1);

		//getters
		int getvel();
		int getdist();
		int nitrostate();
		string getname();

		//setters
		void setvel(int newvel);
		void setdist(int newdist);
		void setnitrostate(int newnitrostate);
		void setname(string newname);
	
		//metodos
		void checkdist();
};