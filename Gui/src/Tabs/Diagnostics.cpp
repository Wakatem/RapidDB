#include "../Tabs.h"

TabWindow setupDiagnosticsWindow(wxWindow* parent)
{
	return 0;
}

Tab setupDiagnosticsTab(wxWindow* parent)
{
	Tab userInfoTab = new wxPanel(parent);
	userInfoTab->SetBackgroundColour("#6F6B66");


	return userInfoTab;
}