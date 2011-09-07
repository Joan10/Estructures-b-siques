#include <stdlib.h>
#include <algorithm>
#include "objecte.h"

using namespace std;

Objecte::Objecte(vector<int> data) {

    try {

        int tam = data.size();

        if (tam % 2 == 1) throw 1;

        assignaForma (FormaBuida);

        int i = 0; //Conmuta entre coordenada x i coordenada y
        int j = 0; //Conmuta entre quadradets

        for (int d = 0; d<tam; d++){

            //printf("%i %i  %i \n", i, j, d);
            this->coords[j][i] = data.at(d);

            if (i == 1) j++;
            i = (i+1) % 2;

        }

        NUM_QUADRES = tam/2;

        this->posAct[0] = 0; this->posAct[1] = 0;


    }catch (int e){

        printf("Número de coordenades incorrecte \n");

    }
}

void Objecte::assignaForma(T_Formes dibuix) {

    static const int coordsTaula[8][4][2] = {
        { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
        { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
        { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
        { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
        { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
        { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
        { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
        { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }
    };

    for (int i = 0; i<4; i++) {
        for (int j = 0; j<2; j++){

            this->coords[i][j] = coordsTaula[dibuix][i][j];

        }
    }

    this->P_Forma = dibuix;
    this->posAct[0] = 0; this->posAct[1] = 0;
}

void Objecte::assignaFormaAleatoria() {

    int x = rand() % 7 + 1;
    this->assignaForma(T_Formes(x));

}

int Objecte::MaxX() const {

    int m = coords[0][0];
    for (int i = 1; i<NUM_QUADRES; i++) {
        if (m<coords[i][0]) m = coords[i][0];

    }
    return m;

}

int Objecte::MinX() const {

    int m = coords[0][0];
    for (int i = 1; i<NUM_QUADRES; i++) {
        if (m>coords[i][0]) m = coords[i][0];

    }
    return m;

}

int Objecte::MaxY() const {

    int m = coords[0][0];
    for (int i = 1; i<NUM_QUADRES; i++) {
        if (m<coords[i][1]) m = coords[i][1];

    }
    return m;

}

int Objecte::MinY() const {

    int m = coords[0][0];
    for (int i = 1; i<NUM_QUADRES; i++) {
        if (m>coords[i][1]) m = coords[i][1];

    }
    return m;

}

void Objecte::RotaEsq(){

    if (!this->P_Forma == FormaQuadre) {

        for (int i = 0; i<NUM_QUADRES; i++){
            this->coords[i][0] = this->coords[i][1];
            this->coords[i][1] = -1*this->coords[i][0];
        }
    }
}

void Objecte::RotaDret(){

    if (!this->P_Forma == FormaQuadre) {

        for (int i = 0; i<NUM_QUADRES; i++){
            this->coords[i][0] = -1*this->coords[i][1];
            this->coords[i][1] = this->coords[i][0];

        }
    }
}

void Objecte::Mou(int x, int y){

    this->posAct[0] = x; this->posAct[1] = y;

}

void Objecte::Pinta(wxPaintDC &dc, int mida_quadre) {

    int x; int y;

    wxPen pen( wxColour(0, 0, 0));
    pen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(pen);
    dc.SetBrush(wxColour(121, 252, 121));

    for (int i = 0; i<NUM_QUADRES; i++){
        x = (this->coords[i][0]+this->posAct[0])*mida_quadre;
        y = (this->coords[i][1]+this->posAct[1])*mida_quadre;

        dc.DrawRectangle(x+1, y+1, mida_quadre-1, mida_quadre-1);

    }


}
