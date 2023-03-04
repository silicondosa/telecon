#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <string>

#include "TeleconRealTimeLineChart.h"

class TeleconWindow : public wxFrame
{
public:
    TeleconWindow(const wxString& title);

    TeleconRealTimeLineChart* addChart(std::string title, string xlabel, std::string ylabel, ColorSequenceMode colorSequenceMode = CSM_BLACK);
    void drawWindow();

    DECLARE_EVENT_TABLE()
private:
    std::vector<TeleconRealTimeLineChart*> list_charts;
};