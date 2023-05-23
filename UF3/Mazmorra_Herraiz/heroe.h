#pragma once
#include "personajes.h"
class heroe :
    public personajes
{
private:
    int embestidaheroica=1;
    int turnoscd = 0;
public:

    void ataqueheroe(personajes& personajequerecibedaño, int dañoheroe, heroe& personaje);
    void ataqueespecial(personajes& personajesrecibe);
    heroe(int vida, int ataque, string nombre);
    heroe();
};