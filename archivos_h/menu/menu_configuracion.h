#ifndef _MENU_CONFIGURACION_H_
#define _MENU_CONFIGURACION_H_
#include "menu.h"

class Menu_configuracion: public Menu{
    public:
        Menu_configuracion();
        
        void mostrar_menu();

        int pedir_opcion();
};

#endif //_MENU_CONFIGURACION_H_