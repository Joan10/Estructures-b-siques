#ifndef SHAPE_H
#define SHAPE_H
#define MAX_QUADRES 20
#define MAX_OBJ_X 50
#define MAX_OBJ_Y 50

#include <wx/wx.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>

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

    void CanviaColor(int x, int y, int z);

    void assignaId ( T_ID n) { id = n; }

    int it_primer() { return 0;}
    bool it_valid(int index) { return index < NUM_QUADRES;}
    int it_seg(int index) { return ++index;}

    int Posx(int index) {return coords[index][0];} //index ens selecciona el quadrat del qual volem saber les coordenades
    int Posy(int index) {return coords[index][1];}

    int MinX() const;
    int MaxX() const;
    int MinY() const;
    int MaxY() const;

    void RotaEsq() ;
    void RotaDret() ;

    void Pinta();

protected:
    int NUM_QUADRES;
    int coords[MAX_QUADRES][2];


private:
    //Una forma està formada per quatre quadres, cadascun d'ells amb coordenades x,y relatives ( no sobre del taulell)
    //al pivot de l'objecte

    T_ID id;

    wxColour *ActColour;

};





#endif

