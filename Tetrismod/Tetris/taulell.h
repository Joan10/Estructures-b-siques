
#ifndef BOARD_H
#define BOARD_H

#define MAX_OBJ_X 50
#define MAX_OBJ_Y 50

#define QPIX 20

#include <wx/wx.h>
#include <stdio.h>

#include "objecte.h"
#include <pthread.h>     /* pthread functions and data structures */
#include <typeinfo>

enum sentit{dreta, esquerra};

class Taulell
{

public:
    Taulell(int cas_x, int cas_y, wxStatusBar *s); //Frame on es dibuixarà el Taulell
    ~Taulell();
    void TaulellBuit();

    void Posa(int x, int y, Objecte *O); //Genera un element, el col·loca i retorna una ID.
    void Mou(Objecte *O, int dest_x, int dest_y);  //Mou l'objecte en funció de la ID
    void Mou(int x, int y, int dest_x, int dest_y);
    void Rota(Objecte *O, sentit s);

    void CanviaColor(Objecte *O, int R, int G, int B);

    bool ExisteixObjecte(int x, int y); //Retorna vertader si existeix l'objecte

    Objecte * ObjecteA (int x, int y); //Retorna la ID de l'objecte a tal posició.

    int posX(Objecte *O) { return TaulaEq[0][(O->treuId()-1)]; }
    int posY(Objecte *O){ return TaulaEq[1][(O->treuId()-1)]; }

    int numQuadresX() {return CAS_X;}
    int numQuadresY() {return CAS_Y;}

    float Distancia(Objecte *O1,Objecte *O2);

    void Pinta();
    void Pinta(int x_infesq, int y_infesq, int x_supdret, int y_supdret );

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
    int TaulaEq[2][MAX_OBJ_X*MAX_OBJ_Y]; //Taula indexada per la identificació (desgraciadament s'ha de convertir a int...)
                                         // que donada una ID ens treu la posició de l'objecte al qual pertany la ID.


    void PosaEf(Objecte *O, int x, int y);
    void MouEf(Objecte *O, int dest_x, int dest_y);

    bool esPotMoure (Objecte *O, int dest_x, int dest_y);
    bool PotGirar (Objecte *O, int posActX, int posActY, sentit s);





    wxStatusBar *sb;

    enum exceptions{CoordIncorrecte, CoordBuida, ResolucioNoValida, Invalid};


};

#endif
