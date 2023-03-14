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



//Setup functions for tabs and corresponding tab window
Tab setupUserInfoTab(wxWindow* parent, wxWindow* tabWindow);
Tab setupDatabasesTab(wxWindow* parent, wxWindow* tabWindow);
Tab setupDiagnosticsTab(wxWindow* parent, wxWindow* tabWindow);
Tab setupReportsTab(wxWindow* parent, wxWindow* tabWindow);
Tab setupUsersManagementTab(wxWindow* parent, wxWindow* tabWindow);
Tab setupSettingsTab(wxWindow* parent, wxWindow* tabWindow);