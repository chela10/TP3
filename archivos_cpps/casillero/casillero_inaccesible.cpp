#include "../../archivos_h/casilleros/casillero_inaccesible.h"

using namespace std;

CasilleroInaccesible::CasilleroInaccesible(){
    tipo_terreno = LAGO;
}

void CasilleroInaccesible::CasilleroInaccesible::mostrar(){
    cout << COLOR_DORADO << LINEA_DIVISORIA_DISENIO << COLOR_POR_DEFECTO;
    cout << "Soy un casillero inaccesible, y no me encuentro vacío. Soy un Lago" << endl;
    cout << COLOR_DORADO << LINEA_DIVISORIA_DISENIO << COLOR_POR_DEFECTO;
}