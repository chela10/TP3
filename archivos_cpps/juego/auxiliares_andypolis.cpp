#include "../../archivos_h/juego/auxiliares_andypolis.h"

using namespace std;

Auxiliares_andypolis::Auxiliares_andypolis() {}

void Auxiliares_andypolis::seleccionar_jugador(string & nombre_jugador_1, string & nombre_jugador_2) {
    cout << "¿Que jugador quiere ser? Ingrese 1 para ser el primer jugador, 2 para el segundo" << endl;
    cout << COLOR_DORADO << ">> " << COLOR_POR_DEFECTO;
    cin >> nombre_jugador_1;
    nombre_jugador_2 = nombre_jugador_1 != NUMERO_JUGADOR_1 ? NUMERO_JUGADOR_1 : NUMERO_JUGADOR_2;
}

Jugador* Auxiliares_andypolis::cambiar_turno(Jugador* jugador_actual, Jugador* jugador_1, Jugador* jugador_2) {
    return jugador_actual == jugador_1 ? jugador_2 : jugador_1;
}

void Auxiliares_andypolis::aumentar_materiales_producidos(Jugador* jugador_actual) {
    Edificio** edificio = jugador_actual -> obtener_edificios_construidos();
    for(int i = 0; i < jugador_actual -> obtener_construidos(); i++)
        edificio[i] -> aumentar_material_producido();
}

Jugador* Auxiliares_andypolis::asignar_turno(Jugador* jugador_1, Jugador* jugador_2) {
    return (rand() % 2 + 1) == 1 ? jugador_1 : jugador_2;
}

int* Auxiliares_andypolis::pedir_coordenadas(Mapa* mapa) {
    int* coordenadas = new int[MAX_COORDENADAS];
    bool ubicado = false;
    while (!ubicado) {
        cout << "Ingrese la fila" << COLOR_DORADO << " >> " << COLOR_POR_DEFECTO;
        cin >> coordenadas[INDICE_FILA];
        cout << "Ingrese la columna" << COLOR_DORADO << " >> " << COLOR_POR_DEFECTO;
        cin >> coordenadas[INDICE_COLUMNA];
        ubicado = !mapa -> coordenadas_fuera_de_rango(coordenadas[INDICE_FILA], coordenadas[INDICE_COLUMNA]);
    }
    return coordenadas;
}

bool Auxiliares_andypolis::validar_coordenadas(Mapa* mapa, int fila, int columna) {
    return !mapa -> coordenadas_fuera_de_rango(fila, columna) && this -> es_casillero_valido(mapa, fila, columna);
}

bool Auxiliares_andypolis::es_casillero_valido(Mapa* mapa, int fila, int columna) {
    bool es_valido = !mapa -> esta_ocupado(fila, columna) && mapa -> obtener_tipo_casillero(fila, columna) != LAGO;
    if (!es_valido)
        cout << COLOR_ROJO << "Las coordenadas que ingresaste no pertenecen a un casillero válido" << COLOR_POR_DEFECTO << endl;
    return es_valido;
}

void Auxiliares_andypolis::verificar_energia(Jugador* jugador_actual, int & opcion_ingresada) {
    if (!jugador_actual -> obtener_energia_actual()) {
        opcion_ingresada = OPCION_FINALIZAR_TURNO;
        cout << jugador_actual -> obtener_codigo_emoji() << COLOR_ROJO << "Te quedaste sin energia :( Ahora es turno del siguiente jugador" << COLOR_POR_DEFECTO << endl;
        sleep(3);
    }
}

string Auxiliares_andypolis::pedir_nombre_edificio() {
    string nombre_edificio;
    cout << "Ingrese el nombre del edificio" << COLOR_DORADO << " >> " << COLOR_POR_DEFECTO;
    getline(cin.ignore(), nombre_edificio);
    transform(nombre_edificio.begin(), nombre_edificio.end(), nombre_edificio.begin(), ::tolower);
    return nombre_edificio;
}

int Auxiliares_andypolis::pedir_nueva_cantidad_material(string material) {
    int cantidad = -1;
    while (cantidad < MIN_VALOR_MATERIAL || cantidad > MAX_VALOR_MATERIALES) {
        cout << "Ingrese la nueva cantidad de " << material << " >> " << COLOR_DORADO << COLOR_POR_DEFECTO;
        cin >> cantidad;
    }
    return cantidad;
}

void Auxiliares_andypolis::modificar_materiales_necesarios(Edificio* edificio) {
    int nueva_cantidad_piedra = this -> pedir_nueva_cantidad_material(PIEDRA);
    int nueva_cantidad_madera = this -> pedir_nueva_cantidad_material(MADERA);
    int nueva_cantidad_metal = this -> pedir_nueva_cantidad_material(METAL);
    edificio -> establecer_nuevos_materiales(nueva_cantidad_piedra, nueva_cantidad_madera, nueva_cantidad_metal);
}

