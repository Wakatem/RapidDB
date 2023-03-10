#include "../Screens.h"
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


/////////////////////////////////////////			User Input Control Functions		///////////////////////////////////////////////////


void RegisterAdmin()
{
    wxLogMessage("Admin Registered");
}


/////////////////////////////////////////			                            		///////////////////////////////////////////////////



Screen setupAdminRegister(wxWindow* parent)
{
    //Create screen parameters
    Screen screen = new wxPanel(parent);
    screen->SetSize(parent->GetSize());
    screen->Show(false);

    //Add screen pointer to list
    screensReference.push_back(make_tuple(screen, ADMIN_REGISTER));

    //Implement screen content
    wxStaticText* text = new wxStaticText(screen, wxID_ANY, "Admin Register screen", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    wxButton* button = new wxButton(screen, wxID_ANY, "Register Admin", wxPoint(700, 600));

    //Bind controls with functions
    button->Bind(wxEVT_BUTTON, [](wxCommandEvent& evt) {RegisterAdmin(); });
    return screen;
}