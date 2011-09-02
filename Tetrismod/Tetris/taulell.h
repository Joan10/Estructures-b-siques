
#ifndef BOARD_H
#define BOARD_H

#include "objecte.h"
#include <wx/wx.h>

class Taulell : public wxPanel
{

public:
    Taulell(wxFrame *parent); //Frame on es dibuixarà el Taulell

    void TaulellBuit();
    void Posa(Objecte O, int x, int y);
    void Mou(Objecte O, int dest_x, int dest_y);
    Objecte ObjecteA (int x, int y);

private:
    enum {amplada = 10, alcada = 22};

    int numObjectes;

    //Un taulell és un vector de x*y posicions(lineal)
    Objecte *taulell[amplada][alcada];

};

#endif
