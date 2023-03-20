#include "../../headers/Tabs.h"

wxPanel* databaseBox(wxWindow* parent)
{
	return NULL;
}


TabWindow setupDatabasesWindow(wxWindow* parent)
{
	wxPanel* window = new wxPanel(parent);
	wxBoxSizer* windowSizer = new wxBoxSizer(wxVERTICAL);
	
	//CONTENT HERE
	wxBoxSizer* sizer1 = new wxBoxSizer(wxHORIZONTAL);
	window->SetSizer(sizer1);
	wxBoxSizer* sizer2 = new wxBoxSizer(wxVERTICAL);



	//sizer2->Add(text, 0, wxCENTER);
	sizer1->Add(sizer2, 1, wxALIGN_CENTER);

	parent->SetSizer(windowSizer);
	windowSizer->Add(window, 1, wxEXPAND);
	return window;
}

void selectDatabasesTab(wxWindow* parent, wxWindow* tab, wxWindow* tabWindow)
{
	//condition to prevent unnecessary changes when clicking the same tab
	if (tabWindow->GetId() != 1)
	{
		activateTab(tabWindow->GetId(), DATABASES, tabWindow);
		tabWindow->SetId(wxWindowID(DATABASES));

		//Replace existing tab window
		bool tabRemoved = tabWindow->DestroyChildren();
		if (tabRemoved)
			TabWindow tabContent = setupDatabasesWindow(tabWindow);
		else
			wxLogError("Cannot open tab");
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
	setupDatabasesWindow(tabWindow);
	tabWindow->SetId(DATABASES);
	

	text->Bind(wxEVT_LEFT_DOWN, [parent, tab, tabWindow](wxMouseEvent& evt) {selectDatabasesTab(parent, tab, tabWindow); });
	tab->Bind(wxEVT_LEFT_DOWN, [parent, tab, tabWindow](wxMouseEvent& evt) {selectDatabasesTab(parent, tab, tabWindow); });

	return tab;
}