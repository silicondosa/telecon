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
    shared_ptr<TeleconWindow> m_window;

    vector<TeleconWxChart*> m_charts;

    wxTimer* m_checkQuitTimer;

    void checkQuit(wxTimerEvent& event);
    void onClose(wxCloseEvent& event);
public:
    TeleconWxWindow(shared_ptr<TeleconWindow> window);
    ~TeleconWxWindow();

    DECLARE_EVENT_TABLE()
};

enum {
    ID_QUIT_TIMER = ID_UPDATE_TIMER + 1
};