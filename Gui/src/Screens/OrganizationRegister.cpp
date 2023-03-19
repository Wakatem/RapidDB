#include "../../headers/Screens.h"


/////////////////////////////////////////			User Input Control Functions		///////////////////////////////////////////////////

void goBackToScreenToOrgSetUp(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    wxMessageDialog* dialog = new wxMessageDialog(currentScreen, "Inputs will be reset. Are you sure you want to leave?", wxString::FromAscii(wxMessageBoxCaptionStr), wxOK | wxCANCEL);

    if (dialog->ShowModal() == wxID_OK)
        shiftScreen(currentScreen, currentScreenID, nextScreenID, false, wxSHOW_EFFECT_SLIDE_TO_RIGHT);

}

void RegisterOrg(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID, wxSizer* inputs, shared_ptr<Organization> org)
{
    wxArrayString choices;
    choices.Add("UTC +9:30");
    choices.Add("UTC +9");
    choices.Add("UTC +5");
    choices.Add("UTC +4");
    choices.Add("UTC +3");
    choices.Add("UTC +1");
    choices.Add("UTC +0");
    choices.Add("UTC -4");
    choices.Add("UTC -6");
    choices.Add("UTC -8:00 / -7:00");

    wxBoxSizer* temp = nullptr; // to hold different input sizers

    temp = ( (wxBoxSizer*) inputs->GetItem(size_t(0))->GetSizer());
    wxTextCtrl* nameInput = ( (wxTextCtrl*) temp->GetItem(size_t(2))->GetWindow() );

    temp = ((wxBoxSizer*)inputs->GetItem(size_t(1))->GetSizer());
    wxTextCtrl* countryInput = ((wxTextCtrl*)temp->GetItem(size_t(2))->GetWindow());

    temp = ((wxBoxSizer*)inputs->GetItem(size_t(2))->GetSizer());
    wxTextCtrl* emailInput = ((wxTextCtrl*)temp->GetItem(size_t(2))->GetWindow());

    temp = ((wxBoxSizer*)inputs->GetItem(size_t(3))->GetSizer());
    wxTextCtrl* passwordInput = ((wxTextCtrl*)temp->GetItem(size_t(2))->GetWindow());

    temp = ((wxBoxSizer*)inputs->GetItem(size_t(4))->GetSizer());
    size_t index = ((wxChoice*)temp->GetItem(size_t(2))->GetWindow())->GetSelection();
   

    //Inform user to provide detail if an input is empty
    if (nameInput->GetValue().IsEmpty() || countryInput->GetValue().IsEmpty() || emailInput->GetValue().IsEmpty() || passwordInput->GetValue().IsEmpty() || index == wxNOT_FOUND)
    {
        wxLogMessage("Kindly provide all the details to continue registration");
    }
    else
    {
        //Save organization details
        string timezone = choices[index].ToStdString();
        org->setDetails(nameInput->GetValue().ToStdString(), countryInput->GetValue().ToStdString(), timezone , passwordInput->GetValue().ToStdString(), emailInput->GetValue().ToStdString());

    }


    shiftScreen(currentScreen, currentScreenID, nextScreenID, false, wxSHOW_EFFECT_SLIDE_TO_LEFT);
    
}


/////////////////////////////////////////			                            		///////////////////////////////////////////////////

wxBoxSizer* textInput_org_setup(wxWindow* screen, wxString title, int marginHorizontally)
{
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* username = new wxStaticText(screen, wxID_ANY, title, wxDefaultPosition, wxDefaultSize);
    username->SetFont(username->GetFont().Scale(1.2f).MakeBold());


    wxTextCtrl* usernameInput = new wxTextCtrl(screen, wxID_ANY);
    usernameInput->SetMinSize(DPI_SIZE(220, 25, usernameInput));
    usernameInput->SetBackgroundColour("#E5E7E9");


    inputSizer->Add(username);
    inputSizer->Add(DPI_X(marginHorizontally, screen), 0);         //Adding space in pixels
    inputSizer->Add(usernameInput, 0);
    return inputSizer;
}

