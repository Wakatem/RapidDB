#include "../Screens.h"

/////////////////////////////////////////			User Input Control Functions		///////////////////////////////////////////////////


void RegisterAdmin()
{
    wxLogMessage("Admin Registered");
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
    wxStaticBitmap* bitmapImage = new wxStaticBitmap(screen, wxID_ANY, wxBitmap(wxImage("C:\\Users\\moody\\Desktop\\icon.png", wxBITMAP_TYPE_PNG).Rescale(350, 350, wxIMAGE_QUALITY_HIGH)));


    wxStaticText* text = new wxStaticText(screen, wxID_ANY, "Admin Registration", wxDefaultPosition, wxDefaultSize);
    text->SetPosition(DIP_POINT(489, 300, text));
    text->SetFont(text->GetFont().Scale(2.0).MakeUnderlined());


    wxButton* button = new wxButton(screen, wxID_ANY, "Register Admin");

    //Bind controls with functions and add controls to sizer
    button->Bind(wxEVT_BUTTON, [](wxCommandEvent& evt) {RegisterAdmin(); });
    sizer->Add(bitmapImage, 0, wxALIGN_CENTER);
    sizer->Add(button, 0, wxALIGN_TOP | wxRIGHT);
    
    
    return screen;
}