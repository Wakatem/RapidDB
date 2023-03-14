#include "../Tabs.h"

TabWindow setupUserInfoScreen(wxWindow* parent)
{
	return 0;
}
void selectUserInfoTab(wxWindow* parent, wxWindow* tab, wxWindow* tabWindow)
{
	//condition to prevent unnecessary changes when clicking the same tab
	if (tabWindow->GetId() != 0)
	{
		TabWindow tabContent = setupUserInfoScreen(parent);
		delete tabWindow;
		tabWindow = tabContent;
		tabWindow->SetId(wxWindowID(0));

		tab->SetBackgroundColour("#000000");
		tab->Refresh();
	}
}

Tab setupUserInfoTab(wxWindow* parent, wxWindow* tabWindow)
{
	Tab tab = new wxPanel(parent);
	tab->SetId(wxWindowID(0));
	tab->SetBackgroundColour("#6F6B66");
	tab->Bind(wxEVT_LEFT_DOWN, [parent, tab, tabWindow](wxMouseEvent& evt) {selectUserInfoTab(parent, tab, tabWindow); });

	return tab;
}