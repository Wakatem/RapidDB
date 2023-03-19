#include "../../headers/Screens.h"

void goBack(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    wxMessageDialog* dialog = new wxMessageDialog(currentScreen, "Inputs will be reset. Are you sure you want to leave?", wxString::FromAscii(wxMessageBoxCaptionStr), wxOK | wxCANCEL);

    if (dialog->ShowModal() == wxID_OK)
        shiftScreen(currentScreen, currentScreenID, nextScreenID, false, wxSHOW_EFFECT_SLIDE_TO_RIGHT);

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
        //shiftScreen(currentScreen, ORG_SIGN_IN, TEST, true);
    }
    else {
        wxMessageBox("Invalid Login", "Error", wxICON_ERROR | wxOK, currentScreen);
    }


}


void login(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID, shared_ptr<Organization> org, shared_ptr<User> user, wxSizer* inputs)
{
    
    wxArrayString choices;
    choices.Add("Admin");
    choices.Add("Moderator");

    wxBoxSizer* temp;
    temp = ((wxBoxSizer*)inputs->GetItem(size_t(0))->GetSizer());
    wxTextCtrl* usernameInput = ((wxTextCtrl*)temp->GetItem(size_t(2))->GetWindow());

    temp = ((wxBoxSizer*)inputs->GetItem(size_t(1))->GetSizer());
    wxTextCtrl* passwordInput = ((wxTextCtrl*)temp->GetItem(size_t(2))->GetWindow());

    temp = ((wxBoxSizer*)inputs->GetItem(size_t(2))->GetSizer());
    size_t index = ((wxChoice*)temp->GetItem(size_t(2))->GetWindow())->GetSelection();
    UserType userType;
    index == ADMIN ? userType = ADMIN : userType = MOD;

    //Inform user to provide detail if an input is empty
    if (usernameInput->GetValue().IsEmpty() || passwordInput->GetValue().IsEmpty() || index == wxNOT_FOUND)
    {
        wxLogMessage("Kindly provide all the details to login");
    }
    else
    {
        bool successfulLogin = RDBSecurityManager::userLogin(*org.get(), *user.get(), usernameInput->GetValue().ToStdString(), passwordInput->GetValue().ToStdString(), userType);

        if (successfulLogin)
        {
            shiftScreen(currentScreen, currentScreenID, nextScreenID, false, wxSHOW_EFFECT_SLIDE_TO_LEFT);
        }
        else
        {
            wxMessageDialog* dialog = new wxMessageDialog(currentScreen, "Incorrect username or password", wxString::FromAscii(wxMessageBoxCaptionStr), wxOK);
            dialog->ShowModal();
        }

    }
}


wxBoxSizer* textInput_setup(wxWindow* screen, wxString title, int marginTop, int style=0L)
{
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* username = new wxStaticText(screen, wxID_ANY, title, wxDefaultPosition, wxDefaultSize);
    username->SetFont(username->GetFont().Scale(1.2f).MakeBold());


    wxTextCtrl* usernameInput = new wxTextCtrl(screen, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style);
    usernameInput->SetMinSize(DPI_SIZE(220, 25, usernameInput));
    usernameInput->SetBackgroundColour("#E5E7E9");


    inputSizer->Add(username);
    inputSizer->Add(DPI_X(marginTop, screen), 0);       //Adding space in pixels
    inputSizer->Add(usernameInput, 0);

    return inputSizer;
}

wxBoxSizer* checkBox_setup(wxWindow* screen)
{
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* userRole = new wxStaticText(screen, wxID_ANY, "User Role :", wxDefaultPosition, wxDefaultSize);
    userRole->SetFont(userRole->GetFont().Scale(1.2f).MakeBold());


    wxArrayString choices;
    choices.Add("Admin");
    choices.Add("Moderator");
    wxChoice* choiceMenu = new wxChoice(screen, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);

    inputSizer->Add(userRole);
    inputSizer->Add(DPI_X(44, screen), 0);       //Adding space in pixels
    inputSizer->Add(choiceMenu, 1);
    return inputSizer;
}

wxSizer* rowinputs(wxWindow* screen)
{
    wxFlexGridSizer* rowSizer = new wxFlexGridSizer(2, 50, 100);

    wxBoxSizer* username1 = textInput_setup(screen, "Username :", 40);
    wxBoxSizer* password1 = textInput_setup(screen, "Password :", 40, wxTE_PASSWORD);

    rowSizer->Add(username1);
    rowSizer->Add(password1);
    wxBoxSizer* choiceMenu = checkBox_setup(screen);

    rowSizer->Add(choiceMenu);



    return rowSizer;
}

Screen setupLogin(wxWindow* parent, shared_ptr<Organization> org, shared_ptr<User> user)
{
    //Create screen parameters
    Screen screen = new wxPanel(parent);
    screen->SetSize(parent->GetSize());
    screen->Hide();
    screen->SetBackgroundColour(wxColor("#FFFFFF"));

    //Add screen pointer to list
    ScreenID previousScreen = ORG_SETUP;
    ScreenID currentScreen = LOGIN;
    ScreenID nextScreen = MAIN;
    screensReference.push_back(make_tuple(screen, currentScreen));


    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    screen->SetSizer(sizer);

    wxPNGHandler* p = new wxPNGHandler();
    wxImage::AddHandler(p);
    wxString logoPath = ASSESTS("image.png");
    wxStaticBitmap* bitmapImage = new wxStaticBitmap(screen, wxID_ANY, wxBitmap(wxImage(logoPath, wxBITMAP_TYPE_PNG).Rescale(100, 130, wxIMAGE_QUALITY_HIGH)));


    wxString backButtonPath = ASSESTS("back_button.png");
    wxButton* backButton = new wxButton(screen, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    backButton->SetSize(DPI_SIZE(40, 40, backButton));
    backButton->SetBitmap(wxBitmap(wxImage(backButtonPath, wxBITMAP_TYPE_PNG).Rescale(40, 40, wxIMAGE_QUALITY_HIGH)));
    backButton->SetBackgroundColour("#FFFFFF");
    backButton->SetForegroundColour("#FFFFFF");
    backButton->SetPosition(DPI_POINT(25, 35, screen));

    //Screen Title
    wxStaticText* text = new wxStaticText(screen, wxID_ANY, "User Login", wxDefaultPosition, wxDefaultSize);
    text->SetPosition(DPI_POINT(527, 180, screen));
    text->SetFont(text->GetFont().Scale(2.2f).MakeUnderlined());

    ////Add input fields and a 'register' button
    wxSizer* inputs = rowinputs(screen);
    wxButton* button = new wxButton(screen, wxID_ANY, "Log In");
    button->SetMinSize(DPI_SIZE(300, 50, button));
    button->SetFont(button->GetFont().Scale(1.8f));

    ////Bind controls with functions and add controls to sizer
    auto loginFunction = [screen, currentScreen, nextScreen, inputs, org, user](wxCommandEvent& evt)
    {


        login(screen, currentScreen, nextScreen, org, user, inputs);
    };
    button->Bind(wxEVT_BUTTON, loginFunction);
    backButton->Bind(wxEVT_BUTTON, [screen, currentScreen, previousScreen](wxCommandEvent& evt) {goBack(screen, currentScreen, previousScreen); });

    sizer->Add(0, 30);
    sizer->Add(bitmapImage, 0, wxALIGN_CENTER);
    sizer->Add(0, DPI_Y(130, screen));
    sizer->Add(inputs, 0, wxALIGN_CENTER);
    sizer->Add(0, DPI_Y(60, screen));
    sizer->Add(button, 0, wxCENTER);

    return screen;
}