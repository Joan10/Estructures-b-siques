#include "taulell.h"

Taulell::Taulell (wxFrame *parent, int qpix, int res_x, int res_y, wxStatusBar *s) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(res_x,res_y), wxBORDER_NONE){

//    m_stsbar = parent->GetStatusBar();

try {

    if (res_x/qpix >= MAX_OBJ_X || res_y/qpix >= MAX_OBJ_Y ) throw 1;

    this->sb = s;

    numObjectes = 0;

    for (int i = 0; i < MAX_OBJ_X; i++) {
        for (int j = 0; j < MAX_OBJ_Y; j++) {
            v_taulell[i][j].actiu = false;
        }
    }

    this->RES_X = res_x;
    this->RES_Y = res_y;

    this->qpix_amplada = qpix;
    this->qpix_alcada = qpix;

    this->lastId = 0;

    Connect(wxEVT_PAINT, wxPaintEventHandler(Taulell::Pinta));
      //Connect(wxEVT_SIZE, wxSizeEventHandler(Taulell::OnSize));
    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Taulell::enTeclaAvall));
    Connect(wxEVT_MOVE, wxMoveEventHandler(Taulell::EnMoure));
} catch(int e) {
    printf("Resolució incorrecte! \n ");

}

}

void Taulell::EnMoure(wxEVT_MOVE, wxMoveEventHandler(Move::OnMove)){


this->sb->SetStatusText(wxT("0"));

}

int Taulell::QuadreX(int pix_x) {
    return pix_x / this->qpix_amplada;
}

int Taulell::QuadreY(int pix_y) {
    return pix_y / this->qpix_alcada;
}

void Taulell::PintaFons(wxPaintDC &dc, int nx, int ny) {

    wxSize size = GetClientSize();

    for (int i = 0; i<= ny; i++) {
        dc.DrawLine(0, i*this->qpix_alcada,  nx*qpix_alcada, i*this->qpix_alcada);
    }
    for (int i = 0; i<= nx; i++) {
        dc.DrawLine(i*this->qpix_amplada, 0 , i*this->qpix_amplada, ny*qpix_alcada);
    }

}

void Taulell::Pinta(wxPaintEvent& event) {

    wxPaintDC dc(this);

    wxPen pen(wxColour(0, 0, 0));
    pen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(pen);

    PintaFons(dc, numQuadresX(), numQuadresY() );

    for (int i = 0; i < numQuadresX(); i++) {
        for (int j = 0; j < numQuadresY(); j++) {
            if (v_taulell[i][j].actiu == true ) {
                v_taulell[i][j].pO->Pinta(dc, qpix_alcada);

            }

        }
    }


}



void Taulell::TaulellBuit(){


    numObjectes = 0;
    for (int i = 0; i < MAX_OBJ_X; i++) {
        for (int j = 0; j < MAX_OBJ_Y; j++) {
            v_taulell[i][j].actiu = false;
        }
    }
}


void Taulell::Posa(Objecte *O, int x, int y){

    O->assignaId(lastId); //Primer assignam l'identificador per poder reutilitzar el codi de esPotMoure, ja que si l'objecte
                          //no té ID no podem comparar i per tant no entrar al condicional de colisió de esPotMoure.

    if (!this->esPotMoure(*O, x, y)) { printf("No es pot col·locar"); return; }

    int i = O->it_primer();

    lastId++;
    numObjectes++;

    O->Mou(x,y);
   //printf("  %i %i    |", O->PosActx(),O->PosActy());
    //Agafam les coordenades de cada quadre i les sumam a les de la posició on volem col·locar l'objecte per a tenir-lo sobre el taulell
    while (O->it_valid(i)) {
        v_taulell[O->Posx(i)][O->Posy(i)].pO = O;
        v_taulell[O->Posx(i)][O->Posy(i)].actiu = true;
      //  printf("  %i %i    |", O->Posx(i),O->Posy(i));
        i = O->it_seg(i);
    }
  //  printf("\n");
    Refresh();
}

void Taulell::Mou(Objecte *O, int dest_x, int dest_y){

    if (!this->esPotMoure(*O, dest_x, dest_y)) { printf("%i No es pot moure \n", numQuadresY() ); return; }

    int i = O->it_primer();

    while (O->it_valid(i)) {
        v_taulell[O->Posx(i)][O->Posy(i)].actiu = false;
        i = O->it_seg(i);
    }

    O->Mou(dest_x,dest_y);

    i = O->it_primer();

    while (O->it_valid(i)) {
        v_taulell[O->Posx(i)][O->Posy(i)].pO = O;
        v_taulell[O->Posx(i)][O->Posy(i)].actiu = true;
        i = O->it_seg(i);
    }

    Refresh();
}

bool Taulell::esPotMoure (Objecte O, int dest_x, int dest_y){
    int it = O.it_primer();

    int x;
    int y;
    while (O.it_valid(it)) {
        x = O.Posx(it)+dest_x-O.PosActx();
        y = O.Posy(it)+dest_y-O.PosActy();
        printf("@@ %i %i %i @@@ %i", x,y, O.treuId(), it);
        if (this->v_taulell[x][y].actiu == true) printf("cert");
        printf("\n");
        if ((x >= numQuadresX() || x<0 || y>=numQuadresY()|| y<0) || (this->v_taulell[x][y].actiu == true &&
                                                                   this->v_taulell[x][y].pO->treuId() !=
                                                                   O.treuId())) return false;
        it = O.it_seg(it);
    }
    return true;
}

Objecte * Taulell::ObjecteA (int x, int y){
    return v_taulell[x][y].pO;
}


void Taulell::enTeclaAvall(wxKeyEvent& event)
{

    Objecte *O = this->ObjecteA(1,1);

    int x = O->PosActx();
    int y = O->PosActy();

    int keycode = event.GetKeyCode();

    switch (keycode) {
    case WXK_LEFT:
        this->Mou(O, x-1, y);
        break;
    case WXK_RIGHT:
        this->Mou(O, x+1, y);
        break;
    case WXK_DOWN:
        this->Mou(O, x, y+1);
        break;
    case WXK_UP:
        this->Mou(O, x, y-1);
        break;
    default:
        event.Skip();
    }




}

