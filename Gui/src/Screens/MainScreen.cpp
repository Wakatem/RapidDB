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

    bool userIsAdmin = true;
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
    TabWindow tabWindow = new wxPanel(screen);
    

    //Create tabs
    Tab UserInfoTab = setupUserInfoTab(screen, tabWindow);
    Tab DatabasesTab = setupDatabasesTab(screen, tabWindow);
    Tab DiagnosticsTab = setupDiagnosticsTab(screen, tabWindow);
    Tab Reports = setupReportsTab(screen, tabWindow);
    Tab SettingsTab = setupSettingsTab(screen, tabWindow);
    
    Tab UsersManagementTab = nullptr;
    userIsAdmin ? UsersManagementTab = setupUsersManagementTab(screen, tabWindow) : NULL;


    //Add tabs
    tabsSizer->Add(UserInfoTab, 1, wxEXPAND);
    tabsSizer->Add(DatabasesTab, 1, wxEXPAND);
    tabsSizer->Add(DiagnosticsTab, 1, wxEXPAND);
    tabsSizer->Add(Reports, 1, wxEXPAND);
    userIsAdmin ? tabsSizer->Add(UsersManagementTab, 1, wxEXPAND) : NULL;
    tabsSizer->Add(SettingsTab, 1, wxEXPAND);


    //Add tabs list and tab window to parent sizer
    sizer->Add(tabsSizer, 1, wxEXPAND);
    sizer->Add(tabWindow, 3, wxEXPAND);

    return screen;
}