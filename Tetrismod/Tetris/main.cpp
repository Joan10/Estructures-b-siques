#include "objecte.h"
#include "taulell.h"
#include "mwin.h"
#include "main.h"

#include <wx/wx.h>
#include <iostream>
#include <stdio.h>


#define RES_X 480
#define RES_Y 480
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{

    Mwin *Joc = new Mwin(wxT("Joc"), RES_X, RES_Y);
    Joc->Centre();
    Joc->Show(true);

    return true;

//    Objecte O1(4); Objecte O2(4);
//    O1.assignaForma(FormaL); O2.assignaForma(FormaQuadre);
//    int i = O1.it_primer();
//
//    if (T.esPotMoure(O1, 5, 5)) {
//        T.Posa(&O1, 5, 5);
//
//        printf("O1 \n");
//        while (O1.it_valid(i)) {
//            printf("%i %i \n", O1.Posx(i), O1.Posy(i));
//            i = O1.it_seg(i);
//        }
//
//    }else{
//        printf("res");
//    }
//
//    if (!T.esPotMoure(O2, 8, 8)) printf("no es pot moure");


}
