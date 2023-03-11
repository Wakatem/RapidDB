#include "../Screens.h"

/////////////////////////////////////////			User Input Control Functions		///////////////////////////////////////////////////


void RegisterAdmin()
{
    wxLogMessage("Admin Registered");
}


/////////////////////////////////////////		    	GUI Elements Functions		    ///////////////////////////////////////////////////


wxBoxSizer* textInput(wxWindow* screen, wxString title, int marginHorizontally = 40)
{
    wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

    wxStaticText* username = new wxStaticText(screen, wxID_ANY, title, wxDefaultPosition, wxDefaultSize);
    username->SetFont(username->GetFont().Scale(1.2).MakeBold());


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
    username->SetFont(username->GetFont().Scale(1.2).MakeBold());


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

    //Implement screen content
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    screen->SetSizer(sizer);


    wxPNGHandler* p = new wxPNGHandler();
    wxImage::AddHandler(p);
    wxStaticBitmap* bitmapImage = new wxStaticBitmap(screen, wxID_ANY, wxBitmap(wxImage("C:\\Users\\moody\\Desktop\\icon.png", wxBITMAP_TYPE_PNG).Rescale(300, 300, wxIMAGE_QUALITY_HIGH)));


    wxStaticText* text = new wxStaticText(screen, wxID_ANY, "Admin Registration", wxDefaultPosition, wxDefaultSize);
    text->SetPosition(DIP_POINT(485, 260, text));
    text->SetFont(text->GetFont().Scale(2.2).MakeUnderlined());
    

    wxSizer* inputs = rowInputs(screen);
    wxButton* button = new wxButton(screen, wxID_ANY, "Register Admin");
    button->SetBackgroundColour("#AEB6BF");
    button->SetMinSize(DIP_SIZE(200, 80, button));
    button->SetFont(button->GetFont().Scale(1.8).MakeItalic());

    //Bind controls with functions and add controls to sizer
    button->Bind(wxEVT_BUTTON, [](wxCommandEvent& evt) {RegisterAdmin(); });
    sizer->Add(bitmapImage, 0, wxALIGN_CENTER_HORIZONTAL);
    sizer->Add(0, 120);
    sizer->Add(inputs, 0, wxALIGN_CENTER);
    sizer->Add(0, 130);
    sizer->Add(button, 0, wxCENTER);
    
    
    return screen;
}