#include "../../archivos_h/materiales/madera.h"

using namespace std;

Madera::Madera(unsigned int cantidad_inventario) {
    this -> nombre = MADERA;
    this -> cantidad = cantidad_inventario;
}

void Madera::saludar() {
    cout << "Soy una Madera " << EMOJI_MADERA << ", y me encuentro en el casillero consultado." << endl;
}

void Madera::mostrar_material() {
    cout << "--> Material: madera, cantidad: " << this -> cantidad << endl;
}