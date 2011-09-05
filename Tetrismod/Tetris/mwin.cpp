#include "mwin.h"
#include "taulell.h"
#include "objecte.h"

Mwin::Mwin(const wxString& title, int res_x, int res_y)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(res_x, res_y),
                 wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER | wxRESIZE_BOX | wxMAXIMIZE_BOX))
{

    Taulell *T = new Taulell(this, 20, res_x, res_y);
    T->SetFocus();
    T->TaulellBuit();


    Objecte *O1 = new Objecte(-1,-1,0,0,-666);
//
    Objecte *O2 = new Objecte(4,4,5,5,6,6,7,7, 8, 8, -666);
//    O2->assignaForma(FormaL);
//
//    Objecte *O3 = new Objecte(4,3,2,5,-1);
//    O3->assignaForma(FormaLinia);
//
//    Objecte *O4 = new Objecte(4,3,2,5,-1);
//    O4->assignaForma(FormaT);

    T->Posa(O1, 1, 1);
    T->Posa(O2, 0, 0);
    //T->Posa(O2, 5, 5);

}

