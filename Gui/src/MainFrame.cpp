#include "MainFrame.h"

MainFrame::MainFrame(wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(2000, 1200), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
{
	CreateStatusBar();
}