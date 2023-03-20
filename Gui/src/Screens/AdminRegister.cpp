#include "../../headers/Screens.h"


/////////////////////////////////////////			User Input Control Functions		///////////////////////////////////////////////////
static bool checkPasswordUser(wxTextCtrl* passwordCtrl)
{
    wxString password = passwordCtrl->GetValue();
    int n = password.length();
    bool hasLower = false, hasUpper = false, hasDigit = false;

    for (int i = 0; i < n; i++) {
        if (islower(password[i]))
            hasLower = true;
        if (isupper(password[i]))
            hasUpper = true;
        if (isdigit(password[i]))
            hasDigit = true;
    }

    if (hasUpper && hasDigit && hasLower && (n >= 6)) // considering a strong must be of length 6 or more
        return true;

    else
        return false;
}

bool isNumber(wxTextCtrl* numberCtrl) {
    wxString phone = numberCtrl->GetValue();
    for (char c : phone)
        if (c < '0' || c > '9')
            return false;
    return true;
}


void goBackToScreen(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    wxMessageDialog* dialog = new wxMessageDialog(currentScreen, "Inputs will be reset. Are you sure you want to leave?", wxString::FromAscii(wxMessageBoxCaptionStr), wxOK | wxCANCEL);

    if (dialog->ShowModal() == wxID_OK)
        shiftScreen(currentScreen, currentScreenID, nextScreenID, false, wxSHOW_EFFECT_SLIDE_TO_RIGHT);

}

void RegisterAdmin(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID, wxSizer* inputs, shared_ptr<Organization> org)
{
    wxArrayString choices;
    choices.Add("Male");
    choices.Add("Female");
    wxBoxSizer* temp = nullptr; // to hold different input sizers

    temp = ((wxBoxSizer*)inputs->GetItem(size_t(0))->GetSizer());
    wxTextCtrl* firstnameInput = ((wxTextCtrl*)temp->GetItem(size_t(2))->GetWindow());

    temp = ((wxBoxSizer*)inputs->GetItem(size_t(1))->GetSizer());
    wxTextCtrl* lastnameInput = ((wxTextCtrl*)temp->GetItem(size_t(2))->GetWindow());

    temp = ((wxBoxSizer*)inputs->GetItem(size_t(3))->GetSizer());
    wxTextCtrl* phoneNumberInput = ((wxTextCtrl*)temp->GetItem(size_t(2))->GetWindow());

    temp = ((wxBoxSizer*)inputs->GetItem(size_t(4))->GetSizer());
    wxTextCtrl* emailInput = ((wxTextCtrl*)temp->GetItem(size_t(2))->GetWindow());

    temp = ((wxBoxSizer*)inputs->GetItem(size_t(5))->GetSizer());
    size_t index = ((wxChoice*)temp->GetItem(size_t(2))->GetWindow())->GetSelection();

    temp = ((wxBoxSizer*)inputs->GetItem(size_t(6))->GetSizer());
    wxTextCtrl* usernameInput = ((wxTextCtrl*)temp->GetItem(size_t(2))->GetWindow());

    temp = ((wxBoxSizer*)inputs->GetItem(size_t(7))->GetSizer());
    wxTextCtrl* passwordInput = ((wxTextCtrl*)temp->GetItem(size_t(2))->GetWindow());

    //Inform user to provide detail if an input is empty
    if (firstnameInput->GetValue().IsEmpty() || lastnameInput->GetValue().IsEmpty() || phoneNumberInput->GetValue().IsEmpty() || emailInput->GetValue().IsEmpty() || index == wxNOT_FOUND || usernameInput->GetValue().IsEmpty() || passwordInput->GetValue().IsEmpty())
    {
        wxLogMessage("Kindly provide all the details to continue registration");
    }
    //else if (emailInput->GetValue() != "(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+") 
    //{
    //    wxLogMessage("Kindly provide a valid email");
    //}
    else if (checkPasswordUser(passwordInput) == false)
    {
        wxLogMessage("Kindly provide a password that meets the following:\n\nPassword should be:\nMore than 6 characters\nContain at least 1 upper case letter\nContain at least 1 lower case letter\n Contain at least 1 number");
    }
    else if (isNumber(phoneNumberInput) == false) {
        wxLogMessage("Kindly provide a valid phone number");
    }
    else 
    {
        //Save user details
        char gender = choices[index].ToStdString()[0];
        User user(firstnameInput->GetValue().ToStdString(), lastnameInput->GetValue().ToStdString(), gender, emailInput->GetValue().ToStdString(), phoneNumberInput->GetValue().ToStdString(), usernameInput->GetValue().ToStdString(), passwordInput->GetValue().ToStdString(), ADMIN);

        //Add user to organization
        RDBUserManager::addUser(*org.get(), user);

        //Save local files
        RDBFileManager::saveRDBfile(*org.get());

        //Go to next screen once file is found
        bool RDBfound = RDBFileManager::findRDBfile();

        if (RDBfound)
        {
            wxMessageDialog* dialog = new wxMessageDialog(currentScreen, "Organization registered successfully", wxString::FromAscii(wxMessageBoxCaptionStr));
            dialog->ShowModal();
            shiftScreen(currentScreen, currentScreenID, nextScreenID, false, wxSHOW_EFFECT_SLIDE_TO_LEFT);
        }
        else
        {
            wxMessageDialog* dialog = new wxMessageDialog(currentScreen, "Error in creating RDB file", wxString::FromAscii(wxMessageBoxCaptionStr), wxOK | wxCANCEL);

            if (dialog->ShowModal() == wxID_OK)
                shiftScreen(currentScreen, currentScreenID, ORG_REGISTER, false, wxSHOW_EFFECT_SLIDE_TO_RIGHT);
        }
    }

}


