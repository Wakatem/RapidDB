#include "../../headers/Tabs.h"
#include <wx/grid.h>
#include "Organization.h"

TabWindow setupUsersManagementWindow(wxWindow* parent)
{
	wxPanel* window = new wxPanel(parent);
	window->SetSize(parent->GetSize());

	wxGrid* grid = new wxGrid(window, wxID_ANY);

	// Set the size and number of rows and columns
	grid->CreateGrid(Organization::getUsers().size(), 3);
	grid->SetRowLabelSize(30);
	grid->SetColLabelSize(30);
	grid->SetDefaultRowSize(25);
	grid->SetDefaultColSize(80);

	wxStaticText* text = new wxStaticText(window, wxID_ANY, "UsersManagement content here", wxDefaultPosition, wxDefaultSize);
	text->SetFont(text->GetFont().Scale(2.2f).MakeUnderlined());
	return window;
}


void selectUsersManagementTab(wxWindow* parent, wxWindow* tab, wxWindow* tabWindow)
{
	//condition to prevent unnecessary changes when clicking the same tab
	if (tabWindow->GetId() != 4)
	{
		activateTab(tabWindow->GetId(), USERSMANAGEMENT, tabWindow);
		tabWindow->SetId(wxWindowID(USERSMANAGEMENT));

		//Replace existing tab window
		bool tabRemoved = tabWindow->DestroyChildren();
		if (tabRemoved)
			TabWindow tabContent = setupUsersManagementWindow(tabWindow);
		else
			wxLogError("Cannot open tab");
	}
}

Tab setupUsersManagementTab(wxWindow* parent, wxWindow* tabWindow)
{
	Tab tab = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
	tab->SetBackgroundColour("#42403D");

	wxBoxSizer* sizer1 = new wxBoxSizer(wxHORIZONTAL);
	tab->SetSizer(sizer1);
	wxBoxSizer* sizer2 = new wxBoxSizer(wxVERTICAL);

	wxStaticText* text = new wxStaticText(tab, USERSMANAGEMENT_TITLE, "Users Management", wxDefaultPosition);
	text->SetForegroundColour("white");
	text->SetFont(text->GetFont().Scale(2.1f));

	sizer2->Add(text, 0, wxCENTER);
	sizer1->Add(sizer2, 1, wxALIGN_CENTER);


	text->Bind(wxEVT_LEFT_DOWN, [parent, tab, tabWindow](wxMouseEvent& evt) {selectUsersManagementTab(parent, tab, tabWindow); });
	tab->Bind(wxEVT_LEFT_DOWN, [parent, tab, tabWindow](wxMouseEvent& evt) {selectUsersManagementTab(parent, tab, tabWindow); });

	return tab;
}