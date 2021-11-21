#include "../../archivos_h/construcciones/obelisco.h"

using namespace std;

Obelisco::Obelisco() : Edificio(){}

Obelisco::Obelisco(char jugador, unsigned int piedra_necesaria, unsigned int metal_necesario, unsigned int madera_necesaria) : Edificio(jugador, piedra_necesaria, metal_necesario, madera_necesaria) {
    this -> nombre_edificio = OBELISCO;
    this -> nombre_material = VACIO;
    this -> cantidad_material_producido = 0;
}
void Obelisco::mostrar_saludo() {
    cout << COLOR_MARRON << "Soy un obelisco y me encuentro en el casillero consultado" << COLOR_POR_DEFECTO << endl;
}