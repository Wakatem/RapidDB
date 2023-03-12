#include "../Screens.h"


/////////////////////////////////////////			User Input Control Functions		///////////////////////////////////////////////////


void RegisterOrg(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    shiftScreen(currentScreen, currentScreenID, nextScreenID, false);
}


/////////////////////////////////////////			                            		///////////////////////////////////////////////////

wxBoxSizer* textInput_org_setup(wxWindow* screen, wxString title, int marginHorizontally = 40)
{
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* username = new wxStaticText(screen, wxID_ANY, title, wxDefaultPosition, wxDefaultSize);
    username->SetFont(username->GetFont().Scale(1.2).MakeBold());


    wxTextCtrl* usernameInput = new wxTextCtrl(screen, wxID_ANY);
    usernameInput->SetMinSize(DIP_SIZE(220, 25, usernameInput));
    usernameInput->SetBackgroundColour("#E5E7E9");


    inputSizer->Add(username);
    inputSizer->Add(DIP_X(marginHorizontally, screen), 0);       //Adding space in pixels
    inputSizer->Add(usernameInput, 0);
    return inputSizer;
}

wxBoxSizer* choicesBox_tz(wxWindow* screen)
{
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* username = new wxStaticText(screen, wxID_ANY, "Time Zone :", wxDefaultPosition, wxDefaultSize);
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
    inputSizer->Add(DIP_X(40, screen), 0);       //Adding space in pixels
    inputSizer->Add(choiceMenu, 1);
    return inputSizer;
}

wxSizer* rowInputs_org_setup(wxWindow* screen)
{
    wxFlexGridSizer* rowSizer = new wxFlexGridSizer(2, 50, 100);

    wxBoxSizer* name = textInput_org_setup(screen, "Organization Name :");
    wxBoxSizer* country = textInput_org_setup(screen, "Country :");

    rowSizer->Add(name);
    rowSizer->Add(country);

    wxBoxSizer* choiceMenu = choicesBox_tz(screen);
    wxBoxSizer* email = textInput_org_setup(screen, "Email :", 50);
    wxBoxSizer* password = textInput_org_setup(screen, "Password :", 50);

    rowSizer->Add(choiceMenu, 1);
    rowSizer->Add(email);
    rowSizer->Add(password);

    return rowSizer;
}


Screen setupOrganizationRegister(wxWindow* parent)
{
    //Create screen parameters
    Screen screen = new wxPanel(parent);
    screen->SetSize(parent->GetSize());
    screen->Show(true);
    screen->SetBackgroundColour(wxColor("#FFFFFF"));

    //Add screen pointer to list
    screensReference.push_back(make_tuple(screen, ORG_REGISTER));

    //Implement screen content
  
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    screen->SetSizer(sizer);

    // logo
    wxPNGHandler* p = new wxPNGHandler();
    wxImage::AddHandler(p);
    wxString logoPath = ASSESTS("image.png");
    wxStaticBitmap* bitmapImage = new wxStaticBitmap(screen, wxID_ANY, wxBitmap(wxImage(logoPath, wxBITMAP_TYPE_PNG).Rescale(DIP_X(80, screen), DIP_X(100, screen), wxIMAGE_QUALITY_HIGH)));

    //title
    wxStaticText* text = new wxStaticText(screen, wxID_ANY, "Organization Register screen", wxDefaultPosition, wxDefaultSize);
    text->SetPosition(DIP_POINT(480, 260, text));
    text->SetFont(text->GetFont().Scale(2.2).MakeUnderlined());


    wxSizer* inputs = rowInputs_org_setup(screen);

    wxButton* button = new wxButton(screen, wxID_ANY, "Register");
    button->SetBackgroundColour("#AEB6BF");
    button->SetMinSize(DIP_SIZE(200, 80, button));
    button->SetFont(button->GetFont().Scale(1.8).MakeItalic());

    //Bind controls with functions
    button->Bind(wxEVT_BUTTON, [screen](wxCommandEvent& evt) {RegisterOrg(screen, ORG_REGISTER, ADMIN_REGISTER); });

    sizer->Add(0,DIP_Y(100,screen));
    sizer->Add(bitmapImage, 0, wxALIGN_CENTER);
    sizer->Add(inputs, 0, wxALIGN_CENTER);
    sizer->Add(0, DIP_Y(110, screen));
    sizer->Add(button, 0, wxCENTER);
    return screen;
}


