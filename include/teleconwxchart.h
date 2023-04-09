#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/tglbtn.h>

#include <memory>

#include "chartdir.h"
#include "wxchartviewer.h"
#include "teleconchart.h"
#include "teleconwxplot.h"
#include "colors.h"
#include "enums.h"

using namespace std;

class TeleconWxChart : public wxPanel {
public:
    TeleconWxChart(
        shared_ptr<TeleconChart> chart,
        wxWindow* parent,
        wxWindowID winid = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxTAB_TRAVERSAL | wxNO_BORDER,
        const wxString& name = wxASCII_STR(wxPanelNameStr)
    );

    /// Destructor
    ~TeleconWxChart();
    // Copy & move constructors and assignment operators are unneeded, and are deleted to comply with Rule of Five
    // See: https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)
    TeleconWxChart(TeleconWxChart&) = delete;
    TeleconWxChart& operator=(TeleconWxChart&) = delete;
    TeleconWxChart(TeleconWxChart&&) = delete;
    TeleconWxChart& operator=(TeleconWxChart&&) = delete;

    // setter functions for wxwindow buttons
    void setPlay();
    void setPause();
    void setRefresh(long);
    void doSave(int, string);

    DECLARE_EVENT_TABLE()

private:
    // Setup functions 
    void SetUpViewOptionsBox();
    void SetUpChartBox();

    // wxWidgets event handler functions
    void OnChartRefreshTimer(wxTimerEvent& event);
    void OnViewPortChanged(wxCommandEvent& event); // updates the chart if it needs updating

    // addPlot() helper functions
    void addLatestValueText(string plottitle);

    // Chart update function
    void DrawChart(bool isRefreshEnabled);
    
    // Calls TrackLineLegend if necessary
    void OnMouseMovePlotArea(wxCommandEvent& event);

    // Adjusts the track line and the values in the legends
    void TrackLineLegend(XYChart* c, int mouseX);

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource(const wxString& name);

    //wxWidgets panels, boxes and sizers
    wxBoxSizer* m_topSizer;
    wxStaticBox* m_viewOptionsBox;
    wxStaticBoxSizer* m_viewOptionsBoxSizer;
    wxFlexGridSizer* m_plotLatestValueFlexGridSizer;
    wxBoxSizer* m_chartBoxSizer;
    TextBox* m_titleBox;

    // Miscellaneous wxWidgets members
    vector<wxTextCtrl*> m_latestValueTextCtrls;
    wxColour m_bgColour;

    // wxWidgets timers
    wxTimer* m_chartRefreshTimer;

    shared_ptr<TeleconChart> m_chart;
    bool m_isRefreshEnabled;

    // Pointer to the chart viewer - main body of panel
    wxChartViewer* m_chartViewer;
};

enum
{
    ID_CHARTVIEWER = wxID_HIGHEST + 1,
    ID_PLAY,
    ID_PAUSE,
    ID_REFRESH_INTERVAL,
    ID_DATA_TIMER,
    ID_REFRESH_TIMER
};
