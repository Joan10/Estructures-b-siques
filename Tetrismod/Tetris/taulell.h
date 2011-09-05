
#ifndef BOARD_H
#define BOARD_H

#define MAX_OBJ_X 50
#define MAX_OBJ_Y 50

#include "objecte.h"
#include <wx/wx.h>
#include <stdio.h>

class Taulell : public wxPanel
{

public:
    Taulell(wxFrame *parent, int qpix, int res_x, int res_y); //Frame on es dibuixarà el Taulell

    void TaulellBuit();
    void Posa(Objecte *O, int x, int y);
    void Mou(Objecte *O, int dest_x, int dest_y);

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

    //Un taulell és un vector de x*y posicions(lineal)
    nTaulell v_taulell[MAX_OBJ_X][MAX_OBJ_Y];

    void Pinta(wxPaintEvent& event);
    void enTeclaAvall(wxKeyEvent& event);
    void PintaFons(wxPaintDC& dc, int nx, int ny);

    int numQuadresX() {return RES_X / qpix_amplada;}
    int numQuadresY() {return RES_Y / qpix_alcada;}

};

#endif
