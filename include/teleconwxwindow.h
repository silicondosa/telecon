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

    //wxWidgets panels, boxes and sizers
    wxBoxSizer* m_topSizer;
    wxStaticBox* m_viewOptionsBox;
    wxStaticBoxSizer* m_viewOptionsBoxSizer;

    // wxWidgets buttons and dropdown boxes
    wxToggleButton* m_playButton;
    wxToggleButton* m_pauseButton;
    wxButton* m_saveButton;
    wxChoice* m_refreshIntervalSelector;

    // wxWidgets timers
    wxTimer* m_chartRefreshTimer;

    // wxWidgets event handler functions
    void OnPlayClick(wxCommandEvent& event);
    void OnPauseClick(wxCommandEvent& event);
    void OnChartRefreshIntervalSelected(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);

    void checkQuit(wxTimerEvent& event);
    void onClose(wxCloseEvent& event);

public:
    TeleconWxWindow(shared_ptr<TeleconWindow> window);
    ~TeleconWxWindow();

    DECLARE_EVENT_TABLE()
};

enum {
    ID_QUIT_TIMER = ID_REFRESH_TIMER + 1
};