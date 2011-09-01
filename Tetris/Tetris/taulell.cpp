#include "taulell.h"

Taulell::Taulell(wxFrame *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition,
             wxDefaultSize, wxBORDER_NONE) {


    timer = new wxTimer(this,1);
    m_stsbar = parent->GetStatusBar();
    this->isAcabatdeCaure = false;
    this->isAturat = false;
    this->isAturat = false;
    this->isIniciat= false;
    this->LiniesEliminades = 0;
    this->actX = 0;
    this->actY = 0;

    this->NetejaTaulell();

    Connect(wxEVT_PAINT, wxPaintEventHandler(Taulell::enPintar));
    Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(Taulell::enTeclaAvall));
    Connect(wxEVT_TIMER, wxCommandEventHandler(Taulell::enTimer));


}

void Taulell::Inicia()
{
    if (this->isAturat) return;

    this->isIniciat = true; this->isAcabatdeCaure = false;
    this->LiniesEliminades = 0;
    this->NetejaTaulell();

    this->NovaFitxa();
    timer->Start(300);

}


void Taulell::Pausa()
{
    if (!this->isAturat) return;

    this->isAturat = !this->isAturat;

    if (isAturat) { timer->Stop(); m_stsbar->SetStatusText(wxT("paused"));}
    else
    {
        timer->Start(300);
        wxString str;
        str.Printf(wxT("%d"), LiniesEliminades);
        m_stsbar->SetStatusText(str);
    }
    Refresh();

}

void Taulell::enPintar(wxPaintEvent& event) {

    wxPaintDC dc(this);
    wxSize size = GetClientSize();
    int altTaulell = size.GetHeight() - BoardHeight * QuadratHeight();

    for (int i = 0; i < BoardHeight; ++i) {
        for (int j = 0; j < BoardWidth; ++j) {
            T_Formes shape = FormaA(j, BoardHeight - i - 1);
            if (shape != FormaBuida)
                PintaQuadre(dc, 0 + j * QuadratWidth(),
                           altTaulell + i * QuadratHeight(), shape);
        }
    }

    if (FitxaActual.TreuForma() != FormaBuida) {
        for (int i = 0; i < 4; ++i) {
            int x = actX + FitxaActual.x(i);
            int y = actY - FitxaActual.y(i);
            PintaQuadre(dc, 0 + x * QuadratWidth(),
                       altTaulell + (BoardHeight - y - 1) * QuadratHeight(),
                       FitxaActual.TreuForma());



        }
    }

}

void Taulell::enTeclaAvall(wxKeyEvent& event)
{
    if (!this->isIniciat || this->FitxaActual.TreuForma() == FormaBuida) {
        event.Skip();
        return;
    }

    int keycode = event.GetKeyCode();

    if (keycode == 'p' || keycode == 'P') {
        Pausa();
        return;
    }

    if (isAturat)
        return;

    switch (keycode) {
    case WXK_LEFT:
        this->ProvaMoure(curPiece, curX - 1, curY);
        break;
    case WXK_RIGHT:
        this->ProvaMoure(curPiece, curX + 1, curY);
        break;
    case WXK_DOWN:
        this->ProvaMoure(curPiece.RotateRight(), curX, curY);
        break;
    case WXK_UP:
        this->ProvaMoure(curPiece.RotateLeft(), curX, curY);
        break;
    case WXK_SPACE:
        this->LlancaAvall();
        break;
    case 'd':
        this->LiniaAbaix();
        break;
    case 'D':
        this->LiniaAbaix();
        break;
    default:
        event.Skip();
    }

}

void Taulell::enTimer(wxCommandEvent& event)
{
    if (this->isAcabatdeCaure) {
        isAcabatdeCaure = false;
        this->NovaFitxa();
    } else {
        this->LiniaAbaix();
    }
}

void Taulell::NetejaTaulell()
{
    for (int i = 0; i < BoardHeight * BoardWidth; ++i)
        taulell[i] = FormaBuida;
}

void Taulell::LlancaAvall() //drop down, l'envia abaix immediatament
{
    int newY = ActY;
    while (newY > 0) {
        if (!this->ProvaMoure(this->FitxaActual, ActX, newY - 1))
            break;
        --newY;
    }
    this->FitxaJaEsAbaix();
}

