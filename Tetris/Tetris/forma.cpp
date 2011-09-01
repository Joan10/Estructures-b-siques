#include <stdlib.h>
#include <algorithm>
#include "forma.h"

using namespace std;

void Forma::CreaForma(T_Formes dibuix) {

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

}

void Forma::CreaFormaAleatoria() {

    int x = rand() % 7 + 1;
    this->CreaForma(T_Formes(x));

}

int Forma::MaxX() const {

    int m = coords[0][0];
    for (int i = 1; i<4; i++) {
        if (m>coords[i][0]) m = coords[i][0];

    }
    return m;

}

int Forma::MinX() const {

    int m = coords[0][0];
    for (int i = 1; i<4; i++) {
        if (m<coords[i][0]) m = coords[i][0];

    }
    return m;

}

int Forma::MaxY() const {

    int m = coords[0][0];
    for (int i = 1; i<4; i++) {
        if (m>coords[i][1]) m = coords[i][1];

    }
    return m;

}

int Forma::MinY() const {

    int m = coords[0][0];
    for (int i = 1; i<4; i++) {
        if (m<coords[i][1]) m = coords[i][1];

    }
    return m;

}

Forma Forma::RotaEsq() const {

    if (this->P_Forma == FormaQuadre) return *this;

    Forma f_resultat;

    f_resultat.P_Forma = this->P_Forma;

    for (int i = 0; i<4; i++){
        f_resultat.coords[i][0] = this->y(i);
        f_resultat.coords[i][1] = -1*this->x(i);

    }
    return f_resultat;
}

Forma Forma::RotaDret() const {

    if (this->P_Forma == FormaQuadre) return *this;

    Forma f_resultat;

    f_resultat.P_Forma = this->P_Forma;

    for (int i = 0; i<4; i++){
        f_resultat.coords[i][0] = -1*this->y(i);
        f_resultat.coords[i][1] = this->x(i);

    }
    return f_resultat;
}

