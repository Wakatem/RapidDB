#include "MainFrame.h"

MainFrame::MainFrame(wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	//Set window size
	SetSize(this->FromDIP(wxSize(1200, 700)));
}