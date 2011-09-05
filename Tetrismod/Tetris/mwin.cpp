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


    Objecte *O1 = new Objecte(4);
    O1->assignaForma(FormaQuadre);

    Objecte *O2 = new Objecte(4);
    O2->assignaForma(FormaL);

    Objecte *O3 = new Objecte(4);
    O3->assignaForma(FormaLinia);

    Objecte *O4 = new Objecte(4);
    O4->assignaForma(FormaT);

    T->Posa(O1, 1, 1);
    T->Posa(O2, 5, 5);

}