bool Auxiliares_andypolis::hay_energia_suficiente(int energia_necesaria, int energia_del_jugador) {
    bool energia_suficiente = energia_del_jugador >= energia_necesaria;
    if (!energia_suficiente)
        cout << COLOR_ROJO << "No hay energia suficiente" << COLOR_POR_DEFECTO << endl;
    return energia_suficiente;
}

void Auxiliares_andypolis::modificar_energia(Jugador* jugador_actual, int cantidad_a_modificar) {
    jugador_actual -> modificar_energia(cantidad_a_modificar);
}

bool Auxiliares_andypolis::es_posible_comprar_bombas(int cantidad_de_bombas, int cantidad_andycoins) {
    bool se_pudo_comprar = cantidad_andycoins >= (cantidad_de_bombas * COSTO_ANDYCOINS_BOMBA);
    if (se_pudo_comprar)
        cout << COLOR_VERDE << "Compra realizada exitosamente" << COLOR_POR_DEFECTO << endl;
    else
        cout << COLOR_ROJO << "No tiene Andycoins suficientes" << COLOR_POR_DEFECTO << endl;
    return se_pudo_comprar;
}

void Auxiliares_andypolis::construir_edificio_auxiliar(Abb* edificios_disponibles, Mapa* mapa, Jugador* jugador_actual, string edificio_a_construir) {
    Edificio* edificio = edificios_disponibles -> buscar_edificio(edificio_a_construir);
    if (!edificio)
        cout << COLOR_ROJO << "El edificio ingresado no existe, intente nuevamente" << COLOR_POR_DEFECTO << endl;

    else if (this -> se_alcanzo_maximo_permitido(edificios_disponibles, edificio, jugador_actual))
        cout << COLOR_ROJO << "Ya estan construidos la cantidad maxima de " << edificio_a_construir << " posibles" << COLOR_POR_DEFECTO << endl;

    else {
        Inventario* inventario = jugador_actual -> obtener_inventario();
        bool hay_piedra_suficiente = this -> hay_material_suficiente(PIEDRA, inventario, edificio -> obtener_cantidad_necesaria(PIEDRA));
        bool hay_madera_suficiente = this -> hay_material_suficiente(MADERA, inventario, edificio -> obtener_cantidad_necesaria(MADERA));
        bool hay_metal_suficiente = this -> hay_material_suficiente(METAL, inventario, edificio -> obtener_cantidad_necesaria(METAL));
        
        if (!hay_piedra_suficiente || !hay_madera_suficiente || !hay_metal_suficiente)
            cout << COLOR_ROJO << "No hay materiales suficientes para construir" << edificio_a_construir << COLOR_POR_DEFECTO << endl;

        else if (!this -> confirmar_construccion(edificio_a_construir))
            cout << COLOR_VERDE << "Operacion cancelada" << COLOR_POR_DEFECTO << endl;

        else {
            int* coordenadas = this -> pedir_coordenadas(mapa);
            Edificio* nuevo_edificio = this -> crear_edificio(edificio_a_construir, coordenadas[INDICE_FILA], coordenadas[INDICE_COLUMNA]);
            if (mapa -> ubicar_edificio(nuevo_edificio, coordenadas[INDICE_FILA], coordenadas[INDICE_COLUMNA])) { 
                int piedra_necesaria = edificio -> obtener_cantidad_necesaria(PIEDRA);
                int madera_necesaria = edificio -> obtener_cantidad_necesaria(MADERA);
                int metal_necesario = edificio -> obtener_cantidad_necesaria(METAL);
                this -> actualizar_inventario(jugador_actual -> obtener_inventario(), - piedra_necesaria, - madera_necesaria, - metal_necesario);
                jugador_actual -> cargar_edificio(nuevo_edificio);
                jugador_actual -> modificar_energia(-ENERGIA_CONSTRUIR_EDIFICIO);
                cout << jugador_actual -> obtener_energia_actual() << endl;
                cout << COLOR_VERDE << "El edificio fue construido satisfactoriamente" << COLOR_POR_DEFECTO << endl;
            }
            delete [] coordenadas;
            coordenadas = nullptr;
        }
    }
}

bool Auxiliares_andypolis::se_alcanzo_maximo_permitido(Abb* edificios_disponibles, Edificio* edificio_a_construir, Jugador* jugador_actual) {
    return edificios_disponibles -> contar_construidos(jugador_actual, edificio_a_construir -> obtener_nombre()) == edificio_a_construir -> obtener_permitidos();
}

