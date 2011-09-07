#include "mwin.h"
#include "taulell.h"
#include "objecte.h"
#include <vector>
#include <iostream>


using namespace std;

Mwin::Mwin(const wxString& title, int res_x, int res_y)
       : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(res_x, res_y),
                 wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER | wxRESIZE_BOX | wxMAXIMIZE_BOX))
{


    wxStatusBar *sb = CreateStatusBar();


    wxSize S = sb->GetClientSize();

    //Taulell *T = new Taulell(this, res_x, res_y-S.GetHeight()-10, sb);
    Taulell *T = new Taulell(this, res_x, res_y-S.GetHeight()-10, sb);


    T->SetFocus();
    T->TaulellBuit();

    vector<int> v1;
    v1.push_back(-1); v1.push_back(-1); v1.push_back(0); v1.push_back(0);

    vector<int> v2;
    v2.push_back(0);
    v2.push_back(0);
    v2.push_back(0);
    v2.push_back(1);
    v2.push_back(1);
    v2.push_back(1);
    v2.push_back(-1);
    v2.push_back(0);
    v2.push_back(-2);
    v2.push_back(0);

    Objecte *O1 = new Objecte(v1);
//
    Objecte *O2 = new Objecte(v2);
//    O2->assignaForma(FormaL);
//
//    Objecte *O3 = new Objecte(4,3,2,5,-1);
//    O3->assignaForma(FormaLinia);
//
//    Objecte *O4 = new Objecte(4,3,2,5,-1);
//    O4->assignaForma(FormaT);

    T->Posa(O1, 1, 1);
    T->Posa(O2, 6, 6);
    //T->Posa(O2, 5, 5);
}

