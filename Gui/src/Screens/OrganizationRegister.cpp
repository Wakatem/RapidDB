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
    usernameInput->SetMinSize(DPI_SIZE(220, 25, usernameInput));
    usernameInput->SetBackgroundColour("#E5E7E9");


    inputSizer->Add(username);
    inputSizer->Add(marginHorizontally, 0);       //Adding space in pixels
    inputSizer->Add(usernameInput, 0);
    return inputSizer;
}

wxSizer* rowInputs_org_setup(wxWindow* screen)
{
    wxFlexGridSizer* rowSizer = new wxFlexGridSizer(2, 50, 100);

    wxBoxSizer* name = textInput_org_setup(screen, "Organization Name :");
    wxBoxSizer* country = textInput_org_setup(screen, "Country :");

    rowSizer->Add(name);
    rowSizer->Add(country);

    wxBoxSizer* timeZone = textInput_org_setup(screen, "Time Zone :", 50);
    wxBoxSizer* email = textInput_org_setup(screen, "Email :", 50);
    wxBoxSizer* password = textInput_org_setup(screen, "Password :", 50);

    rowSizer->Add(timeZone, 1);
    rowSizer->Add(email);
    rowSizer->Add(password);

    return rowSizer;
}


Screen setupOrganizationRegister(wxWindow* parent)
{
    //Create screen parameters
    Screen screen = new wxPanel(parent);
    screen->SetSize(parent->GetSize());
    screen->Show(false);
    screen->SetBackgroundColour(wxColor("#FFFFFF"));

    //Add screen pointer to list
    screensReference.push_back(make_tuple(screen, ORG_REGISTER));

    //Implement screen content
  
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    screen->SetSizer(sizer);

    // logo
   /* wxPNGHandler* handler = new wxPNGHandler;
    wxImage::AddHandler(handler);
    wxStaticBitmap* image;
    image = new wxStaticBitmap(screen, wxID_ANY, wxBitmap("rapidDB_logo.png", wxBITMAP_TYPE_PNG), wxPoint(900, 100), wxSize(100, 500));*/

    //title
    wxStaticText* text = new wxStaticText(screen, wxID_ANY, "Organization Register screen", wxDefaultPosition, wxDefaultSize);
    text->SetPosition(DPI_POINT(480, 260, text));
    text->SetFont(text->GetFont().Scale(2.2).MakeUnderlined());


    wxSizer* inputs = rowInputs_org_setup(screen);

    wxButton* button = new wxButton(screen, wxID_ANY, "Register");
    button->SetBackgroundColour("#AEB6BF");
    button->SetMinSize(DPI_SIZE(200, 80, button));
    button->SetFont(button->GetFont().Scale(1.8).MakeItalic());

    //Bind controls with functions
    button->Bind(wxEVT_BUTTON, [screen](wxCommandEvent& evt) {RegisterOrg(screen, ORG_REGISTER, ADMIN_REGISTER); });

    sizer->Add(0, 120);
    sizer->Add(inputs, 0, wxALIGN_CENTER);
    sizer->Add(0, 130);
    sizer->Add(button, 0, wxCENTER);
    return screen;
}


