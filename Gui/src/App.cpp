
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


    //Remove object of current screen
    if (destroyCurrentScreen)
    {
        currentScreen->Destroy();
        screensReference.erase(screensReference.begin()+currentScreenIndex);
    }
    else
    {
        //Hide current screen
        currentScreen->Show(false);
    }

    //Display next screen
    nextScreen->Show(true);
    wxLogMessage(wxString(std::to_string(screensReference.size())));
}


bool MyApp::OnInit()
{

    wxString* title = new wxString("RapidDB");
    MainFrame* mainWindow = new MainFrame(*title);
    Screen OrgRegister = setupOrganizationRegister(mainWindow);
    Screen AdminRegister = setupAdminRegister(mainWindow);

    mainWindow->Show(true);
    return true;
}



