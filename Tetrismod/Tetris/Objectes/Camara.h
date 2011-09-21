#ifndef CAMARA_H
#define CAMARA_H

#include "taulell.h"
#include "objecte.h"

class Camara : public Objecte, public wxPanel
{
    public:
        Camara(wxFrame *parent, int ampl, int alc, Taulell *Tref);
        ~Camara();

        void Mou(int PosX, int PosY); //Posicions, no píxels.
        void Pinta();

        int getInfEsqx() {return x_infesq;}
        int getInfEsqy() {return y_infesq;}

        int getSupEsqx() {return (x_infesq + amplada_quadre);}
        int getSupEsqy() {return (y_infesq + alcada_quadre);}

    private:

        /**********************
         Definim variables.
         Posicions, no píxels.
        ***********************/
        int x_infesq;
        int y_infesq;
        int amplada;
        int alcada;

        static const int amplada_quadre = 20;
        static const int alcada_quadre = 20;

        /**********************
         Taulell associat a la càmara
        ***********************/
        Taulell *T;
};

#endif // CAMARA_H
