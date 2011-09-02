#include "taulell.h"

Taulell::Taulell(wxFrame *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition,
             wxDefaultSize, wxBORDER_NONE) {


//    m_stsbar = parent->GetStatusBar();


    numObjectes = 0;

   // Connect(wxEVT_PAINT, wxPaintEventHandler(Taulell::enPintar));
   // Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Taulell::enTeclaAvall));
   // Connect(wxEVT_TIMER, wxCommandEventHandler(Taulell::enTimer));


}

void Taulell::TaulellBuit(){

    numObjectes = 0;

    for (int i = 0; i < alcada; ++i) {
        for (int j = 0; j < amplada; ++j) {
            taulell[i][j] = 0;
        }
    }
}


void Taulell::Posa(Objecte O, int x, int y){

    int posx; int posy;
    numObjectes++;

    //Agafam les coordenades de cada quadre i les sumam a les de la posició on volem col·locar l'objecte per a tenir-lo sobre el taulell
    for (int i = 0; i < 4; i++) {
        posx = x + O.x(i);
        posy = y + O.y(i);
        taulell[posx][posy] = &O;
    }




}

void Taulell::Mou(Objecte O, int dest_x, int dest_y);

    O.Mou(dest_x,dest_y);

    int posx; int posy;
    numObjectes++;

    //Agafam les coordenades de cada quadre i les sumam a les de la posició on volem col·locar l'objecte per a tenir-lo sobre el taulell
    for (int i = 0; i < 4; i++) {
        posx = x + O.x(i);
        posy = y + O.y(i);
        taulell[posx][posy] = &O;
    }
}
