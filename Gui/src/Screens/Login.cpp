#include "../Screens.h"

void goBack(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    wxMessageDialog* dialog = new wxMessageDialog(currentScreen, "Inputs will be reset. Are you sure you want to leave?", wxString::FromAscii(wxMessageBoxCaptionStr), wxOK | wxCANCEL);

    if (dialog->ShowModal() == wxID_OK)
        shiftScreen(currentScreen, currentScreenID, nextScreenID, true);
}

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
        shiftScreen(currentScreen, ORG_SIGN_IN, TEST, true);
    }
    else {
        wxMessageBox("Invalid Login", "Error", wxICON_ERROR | wxOK, currentScreen);
    }


}

void RegisterLogin(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    shiftScreen(currentScreen, currentScreenID, nextScreenID, false);
}

wxBoxSizer* textInput_setup(wxWindow* screen, wxString title, int marginTop)
{
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* username = new wxStaticText(screen, wxID_ANY, title, wxDefaultPosition, wxDefaultSize);
    username->SetFont(username->GetFont().Scale(1.2f).MakeBold());

    wxTextCtrl* usernameInput = new wxTextCtrl(screen, wxID_ANY);
    usernameInput->SetMinSize(DPI_SIZE(220, 25, usernameInput));
    usernameInput->SetBackgroundColour("#E5E7E9");

    inputSizer->Add(username);
    inputSizer->Add(DPI_X(20, screen), 0); // Adding space in pixels
    inputSizer->Add(usernameInput, 0);
    inputSizer->AddStretchSpacer(1);

    return inputSizer;
}

wxBoxSizer* checkBox_setup(wxWindow* screen, wxString label1, int marginTop)
{
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    wxCheckBox* checkBox1 = new wxCheckBox(screen, wxID_ANY, label1);
    checkBox1->SetFont(checkBox1->GetFont().Scale(1.2f).MakeBold());
    checkBox1->SetMinSize(DPI_SIZE(220, 25, checkBox1));
    checkBox1->SetBackgroundColour("#E5E7E9");


    inputSizer->Add(checkBox1, 0);
    inputSizer->AddStretchSpacer(1);

    return inputSizer;
}



Screen setupLogin(wxWindow* parent)
{
    //Create screen parameters
    Screen screen = new wxPanel(parent);
    screen->SetSize(parent->GetSize());
    screen->Show(true);
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
    wxStaticBitmap* bitmapImage = new wxStaticBitmap(screen, wxID_ANY, wxBitmap(wxImage(logoPath, wxBITMAP_TYPE_PNG).Rescale(100, 130, wxIMAGE_QUALITY_HIGH)));

    // title
    wxStaticText* text = new wxStaticText(screen, wxID_ANY, "Sign in", wxDefaultPosition, wxDefaultSize);
    text->SetPosition(DPI_POINT(500, 180, screen));
    text->SetFont(text->GetFont().Scale(2.2f).MakeUnderlined());

    //Add input fields and "Sign In" button
    wxSizer* user = textInput_setup(screen, "Username: ", 35);
    wxSizer* pass = textInput_setup(screen, "Password: ", 40);

    wxSizer* adminCheck = checkBox_setup(screen, "Admin", 45);
    wxSizer* moderatorCheck = checkBox_setup(screen, "Moderator", 45);

    wxButton* button = new wxButton(screen, wxID_ANY, "Sign In");
    button->SetMinSize(DPI_SIZE(200, 80, button));
    button->SetFont(button->GetFont().Scale(1.8f));

    //Bind controls with functions
    button->Bind(wxEVT_BUTTON, [screen ](wxCommandEvent& evt) {RegisterLogin(screen, ORG_SIGN_IN, TEST); });

    wxBoxSizer* sizerWrapper = new wxBoxSizer(wxVERTICAL);
    sizerWrapper->Add(user);
    sizerWrapper->Add(pass);

    sizerWrapper->Add(adminCheck);
    sizerWrapper->Add(moderatorCheck);

    sizer->Add(0, DPI_Y(130, screen));
    sizer->Add(bitmapImage, 0, wxALIGN_CENTER);
    sizer->Add(0, DPI_Y(40, screen));
    sizer->Add(text, 0, wxCENTER);
    sizer->Add(0, DPI_Y(30, screen));
    sizer->Add(sizerWrapper, 0, wxALIGN_CENTER);
    sizer->Add(0, DPI_Y(30, screen));
    sizer->Add(button, 0, wxCENTER);

    return screen;
}