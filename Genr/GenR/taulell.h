
#ifndef TAULELL_H
#define TAULELL_H

#define MAX_OBJ_X 50
#define MAX_OBJ_Y 50

#define QPIX 20

#include <stdio.h>

#include "objecte.h"
#include <pthread.h>     /* pthread functions and data structures */
#include <typeinfo>
#include <math.h>


enum sentit{dreta, esquerra};

class Taulell
{

public:
    Taulell(int cas_x, int cas_y); //Frame on es dibuixarà el Taulell
    ~Taulell();
    void TaulellBuit();

    void Posa(Objecte *O, Punt Desti); //col·loca
    void Mou(Objecte *O, Punt Desti);  //Mou l'objecte
    void Mou(Punt Origen, Punt Desti); //Mou l'objecte al punt origen al punt destí
    void Rota(Objecte *O, sentit s);

    void CanviaColor(Objecte *O, int R, int G, int B);

    bool ExisteixObjecte(Punt P); //Retorna vertader si existeix l'objecte

    Objecte * ObjecteA (Punt P); //Retorna un punter de l'objecte a tal posició.

    Punt Posicio(Objecte *O) { return O->pos_abs(); } //posició actual de l'objecte

    int numQuadresX() {return CAS_X;}
    int numQuadresY() {return CAS_Y;}

    float Distancia(Objecte *O1,Objecte *O2);

    void Pinta();
    void Pinta(Punt infesq, Punt infdret );

    bool haCanviat(){ if (v_upd == true ) {v_upd = false; return true;}else{return false;}}
private:

    int CAS_X;
    int CAS_Y;

    int numObjectes;

    struct nTaulell {
        Objecte *pO;
        bool actiu;
    };



    /********************
    / Estructura de dades
    *********************/
    T_ID lastId; //Darrer identificador entrat

    Objecte *OAct; //Objecte actual seleccionat.
    T_ID IdAct; // Identificador de l'objecte actual

    //Un taulell és un vector de x*y posicions(lineal)
    nTaulell v_taulell[MAX_OBJ_X][MAX_OBJ_Y]; //Taulell, matriu.

    void PosaEf(Objecte *O, Punt P);
    void MouEf(Objecte *O, Punt Desti);

    bool esPotMoure (Objecte *O,  Punt Desti);
    bool PotGirar (Objecte *O, sentit s);

    enum exceptions{CoordIncorrecte, CoordBuida, ResolucioNoValida, Invalid};
    bool v_upd;

};

#endif
