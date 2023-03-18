/*
NOTE!!!
Before comitting ensure to pull updates...then use commiit and pull with amend
*/

#include "../../headers/Screens.h"

/////////////////////////////////////////			User Input Control Functions		///////////////////////////////////////////////////


void Org_set(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    shiftScreen(currentScreen, currentScreenID, nextScreenID, false, wxSHOW_EFFECT_SLIDE_TO_LEFT);
}

void Org_sign(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    shiftScreen(currentScreen, currentScreenID, nextScreenID, false, wxSHOW_EFFECT_SLIDE_TO_LEFT);
}


/////////////////////////////////////////			                            		///////////////////////////////////////////////////






Screen setOrg(wxWindow* parent)
{

    //Create screen parameters
    Screen screen1 = new wxPanel(parent);
    screen1->SetSize(parent->GetSize());

    //Add screen pointer to list
    ScreenID currentScreen = ORG_SETUP;
    ScreenID nextScreen1 = ORG_REGISTER;
    ScreenID nextScreen2 = ORG_SIGN_IN;
    screensReference.push_back(make_tuple(screen1, currentScreen));

    //Implement screen content
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    screen1->SetSizer(sizer);

    wxPNGHandler* p = new wxPNGHandler();
    wxImage::AddHandler(p);
    wxString logoPath = ASSESTS("image.png");
    wxStaticBitmap* bitmapImage = new wxStaticBitmap(screen1, wxID_ANY, wxBitmap(wxImage(logoPath, wxBITMAP_TYPE_PNG)));

    wxBoxSizer* sizer2 = new wxBoxSizer(wxHORIZONTAL);
    wxButton* button1 = new wxButton(screen1, wxID_ANY, "Set Up Org", wxDefaultPosition); 
    wxButton* button2 = new wxButton(screen1, wxID_ANY, "Sign In Org", wxDefaultPosition);

    sizer->Add(bitmapImage, 0, wxCENTER);

    sizer2->Add(button1, 0, wxCENTER);
    sizer2->Add(1000, 0);
    sizer2->Add(button2, 0, wxCENTER);


    sizer->Add(sizer2, 1, wxALIGN_CENTER);
    //Bind controls with functions
    button1->Bind(wxEVT_BUTTON, [screen1, currentScreen, nextScreen1](wxCommandEvent& evt) {Org_set(screen1, currentScreen, nextScreen1); });
    button2->Bind(wxEVT_BUTTON, [screen1, currentScreen, nextScreen2](wxCommandEvent& evt) {Org_sign(screen1, currentScreen, nextScreen2); });
    return screen1;
}
