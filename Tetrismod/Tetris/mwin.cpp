#include "mwin.h"
#include "utils.h"
#include "behaviors.h"
#include "interaccions.h"

using namespace std;

Mwin::Mwin(const wxString& title, int res_x, int res_y)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(res_x, res_y),
                 wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER | wxRESIZE_BOX | wxMAXIMIZE_BOX))
{


    wxStatusBar *sb = CreateStatusBar();


    wxSize S = sb->GetClientSize();

    //Taulell *T = new Taulell(this, res_x, res_y-S.GetHeight()-10, sb);
    Taulell *T = new Taulell(20, 20, sb);

    T->TaulellBuit();

    Objecte *O1 = new Objecte1();
    Objecte *O2 = new Objecte1();

    Objecte *Cam1 = new Camara(this, 5, 5, T);

    T->Posa(10,10, O1);
    T->Posa(15,10, O2);


    Rutina *R1 = new Rutina(T);
    R1->CreaInteraccio(O1,O2, Interaccio_01);
  //  R1->EliminaInteraccio(1,2);

}




