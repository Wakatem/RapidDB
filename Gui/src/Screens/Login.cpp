#include "../Screens.h"

void SignIn(wxString username, wxString password, bool isAdmin, bool isModerator, Screen currentScreen)
{
    bool isLoggedIn = false;
    if (username == "admin" && password == "admin" && isAdmin)
    {
        wxMessageBox("Logged in as Admin");
        isLoggedIn = true;
    }
    else if (username == "moderator" && password == "moderator" && isModerator)
    {
        wxMessageBox("Logged in as Moderator");
        isLoggedIn = true;

    }
    else if (username == "user" && password == "user" && isModerator == false && isAdmin == false)
    {
        wxMessageBox("Logged in as User");
        isLoggedIn = true;
    }
    else
    {
        wxMessageBox("Invalid credentials or user type");
    }

    if (isLoggedIn) {
        shiftScreen(currentScreen, ORG_SIGN_IN, TEST, true, wxSHOW_EFFECT_SLIDE_TO_LEFT);
    }
    else {
        wxMessageBox("Invalid Login", "Error", wxICON_ERROR | wxOK, currentScreen);
    }

}

void goBack(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    wxMessageDialog* dialog = new wxMessageDialog(currentScreen, "Inputs will be reset. Are you sure you want to leave?", wxString::FromAscii(wxMessageBoxCaptionStr), wxOK | wxCANCEL);

    if (dialog->ShowModal() == wxID_OK)
        shiftScreen(currentScreen, currentScreenID, nextScreenID, true, wxSHOW_EFFECT_SLIDE_TO_RIGHT);

}

Screen setupSignIn(wxWindow* parent) {

    // Create screen parameters
    Screen screen = new wxPanel(parent);
    screen->SetSize(parent->GetSize());
    screen->Show(true);
    screen->SetBackgroundColour(wxColor("#FFFFFF"));

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    screen->SetSizer(sizer);

    // logo
    wxPNGHandler* p = new wxPNGHandler();
    wxImage::AddHandler(p);
    wxString logoPath = ASSESTS("image.png");
    wxStaticBitmap* bitmapImage = new wxStaticBitmap(screen, wxID_ANY, wxBitmap(wxImage(logoPath, wxBITMAP_TYPE_PNG).Rescale(100, 130, wxIMAGE_QUALITY_HIGH)));

    //
   
    //add backbutton
    wxString backButtonPath = ASSESTS("back_button.png");
    wxButton* backButton = new wxButton(screen, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    backButton->SetSize(DPI_SIZE(40, 40, backButton));
    backButton->SetBitmap(wxBitmap(wxImage(backButtonPath, wxBITMAP_TYPE_PNG).Rescale(40, 40, wxIMAGE_QUALITY_HIGH)));
    backButton->SetBackgroundColour("#FFFFFF");
    backButton->SetForegroundColour("#FFFFFF");
    backButton->SetPosition(DPI_POINT(20, 30, backButton));

    // Add screen pointer to list
    screensReference.push_back(make_tuple(screen, ORG_SIGN_IN));

    // screen title
    wxStaticText* text = new wxStaticText(screen, wxID_ANY, "Organization Log In screen", wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
    text->SetPosition(DPI_POINT(430, 240, text));
    text->SetFont(text->GetFont().Scale(2.2f).MakeUnderlined());

    // Username input
    wxStaticText* usernameLabel = new wxStaticText(screen, wxID_ANY, "Username:", wxPoint(500, 400), wxDefaultSize, wxALIGN_RIGHT);
    wxTextCtrl* usernameInput = new wxTextCtrl(screen, wxID_ANY, "", wxPoint(650, 400), wxSize(200, 30));
    usernameInput->SetHint("Username");

    // Password input
    wxStaticText* passwordLabel = new wxStaticText(screen, wxID_ANY, "Password:", wxPoint(500, 450), wxDefaultSize, wxALIGN_RIGHT);
    wxTextCtrl* passwordInput = new wxTextCtrl(screen, wxID_ANY, "", wxPoint(650, 450), wxSize(200, 30), wxTE_PASSWORD);
    passwordInput->SetHint("Password");

    // Admin checkbox
    wxCheckBox* adminCheckbox = new wxCheckBox(screen, wxID_ANY, "Admin", wxPoint(650, 500));
    adminCheckbox->SetFont(adminCheckbox->GetFont().MakeBold());

    // Moderator checkbox
    wxCheckBox* moderatorCheckbox = new wxCheckBox(screen, wxID_ANY, "Moderator", wxPoint(650, 530));
    moderatorCheckbox->SetFont(moderatorCheckbox->GetFont().MakeBold());

    // Sign in button
    wxButton* button = new wxButton(screen, wxID_ANY, "Sign In", wxPoint(600, 600), wxSize(300, 50));
    button->SetFont(button->GetFont().MakeItalic());

    // Bind controls with functions
    button->Bind(wxEVT_BUTTON, [screen, usernameInput, passwordInput, adminCheckbox, moderatorCheckbox](wxCommandEvent& evt)
        {
            SignIn(usernameInput->GetValue(), passwordInput->GetValue(), adminCheckbox->GetValue(), moderatorCheckbox->GetValue(), screen);
        });
    backButton->Bind(wxEVT_BUTTON, [screen](wxCommandEvent& evt) {goBack(screen, ORG_SIGN_IN, ORG_REGISTER); });

    return screen;
}

