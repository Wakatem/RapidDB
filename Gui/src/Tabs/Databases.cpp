#include "../../headers/Tabs.h"


wxBoxSizer* textField(wxWindow* parent, wxString title, wxString titleValue, int marginHorizontally, int style = 0L)
{
	wxBoxSizer* inputSizer = new wxBoxSizer(wxHORIZONTAL);

	wxStaticText* databaseName = new wxStaticText(parent, wxID_ANY, title, wxDefaultPosition, wxDefaultSize);
	databaseName->SetFont(databaseName->GetFont().Scale(1.2f).MakeUnderlined());


	wxStaticText* databaseNameField = new wxStaticText(parent, wxID_ANY, titleValue, wxDefaultPosition, wxDefaultSize);
	databaseNameField->SetFont(databaseNameField->GetFont().Scale(1.7f));


	inputSizer->Add(databaseName, 0, wxALIGN_CENTER);
	inputSizer->Add(DPI_X(marginHorizontally, parent), 0);       //Adding space in pixels
	inputSizer->Add(databaseNameField, 0, wxALIGN_CENTER);
	return inputSizer;
}


wxPanel* databaseBox(wxWindow* windowParent, Database& db)
{
	wxPanel* box = new wxPanel(windowParent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE);
	box->SetMinSize(DPI_SIZE(390, 130, windowParent));
	box->SetBackgroundColour("#e7e2db");

	wxBoxSizer* boxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	box->SetSizer(boxSizer1);
	wxBoxSizer* boxSizer2 = new wxBoxSizer(wxVERTICAL);


	wxPNGHandler* p = new wxPNGHandler();
	wxImage::AddHandler(p);
	wxString logoPath = ASSESTS("oracle_icon.png");
	wxStaticBitmap* bitmapImage = new wxStaticBitmap(box, wxID_ANY, wxBitmap(wxImage(logoPath, wxBITMAP_TYPE_PNG).Rescale(100, 100, wxIMAGE_QUALITY_HIGH)));


	wxBoxSizer* name = textField(box, "Name:", db.getName(), 10);
	wxBoxSizer* name2 = textField(box, "Type:", db.getType(), 5);
	wxBoxSizer* name3 = textField(box, "Location:", db.getLocationText(), 10);

	boxSizer2->Add(name, 0, wxALIGN_CENTER);
	boxSizer2->Add(name2, 0, wxALIGN_CENTER);
	boxSizer2->Add(name3, 0, wxALIGN_CENTER);

	boxSizer1->Add(DPI_X(30, box), 0);
	boxSizer1->Add(bitmapImage, 0, wxALIGN_CENTER);
	boxSizer1->Add(DPI_X(20, box), 0);
	boxSizer1->Add(boxSizer2, 0, wxALIGN_CENTER);
	return box;
}


TabWindow setupDatabasesWindow(wxWindow* parent, shared_ptr<Organization> org)
{
	wxPanel* window = new wxPanel(parent);
	
	//determine number of databases and create rows accordingly
	int rows = org->getDatabases().size() / 2;
	rows += 2; //+1 for the space above, and +1 for the odd row

	wxBoxSizer* sizer1 = new wxBoxSizer(wxHORIZONTAL);
	window->SetSizer(sizer1);
	wxFlexGridSizer* sizer2 = new wxFlexGridSizer(rows, 2, 70, 50);
	sizer1->Add(DPI_X(20, window), 0);
	sizer1->Add(sizer2, 1);
	sizer2->Add(0, DPI_Y(1, window));
	sizer2->Add(0, DPI_Y(1, window));


	//MAIN CONTENT HERE
	for (auto& db : org->getDatabases())
	{
		sizer2->Add(databaseBox(window, db));
	}


	wxButton* addButton = new wxButton(window, wxID_ANY, "Add a database");
	addButton->SetPosition(DPI_POINT(600, 600, addButton));
	addButton->SetMinSize(DPI_SIZE(210, 100, addButton));
	addButton->SetFont(addButton->GetFont().Scale(1.2f));
	addButton->Raise();

	wxBoxSizer* windowSizer = new wxBoxSizer(wxVERTICAL);
	parent->SetSizer(windowSizer);
	windowSizer->Add(window, 1, wxEXPAND);
	parent->Layout();
	return window;
}

void selectDatabasesTab(wxWindow* parent, wxWindow* tab, wxWindow* tabWindow, shared_ptr<Organization> org)
{
	//condition to prevent unnecessary changes when clicking the same tab
	if (tabWindow->GetId() != 1)
	{
		activateTab(tabWindow->GetId(), DATABASES, tabWindow);
		tabWindow->SetId(wxWindowID(DATABASES));

		//Replace existing tab window
		bool tabRemoved = tabWindow->DestroyChildren();
		if (tabRemoved)
			TabWindow tabContent = setupDatabasesWindow(tabWindow, org);
		else
			wxLogError("Cannot open tab");
	}

}

Tab setupDatabasesTab(wxWindow* parent, wxWindow* tabWindow, shared_ptr<Organization> org)
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
	setupDatabasesWindow(tabWindow, org);
	tabWindow->SetId(DATABASES);
	

	text->Bind(wxEVT_LEFT_DOWN, [parent, tab, tabWindow, org](wxMouseEvent& evt) {selectDatabasesTab(parent, tab, tabWindow, org); });
	tab->Bind(wxEVT_LEFT_DOWN, [parent, tab, tabWindow, org](wxMouseEvent& evt) {selectDatabasesTab(parent, tab, tabWindow, org); });

	return tab;
}