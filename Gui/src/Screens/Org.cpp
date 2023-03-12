/*
NOTE!!!
Before comitting ensure to pull updates...then use commiit and pull with amend
*/

#include "../Screens.h"

/////////////////////////////////////////			User Input Control Functions		///////////////////////////////////////////////////


void Org_set(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    shiftScreen(currentScreen, currentScreenID, nextScreenID, false);
}

void Org_sign(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    shiftScreen(currentScreen, currentScreenID, nextScreenID, false);
}


/////////////////////////////////////////			                            		///////////////////////////////////////////////////



Screen setOrg(wxWindow* parent)
{
    //Create screen parameters
    Screen screen1 = new wxPanel(parent);
    screen1->SetSize(parent->GetSize());
    screen1->Show(false);

    //Add screen pointer to list
    screensReference.push_back(make_tuple(screen1, ORG_SETUP));

    //Implement screen content
    wxStaticText* text = new wxStaticText(screen1, wxID_ANY, "Organization screen", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    wxButton* button1 = new wxButton(screen1, wxID_ANY, "Set Up Org", wxPoint(300, 600)); // (x, y)
    wxButton* button2 = new wxButton(screen1, wxID_ANY, "Sign In Org", wxPoint(1100, 600));

    //Bind controls with functions
    button1->Bind(wxEVT_BUTTON, [screen1](wxCommandEvent& evt) {Org_set(screen1, ORG_SETUP, ORG_REGISTER); });
    button2->Bind(wxEVT_BUTTON, [screen1](wxCommandEvent& evt) {Org_sign(screen1, ORG_SETUP, ORG_SIGN_IN); });
    return screen1;
}