bool Auxiliares_andypolis::hay_material_suficiente(string material, Inventario* inventario, int cantidad_material) {
    return inventario -> obtener_material(material) -> obtener_cantidad() >= cantidad_material;
}

void Auxiliares_andypolis::actualizar_inventario(Inventario* inventario, int piedra, int madera, int metal) {
    inventario -> modificar_cantidad_material(PIEDRA, piedra);
    inventario -> modificar_cantidad_material(MADERA, madera);
    inventario -> modificar_cantidad_material(METAL, metal);
}

bool Auxiliares_andypolis::confirmar_construccion(string edificio_a_construir) {
    string decision;
    cout << "Está seguro que quiere construir un/a " << edificio_a_construir << " ?(s/n): ";
    cin >> decision;
    transform(decision.begin(), decision.end(), decision.begin(), ::tolower);
    return (decision == DECISION_SI);
}

void Auxiliares_andypolis::demoler_edificio_auxiliar(Abb* edificios_disponibles, Mapa* mapa, Jugador* jugador_actual, int fila, int columna) {
    string nombre_edificio = mapa -> obtener_edificio(fila, columna) -> obtener_nombre();    
    if (mapa -> obtener_tipo_casillero(fila, columna) != TERRENO)
        cout << COLOR_ROJO << "En las coordenadas ingresadas no se puede demoler dado que no es un casillero de tipo Terreno" << COLOR_POR_DEFECTO << endl;
    else if (!mapa -> obtener_edificio(fila, columna))
        cout << COLOR_ROJO << "En las coordenadas ingresadas no hay un edificio por demoler" << COLOR_POR_DEFECTO << endl;
    else if (!jugador_actual -> eliminar_edificio(fila, columna))
        cout << COLOR_ROJO << "No puede demoler un edificio que no le pertenece" << COLOR_POR_DEFECTO << endl;
    else {
        Edificio* edificio_a_demoler = edificios_disponibles -> buscar_edificio(nombre_edificio);
        int piedra_necesaria = edificio_a_demoler -> obtener_cantidad_necesaria(PIEDRA);
        int madera_necesaria = edificio_a_demoler -> obtener_cantidad_necesaria(MADERA);
        int metal_necesario = edificio_a_demoler -> obtener_cantidad_necesaria(METAL);
        this -> actualizar_inventario(jugador_actual -> obtener_inventario(), piedra_necesaria / 2, madera_necesaria / 2, metal_necesario / 2);
        mapa -> liberar_posicion(fila, columna);
        jugador_actual -> modificar_energia(-ENERGIA_DEMOLER_EDIFICIO_COORDENADA);
        cout << COLOR_VERDE << nombre_edificio << " fue demolido statisfactoriamente!" << COLOR_POR_DEFECTO << endl;
    }
}

void Auxiliares_andypolis::reparar_edificio_auxiliar(Abb* edificios_disponibles, Mapa* mapa, Jugador* jugador, int fila, int columna) {
    Edificio* edificio = mapa -> obtener_edificio(fila, columna);
    if (mapa -> obtener_tipo_casillero(fila, columna) != TERRENO)
        cout << COLOR_ROJO << "En las coordenadas ingresadas no se puede reparar dado que no es un casillero de tipo Terreno" << COLOR_POR_DEFECTO << endl;
    else if (!edificio)
        cout << COLOR_ROJO << "En las coordenadas ingresadas no hay un edificio por reparar" << COLOR_POR_DEFECTO << endl;
    else if (!jugador -> existe_el_edificio(fila, columna))
        cout << COLOR_ROJO << "No puede reparar un edificio que no le pertenece" << COLOR_POR_DEFECTO << endl;
    else if (!edificio -> esta_afectado())
        cout << COLOR_ROJO << "No puede reparar un edificio que no esta afectado" << COLOR_POR_DEFECTO << endl;
    else {
        Edificio* receta_edificio = edificios_disponibles -> buscar_edificio(edificio -> obtener_nombre());
        int piedra_necesaria = (int) (receta_edificio -> obtener_cantidad_necesaria(PIEDRA) * 0.25);
        int madera_necesaria = (int) (receta_edificio -> obtener_cantidad_necesaria(MADERA) * 0.25);
        int metal_necesario = (int) (receta_edificio -> obtener_cantidad_necesaria(METAL) * 0.25);
        Inventario* inventario = jugador -> obtener_inventario();
        bool hay_piedra_suficiente = this -> hay_material_suficiente(PIEDRA, inventario, piedra_necesaria);
        bool hay_madera_suficiente = this -> hay_material_suficiente(MADERA, inventario, madera_necesaria);
        bool hay_metal_suficiente = this -> hay_material_suficiente(METAL, inventario, metal_necesario);
        if (!hay_piedra_suficiente || !hay_madera_suficiente || !hay_metal_suficiente)
            cout << COLOR_ROJO << "No tiene materiales suficientes para reparar" << edificio -> obtener_nombre() << COLOR_POR_DEFECTO << endl;
        else {
            edificio -> cambiar_estado_afectado();
            this -> actualizar_inventario(inventario, piedra_necesaria, madera_necesaria, metal_necesario);
            jugador -> modificar_energia(-ENERGIA_REPARAR_EDIFICIO);
            cout << COLOR_VERDE << edificio -> obtener_nombre() << " fue reparado satisfactoriamente" << COLOR_POR_DEFECTO << endl;
        } 
    }
}

