
#include "../headers/MainFrame.h"
#include "../headers/Screens.h"
#include "RDBManagers.h"
#include "Organization.h"
#include "User.h"

using std::get;
vector<tuple<Screen, ScreenID>> screensReference;

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

IMPLEMENT_APP_CONSOLE(MyApp);

void refreshScreenValues(Screen nextScreen, ScreenID nextScreenID)
{
    if (nextScreenID == ORG_SIGN_IN)
    {
        bool RDBfound = RDBFileManager::findRDBfile();

        if (RDBfound)
        {
            //update org title on screen
            string title = RDBSecurityManager::loadOrgName();
            ( (wxStaticText*) nextScreen->GetWindowChild(ORG_SIGN_ORG_NAME) )->SetLabel(title);
        }
    }
}

void shiftScreen(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID, bool destroyCurrentScreen, wxShowEffect animation, int animationDuration)
{

    try
    {
        int currentScreenIndex;
        Screen nextScreen = nullptr;

        int i = 0;
        for (auto& screenTuple : screensReference)
        {
            if (get<1>(screenTuple) == currentScreenID)
                currentScreenIndex = i;

            if (get<1>(screenTuple) == nextScreenID)
                nextScreen = get<0>(screenTuple);

            i++;
        }


        //Display next screen
        nextScreen == nullptr ? throw std::exception() : NULL;
        //nextScreen->Show(true);
        nextScreen->ShowWithEffect(animation, animationDuration);
        currentScreen->Show(false);
        refreshScreenValues(nextScreen, nextScreenID);
        nextScreen->GetContainingSizer()->Layout();     //Align new screen on the window


    }
    catch (const std::exception&)
    {
        wxLogMessage("Unable to shift screens");
    }
}


void clearInitialScreens()
{
    int i = 0;
    for (auto& screenTuple : screensReference)
    {
        if (get<1>(screenTuple) != MAIN)
        {
            get<0>(screenTuple)->Destroy();
            screensReference.erase(screensReference.begin() + i);
        }

        i++;
    }
}



bool MyApp::OnInit()
{

    RDBFileManager::addPaths(wxStandardPaths::Get().GetDataDir().ToStdString(), ASSESTS("").ToStdString(), wxStandardPaths::Get().GetDataDir().append("\\data\\").ToStdString(), wxStandardPaths::Get().GetDataDir().append("\\reports\\").ToStdString());
    RDBFileManager::createFolders();

    shared_ptr<Organization> org = std::make_shared<Organization>();
    shared_ptr<User> user = std::make_shared<User>();

    //RDBDatabaseManager::addDatabase(*org.get(), Database("OC1", "Oracle", LOCAL, "localhost", 1521, "xepdb1"));
    //RDBDatabaseManager::addDatabase(*org.get(), Database("OC1", "Oracle", LOCAL, "localhost", 1521, "xepdb1"));
    //RDBDatabaseManager::addDatabase(*org.get(), Database("OC1", "Oracle", LOCAL, "localhost", 1521, "xepdb1"));
    //RDBDatabaseManager::addDatabase(*org.get(), Database("OC1", "Oracle", LOCAL, "localhost", 1521, "xepdb1"));
    //RDBDatabaseManager::addDatabase(*org.get(), Database("OC1", "Oracle", LOCAL, "localhost", 1521, "xepdb1"));
    //RDBDatabaseManager::addDatabase(*org.get(), Database("OC1", "Oracle", LOCAL, "localhost", 1521, "xepdb1"));
    //RDBDatabaseManager::addDatabase(*org.get(), Database("OC1", "Oracle", LOCAL, "localhost", 1521, "xepdb1"));
    //RDBDatabaseManager::addDatabase(*org.get(), Database("OC1", "Oracle", LOCAL, "localhost", 1521, "xepdb1"));

    //Main frame setup
    wxString* title = new wxString("RapidDB");
    MainFrame* mainWindow = new MainFrame(*title);
    wxString logoPath = ASSESTS("icon.ico");
    mainWindow->SetIcon(wxIcon(logoPath, wxBITMAP_TYPE_ICO));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainWindow->SetSizer(mainSizer);


    Screen OrgSet = setOrg(mainWindow);
    Screen OrgRegister = setupOrganizationRegister(mainWindow, org);
    Screen AdminRegister = setupAdminRegister(mainWindow, org);
    Screen OrgSign = OrganizationSignin(mainWindow, org, user);
    Screen Login = setupLogin(mainWindow, org, user);
    Screen MainScreen = setupMainScreen(mainWindow, org, user);


    //Automatic login
    bool RDBfound = RDBFileManager::findRDBfile();
    bool RDBUfound = RDBFileManager::findRDBUfile();
    bool automaticLogin = RDBfound && RDBUfound;

    if (automaticLogin)
    {
        clearInitialScreens();
        MainScreen->Show();
        mainSizer->Add(MainScreen, 1, wxEXPAND);
    }

    else
    {
        OrgSet->Show();
        mainSizer->Add(OrgSet, 1, wxEXPAND);
        mainSizer->Add(OrgRegister, 1, wxEXPAND);
        mainSizer->Add(AdminRegister, 1, wxEXPAND);
        mainSizer->Add(OrgSign, 1, wxEXPAND);
        mainSizer->Add(Login, 1, wxEXPAND);
        mainSizer->Add(MainScreen, 1, wxEXPAND);
    }


    mainWindow->Show(true);


    return true;
}
