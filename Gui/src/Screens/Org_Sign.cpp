/*
NOTE!!!
Before comitting ensure to pull updates...then use commiit and pull with amend
*/

#include "../../headers/Screens.h"
#include "RDBManagers.h"

/////////////////////////////////////////			User Input Control Functions		///////////////////////////////////////////////////


void goBackToScreenToOrgPage(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    wxMessageDialog* dialog = new wxMessageDialog(currentScreen, "Inputs will be reset. Are you sure you want to leave?", wxString::FromAscii(wxMessageBoxCaptionStr), wxOK | wxCANCEL);

    if (dialog->ShowModal() == wxID_OK)
        shiftScreen(currentScreen, currentScreenID, nextScreenID, false, wxSHOW_EFFECT_SLIDE_TO_RIGHT);

}

void Org_signin(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID, shared_ptr<Organization> org, shared_ptr<User> user, string givenPasscode)
{
    bool validPasscode = RDBSecurityManager::orgSignin(*org.get(), givenPasscode);
    
    if (validPasscode)
    {
        shiftScreen(currentScreen, currentScreenID, nextScreenID, false, wxSHOW_EFFECT_SLIDE_TO_LEFT);
    }
    else
    {
        wxMessageDialog* dialog = new wxMessageDialog(currentScreen, "Incorrect passcode", wxString::FromAscii(wxMessageBoxCaptionStr), wxOK);
        dialog->ShowModal();
    }
}


/////////////////////////////////////////			                            		///////////////////////////////////////////////////


wxBoxSizer* passwordInput(wxWindow* screen, wxString title, int marginHorizontally)
{
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* pass = new wxStaticText(screen, wxID_ANY, title, wxDefaultPosition, wxDefaultSize);
    pass->SetFont(pass->GetFont().Scale(1.2f).MakeBold());


    wxTextCtrl* passInput = new wxTextCtrl(screen, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    passInput->SetMinSize(DPI_SIZE(220, 25, passInput));
    passInput->SetBackgroundColour("#E5E7E9");


    inputSizer->Add(pass);
    inputSizer->Add(DPI_X(marginHorizontally, screen), 0);         //Adding space in pixels
    inputSizer->Add(passInput, 0);
    return inputSizer;
}





Screen OrganizationSignin(wxWindow* parent, shared_ptr<Organization> org, shared_ptr<User> user)
{
    //Create screen parameters
    Screen screen = new wxPanel(parent);
    screen->SetSize(parent->GetSize());
    screen->Hide();
    screen->SetBackgroundColour(wxColor("#FFFFFF"));

    //Add screen pointer to list
    ScreenID previousScreen = ORG_SETUP;
    ScreenID currentScreen = ORG_SIGN_IN;
    ScreenID nextScreen = LOGIN;
    screensReference.push_back(make_tuple(screen, currentScreen));

    //Implement screen content
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    screen->SetSizer(sizer);

    //logo
    wxPNGHandler* p = new wxPNGHandler();
    wxImage::AddHandler(p);
    wxString logoPath = ASSESTS("image.png");
    wxStaticBitmap* bitmapImage = new wxStaticBitmap(screen, wxID_ANY, wxBitmap(wxImage(logoPath, wxBITMAP_TYPE_PNG).Rescale(130, 160, wxIMAGE_QUALITY_HIGH)));

    //back button
    wxString backButtonPath = ASSESTS("back_button.png");
    wxButton* backButton = new wxButton(screen, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    backButton->SetSize(DPI_SIZE(40, 40, backButton));
    backButton->SetBitmap(wxBitmap(wxImage(backButtonPath, wxBITMAP_TYPE_PNG).Rescale(40, 40, wxIMAGE_QUALITY_HIGH)));
    backButton->SetBackgroundColour("#FFFFFF");
    backButton->SetForegroundColour("#FFFFFF");
    backButton->SetPosition(DPI_POINT(25, 35, screen));

    string title = RDBSecurityManager::loadOrgName();
    wxStaticText* text = new wxStaticText(screen, ORG_SIGN_ORG_NAME, title, wxDefaultPosition, wxDefaultSize);
    text->SetFont(text->GetFont().Scale(3.5f).MakeBold());


    //Add input fields and "Register" button
    wxBoxSizer* password = passwordInput(screen, "Password:", 10);
    wxButton* button = new wxButton(screen, wxID_ANY, "Sign in");
    button->SetMinSize(DPI_SIZE(200, 80, button));
    button->SetFont(button->GetFont().Scale(1.8f));


    //A Sizer to vertically align OrgName and password input
    wxFlexGridSizer* rowSizer = new wxFlexGridSizer(2, 1, 100, 0);
    rowSizer->Add(text, 0, wxALIGN_CENTER);
    rowSizer->Add(password, 0, wxALIGN_CENTER);


    //Bind controls with functions
    auto signInFunction = [screen, currentScreen, nextScreen, org, user, password](wxCommandEvent& evt)
    {
        wxTextCtrl* password_input_box = ((wxTextCtrl*)password->GetItem(size_t(2))->GetWindow());

        Org_signin(screen, currentScreen, nextScreen, org, user, password_input_box->GetValue().ToStdString());
    };

    button->Bind(wxEVT_BUTTON, signInFunction);
    backButton->Bind(wxEVT_BUTTON, [screen, currentScreen, previousScreen](wxCommandEvent& evt) {goBackToScreenToOrgPage(screen, currentScreen, previousScreen); });

    sizer->Add(0, 30);
    sizer->Add(bitmapImage, 0, wxALIGN_CENTER);
    sizer->Add(0, DPI_Y(30, screen));
    sizer->Add(rowSizer, 0, wxALIGN_CENTER);
    sizer->Add(0, DPI_Y(100, screen));
    sizer->Add(button, 0, wxCENTER);
    return screen;
}
