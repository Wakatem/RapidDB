
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
        nextScreen->GetContainingSizer()->Layout();     //Align new screen on the window



        //Remove object of current screen
        //if (destroyCurrentScreen)
        //{
        //    currentScreen->Destroy();
        //    screensReference.erase(screensReference.begin() + currentScreenIndex);
        //}
        //else
        //{
        //    //Hide current screen
        //    currentScreen->Show(false);
        //}

    }
    catch (const std::exception&)
    {
        wxLogMessage("Unable to go to previous screen");
    }
}



bool MyApp::OnInit()
{
    RDBFileManager::addPaths("", "", wxStandardPaths::Get().GetDataDir().append("\\data\\").ToStdString(), "");
    RDBFileManager::createFolders();

    shared_ptr<Organization> org = std::make_shared<Organization>();
    shared_ptr<User> user = std::make_shared<User>();


    //Main frame setup
    wxString* title = new wxString("RapidDB");
    MainFrame* mainWindow = new MainFrame(*title);
    wxString logoPath = ASSESTS("icon.ico");
    mainWindow->SetIcon(wxIcon(logoPath, wxBITMAP_TYPE_ICO));

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    mainWindow->SetSizer(mainSizer);


    Screen OrgSet = setOrg(mainWindow);
    Screen OrgRegister = setupOrganizationRegister(mainWindow, org);
    Screen AdminRegister = setupAdminRegister(mainWindow, org, user);
    Screen OrgSign = OrganizationSigin(mainWindow);
    Screen Login = setupLogin(mainWindow);
    Screen MainScreen = setupMainScreen(mainWindow);

    mainSizer->Add(OrgSet, 1, wxEXPAND);
    mainSizer->Add(OrgRegister, 1, wxEXPAND);
    mainSizer->Add(AdminRegister, 1, wxEXPAND);
    mainSizer->Add(OrgSign, 1, wxEXPAND);
    mainSizer->Add(Login, 1, wxEXPAND);
    mainSizer->Add(MainScreen, 1, wxEXPAND);



    mainWindow->Show(true);
    return true;
}
