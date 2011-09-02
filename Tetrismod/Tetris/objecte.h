#ifndef SHAPE_H
#define SHAPE_H

enum T_Formes { FormaBuida, FormaZ, FormaS, FormaLinia, FormaT, FormaQuadre, FormaL, FormaLreves };

class Objecte {

public:

    Objecte(){ assignaForma (FormaBuida); } // Constructor
    void assignaForma (T_Formes dibuix);
    void assignaFormaAleatoria ();

    T_Formes TreuForma() const { return P_Forma; }
    int x(int index) const { return coords[index][0]; } //index ens selecciona el quadrat del qual volem saber les coordenades
    int y(int index) const { return coords[index][1]; }

    int MinX() const;
    int MaxX() const;
    int MinY() const;
    int MaxY() const;

    void RotaEsq() ;
    void RotaDret() ;

    void Mou(int x, int y);

    bool esA(int x, int y);

private:

    T_Formes P_Forma;

    int coords[4][2]; //Una forma està formada per quatre quadres, cadascun d'ells amb coordenades x,y
    int posAct[2];

};

#endif

