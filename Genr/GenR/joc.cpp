
#include "joc.h"
#include "utils.h"
#include "behaviors.h"
#include "interaccions.h"
#include <stdio.h>



using namespace std;

Joc::Joc(int res_x, int res_y)
       //: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(res_x, res_y),
         //        wxDEFAULT_FRAME_STYLE & ~ (wxRESIZE_BORDER | wxRESIZE_BOX | wxMAXIMIZE_BOX))
{



    //wxSize S = sb->GetClientSize();

    Taulell *T = new Taulell(40, 40);

    T->TaulellBuit();

    Objecte *O1 = new Objecte1();
    Objecte *O2 = new Objecte1();

    Punt P = Punt(10,10);
    T->Posa(O1, Punt(10,10));
    T->Posa(O2, Punt(15,10));

    Rutina *R1 = new Rutina(T);
    R1->CreaInteraccio(O1,O2, Interaccio_01);

    Camara *C1 = new Camara(10,10,T);
    T->Posa(C1, Punt(6,6));

    Camara *C2 = new Camara(25,25,T);
    T->Posa(C2, Punt(20,20));

    Ctrl_Objecte *CO1 = new Ctrl_Objecte(T);
    CO1->AfegeixObjecte(O1);
    Ctrl_Objecte *CCam = new Ctrl_Objecte(T);
    CCam->AfegeixObjecte(C1);
    CCam->AfegeixObjecte(C2);

    allegro_init();
    install_keyboard();
    set_color_depth(16);
    set_gfx_mode( GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

    while( !key[KEY_ESC]){
        clear_keybuf();
        CCam->Controla();
        if (T->haCanviat()) {
            C1->Pinta(); C2->Pinta();

        }
    }

    //R1->EliminaInteraccio(O1, O2);

}
END_OF_MAIN();



