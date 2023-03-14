#include "../Tabs.h"

TabWindow setupDiagnosticsWindow(wxWindow* parent)
{
	return 0;
}

void selectDiagnosticsTab(wxWindow* parent, wxWindow* tab, wxWindow* tabWindow)
{
	//condition to prevent unnecessary changes when clicking the same tab
	if (tabWindow->GetId() != 2)
	{
		//TabWindow tabContent = setupDiagnosticsWindow(parent);
		//delete tabWindow;
		//tabWindow = tabContent;
		tabWindow->SetId(wxWindowID(2));

		tab->SetBackgroundColour("#000000");
		tab->Refresh();
	}
}

Tab setupDiagnosticsTab(wxWindow* parent, wxWindow* tabWindow)
{
	Tab tab = new wxPanel(parent);
	tab->SetBackgroundColour("#6F6B66");

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	tab->SetSizer(sizer);

	wxStaticText* text = new wxStaticText(tab, wxID_ANY, "Diagonstics", wxDefaultPosition, wxDefaultSize);
	text->SetForegroundColour("white");
	text->SetFont(text->GetFont().Scale(3.0f).MakeBold());
	sizer->Add(text, 1, wxALIGN_CENTER);

	tab->Bind(wxEVT_LEFT_DOWN, [parent, tab, tabWindow](wxMouseEvent& evt) {selectDiagnosticsTab(parent, tab, tabWindow); });

	return tab;
}