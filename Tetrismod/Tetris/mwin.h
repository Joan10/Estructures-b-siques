#include <wx/wx.h>

class Mwin : public wxFrame
{
public:

    wxStatusBar *m_stsbar;
    Mwin(const wxString& title, int res_x, int res_y);

};
