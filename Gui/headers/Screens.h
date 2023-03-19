#pragma once

#include <wx/wxprec.h>
#include <wx/stdpaths.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <vector>
#include <tuple>
#include <string>
#include <Organization.h>
#include "RDBManagers.h"

//if in release mode
#if NDEBUG
	#define ASSESTS(assestName) wxStandardPaths::Get().GetDataDir().append("\\assets\\").append(assestName)
	#define RDB_DATA(filename) wxStandardPaths::Get().GetDataDir().append("\\data\\").append(filename)
#else
	#define ASSESTS(assestName) wxStandardPaths::Get().GetDataDir().erase(wxStandardPaths::Get().GetDataDir().find("RapidDB") + 7).append("\\resources\\assets\\").append(assestName)
#endif

//#define ASSESTS(assestName) wxStandardPaths::Get().GetDataDir().erase(wxStandardPaths::Get().GetDataDir().find("RapidDB") + 7).append("\\resources\\assets\\").append(assestName)
#define DPI_SIZE(width, height, window) wxWindow::FromDIP(wxSize(width, height), window)
#define DPI_POINT(x, y, window) wxWindow::FromDIP(wxPoint(x, y), window)
#define DPI_X(xValue, window) wxWindow::FromDIP(xValue, window)
#define DPI_Y(yValue, window) wxWindow::FromDIP(yValue, window)

typedef wxPanel* Screen;
typedef wxPanel* Tab;
typedef wxPanel* TabWindow;
using std::vector;
using std::tuple;
using std::make_tuple;

//Each screen must have a unique ScreenID assigned to it!
enum ScreenID
{
	ORG_SETUP,
	ORG_REGISTER,
	ORG_SIGN_IN,
	ADMIN_REGISTER,
	LOGIN,
	MAIN
};

enum ScreenItemIDS
{
	ORG_SIGN_ORG_NAME
};

extern vector<tuple<Screen, ScreenID>> screensReference;
void shiftScreen(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID, bool destroyCurrentScreen, wxShowEffect animation, int animationDuration = 0U);
void refreshScreenValues(Screen nextScreen, ScreenID nextScreenID);

//Setup functions for screens
Screen setupOrganizationRegister(wxWindow* parent, shared_ptr<Organization> org);
Screen setupAdminRegister(wxWindow* parent, shared_ptr<Organization> org);
Screen setOrg(wxWindow* parent);
Screen setupLogin(wxWindow* parent, shared_ptr<Organization> org, shared_ptr<User> user);
Screen OrganizationSignin(wxWindow* parent, shared_ptr<Organization> org, shared_ptr<User> user);
Screen setupMainScreen(wxWindow* parent);