void Taulell::LiniaAbaix()
{
    if (!this->ProvaMoure(this->FitxaActual, ActX, newY - 1))
        this->FitxaJaEsAbaix();
}

void Taulell::FitxaJaEsAbaix() //Hem arribat al final
{
    for (int i = 0; i < 4; ++i) {
        int x = ActX + this->FitxaActual.x(i);
        int y = ActY - this->FitxaActual.y(i);
        FormaA(x, y) = this->FitxaActual.TreuForma();
    }

    this->EliminaLiniesCompletes();//Elimina les linies ja completades

    if (!this->isAcabatdeCaure)
        this->NovaFitxa();
}

void Taulell::EliminaLiniesCompletes()
{
     int numFullLines = 0;

     for (int i = BoardHeight - 1; i >= 0; --i) {
         bool lineIsFull = true;

         for (int j = 0; j < BoardWidth; ++j) {
             if (this->FormaA(j, i) == FormaBuida) {
                 lineIsFull = false;
                 break;
             }
         }

         if (lineIsFull) {
             ++numFullLines;
             for (int k = i; k < BoardHeight - 1; ++k) {
                 for (int j = 0; j < BoardWidth; ++j)
                     FormaA(j, k) = FormaA(j, k + 1);
             }
         }
     }

     if (numFullLines > 0) {
         LiniesEliminades += numFullLines;
         wxString str;
	 str.Printf(wxT("%d"), LiniesEliminades);
         m_stsbar->SetStatusText(str);

         this->isAcabatdeCaure = true;
         this->FitxaActual.CreaForma(FormaBuida);
         Refresh();
     }
 }


void Taulell::NovaFitxa()
{
    this->FitxaActual.CreaFormaAleatoria;
    ActX = BoardWidth / 2 + 1;
    ActY = BoardHeight - 1 + FitxaActual.MinY();

    if (!this->ProvaMoure(FitxaActual, ActX, ActY)) {
        FitxaActual.CreaForma(FormaBuida);
        timer->Stop();
        this->isIniciat = false;
        m_stsbar->SetStatusText(wxT("game over"));
    }
}


bool Taulell::ProvaMoure(const Forma& newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + newPiece.x(i);
        int y = newY - newPiece.y(i);
        if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
            return false;
        if (FormaA(x, y) != FormaBuida)
            return false;
    }

    this->FitxaActual = newPiece;
    ActX = newX;
    ActY = newY;
    Refresh();
    return true;
}

void Taulell::PintaQuadre(wxPaintDC &dc, int x, int y, T_Formes shape)
{
    static wxColour colors[] = { wxColour(0, 0, 0), wxColour(204, 102, 102),
             wxColour(102, 204, 102), wxColour(102, 102, 204),
             wxColour(204, 204, 102), wxColour(204, 102, 204),
             wxColour(102, 204, 204), wxColour(218, 170, 0) };

    static wxColour light[] = { wxColour(0, 0, 0), wxColour(248, 159, 171),
             wxColour(121, 252, 121), wxColour(121, 121, 252),
             wxColour(252, 252, 121), wxColour(252, 121, 252),
             wxColour(121, 252, 252), wxColour(252, 198, 0) };

    static wxColour dark[] = { wxColour(0, 0, 0), wxColour(128, 59, 59),
             wxColour(59, 128, 59), wxColour(59, 59, 128),
             wxColour(128, 128, 59), wxColour(128, 59, 128),
             wxColour(59, 128, 128), wxColour(128, 98, 0) };


    wxPen pen(light[int(shape)]);
    pen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(pen);

    dc.DrawLine(x, y + QuadratHeight() - 1, x, y);
    dc.DrawLine(x, y, x + QuadratWidth() - 1, y);

    wxPen darkpen(dark[int(shape)]);
    darkpen.SetCap(wxCAP_PROJECTING);
    dc.SetPen(darkpen);

    dc.DrawLine(x + 1, y + QuadratHeight() - 1,
        x + QuadratWidth() - 1, y + QuadratHeight() - 1);
    dc.DrawLine(x + QuadratWidth() - 1,
        y + QuadratHeight() - 1, x + QuadratWidth() - 1, y + 1);

    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(wxBrush(colors[int(shape)]));
    dc.DrawRectangle(x + 1, y + 1, QuadratWidth() - 2,
        QuadratHeight() - 2);
}

