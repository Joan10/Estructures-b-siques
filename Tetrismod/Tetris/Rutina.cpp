#include "Rutina.h"
#include "utils.h"
#include <pthread.h>

Rutina::Rutina(Taulell *TNou)
{
    this->T = TNou;

    for (int i = 0; i<MAX_OBJ_X*MAX_OBJ_Y; i++){
        v_Behav[i] = NULL;
        //v_Interaccio[i] = new List;
    }
}

Rutina::~Rutina()
{
    //dtor
}

void Rutina::Activa(Objecte *O, void* (*f)(void *) ) {

    bool l = false; // l és un punter a una variable que informa al pare quan el fill està llest de carregar memòria i per
                    // tant el pare pot acabar i sortir. Sino sembla que intentava accedir a llocs de memòria buits i botaven
                    //excepcions.

    try{
        pthread_t  p_thread;
        int        thr_id;

        buff buff_1; buff_1.tempT = T; buff_1.O = O; buff_1.llest = &l;

        thr_id = pthread_create(&p_thread, NULL, f, (void *) &buff_1 );

        v_Behav[O->treuId()] = &p_thread;

        int temps = 0;

        while (!l && temps < MAX_TIMEOUT ) {
            temps++;
        } //esperam a que el fill acabi o que la variable temps arribi a TIME OUT, cas en què llançarà una excepció, ja que voldrà dir que el fill no respon.

        if (temps == MAX_TIMEOUT) {
            throw time_out;
        }
        l = false; // posam l a fals un altre cop.

    }catch(exceptions e){ //En cas que el fill no respongui ho aturam tot.

        pthread_cancel(*v_Behav[O->treuId()]);
        v_Behav[O->treuId()] = NULL;
        l = false; // posam l a fals un altre cop.

        printf ("Rutina::Activa(T_ID O, void* (*f)(void *) => Error de time out, el procés fill de l'objecte %i no respon. Has posat la variable 'lliure' del buffer a cert? \n ",
                O->treuId());

    }
}

void Rutina::Desactiva(Objecte *O) {

    try{
        if (v_Behav[O->treuId()]==NULL) throw inexistent;
        pthread_cancel(*v_Behav[O->treuId()]);
        v_Behav[O->treuId()] = NULL;
    }catch(exceptions e){

        printf ("Rutina::Desactiva(T_ID O) => L'objecte %i no té cap comportament predefinit \n ",
                O->treuId());

    }
}


void Rutina::CreaInteraccio (Objecte *O1, Objecte *O2, void* (*f)(void *) )
{

    bool l = false; // l és un punter a una variable que informa al pare quan el fill està llest de carregar memòria i per
                    // tant el pare pot acabar i sortir. Sino sembla que intentava accedir a llocs de memòria buits i botaven
                    //excepcions.

    try{
        pthread_t  p_thread;
        int        thr_id;

        buff_multi buff_1;
        buff_1.tempT = T; buff_1.O1 = O1; buff_1.O2 = O2; buff_1.llest = &l;

        thr_id = pthread_create(&p_thread, NULL, f, (void *) &buff_1 );


        nodeInt IntBuff01; IntBuff01.O = O2; IntBuff01.fil = &p_thread;
        nodeInt IntBuff02; IntBuff02.O = O1; IntBuff02.fil = &p_thread;

        v_Interaccio[O1->treuId()].push_back(IntBuff01);
        v_Interaccio[O2->treuId()].push_back(IntBuff02);

        int temps = 0;
        while (!l && temps < MAX_TIMEOUT ) {
            temps++;
        } //esperam a que el fill acabi o que la variable temps arribi a TIME OUT, cas en què llançarà una excepció, ja que voldrà dir que el fill no respon.

        if (temps == MAX_TIMEOUT) {
            throw time_out;
        }
        l = false; // posam l a fals un altre cop.

    }catch(exceptions e){ //En cas que el fill no respongui ho aturam tot.

        pthread_t p_thread = *v_Interaccio[O1->treuId()].back().fil;
        v_Interaccio[O1->treuId()].pop_back();
        pthread_cancel(p_thread);

        v_Interaccio[O2->treuId()].pop_back();

        l = false; // posam l a fals un altre cop.

        printf ("Rutina::CreaInteraccio (T_ID O1, T_ID O2, void* (*f)(void *) ) => Error de time out, el procés fill de la interacció dels objectes %i i %i no respon. Has posat la variable 'lliure' del buffer a cert? \n ",
                O1->treuId(), O2->treuId());

    }
}


void Rutina::EliminaInteraccio (Objecte *O1, Objecte *O2) {

        pthread_t p_thread = *v_Interaccio[O1->treuId()].back().fil;
        v_Interaccio[O1->treuId()].pop_back();
        pthread_cancel(p_thread);

        v_Interaccio[O2->treuId()].pop_back();


}

