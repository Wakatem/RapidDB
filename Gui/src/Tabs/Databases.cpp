#include "../Tabs.h"

TabWindow setupDatabasesWindow(wxWindow* parent)
{
	wxPanel* window = new wxPanel(parent);
	window->SetSize(parent->GetSize());

	//CONTENT HERE

	wxStaticText* text = new wxStaticText(window, wxID_ANY, "Databases content here", wxDefaultPosition, wxDefaultSize);
	text->SetFont(text->GetFont().Scale(2.2f).MakeUnderlined());
	return window;
}

void selectDatabasesTab(wxWindow* parent, wxWindow* tab, wxWindow* tabWindow)
{
	//condition to prevent unnecessary changes when clicking the same tab
	if (tabWindow->GetId() != 1)
	{
		//Replace existing tab
		bool tabRemoved = tabWindow->DestroyChildren();
		if (tabRemoved)
			TabWindow tabContent = setupDatabasesWindow(tabWindow);
		else
			wxLogError("Cannot open tab");
		tabWindow->SetId(wxWindowID(DATABASES));
		activateTab(DATABASES, tabWindow);
	}

}

Tab setupDatabasesTab(wxWindow* parent, wxWindow* tabWindow)
{
	Tab tab = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
	tab->SetBackgroundColour("#42403D");

	wxBoxSizer* sizer1 = new wxBoxSizer(wxHORIZONTAL);
	tab->SetSizer(sizer1);
	wxBoxSizer* sizer2 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* text = new wxStaticText(tab, DATABASES_TITLE, "Databases", wxDefaultPosition);
	text->SetForegroundColour("white");
	text->SetFont(text->GetFont().Scale(2.7f).MakeBold());
	
	sizer2->Add(text, 0, wxCENTER);
	sizer1->Add(sizer2, 1, wxALIGN_CENTER);

	//On first load, databases tab is the default
	TabWindow tabContent = setupDatabasesWindow(tabWindow);

	text->Bind(wxEVT_LEFT_DOWN, [parent, tab, tabWindow](wxMouseEvent& evt) {selectDatabasesTab(parent, tab, tabWindow); });
	tab->Bind(wxEVT_LEFT_DOWN, [parent, tab, tabWindow](wxMouseEvent& evt) {selectDatabasesTab(parent, tab, tabWindow); });

	return tab;
}