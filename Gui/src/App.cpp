
#include "MainFrame.h"
#include "Screens.h"

using std::get;
vector<tuple<Screen, ScreenID>> screensReference;

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

wxIMPLEMENT_APP(MyApp);


void shiftScreen(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID, bool destroyCurrentScreen)
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
        nextScreen->Show(true);

        //Remove object of current screen
        if (destroyCurrentScreen)
        {
            currentScreen->Destroy();
            screensReference.erase(screensReference.begin() + currentScreenIndex);
        }
        else
        {
            //Hide current screen
            currentScreen->Show(false);
        }
    }
    catch (const std::exception&)
    {
        wxLogMessage("Unable to go to previous screen");
    }
}


bool MyApp::OnInit()
{

    wxString* title = new wxString("RapidDB");
    MainFrame* mainWindow = new MainFrame(*title);
    wxString logoPath = ASSESTS("icon.ico");
    mainWindow->SetIcon(wxIcon(logoPath, wxBITMAP_TYPE_ICO));

    //Screen OrgRegister = setupOrganizationRegister(mainWindow);
    Screen AdminRegister = setupAdminRegister(mainWindow); 
    //Screen OrgSet = setOrg(mainWindow);

    mainWindow->Show(true);
    return true;
}



