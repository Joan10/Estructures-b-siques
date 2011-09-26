#include <allegro.h>
#include "Controlador.h"

Controlador::Controlador(Taulell *T)
{
    this->aT = T;

}

Controlador::~Controlador()
{
    //dtor
}

void Controlador::AfegeixObjecte(Objecte *O)
{
    L.push_back(O);
}


//CTRL_OBJECTE

Ctrl_Objecte::Ctrl_Objecte(Taulell *T) : Controlador (T)
{}

void Ctrl_Objecte::Controla(){

    Objecte *O = L.back();

        if ( key[KEY_DOWN]){
            aT->Mou(O, Punt(aT->Posicio(O).x(), aT->Posicio(O).y()+1));
        } else if ( key[KEY_UP]){
            aT->Mou(O, Punt(aT->Posicio(O).x(), aT->Posicio(O).y()-1));
        } else if ( key[KEY_RIGHT]){
            aT->Mou(O, Punt(aT->Posicio(O).x()+1, aT->Posicio(O).y()));
        } else if ( key[KEY_LEFT]){
            aT->Mou(O, Punt(aT->Posicio(O).x()-1, aT->Posicio(O).y()));
        }

    while (key[KEY_DOWN] || key[KEY_UP] || key[KEY_RIGHT] || key[KEY_LEFT]) {};

   // while (keypressed()) { clear_keybuf(); printf("hola");}

}
