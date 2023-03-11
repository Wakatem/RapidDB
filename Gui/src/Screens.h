#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <vector>
#include <tuple>
#include <string>

#define DIP_SIZE(width, height, window) wxWindow::FromDIP(wxSize(width, height), window)
#define DIP_POINT(x, y, window) wxWindow::FromDIP(wxPoint(x, y), window)

typedef wxPanel* Screen;
using std::vector;
using std::tuple;
using std::make_tuple;

//Each screen must have a unique ScreenID assigned to it!
enum ScreenID
{
	ORG_REGISTER,
	ADMIN_REGISTER,
};

extern vector<tuple<Screen, ScreenID>> screensReference;
void shiftScreen(Screen currentScreen, ScreenID currentScreenID, ScreenID nextScreenID, bool destroyCurrentScreen);


//Setup functions for screens
Screen setupOrganizationRegister(wxWindow* parent);
Screen setupAdminRegister(wxWindow* parent);