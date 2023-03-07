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

    TeleconRealTimeLineChart* addChart(string title, string xlabel, string ylabel, ColorSequenceMode colorSequenceMode = CSM_BLACK, int dataInterval = 100, int memoryDepth = 1000);
    void drawWindow();

    // Iterator functions
    vector<TeleconRealTimeLineChart*>::iterator begin();
    vector<TeleconRealTimeLineChart*>::iterator end();

    TeleconRealTimeLineChart* getChart(int index);
    size_t getNumCharts() const;

    DECLARE_EVENT_TABLE()
private:
    vector<TeleconRealTimeLineChart*> list_charts;
};