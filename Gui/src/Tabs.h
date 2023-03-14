#pragma once

#include <wx/wxprec.h>
#include <wx/stdpaths.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <vector>
#include <tuple>
#include <string>

#define DPI_SIZE(width, height, window) wxWindow::FromDIP(wxSize(width, height), window)
#define DPI_POINT(x, y, window) wxWindow::FromDIP(wxPoint(x, y), window)
#define DPI_X(xValue, window) wxWindow::FromDIP(xValue, window)
#define DPI_Y(yValue, window) wxWindow::FromDIP(yValue, window)

typedef wxPanel* Tab;
typedef wxPanel* TabWindow;
using std::vector;
using std::tuple;
using std::make_tuple;


//Each tab must have a unique ScreenID assigned to it!
enum TabID
{
	DATABASES
};

extern vector<tuple<Tab, TabID>> tabsReference;
void shiftTab(Tab currentScreen, Tab currentScreenID, Tab nextScreenID, bool destroyCurrentScreen, wxShowEffect animation, int animationDuration = 0U);


//Setup functions for tabs and corresponding tab window
Tab setupUserInfoTab(wxWindow* parent);
TabWindow setupUserInfoScreen(wxWindow* parent);

Tab setupDatabasesTab(wxWindow* parent);
TabWindow setupDatabasesWindow(wxWindow* parent);

Tab setupDiagnosticsTab(wxWindow* parent);
TabWindow setupDiagnosticsWindow(wxWindow* parent);

Tab setupReportsTab(wxWindow* parent);
TabWindow setupReportsWindow(wxWindow* parent);

Tab setupUsersManagementTab(wxWindow* parent);
TabWindow setupUsersManagementWindow(wxWindow* parent);

Tab setupSettingsTab(wxWindow* parent);
TabWindow setupSettingsWindow(wxWindow* parent);