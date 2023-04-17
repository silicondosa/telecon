#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <string>

#include "teleconwxchart.h"
#include "teleconwindow.h"

using namespace std;

 /**
  * Window GUI implementation, inherits from wxFrame.
  * 
  * This is an implementation class and should not be interacted with directly by the user.
  */
class TeleconWxWindow : public wxFrame
{
private:
    shared_ptr<TeleconWindow> m_window;

    vector<TeleconWxChart*> m_charts;

    // Setup functions 
    void SetUpViewOptionsBox();

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

    void refreshCharts(wxTimerEvent& event);
    void onClose(wxCloseEvent& event);

public:

    /**
     * Constructs the window based on the specification of the provided ::TeleconWindow object.
     *
     * \param window A pointer to the ::TeleconWindow object representing the window.
     */
    TeleconWxWindow(shared_ptr<TeleconWindow> window);

    DECLARE_EVENT_TABLE()
};

enum {
    ID_REFRESH_TIMER = ID_CHARTVIEWER + 1,
    ID_PLAY,
    ID_PAUSE,
    ID_REFRESH_INTERVAL
};