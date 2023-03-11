#include "../Screens.h"


/////////////////////////////////////////			User Input Control Functions		///////////////////////////////////////////////////


void RegisterOrg(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    shiftScreen(currentScreen, currentScreenID, nextScreenID, false);
}


/////////////////////////////////////////			                            		///////////////////////////////////////////////////



Screen setupOrganizationRegister(wxWindow* parent)
{
    //Create screen parameters
    Screen screen = new wxPanel(parent);
    screen->SetSize(parent->GetSize());
    screen->Show(true);

    //Add screen pointer to list
    screensReference.push_back(make_tuple(screen, ORG_REGISTER));

    //Implement screen content
  
    // logo
    wxPNGHandler* handler = new wxPNGHandler;
    wxImage::AddHandler(handler);
    wxStaticBitmap* image;
    image = new wxStaticBitmap(screen, wxID_ANY, wxBitmap("rapidDB_logo.png", wxBITMAP_TYPE_PNG), wxPoint(900, 100), wxSize(100, 500));

    //title
    wxStaticText* title = new wxStaticText(screen, wxID_ANY, "Organization Register screen", wxPoint(850,300), wxDefaultSize, wxALIGN_RIGHT);

    //org name
    wxStaticText* name = new wxStaticText(screen, wxID_ANY, "Organization Name:", wxPoint(500, 400), wxDefaultSize, wxALIGN_RIGHT);
    wxTextCtrl* name_entry = new wxTextCtrl(screen, wxID_ANY, "", wxPoint(650, 400), wxSize(200, 30));
    name_entry->SetHint("Organization Name");
    wxFont font = name->GetFont();
    font.SetWeight(wxFONTWEIGHT_BOLD);
    name->SetFont(font);

    //country
    wxStaticText* country = new wxStaticText(screen, wxID_ANY, "Country:", wxPoint(500, 450), wxDefaultSize, wxALIGN_RIGHT);
    wxTextCtrl* country_entry = new wxTextCtrl(screen, wxID_ANY, "", wxPoint(650, 450), wxSize(200, 30));
    country_entry->SetHint("Country");
    country->SetFont(font);

    //TimeZone
    wxStaticText* timeZone = new wxStaticText(screen, wxID_ANY, "Time Zone:", wxPoint(500, 500), wxDefaultSize, wxALIGN_RIGHT);
    wxTextCtrl* timeZone_entry = new wxTextCtrl(screen, wxID_ANY, "", wxPoint(650, 500), wxSize(200, 30));
    timeZone_entry->SetHint("Time Zone");
    timeZone->SetFont(font);

    //email
    wxStaticText* email = new wxStaticText(screen, wxID_ANY, "Email", wxPoint(500, 550), wxDefaultSize, wxALIGN_RIGHT);
    wxTextCtrl* email_entry = new wxTextCtrl(screen, wxID_ANY, "", wxPoint(650, 550), wxSize(200, 30));
    email_entry->SetHint("Email (xyz@org.com)");
    email->SetFont(font);

    //password
    wxStaticText* password = new wxStaticText(screen, wxID_ANY, "Password:", wxPoint(1000, 400), wxDefaultSize, wxALIGN_RIGHT);
    wxTextCtrl* password_entry = new wxTextCtrl(screen, wxID_ANY, "", wxPoint(1150, 400), wxSize(200, 30), wxTE_PASSWORD);
    password_entry->SetHint("Password");
    password->SetFont(font);

    wxButton* button = new wxButton(screen, wxID_ANY, "Register", wxPoint(900, 900), wxSize(100,50));
    wxFont button_font = button->GetFont();
    button_font.SetStyle(wxFONTSTYLE_ITALIC);
    button_font.SetPixelSize(wxSize(0,24));
    button->SetFont(button_font);


    //Bind controls with functions
    button->Bind(wxEVT_BUTTON, [screen](wxCommandEvent& evt) {RegisterOrg(screen, ORG_REGISTER, ADMIN_REGISTER); });
    return screen;
}


