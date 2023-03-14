#include "../Tabs.h"

TabWindow setupDiagnosticsWindow(wxWindow* parent)
{
	wxPanel* window = new wxPanel(parent);
	window->SetSize(parent->GetSize());

	//CONTENT HERE

	wxStaticText* text = new wxStaticText(window, wxID_ANY, "Diagnostics content here", wxDefaultPosition, wxDefaultSize);
	text->SetFont(text->GetFont().Scale(2.2f).MakeUnderlined());
	return window;
}

void selectDiagnosticsTab(wxWindow* parent, wxWindow* tab, wxWindow* tabWindow)
{
	//condition to prevent unnecessary changes when clicking the same tab
	if (tabWindow->GetId() != 2)
	{
		//Replace existing tab
		bool tabRemoved = tabWindow->DestroyChildren();
		if (tabRemoved)
			TabWindow tabContent = setupDiagnosticsWindow(tabWindow);
		else
			wxLogError("Cannot open tab");
		tabWindow->SetId(wxWindowID(2));

		tab->SetBackgroundColour("#000000");
		tab->Refresh();
	}
}

Tab setupDiagnosticsTab(wxWindow* parent, wxWindow* tabWindow)
{
	Tab tab = new wxPanel(parent);
	tab->SetBackgroundColour("#6F6B66");

	wxBoxSizer* sizer1 = new wxBoxSizer(wxHORIZONTAL);
	tab->SetSizer(sizer1);
	wxBoxSizer* sizer2 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* text = new wxStaticText(tab, wxID_ANY, "Diagnostics", wxDefaultPosition);
	text->SetForegroundColour("white");
	text->SetFont(text->GetFont().Scale(2.5f).MakeBold());

	sizer2->Add(text, 0, wxCENTER);
	sizer1->Add(sizer2, 1, wxALIGN_CENTER);

	text->Bind(wxEVT_LEFT_DOWN, [parent, tab, tabWindow](wxMouseEvent& evt) {selectDiagnosticsTab(parent, tab, tabWindow); });
	tab->Bind(wxEVT_LEFT_DOWN, [parent, tab, tabWindow](wxMouseEvent& evt) {selectDiagnosticsTab(parent, tab, tabWindow); });

	return tab;
}