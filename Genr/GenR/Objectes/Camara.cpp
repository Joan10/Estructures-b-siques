#include "Camara.h"

//Camara::Camara(wxFrame *parent, int ampl, int alc, Taulell *Tref) : Objecte (),
//
//        wxPanel(parent,
//                wxID_ANY,
//                wxDefaultPosition,
//                wxSize(amplada_quadre * ampl, alcada_quadre*alc),
//                wxBORDER_NONE)
//
//{
Camara::Camara(int ampl, int alc, Taulell *Tref) : Objecte ()
{

    /*************************
    Inicialitzam les variables.
    **************************/
    this->amplada = ampl;
    this->alcada = alc;

    this->T = Tref;

    this->InfEsq = Punt();
    this->SupDret = Punt();
}

Camara::~Camara()
{
    delete this;
}

void Camara::assignaForma(){

}


void Camara::Mou(Punt Desti)
{

    int infx = Desti.x() - (amplada/2);
    int infy = Desti.y() - (alcada/2);

    int supx = Desti.x() + (amplada/2);
    int supy = Desti.y() + (alcada/2);

    if (infx < 0) {
        infx = 0;
        supx = amplada -1;
    }

    if (infx >= (T->numQuadresX() )) {
        infx = T->numQuadresX()-(amplada);
        supx = T->numQuadresX();
    }

    if (infy < 0) {
        infy = 0;
        supy = alcada -1;
    }

    if (infy >= (T->numQuadresY() )) {
        infy = T->numQuadresY()-(alcada);
        supy = T->numQuadresY();
    }

    InfEsq.set(infx,infy);
    SupDret.set(supx,supy);

    this->posabs = Desti;

}

void Camara::Pinta(){

    T->Pinta(InfEsq, SupDret);

}
