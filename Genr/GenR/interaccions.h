#ifndef INTERACCIO_H
#define INTERACCIO_H

void *Interaccio_01(void *ptr) {

/*****************************
    Passos obligats, no ho toqueu
******************************/
	buff_multi B = *(buff_multi *) ptr;
    Taulell *T = B.tempT;

    Objecte *O1 = B.O1;
    Objecte *O2 = B.O2;
    *B.llest = true;

/*******************************************
    Definit per l'usuari. Recomanat
    emprar variables *T per al taulell i
    O per l'identificador de l'objecte
********************************************/
    Punt P = Punt();
    while (1 == 1) {
        if (T->Distancia(O1,O2) < 200){
            T->Rota(O1, esquerra);
            T->Rota(O2, dreta);
        }

        /***************************
         Codi per moure un objecte.
        ****************************/
//        P=T->Posicio(O1);
//        P.setY(P.y()+1);
//
//        T->Mou(O1, P);
//        T->Pinta();

        //printf("%f \n", T->Distancia(O1,O2));
        sleep(1);
    }

    return NULL;

}
#endif
