#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <string>

#include "teleconwxchart.h"
#include "teleconwindow.h"

using namespace std;

class TeleconWxWindow : public wxFrame
{
private:
    TeleconWindow* m_window;

    vector<TeleconWxChart*> m_charts;
public:
    TeleconWxWindow(TeleconWindow* window);

    void drawWindow();

    DECLARE_EVENT_TABLE()
};