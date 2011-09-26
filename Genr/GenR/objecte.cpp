
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

    Punt A,B,C,D = Punt();

    for (this->i = this->BBox.begin(); this->i != this->BBox.end(); ++this->i)
    { //Per tots els quadres de l'objecte que no es mou
        C = *this->i;
        D = this->pos_abs();
        B = C+D;
        for (O->i = O->BBox.begin(); O->i != O->BBox.end(); ++O->i)
        {//Per tots els quadres de l'objecte que volem moure

            A.set(O->i->x()+Desti.x(),O->i->y()+Desti.y());
            //Calculam la posició de la component de la bounding box en cas que s'arribés a moure

            if (B == A) return true; //Comprovam si els punts coincideixen.

        }

    }

    return false;



}



