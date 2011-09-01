#ifndef SHAPE_H
#define SHAPE_H

enum T_Formes { FormaBuida, FormaZ, FormaS, FormaLinia, FormaT, FormaQuadre, FormaL, FormaLreves };

class Forma {

public:

    Forma(){ CreaForma (FormaBuida); } // Constructor
    void CreaForma (T_Formes dibuix);
    void CreaFormaAleatoria ();

    T_Formes TreuForma() const { return P_Forma; }
    int x(int index) const { return coords[index][0]; } //index ens selecciona el quadrat del qual volem saber les coordenades
    int y(int index) const { return coords[index][1]; }

    int MinX() const;
    int MaxX() const;
    int MinY() const;
    int MaxY() const;

    Forma RotaEsq() const;
    Forma RotaDret() const;


private:

    T_Formes P_Forma;

    int coords[4][2]; //Una forma està formada per quatre quadres, cadascun d'ells amb coordenades x,y


};

#endif

