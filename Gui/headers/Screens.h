#pragma once

#include <wx/wxprec.h>
#include <wx/stdpaths.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <vector>
#include <tuple>
#include <string>

#define ASSESTS(assestName) wxStandardPaths::Get().GetDataDir().erase(wxStandardPaths::Get().GetDataDir().find("RapidDB") + 7).append("\\resources\\assets\\").append(assestName)
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

extern vector<tuple<Screen, ScreenID>> screensReference;
void shiftScreen(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID, bool destroyCurrentScreen, wxShowEffect animation, int animationDuration = 0U);


//Setup functions for screens
Screen setupOrganizationRegister(wxWindow* parent);
Screen setupAdminRegister(wxWindow* parent);
Screen setOrg(wxWindow* parent);
Screen setupLogin(wxWindow* parent);
Screen OrganizationSigin(wxWindow* parent);
Screen setupMainScreen(wxWindow* parent);