#include "../../archivos_h/construcciones/mina_oro.h"

using namespace std;

Mina_oro::Mina_oro(): Edificio() {}

Mina_oro::Mina_oro(char jugador, unsigned int piedra_necesaria, unsigned int metal_necesario, unsigned int madera_necesaria): Edificio(jugador, piedra_necesaria, metal_necesario, madera_necesaria){
    nombre_edificio = MINA;
    nombre_material = PIEDRA;
    cantidad_material_producido = BRINDAR_MATERIALES_MINA_ORO;
}
void Mina_oro::mostrar_saludo() {
    cout << COLOR_MARRON << "Soy una mina de oro y me encuentro en el casillero consultado" << COLOR_POR_DEFECTO << endl;
}