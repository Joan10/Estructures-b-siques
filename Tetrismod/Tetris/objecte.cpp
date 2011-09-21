
#include "objecte.h"
using namespace std;
Objecte::Objecte() {

        ActColour = new wxColour(121, 252, 121);

}

Objecte::~Objecte(){

    delete ActColour;

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

        int coordX; int coordY;

        for (int i = 0; i<NUM_QUADRES; i++){

            coordX = coords[i][0];
            coordY = coords[i][1];

            this->coords[i][0] = coordY;
            this->coords[i][1] = -1*coordX;

        }
}

void Objecte::RotaDret(){

        int coordX; int coordY;

        for (int i = 0; i<NUM_QUADRES; i++){

            coordX = coords[i][0];
            coordY = coords[i][1];

            this->coords[i][0] = -1*coordY;
            this->coords[i][1] = coordX;

        }

}


void Objecte::Pinta(){//(wxPaintDC &dc, int mida_quadre, int PosActX, int PosActY) {

//    int x; int y;
//
//    wxPen pen( wxColour(0, 0, 0));
//    pen.SetCap(wxCAP_PROJECTING);
//    dc.SetPen(pen);
//    dc.SetBrush(*ActColour);
//        x = (PosActX)*mida_quadre;
//        y = (PosActY)*mida_quadre;
//        dc.DrawRectangle(x+1, y+1, mida_quadre-1, mida_quadre-1);

printf("1 ");

}

void Objecte::CanviaColor(int x, int y, int z) {
   ActColour->Set(x,y,z);
}




