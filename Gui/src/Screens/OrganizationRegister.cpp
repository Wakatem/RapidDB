#include "../Screens.h"


/////////////////////////////////////////			User Input Control Functions		///////////////////////////////////////////////////


void RegisterOrg(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    shiftScreen(currentScreen, currentScreenID, nextScreenID, false);
}


/////////////////////////////////////////			                            		///////////////////////////////////////////////////



Screen setupOrganizationRegister(wxWindow* parent)
{
    //Create screen parameters
    Screen screen = new wxPanel(parent);
    screen->SetSize(parent->GetSize());
    screen->Show(false);

    //Add screen pointer to list
    screensReference.push_back(make_tuple(screen, ORG_REGISTER));

    //Implement screen content
    wxStaticText* text = new wxStaticText(screen, wxID_ANY, "Organization Register screen", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    wxButton* button = new wxButton(screen, wxID_ANY, "Register Org", wxPoint(700, 600));

    //Bind controls with functions
    button->Bind(wxEVT_BUTTON, [screen](wxCommandEvent& evt) {RegisterOrg(screen, ORG_REGISTER, ADMIN_REGISTER); });
    return screen;
}