/////////////////////////////////////////		    	GUI Elements Functions		    ///////////////////////////////////////////////////


wxBoxSizer* textInput(wxWindow* screen, wxString title, int marginHorizontally, int style=0L)
{
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* username = new wxStaticText(screen, wxID_ANY, title, wxDefaultPosition, wxDefaultSize);
    username->SetFont(username->GetFont().Scale(1.2f).MakeBold());


    wxTextCtrl* usernameInput = new wxTextCtrl(screen, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style);
    usernameInput->SetMinSize(DPI_SIZE(220, 25, usernameInput));
    usernameInput->SetBackgroundColour("#E5E7E9");


    inputSizer->Add(username);
    inputSizer->Add(DPI_X(marginHorizontally, screen), 0);       //Adding space in pixels
    inputSizer->Add(usernameInput, 0);
    return inputSizer;
}

wxBoxSizer* choicesBox(wxWindow* screen)
{
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* username = new wxStaticText(screen, wxID_ANY, "Gender :", wxDefaultPosition, wxDefaultSize);
    username->SetFont(username->GetFont().Scale(1.2f).MakeBold());


    wxArrayString choices;
    choices.Add("Male");
    choices.Add("Female");
    wxChoice* choiceMenu = new wxChoice(screen, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);

    inputSizer->Add(username);
    inputSizer->Add(DPI_X(40, screen), 0);       //Adding space in pixels
    inputSizer->Add(choiceMenu, 1);
    return inputSizer;
}

wxSizer* rowInputs(wxWindow* screen)
{
    wxFlexGridSizer* rowSizer = new wxFlexGridSizer(3, 50, 100);

    wxBoxSizer* textInput1 = textInput(screen, "First Name :", 40);
    wxBoxSizer* textInput2 = textInput(screen, "Last Name :", 40);

    rowSizer->Add(textInput1);
    rowSizer->Add(textInput2);
    rowSizer->Add(DPI_X(200, screen), 0);



    wxBoxSizer* textInput3 = textInput(screen, "Phone NO :", 45);
    wxBoxSizer* textInput4 = textInput(screen, "Email :", 75);
    wxBoxSizer* choiceMenu = choicesBox(screen);
    wxBoxSizer* textInput5 = textInput(screen, "Username :", 45);
    wxBoxSizer* textInput6 = textInput(screen, "Password :", 45, wxTE_PASSWORD);

    rowSizer->Add(textInput3, 1);
    rowSizer->Add(textInput4);
    rowSizer->Add(choiceMenu);
    rowSizer->Add(textInput5);
    rowSizer->Add(textInput6);

    return rowSizer;
}


/////////////////////////////////////////			                            		///////////////////////////////////////////////////



Screen setupAdminRegister(wxWindow* parent, shared_ptr<Organization> org)
{
    //Create screen parameters
    Screen screen = new wxPanel(parent);
    screen->SetSize(parent->GetSize());
    screen->Hide();
    screen->SetBackgroundColour(wxColor("#FFFFFF"));

    //Add screen pointer to list
    ScreenID previousScreen = ORG_REGISTER;
    ScreenID currentScreen = ADMIN_REGISTER;
    ScreenID nextScreen = ORG_SIGN_IN;
    screensReference.push_back(make_tuple(screen, currentScreen));


    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    screen->SetSizer(sizer);

    wxPNGHandler* p = new wxPNGHandler();
    wxImage::AddHandler(p);
    wxString logoPath = ASSESTS("image.png");
    wxStaticBitmap* bitmapImage = new wxStaticBitmap(screen, wxID_ANY, wxBitmap(wxImage(logoPath, wxBITMAP_TYPE_PNG).Rescale(130, 160, wxIMAGE_QUALITY_HIGH)));


    wxString backButtonPath = ASSESTS("back_button.png");
    wxButton* backButton = new wxButton(screen, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    backButton->SetSize(DPI_SIZE(40, 40, backButton));
    backButton->SetBitmap(wxBitmap(wxImage(backButtonPath, wxBITMAP_TYPE_PNG).Rescale(40, 40, wxIMAGE_QUALITY_HIGH)));
    backButton->SetBackgroundColour("#FFFFFF");
    backButton->SetForegroundColour("#FFFFFF");
    backButton->SetPosition(DPI_POINT(25, 35, screen));

    //Screen Title
    wxStaticText* text = new wxStaticText(screen, wxID_ANY, "Admin Registration", wxDefaultPosition, wxDefaultSize);
    text->SetPosition(DPI_POINT(483, 180, screen));
    text->SetFont(text->GetFont().Scale(2.2f).MakeUnderlined());

    ////Add input fields and a 'register' button
    wxSizer* inputs = rowInputs(screen);
    wxButton* button = new wxButton(screen, wxID_ANY, "Register Admin");
    button->SetMinSize(DPI_SIZE(200, 80, button));
    button->SetFont(button->GetFont().Scale(1.8f));

    ////Bind controls with functions and add controls to sizer
    button->Bind(wxEVT_BUTTON, [screen, currentScreen, nextScreen, inputs, org](wxCommandEvent& evt) {RegisterAdmin(screen, currentScreen, nextScreen, inputs, org); });
    backButton->Bind(wxEVT_BUTTON, [screen, currentScreen, previousScreen](wxCommandEvent& evt) {goBackToScreen(screen, currentScreen, previousScreen); });

    sizer->Add(0, 30);
    sizer->Add(bitmapImage, 0, wxALIGN_CENTER);
    sizer->Add(0, DPI_Y(130, screen));
    sizer->Add(inputs, 0, wxALIGN_CENTER);
    sizer->Add(0, DPI_Y(60, screen));
    sizer->Add(button, 0, wxCENTER);

    return screen;
}