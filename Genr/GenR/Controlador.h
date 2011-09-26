#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#include <list>

#include "taulell.h"
#include "objecte.h"
#include "Punt.h"

class Controlador
{
    public:
        Controlador(Taulell *T);
        ~Controlador();

        void AfegeixObjecte(Objecte *O);
        //void TreuObjecte(Objecte *O);
        virtual void Controla() = 0;
    protected:
        Taulell *aT;
        list<Objecte*> L;
        list<Objecte*>::iterator i;

};

#endif // CONTROLADOR_H

#ifndef CTRL_OBJECTE_H
#define CTRL_OBJECTE_H
class Ctrl_Objecte : public Controlador{
public:
    Ctrl_Objecte(Taulell *T);
    void Controla();
};
#endif
