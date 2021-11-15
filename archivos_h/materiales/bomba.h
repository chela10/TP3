#ifndef _BOMBA_H_
#define _BOMBA_H_

#include "../material.h"

class Bomba: public Material{

public:
    /*
        * Post: Creará un objeto de tipo Bomba, dejando sus atributos cargados con los valores por defecto.
        */
    Bomba();

    /*
        * Post: Creará un objeto de tipo Bomba con el parámetro cantidad_inventario.
        */
    Bomba(int cantidad_inventario);
};

#endif // _BOMBA_H_