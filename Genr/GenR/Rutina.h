#ifndef RUTINA_H
#define RUTINA_H

#define MAX_TIMEOUT 50000000
#include "taulell.h"
#include <list>

class Rutina
{
    public:
        Rutina(Taulell *TNou);
        virtual ~Rutina();

        void Activa(Objecte *O, void* (*f)(void *) );
        void CreaInteraccio (Objecte *O1, Objecte *O2, void* (*f)(void *) );
        void Desactiva(Objecte *O);
        void EliminaInteraccio (Objecte *O1, Objecte *O2);

    private:

        Taulell *T;

        pthread_t *v_Behav[MAX_OBJ_X * MAX_OBJ_Y];

        struct nodeInt {
            Objecte *O;
            pthread_t *fil;
        };

        list<nodeInt> v_Interaccio[MAX_OBJ_X * MAX_OBJ_Y];

        enum exceptions{time_out, inexistent};
};

#endif // RUTINA_H
