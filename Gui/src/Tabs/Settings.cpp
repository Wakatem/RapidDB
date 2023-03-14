#include "../Tabs.h"

TabWindow setupSettingsWindow(wxWindow* parent)
{
	return 0;
}

Tab setupSettingsTab(wxWindow* parent)
{
	Tab userInfoTab = new wxPanel(parent);
	userInfoTab->SetBackgroundColour("#6F6B66");


	return userInfoTab;
}