#ifndef BEHAVIORS_H
#define BEHAVIORS_H

void *Behavior_01(void *ptr) {

/*****************************
    Passos obligats, no ho toqueu
******************************/
	buff B = *(buff *) ptr;
    Taulell *T = B.tempT;

    Objecte *O = B.O;
    *B.llest = true;

/*******************************************
    Definit per l'usuari. Recomanat
    emprar variables *T per al taulell i
    O per l'identificador de l'objecte
********************************************/

    while (1 == 1) {

        T->Rota(O, esquerra);
        sleep(1);
    }

    return NULL;

}

void *Behavior_02(void *ptr) {

/*****************************
    Passos obligats, no ho toqueu
******************************/
	buff B = *(buff *) ptr;
    Taulell *T = B.tempT;

    Objecte *O = B.O;
    *B.llest = true;

/*******************************************
    Definit per l'usuari. Recomanat
    emprar variables *T per al taulell i
    O per l'identificador de l'objecte
********************************************/
    for (int i = 1; i<100; i++){
        for (int j = 1; j<100; j++){
            for (int k = 1; k<100; k++){
                T->CanviaColor(O,i,j,k);
                sleep(1);
            }
        }
    }

    return NULL;

}

#endif

