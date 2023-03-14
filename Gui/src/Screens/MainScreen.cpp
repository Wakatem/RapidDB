#include "../Screens.h"
#include "../Tabs.h"

vector<Tab> tabsReference;

/////////////////////////////////////////			User Input Control Functions		///////////////////////////////////////////////////




/////////////////////////////////////////		    	GUI Elements Functions		    ///////////////////////////////////////////////////



void activateTab(int newTabWindowID, wxWindow* tabWindow)
{
    for (int i = 0; i < tabsReference.size(); i++)
    {
        Tab t = tabsReference[i];
        wxWindow* title;

        //Detect which tab is currently active
        switch (tabWindow->GetId())
        {
        case DATABASES:
            title = t->GetWindowChild(DATABASES_TITLE);
            break;
        case DIAGNOSTICS:
            title = t->GetWindowChild(DIAGNOSTICS_TITLE);
            break;
        case REPORTS:
            title = t->GetWindowChild(REPORTS_TITLE);
            break;
        case USERSMANAGEMENT:
            title = t->GetWindowChild(USERSMANAGEMENT);
            break;
        case SETTINGS:
            title = t->GetWindowChild(SETTINGS_TITLE);
            break;
        default:
            title = nullptr;
            break;
        }

        //update selected tab style
        if (i == newTabWindowID)
        {
            if (title != nullptr)
                title->SetFont(title->GetFont().Scale(2.7f).MakeBold());
            continue;
        }

        //update "un-selected" tab style
        if (title != nullptr)
            title->SetFont(title->GetFont().Scale(2.1f));
    }
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


    //Add tabs to list
    tabsReference.push_back(UserInfoTab);
    tabsReference.push_back(DatabasesTab);
    tabsReference.push_back(DiagnosticsTab);
    tabsReference.push_back(Reports);
    tabsReference.push_back(UsersManagementTab);    // must be at index 4
    tabsReference.push_back(SettingsTab);

    //Add tabs to sizer
    tabsSizer->Add(UserInfoTab, 2, wxEXPAND);
    tabsSizer->Add(DatabasesTab, 3, wxEXPAND);
    tabsSizer->Add(DiagnosticsTab, 3, wxEXPAND);
    tabsSizer->Add(Reports, 3, wxEXPAND);
    userIsAdmin ? tabsSizer->Add(UsersManagementTab, 3, wxEXPAND) : NULL;
    tabsSizer->Add(SettingsTab, 3, wxEXPAND);


    //Add tabs list and tab window to parent sizer
    sizer->Add(tabsSizer, 1, wxEXPAND);
    sizer->Add(tabWindow, 3, wxEXPAND);

    return screen;
}