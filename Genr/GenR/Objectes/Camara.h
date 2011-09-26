#ifndef CAMARA_H
#define CAMARA_H

#include "../taulell.h"
#include "../objecte.h"

class Camara : public Objecte
{
    public:
        Camara( int ampl, int alc, Taulell *Tref);
        ~Camara();

//        void Pinta();

        Punt getInfEsq()
        {
            return InfEsq;

        }
        Punt getSupDret()
        {

            return SupDret;

        }

        void assignaForma();

        void Pinta();
        virtual void Mou(Punt Desti);

    private:

        /**********************
         Definim variables.
         Posicions, no píxels.
        ***********************/
        Punt InfEsq;
        Punt SupDret;

        int amplada;
        int alcada;

        /*******************
        Mides en píxels d'un quadre.
        *******************/
        static const int amplada_quadre = 20;
        static const int alcada_quadre = 20;

        /**********************
         Taulell associat a la càmara
        ***********************/
        Taulell *T;
};

#endif // CAMARA_H
