#include "../Tabs.h"

TabWindow setupUserInfoScreen(wxWindow* parent)
{
	wxPanel* window = new wxPanel(parent);
	window->SetSize(parent->GetSize());

	//CONTENT HERE

	wxStaticText* text = new wxStaticText(window, wxID_ANY, "The whole screen should change once the settings icon is clicked, not the entire box", wxDefaultPosition, wxDefaultSize);
	text->SetFont(text->GetFont().Scale(2.2f).MakeUnderlined());
	return window;
}
void selectUserInfoTab(wxWindow* parent, wxWindow* tab, wxWindow* tabWindow)
{
	//condition to prevent unnecessary changes when clicking the same tab
	if (tabWindow->GetId() != 0)
	{
		//Replace existing tab
		bool tabRemoved = tabWindow->DestroyChildren();
		if (tabRemoved)
			TabWindow tabContent = setupUserInfoScreen(tabWindow);
		else
			wxLogError("Cannot open tab");
		tabWindow->SetId(wxWindowID(0));

		tab->SetBackgroundColour("#000000");
		tab->Refresh();
	}
}

Tab setupUserInfoTab(wxWindow* parent, wxWindow* tabWindow)
{
	Tab tab = new wxPanel(parent);
	tab->SetBackgroundColour("#6F6B66");

	//tab->Bind(wxEVT_LEFT_DOWN, [parent, tab, tabWindow](wxMouseEvent& evt) {selectUserInfoTab(parent, tab, tabWindow); });

	return tab;
}