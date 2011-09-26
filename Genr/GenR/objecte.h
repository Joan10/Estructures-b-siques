#ifndef OBJECTE_H
#define OBJECTE_H
#define MAX_QUADRES 20
#define MAX_OBJ_X 50
#define MAX_OBJ_Y 50

#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include "Punt.h"


using namespace std;

typedef int T_ID;

class Objecte {

public:
    friend class Taulell;

    T_ID treuId () { return id;}

    Objecte(); // Constructor
    ~Objecte();

    virtual void assignaForma() = 0;

protected: //per mantenir la integritat de les dades cal que només la classe Taulell pugui accedir a aquests procediments

    bool SomElMateix(Objecte *O) { return (O->id == this->id); } //Funció que retorna cert si els objectes són el mateix.
    bool EmToca(Objecte *O, Punt Desti); // O és l'objecte que volem moure.

    void CanviaColor(int x, int y, int z);
    void assignaId ( T_ID n) { id = n; }

    Punt pos_rel(int index) {return coords[index];} //index ens selecciona el quadrat del qual volem saber les coordenades
    Punt pos_abs() { return posabs;}

    virtual void Mou(Punt Desti);

    int it_primer() { return 0;}
    bool it_valid(int index) { return index < NUM_QUADRES;}
    int it_seg(int index) { return ++index;}

    void RotaEsq() ;
    void RotaDret() ;

    void Pinta();

    int NUM_QUADRES;

    Punt coords[MAX_QUADRES]; //Coordenades relatives.
    Punt posabs; //Posició absoluta dins del món.


    struct T_BoundingBox { //Coordenades relatives.
        Punt pInfEsq;
        Punt pSupDret;

    }BBox;

private:
    //Una forma està formada per quatre quadres, cadascun d'ells amb coordenades x,y relatives ( no sobre del taulell)
    //al pivot de l'objecte

    T_ID id;

    int ActColour;


};





#endif

