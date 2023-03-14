#include "../Tabs.h"

TabWindow setupDatabasesWindow(wxWindow* parent)
{
	wxPanel* window = new wxPanel(parent);
	window->SetSize(parent->GetSize());

	wxStaticText* text = new wxStaticText(window, wxID_ANY, "Databases content here", wxDefaultPosition, wxDefaultSize);
	text->SetFont(text->GetFont().Scale(2.2f).MakeUnderlined());
	return window;
}

void selectDatabasesTab(wxWindow* parent, wxWindow* tab, wxWindow* tabWindow)
{
	//condition to prevent unnecessary changes when clicking the same tab
	if (tabWindow->GetId() != 1)
	{
		TabWindow tabContent = setupDatabasesWindow(parent);
		delete tabWindow;
		tabWindow = tabContent;
		tabWindow->SetId(wxWindowID(1));

		tab->SetBackgroundColour("#000000");
		tab->Refresh();

		wxLogMessage("new");
	}
	else
	{
		wxLogMessage("sameeeeeeeeee");
	}
}

Tab setupDatabasesTab(wxWindow* parent, wxWindow* tabWindow)
{
	Tab tab = new wxPanel(parent);
	tab->SetBackgroundColour("#6F6B66");

	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	tab->SetSizer(sizer);

	wxStaticText* text = new wxStaticText(tab, wxID_ANY, "Databases", wxDefaultPosition, wxDefaultSize);
	text->SetForegroundColour("white");
	text->SetFont(text->GetFont().Scale(3.0f).MakeBold());
	sizer->Add(text,  1, wxALIGN_CENTER);

	//On first load, databases tab is the default
	//TabWindow tabContent = setupDatabasesWindow(parent);
	//delete tabWindow;
	//tabWindow = tabContent;
	//tabWindow->SetId(wxWindowID(1));

	tab->Bind(wxEVT_LEFT_DOWN, [parent, tab, tabWindow](wxMouseEvent& evt) {selectDatabasesTab(parent, tab, tabWindow); });

	return tab;
}