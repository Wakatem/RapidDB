#include "../Screens.h"
#include "../Tabs.h"

/////////////////////////////////////////			User Input Control Functions		///////////////////////////////////////////////////




/////////////////////////////////////////		    	GUI Elements Functions		    ///////////////////////////////////////////////////



void activateTab(Tab selectedTab, TabWindow selectedWindow, TabWindow tabWindow)
{

    tabWindow = selectedWindow;
}

/////////////////////////////////////////			                            		///////////////////////////////////////////////////



Screen setupMainScreen(wxWindow* parent)
{

    bool userIsAdmin = false;
    //Create screen parameters
    Screen screen = new wxPanel(parent);
    screen->SetSize(parent->GetSize());
    //screen->Hide();
    screen->SetBackgroundColour(wxColor("#FFF"));

    //Add screen pointer to list
    ScreenID previousScreen = LOGIN;
    ScreenID currentScreen = MAIN;
    screensReference.push_back(make_tuple(screen, currentScreen));


    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    screen->SetSizer(sizer);

    wxBoxSizer* tabsSizer = new wxBoxSizer(wxVERTICAL);

    Tab UserInfoTab = setupUserInfoTab(screen);
    Tab DatabasesTab = setupDatabasesTab(screen);
    Tab DiagnosticsTab = setupDiagnosticsTab(screen);
    Tab Reports = setupReportsTab(screen);
    Tab UsersManagementTab = nullptr;
    if (userIsAdmin)
    {
        Tab UsersManagementTab = setupUsersManagementTab(screen);
    }
    Tab SettingsTab = setupSettingsTab(screen);


    tabsSizer->Add(UserInfoTab, 1, wxEXPAND);
    tabsSizer->Add(DatabasesTab, 1, wxEXPAND);
    tabsSizer->Add(DiagnosticsTab, 1, wxEXPAND);
    tabsSizer->Add(Reports, 1, wxEXPAND);
    userIsAdmin ? tabsSizer->Add(UsersManagementTab, 1, wxEXPAND) : NULL;
    tabsSizer->Add(SettingsTab, 1, wxEXPAND);


    TabWindow tabWindow = new wxPanel(screen);

    //activateTab(DatabasesTab, DatabasesWindow, tabWindow);

    sizer->Add(tabsSizer, 1, wxEXPAND);
    sizer->Add(tabWindow, 3, wxEXPAND);

    return screen;
}