void Auxiliares_andypolis::recolectar_recursos_auxiliares(Jugador* jugador_actual) {
    string material;
    int cantidad_material = 0;
    Edificio** edificios_construidos = jugador_actual -> obtener_edificios_construidos();
    for (int i = 0; i < jugador_actual -> obtener_construidos(); i++) {
        material = edificios_construidos[i] -> obtener_nombre_del_material();
        cantidad_material = edificios_construidos[i] -> obtener_cantidad_de_material_producido();
        jugador_actual -> modificar_inventario(material, cantidad_material);
    }
    cout << COLOR_VERDE_AGUA << " Los recursos producidos por los edificios fueron recolectados satisfactoriamente" << COLOR_POR_DEFECTO << endl;
}

void Auxiliares_andypolis::atacar_edificio_auxiliar(Mapa* mapa, Jugador* jugador_actual, Jugador* jugador_1, Jugador* jugador_2, int fila, int columna) {
    Jugador* jugador_atacado = jugador_actual == jugador_1 ? jugador_2 : jugador_1;
    if (mapa -> obtener_tipo_casillero(fila, columna) != TERRENO)
        cout << COLOR_ROJO << "En las coordenadas ingresadas no se puede atacar dado que no es un casillero de tipo Terreno" << endl;
    else if (mapa -> esta_ocupado(fila, columna) && !mapa -> obtener_edificio(fila, columna))
        cout << COLOR_ROJO << "En las coordenadas ingresadas no hay un edificio por atacar" << endl;
    else if (jugador_actual -> existe_el_edificio(fila, columna))
        cout << COLOR_ROJO << "Sos suicida???, estas atacandote a vos mismo" << endl;
    else {
        Edificio* edificio = mapa -> obtener_edificio(fila, columna);
        Inventario* inventario = jugador_actual -> obtener_inventario();
        int cantidad_bombas = inventario -> obtener_material(BOMBA) -> obtener_cantidad();
        if (!cantidad_bombas)
            cout << COLOR_ROJO << "No tiene bombas suficientes para atacar" << endl;
        else if ((edificio -> obtener_nombre() == NOMBRE_MINA || edificio -> obtener_nombre() == NOMBRE_FABRICA) && !edificio -> esta_afectado()) {
            edificio -> cambiar_estado_afectado();
            jugador_actual -> modificar_energia(-ENERGIA_ATACAR_EDIFICIO_COORDENADA);
            cout << COLOR_VERDE << edificio -> obtener_nombre() << " fue dañado" << endl;
        }
        else {
            mapa -> liberar_posicion(fila, columna);
            jugador_atacado -> eliminar_edificio(fila, columna);
            inventario -> modificar_cantidad_material(BOMBA, -1);
            jugador_actual -> modificar_energia(-ENERGIA_ATACAR_EDIFICIO_COORDENADA);
            cout << COLOR_VERDE << edificio -> obtener_nombre() << " fue destruido" << endl;
        }
    }
    cout << COLOR_POR_DEFECTO;
}

Edificio* Auxiliares_andypolis::crear_edificio(string nombre, int fila, int columna) { //metodo repetido
    Edificio* edificio_creado = nullptr;

    if (nombre == NOMBRE_ASERRADERO)
        edificio_creado = new Aserradero(fila, columna);
    else if (nombre == NOMBRE_ESCUELA) 
        edificio_creado = new Escuela(fila, columna);
    else if (nombre == NOMBRE_FABRICA) 
        edificio_creado = new Fabrica(fila, columna);
    else if (nombre == NOMBRE_MINA) 
        edificio_creado = new Mina(fila, columna);
    else if (nombre == NOMBRE_OBELISCO) 
        edificio_creado = new Obelisco(fila, columna);
    else if (nombre == NOMBRE_PLANTA_ELECTRICA) 
        edificio_creado = new Planta_electrica(fila, columna);
    else if (nombre == NOMBRE_MINA_ORO) 
        edificio_creado = new Mina_oro(fila, columna);

    return edificio_creado;
}