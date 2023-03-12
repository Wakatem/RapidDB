#include "../Screens.h"

/////////////////////////////////////////			User Input Control Functions		///////////////////////////////////////////////////


void goBackToScreen(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID)
{
    wxMessageDialog* dialog = new wxMessageDialog(currentScreen, "Inputs will be reset. Are you sure you want to leave?", wxString::FromAscii(wxMessageBoxCaptionStr), wxOK | wxCANCEL);

    if (dialog->ShowModal() == wxID_OK)
        shiftScreen(currentScreen, currentScreenID, nextScreenID, true);
    
}

void RegisterAdmin()
{
    wxLogMessage("Admin Registered");
}


/////////////////////////////////////////		    	GUI Elements Functions		    ///////////////////////////////////////////////////


wxBoxSizer* textInput(wxWindow* screen, wxString title, int marginHorizontally = 40)
{
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* username = new wxStaticText(screen, wxID_ANY, title, wxDefaultPosition, wxDefaultSize);
    username->SetFont(username->GetFont().Scale(1.2f).MakeBold());


    wxTextCtrl* usernameInput = new wxTextCtrl(screen, wxID_ANY);
    usernameInput->SetMinSize(DIP_SIZE(220, 25, usernameInput));
    usernameInput->SetBackgroundColour("#E5E7E9");


    inputSizer->Add(username);
    inputSizer->Add(marginHorizontally, 0);       //Adding space in pixels
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
    inputSizer->Add(40, 0);       //Adding space in pixels
    inputSizer->Add(choiceMenu, 1);
    return inputSizer;
}

wxSizer* rowInputs(wxWindow* screen)
{
    wxFlexGridSizer* rowSizer = new wxFlexGridSizer(3, 50, 100);
    
    wxBoxSizer* textInput1 = textInput(screen, "First Name :");
    wxBoxSizer* textInput2 = textInput(screen, "Last Name :");

    rowSizer->Add(textInput1);
    rowSizer->Add(textInput2);
    rowSizer->Add(200, 0);



    wxBoxSizer* textInput3 = textInput(screen, "Phone NO :", 50);
    wxBoxSizer* textInput4 = textInput(screen, "Email :", 110);
    wxBoxSizer* choiceMenu = choicesBox(screen);
    wxBoxSizer* textInput5 = textInput(screen, "Username :", 50);
    wxBoxSizer* textInput6 = textInput(screen, "Password :", 50);

    rowSizer->Add(textInput3, 1);
    rowSizer->Add(textInput4);
    rowSizer->Add(choiceMenu);
    rowSizer->Add(textInput5);
    rowSizer->Add(textInput6);

    return rowSizer;
}


/////////////////////////////////////////			                            		///////////////////////////////////////////////////



Screen setupAdminRegister(wxWindow* parent)
{
    //Create screen parameters
    Screen screen = new wxPanel(parent);
    screen->SetSize(parent->GetSize());
    screen->Show(true);
    screen->SetBackgroundColour(wxColor("#FFFFFF"));

    //Add screen pointer to list
    screensReference.push_back(make_tuple(screen, ADMIN_REGISTER));


    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    screen->SetSizer(sizer);

    wxPNGHandler* p = new wxPNGHandler();
    wxImage::AddHandler(p);
    wxString logoPath = ASSESTS("image.png");
    wxStaticBitmap* bitmapImage = new wxStaticBitmap(screen, wxID_ANY, wxBitmap(wxImage(logoPath, wxBITMAP_TYPE_PNG).Rescale(150, 200, wxIMAGE_QUALITY_HIGH)));


    wxString backButtonPath = ASSESTS("back_button.png");
    wxButton* backButton = new wxButton(screen, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE);
    backButton->SetSize(DIP_SIZE(40, 40, backButton));
    backButton->SetBitmap(wxBitmap(wxImage(backButtonPath, wxBITMAP_TYPE_PNG).Rescale(40, 40, wxIMAGE_QUALITY_HIGH)));
    backButton->SetBackgroundColour("#FFFFFF");
    backButton->SetForegroundColour("#FFFFFF");
    backButton->SetPosition(DIP_POINT(20, 30, backButton));

    //Screen Title
    wxStaticText* text = new wxStaticText(screen, wxID_ANY, "Admin Registration", wxDefaultPosition, wxDefaultSize);
    text->SetPosition(DIP_POINT(483, 250, text));
    text->SetFont(text->GetFont().Scale(2.2f).MakeUnderlined());
    
    //Add input fields and a 'register' button
    wxSizer* inputs = rowInputs(screen);
    wxButton* button = new wxButton(screen, wxID_ANY, "Register Admin");
    button->SetMinSize(DIP_SIZE(200, 80, button));
    button->SetFont(button->GetFont().Scale(1.8f));

    //Bind controls with functions and add controls to sizer
    button->Bind(wxEVT_BUTTON, [](wxCommandEvent& evt) {RegisterAdmin(); });
    backButton->Bind(wxEVT_BUTTON, [screen](wxCommandEvent& evt) {goBackToScreen(screen, ADMIN_REGISTER, ORG_REGISTER); });

    sizer->Add(0, 40);
    sizer->Add(bitmapImage, 0, wxALIGN_CENTER);
    sizer->Add(0, 240);
    sizer->Add(inputs, 0, wxALIGN_CENTER);
    sizer->Add(0, 120);
    sizer->Add(button, 0, wxCENTER);
    
    
    return screen;
}