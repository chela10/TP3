#ifndef _ASERRADERO_H_
#define _ASERRADERO_H_

#include "edificio.h"

class Aserradero : public Edificio {

    public:

        /*
        * Post: Creará un objeto de tipo Aserradero dejando sus atributos cargados con valores por defecto.
        */
        Aserradero();

        /*
        * Post: Creará un objeto de tipo Aserradero usando los parametros que recibe.
        */
        Aserradero(char jugador, unsigned int piedra_necesaria, unsigned int metal_necesario, unsigned int madera_necesaria);

        Aserradero(char jugador);

        // PRE:
        // POS: muestra por pantalla el saludo del edificio
        void mostrar_saludo();
};

#endif // _ASERRADERO_H_