wxBoxSizer* choicesBox_tz(wxWindow* screen, int marginHorizontally)
{
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* username = new wxStaticText(screen, wxID_ANY, "Time Zone:", wxDefaultPosition, wxDefaultSize);
    username->SetFont(username->GetFont().Scale(1.2f).MakeBold());


    wxArrayString choices;
    choices.Add("UTC +9:30");
    choices.Add("UTC +9");
    choices.Add("UTC +5");
    choices.Add("UTC +4");
    choices.Add("UTC +3");
    choices.Add("UTC +1");
    choices.Add("UTC +0");
    choices.Add("UTC -4");
    choices.Add("UTC -6");
    choices.Add("UTC -8:00 / -7:00");

    wxChoice* choiceMenu = new wxChoice(screen, wxID_ANY, wxDefaultPosition, wxDefaultSize, choices);

    inputSizer->Add(username);
    inputSizer->Add(DPI_X(marginHorizontally, screen), 0);       //Adding space in pixels
    inputSizer->Add(choiceMenu, 1);
    return inputSizer;
}

wxSizer* rowInputs_org_setup(wxWindow* screen)
{
    wxFlexGridSizer* rowSizer = new wxFlexGridSizer(2, 50, 100);

    wxBoxSizer* name = textInput_org_setup(screen, "Name:", 35);
    wxBoxSizer* country = textInput_org_setup(screen, "Country:", 40);

    rowSizer->Add(name);
    rowSizer->Add(country);

    wxBoxSizer* email = textInput_org_setup(screen, "Email:", 39);
    wxBoxSizer* password = textInput_org_setup(screen, "Password:", 30);
    wxBoxSizer* choiceMenu = choicesBox_tz(screen, 20);

    rowSizer->Add(email, 1);
    rowSizer->Add(password);
    rowSizer->Add(choiceMenu);

    return rowSizer;
}


Screen setupOrganizationRegister(wxWindow* parent, shared_ptr<Organization> org)
{
   
    //Create screen parameters
    Screen screen = new wxPanel(parent);
    screen->SetSize(parent->GetSize());
    screen->Hide();
    screen->SetBackgroundColour(wxColor("#FFFFFF"));

    //Add screen pointer to list
    ScreenID previousScreen = ORG_SETUP;
    ScreenID currentScreen = ORG_REGISTER;
    ScreenID nextScreen = ADMIN_REGISTER;
    screensReference.push_back(make_tuple(screen, currentScreen));

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
    wxStaticText* text = new wxStaticText(screen, wxID_ANY, "Organization Registration", wxDefaultPosition, wxDefaultSize);
    text->SetPosition(DPI_POINT(463, 180, screen));
    text->SetFont(text->GetFont().Scale(2.2f).MakeUnderlined());


    //Add input fields and "Register" button
    wxSizer* inputs = rowInputs_org_setup(screen);
    wxButton* button = new wxButton(screen, wxID_ANY, "Register Organization");
    button->SetMinSize(DPI_SIZE(230, 80, button));
    button->SetFont(button->GetFont().Scale(1.8f));

    //Bind controls with functions
    button->Bind(wxEVT_BUTTON, [screen, currentScreen, nextScreen, inputs, org](wxCommandEvent& evt) { RegisterOrg(screen, currentScreen, nextScreen, inputs, org); });
    backButton->Bind(wxEVT_BUTTON, [screen, currentScreen, previousScreen](wxCommandEvent& evt) {goBackToScreenToOrgSetUp(screen, currentScreen, previousScreen); });

    sizer->Add(0, 30);
    sizer->Add(bitmapImage, 0, wxALIGN_CENTER);
    sizer->Add(0, DPI_Y(130, screen));
    sizer->Add(inputs, 0, wxALIGN_CENTER);
    sizer->Add(0, DPI_Y(60, screen));
    sizer->Add(button, 0, wxCENTER);
    return screen;
}

