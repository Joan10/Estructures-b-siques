
#include "objecte.h"
using namespace std;
Objecte::Objecte() {

        ActColour = 1; //new wxColour(121, 252, 121);

}

Objecte::~Objecte(){

   // delete ActColour;

}

void Objecte::RotaEsq(){

        int coordX; int coordY;

        for (int i = 0; i<NUM_QUADRES; i++){

            coordX = coords[i].x();
            coordY = coords[i].y();
            this->coords[i].set(coordY,-1*coordX);

        }
}

void Objecte::RotaDret(){

        int coordX; int coordY;

        for (int i = 0; i<NUM_QUADRES; i++){

            coordX = coords[i].x();
            coordY = coords[i].y();
            this->coords[i].set(-1*coordY,coordX);

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
   ActColour = x*y*z;
}




void Objecte::Mou(Punt Desti) {

    this->posabs = Desti;

}


bool Objecte::EmToca(Objecte *O, Punt Desti) //O és l'objecte que volem moure.
{

    T_BoundingBox tempBB = O->BBox;
    tempBB.pInfEsq.set(tempBB.pInfEsq.x()+Desti.x(), tempBB.pInfEsq.y()+Desti.y());
    tempBB.pSupDret.set(tempBB.pSupDret.x()+Desti.x(), tempBB.pSupDret.y()+Desti.y());




}



