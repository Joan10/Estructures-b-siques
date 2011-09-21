#include <wx/wx.h>
#include "taulell.h"
#include "Objectes/Objecte1.h"
#include "Objectes/Camara.h"
#include <vector>
#include <iostream>
#include "Rutina.h"

class Mwin : public wxFrame
{
public:

    wxStatusBar *m_stsbar;
    Mwin(const wxString& title, int res_x, int res_y);

};
