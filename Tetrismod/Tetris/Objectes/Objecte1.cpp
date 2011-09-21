#include "Objecte1.h"

Objecte1::Objecte1() : Objecte() {
    this->NUM_QUADRES = 4;
    this->assignaForma();
}

void Objecte1::assignaForma(){

    static const int coordsTaula[4][2] =
        { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } };

    for (int i = 0; i<NUM_QUADRES; i++) {
        for (int j = 0; j<2; j++){
            this->coords[i][j] = coordsTaula[i][j];

        }
    }

}
