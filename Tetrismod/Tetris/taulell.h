
#ifndef BOARD_H
#define BOARD_H

#define MAX_OBJ_X 50
#define MAX_OBJ_Y 50

#include "objecte.h"
#include <wx/wx.h>
#include <stdio.h>

#include <pthread.h>     /* pthread functions and data structures */



class Taulell : public wxPanel
{

public:
    Taulell(wxFrame *parent, int res_x, int res_y, wxStatusBar *s); //Frame on es dibuixarà el Taulell

    void TaulellBuit();
    void Posa(Objecte *O, int x, int y);
    void Mou(Objecte *O, int dest_x, int dest_y);

    int QuadreX(int pix_x); //retorna el quadre corresponent als píxels entrats.
    int QuadreY(int pix_y); //retorna el quadre corresponent als píxels entrats.

    bool esPotMoure (Objecte O, int dest_x, int dest_y);

    Objecte * ObjecteA (int x, int y);



private:

    int RES_X;
    int RES_Y;

    int qpix_amplada;
    int qpix_alcada;

    int numObjectes;

    struct nTaulell {
        Objecte *pO;
        bool actiu;
    };

    int lastId;

    Objecte *OAct;
    //Un taulell és un vector de x*y posicions(lineal)
    nTaulell v_taulell[MAX_OBJ_X][MAX_OBJ_Y];

    void Pinta(wxPaintEvent& event);
    void enTeclaAvall(wxKeyEvent& event);
    void PintaFons(wxPaintDC& dc, int nx, int ny);
    void OnMove(wxMouseEvent & event);

    int numQuadresX() {return RES_X / qpix_amplada;}
    int numQuadresY() {return RES_Y / qpix_alcada;}

    wxStatusBar *sb;

    static const int eCoordIncorrectes = 0;
    static const int eCoordIncorrecte = 1;
};

    struct dTaulellObjecte {
        Objecte *pO;
        Taulell *pT;
    };


#endif
