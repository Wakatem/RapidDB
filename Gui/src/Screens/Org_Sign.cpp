/*
NOTE!!!
Before comitting ensure to pull updates...then use commiit and pull with amend
*/

#include "../Screens.h"

/////////////////////////////////////////			User Input Control Functions		///////////////////////////////////////////////////


void goBackToScreenToOrgPage(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    wxMessageDialog* dialog = new wxMessageDialog(currentScreen, "Inputs will be reset. Are you sure you want to leave?", wxString::FromAscii(wxMessageBoxCaptionStr), wxOK | wxCANCEL);

    if (dialog->ShowModal() == wxID_OK)
        shiftScreen(currentScreen, currentScreenID, nextScreenID, false, wxSHOW_EFFECT_SLIDE_TO_RIGHT);

}

void Org_signin(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    shiftScreen(currentScreen, currentScreenID, nextScreenID, false, wxSHOW_EFFECT_SLIDE_TO_LEFT);
}


/////////////////////////////////////////			                            		///////////////////////////////////////////////////


wxBoxSizer* textInput_org_sign_in(wxWindow* screen, wxString title, int marginHorizontally)
{
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* pass = new wxStaticText(screen, wxID_ANY, title, wxDefaultPosition, wxDefaultSize);
    pass->SetFont(pass->GetFont().Scale(1.2f).MakeBold());


    wxTextCtrl* passInput = new wxTextCtrl(screen, wxID_ANY);
    passInput->SetMinSize(DPI_SIZE(220, 25, passInput));
    passInput->SetBackgroundColour("#E5E7E9");


    inputSizer->Add(pass);
    inputSizer->Add(DPI_X(marginHorizontally, screen), 0);         //Adding space in pixels
    inputSizer->Add(passInput, 0);
    return inputSizer;
}

wxSizer* rowInputs_org_sign(wxWindow* screen)
{
    wxFlexGridSizer* rowSizer = new wxFlexGridSizer(2, 50, 100);

    wxBoxSizer* Orgname = textInput_org_sign_in(screen, "Organization Name:", 35);

    rowSizer->Add(Orgname);

    wxBoxSizer* password = textInput_org_sign_in(screen, "Password:", 33);
 
    rowSizer->Add(password);

    return rowSizer;
}

Screen OrganizationSigin(wxWindow* parent)
{
    //Create screen parameters
    Screen screen = new wxPanel(parent);
    screen->SetSize(parent->GetSize());
    screen->Hide();
    screen->SetBackgroundColour(wxColor("#FFFFFF"));

    //Add screen pointer to list
    screensReference.push_back(make_tuple(screen, ORG_SIGN_IN));

    //Implement screen content

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    screen->SetSizer(sizer);

    // logo

    wxPNGHandler* p = new wxPNGHandler();
    wxImage::AddHandler(p);
    wxString logoPath = ASSESTS("image.png");
    wxStaticBitmap* bitmapImage = new wxStaticBitmap(screen, wxID_ANY, wxBitmap(wxImage(logoPath, wxBITMAP_TYPE_PNG).Rescale(130, 160, wxIMAGE_QUALITY_HIGH)));

    //back
    wxString backButtonPath = ASSESTS("back_button.png");
    wxButton* backButton = new wxButton(screen, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    backButton->SetSize(DPI_SIZE(40, 40, backButton));
    backButton->SetBitmap(wxBitmap(wxImage(backButtonPath, wxBITMAP_TYPE_PNG).Rescale(40, 40, wxIMAGE_QUALITY_HIGH)));
    backButton->SetBackgroundColour("#FFFFFF");
    backButton->SetForegroundColour("#FFFFFF");
    backButton->SetPosition(DPI_POINT(25, 35, screen));

    //title
    wxStaticText* text = new wxStaticText(screen, wxID_ANY, "Organization Sign In", wxDefaultPosition, wxDefaultSize);
    text->SetPosition(DPI_POINT(470, 180, screen));
    text->SetFont(text->GetFont().Scale(2.2f).MakeUnderlined());


    //Add input fields and "Register" button
    wxSizer* inputs = rowInputs_org_sign(screen);
    wxButton* button = new wxButton(screen, wxID_ANY, "Enter");
    button->SetMinSize(DPI_SIZE(200, 80, button));
    button->SetFont(button->GetFont().Scale(1.8f));

    //Bind controls with functions
    button->Bind(wxEVT_BUTTON, [screen](wxCommandEvent& evt) {Org_signin(screen, ORG_SIGN_IN, LOGIN); });
    backButton->Bind(wxEVT_BUTTON, [screen](wxCommandEvent& evt) {goBackToScreenToOrgPage(screen, ORG_SIGN_IN, ORG_SETUP); });

    sizer->Add(0, 30);
    sizer->Add(bitmapImage, 0, wxALIGN_CENTER);
    sizer->Add(0, DPI_Y(130, screen));
    sizer->Add(inputs, 0, wxALIGN_CENTER);
    sizer->Add(0, DPI_Y(60, screen));
    sizer->Add(button, 0, wxCENTER);
    return screen;
}
