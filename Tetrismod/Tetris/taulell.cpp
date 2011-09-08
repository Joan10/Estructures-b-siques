#include "taulell.h"
#define QPIX 20
using namespace std;

Taulell::Taulell (wxFrame *parent, int res_x, int res_y, wxStatusBar *s) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(res_x,res_y), wxBORDER_NONE){

//    m_stsbar = parent->GetStatusBar();


    try {

        if (res_x/QPIX >= MAX_OBJ_X || res_y/QPIX >= MAX_OBJ_Y ) throw 1;

        this->sb = s;

        numObjectes = 0;

        for (int i = 0; i < MAX_OBJ_X; i++) {
            for (int j = 0; j < MAX_OBJ_Y; j++) {
                v_taulell[i][j].actiu = false;
            }
        }

        this->RES_X = res_x;
        this->RES_Y = res_y;

        this->qpix_amplada = QPIX;
        this->qpix_alcada = QPIX;

        this->lastId = 0;
        OAct = NULL;

        Connect(wxEVT_PAINT, wxPaintEventHandler(Taulell::Pinta));
          //Connect(wxEVT_SIZE, wxSizeEventHandler(Taulell::OnSize));
        Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Taulell::enTeclaAvall));
        Connect(wxEVT_MOTION, wxMouseEventHandler(Taulell::OnMove));
    } catch(int e) {
        printf("Resolució incorrecte! \n ");

    }

}

void Taulell::OnMove(wxMouseEvent & event){

    wxPoint p = event.GetPosition();
    this->sb->SetStatusText(wxString::Format(wxT("x: %d, y: %d"), p.x, p.y ));

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

void*
do_loop(void* data)
{
    Objecte *O = ((Objecte*)data);
    printf("id1: %i \n", O->treuId());
    O->activa();

    /* terminate the thread */
    pthread_exit(NULL);
}


void Taulell::Posa(Objecte *O, int x, int y){

    O->assignaId(lastId); //Primer assignam l'identificador per poder reutilitzar el codi de esPotMoure, ja que si l'objecte
                          //no té ID no podem comparar i per tant no entrar al condicional de colisió de esPotMoure.
    pthread_t  p_thread;
    int        thr_id;

    try{
        if (!this->esPotMoure(*O, x, y)) { throw 1; }

        int i = O->it_primer();

        lastId++;
        numObjectes++;

        O->Mou(x,y);
        //Agafam les coordenades de cada quadre i les sumam a les de la posició on volem col·locar l'objecte per a tenir-lo sobre el taulell
        while (O->it_valid(i)) {
            v_taulell[O->Posx(i)][O->Posy(i)].pO = O;
            v_taulell[O->Posx(i)][O->Posy(i)].actiu = true;
            i = O->it_seg(i);
        }
      //  printf("\n");
        printf("id0: %i \n", O->treuId());
        thr_id = pthread_create(&p_thread, NULL, do_loop, (void*)O);

        Refresh();

    }catch (int e) {
        printf("No es pot col·locar a %i %i. \n", x, y);
    }
}

void Taulell::Mou(Objecte *O, int dest_x, int dest_y){

    try{
        if (!this->esPotMoure(*O, dest_x, dest_y)) { throw eCoordIncorrectes; }

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

    }catch (int e) {
        printf("No es pot moure a %i %i. \n", dest_x, dest_y);
    }

}

bool Taulell::esPotMoure (Objecte O, int dest_x, int dest_y){
    int it = O.it_primer();

    int x;
    int y;
    while (O.it_valid(it)) {
        x = O.Posx(it)+dest_x-O.PosActx();
        y = O.Posy(it)+dest_y-O.PosActy();
        if ((x >= numQuadresX() || x<0 || y>=numQuadresY()|| y<0) || (this->v_taulell[x][y].actiu == true &&
                                                                   this->v_taulell[x][y].pO->treuId() !=
                                                                   O.treuId())) return false;
        it = O.it_seg(it);
    }
    return true;
}

Objecte * Taulell::ObjecteA (int x, int y){
    try{

        if( x >= numQuadresX() || y >= numQuadresY() || x<0 || y<0) throw 1;
        if( v_taulell[x][y].actiu == false) throw 1;

        return v_taulell[x][y].pO;

    }catch (int e){
        printf("Coordenades incorrectes! \n");
        return NULL;
    }
}


void Taulell::enTeclaAvall(wxKeyEvent& event)
{

    if (OAct == NULL) OAct = this->ObjecteA(0,0); if (OAct == NULL) return;

    int x = OAct->PosActx();
    int y = OAct->PosActy();

    int keycode = event.GetKeyCode();

    switch (keycode) {
    case WXK_LEFT:
        this->Mou(OAct, x-1, y);
        break;
    case WXK_RIGHT:
        this->Mou(OAct, x+1, y);
        break;
    case WXK_DOWN:
        this->Mou(OAct, x, y+1);
        break;
    case WXK_UP:
        this->Mou(OAct, x, y-1);
        break;
    default:
        event.Skip();
    }




}

