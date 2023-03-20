#pragma once

#include <wx/wxprec.h>
#include <wx/stdpaths.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <vector>
#include <tuple>
#include <string>
#include "Organization.h"
using namespace std;

#if NDEBUG
#define ASSESTS(assestName) wxStandardPaths::Get().GetDataDir().append("\\assets\\").append(assestName)
#define RDB_DATA(filename) wxStandardPaths::Get().GetDataDir().append("\\data\\").append(filename)
#else
#define ASSESTS(assestName) wxStandardPaths::Get().GetDataDir().erase(wxStandardPaths::Get().GetDataDir().find("RapidDB") + 7).append("\\resources\\assets\\").append(assestName)
#endif

#define DPI_SIZE(width, height, window) wxWindow::FromDIP(wxSize(width, height), window)
#define DPI_POINT(x, y, window) wxWindow::FromDIP(wxPoint(x, y), window)
#define DPI_X(xValue, window) wxWindow::FromDIP(xValue, window)
#define DPI_Y(yValue, window) wxWindow::FromDIP(yValue, window)

typedef wxPanel* Tab;
typedef wxPanel* TabWindow;


//Any tab-related component that needs a unique id, its id must be defined here
enum ComponentID
{
	//Tabs IDs
	USERINFO,
	DATABASES,
	DIAGNOSTICS,
	REPORTS,
	USERSMANAGEMENT,
	SETTINGS,


	//Tab components
	DATABASES_TITLE,
	DIAGNOSTICS_TITLE,
	REPORTS_TITLE,
	USERSMANAGEMENT_TITLE,
	SETTINGS_TITLE,
};


extern vector<Tab> tabsReference;
void activateTab(int previousTabWindowID, int newTabWindowID, wxWindow* tabWindow);

//Setup functions for tabs and corresponding tab window
Tab setupUserInfoTab(wxWindow* parent, wxWindow* tabWindow);
Tab setupDatabasesTab(wxWindow* parent, wxWindow* tabWindow, shared_ptr<Organization> org);
Tab setupDiagnosticsTab(wxWindow* parent, wxWindow* tabWindow);
Tab setupReportsTab(wxWindow* parent, wxWindow* tabWindow);
Tab setupUsersManagementTab(wxWindow* parent, wxWindow* tabWindow);
Tab setupSettingsTab(wxWindow* parent, wxWindow* tabWindow);