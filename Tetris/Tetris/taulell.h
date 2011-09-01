
#ifndef BOARD_H
#define BOARD_H

#include "forma.h"
#include <wx/wx.h>

class Taulell : public wxPanel
{

public:
    Taulell(wxFrame *parent); //Frame on es dibuixarà el Taulell
    void Inicia();
    void Pausa();
    void LiniesEliminadesCanvia(int numLinies);

protected:
    void enPintar (wxPaintEvent& event);
    void enTeclaAvall (wxKeyEvent& event);
    void enTimer (wxCommandEvent& event);

private:
    enum {BoardWidth = 10, BoardHeight = 22};
    T_Formes& FormaA (int x, int y) { return taulell[(y*BoardWidth)+x]; }

    int QuadratWidth() { return GetClientSize().GetWidth() / BoardWidth; }
    int QuadratHeight() { return GetClientSize().GetHeight() / BoardHeight; }

    void NetejaTaulell();
    void LlancaAvall();
    void LiniaAbaix();
    void FitxaJaEsAbaix();
    void EliminaLiniesCompletes();
    void NovaFitxa();
    bool ProvaMoure(const Forma& newPiece, int newX, int newY);
    void PintaQuadre(wxPaintDC &dc, int x, int y, T_Formes shape);

    wxTimer *timer;
    bool isIniciat;
    bool isAturat;
    bool isAcabatdeCaure;
    Forma FitxaActual;
    int actX;
    int actY;
    int LiniesEliminades;

    //Un taulell és un vector de x*y posicions(lineal)
    T_Formes taulell[BoardWidth * BoardHeight];
    wxStatusBar *m_stsbar;

};

#endif
