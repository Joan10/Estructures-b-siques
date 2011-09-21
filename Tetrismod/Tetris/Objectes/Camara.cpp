#include "Camara.h"

Camara::Camara(wxFrame *parent, int ampl, int alc, Taulell *Tref) : Objecte (),

        wxPanel(parent,
                wxID_ANY,
                wxDefaultPosition,
                wxSize(amplada_quadre * ampl, alcada_quadre*alc),
                wxBORDER_NONE)

{


    /*************************
    Inicialitzam les variables.
    **************************/
    this->amplada = ampl;
    this->alcada = alc;

    this->T = Tref;
}

Camara::~Camara()
{
    delete this;
}

void Camara::Mou(int PosX, int PosY)
{

    int x = PosX - (amplada/2);
    int y = PosY - (alcada/2);

    if (x < 0) x_infesq = 0;
    else x_infesq = x;

    if (x >= (T->numQuadresX() )) x_infesq = T->numQuadresX();
    else x_infesq = x;

    if (y < 0) y_infesq = 0;
    else y_infesq = y;

    if (y >= (T->numQuadresY() )) y_infesq = T->numQuadresY();
    else y_infesq = y;

}

void Camara::Pinta(int PosX, int PosY){

    T->Pinta(getInfEsqx(), getInfEsqy(), getSupEsqx(), getSupEsqy() );

}
