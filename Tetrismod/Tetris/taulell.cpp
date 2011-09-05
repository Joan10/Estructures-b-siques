#include "taulell.h"

Taulell::Taulell (wxFrame *parent, int qpix, int res_x, int res_y) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE){

//    m_stsbar = parent->GetStatusBar();

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
   // Connect(wxEVT_TIMER, wxCommandEventHandler(Taulell::enTimer));


}

void Taulell::Pinta(wxPaintEvent& event) {

    wxPaintDC dc(this);
  // wxPaintDC dc2(this);

    wxPen pen(wxColour(0, 0, 0));
    pen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(pen);

    wxSize size = GetClientSize();

   // dc.DrawLine(0, 0, 20, 20);

    for (int i = 0; i<= this->numQuadresY(); i++) {
        dc.DrawLine(0, i*this->qpix_alcada, size.GetWidth(), i*this->qpix_alcada);
    }
    for (int i = 0; i<= this->numQuadresX(); i++) {
        dc.DrawLine(i*this->qpix_amplada, 0 , i*this->qpix_amplada,size.GetHeight());
    }



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

    if (!this->esPotMoure(*O, x, y)) { printf("No es pot moure"); return; }

    int i = O->it_primer();

    O->assignaId(lastId); lastId++;
    numObjectes++;

    O->Mou(x,y);

    //Agafam les coordenades de cada quadre i les sumam a les de la posició on volem col·locar l'objecte per a tenir-lo sobre el taulell
    while (O->it_valid(i)) {
        v_taulell[O->Posx(i)][O->Posy(i)].pO = O;
        v_taulell[O->Posx(i)][O->Posy(i)].actiu = true;

        i = O->it_seg(i);
    }
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
        printf("%i %i \n", x, y);
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

