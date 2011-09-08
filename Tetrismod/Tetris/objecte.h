#ifndef SHAPE_H
#define SHAPE_H
#include <wx/wx.h>
#define MAX_QUADRES 20
#include <vector>
using namespace std;

enum T_Formes { FormaBuida, FormaZ, FormaS, FormaLinia, FormaT, FormaQuadre, FormaL, FormaLreves };

class Objecte {

public:

    Objecte(vector<int> data); // Constructor
    void assignaForma (T_Formes dibuix);
    void assignaFormaAleatoria ();

    void CanviaColor(int x, int y, int z);

    friend class Taulell;

    int treuId () { return id;}


protected: //per mantenir la integritat de les dades cal que només la classe Taulell pugui accedir a aquests procediments

    void assignaId ( int n) { id = n; }


    T_Formes TreuForma() const { return P_Forma; }

    int it_primer() { return 0;}
    bool it_valid(int index) { return index < NUM_QUADRES;}
    int it_seg(int index) { return ++index;}

    int Posx(int index) {return coords[index][0] + posAct[0];} //index ens selecciona el quadrat del qual volem saber les coordenades
    int Posy(int index) {return coords[index][1] + posAct[1];}

    int PosActx() { return posAct[0];}
    int PosActy() { return posAct[1];}

    int MinX() const;
    int MaxX() const;
    int MinY() const;
    int MaxY() const;

    void RotaEsq() ;
    void RotaDret() ;

    void Pinta(wxPaintDC &dc, int mida_quadre);


private:

    void Mou(int x, int y);

    int NUM_QUADRES;
    int MIDA_QUADRES;

    T_Formes P_Forma;

    int coords[MAX_QUADRES][2]; //Una forma està formada per quatre quadres, cadascun d'ells amb coordenades x,y
    int posAct[2];

    int id;

    wxColour *ActColour;

};

#endif

