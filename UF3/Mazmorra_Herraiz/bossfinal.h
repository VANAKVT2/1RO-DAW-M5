#pragma once
#include "personajes.h"
#include <iostream>
class bossfinal :
    public personajes
{
private:
    int ataquedefinitivo = getATK() * 2;
	int turnoscd2 = 0;
	int turnoscd3 = 0;
	int ataquedefinitivo2 = getATK() * 2.5;

public:
	void ataqueboss(personajes& elpersonajequerecibe, int ataque, personajes& elqueataca, int random);
	bossfinal(int vida, int ataque, string nombre );
	};

