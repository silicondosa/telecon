#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <string>

#include "teleconrealtimechart.h"

using namespace std;

class TeleconWindow : public wxFrame
{
public:
    TeleconWindow(const wxString& title);

    TeleconRealTimeLineChart* addChart(std::string title, string xlabel, std::string ylabel, ColorSequenceMode colorSequenceMode = CSM_BLACK);
    void drawWindow();

    // Iterator functions
    vector<TeleconRealTimeLineChart*>::iterator begin();
    vector<TeleconRealTimeLineChart*>::iterator end();

    DECLARE_EVENT_TABLE()
private:
    vector<TeleconRealTimeLineChart*> list_charts;
};