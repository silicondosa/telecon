#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/tglbtn.h>

#include <memory>

#include "chartdir.h"
#include "wxchartviewer.h"
#include "teleconplot.h"
#include "teleconlineplot.h"
#include "colors.h"

using namespace std;

class TeleconRealTimeLineChart : public wxPanel {
public:
    TeleconRealTimeLineChart(wxWindow *parent,
                                wxWindowID winid = wxID_ANY,
                                const wxPoint &pos = wxDefaultPosition,
                                const wxSize &size = wxDefaultSize,
                                const wxString title = "",
                                const wxString xLabel = "",
                                const wxString yLabel = "",
                                long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                                const wxString &name = wxASCII_STR(wxPanelNameStr),
                                ColorSequenceMode colorSequenceMode = CSM_BLACK);

    // ~TeleconChartPanel(){ }
    bool createWindow(const wxString& caption, int width, int height);
        // Will create a new dynamic teleconWindow object and add it to windowList

    /// Destructor
    ~TeleconRealTimeLineChart();
        // Delete each teleconPlot object, teleconChart object and each teleconWindow object

    // Copy & move constructors and assignment operators are unneeded, and are deleted to comply with Rule of Five
    // See: https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)
    TeleconRealTimeLineChart(TeleconRealTimeLineChart&) = delete;
    TeleconRealTimeLineChart& operator=(TeleconRealTimeLineChart&) = delete;
    TeleconRealTimeLineChart(TeleconRealTimeLineChart&&) = delete;
    TeleconRealTimeLineChart& operator=(TeleconRealTimeLineChart&&) = delete;

    // Will create a new dynamic TeleconPlot object and add it to plotList
    void addLinePlot(double (*ptr)(), const char * plottitle, long plotcolor = -1, int symbol = Chart::NoSymbol, int symbolSize = 5, LineType lineType = LT_SOLID, int lineWidth = 1);
    void addScatterPlot(double (*ptr)(), const char * plottitle, long plotcolor = -1, int symbol = Chart::SquareShape, int symbolSize = 5);

    typedef double (*FuncPtr)();

    DECLARE_EVENT_TABLE()

private:
    // Setup functions 
    void SetUpViewOptionsBox();
    void SetUpChartBox(const wxString title, const wxString xlabel, const wxString ylabel);

    // wxWidgets event handler functions
    void OnPlayClick(wxCommandEvent& event);
    void OnPauseClick(wxCommandEvent& event);
    void OnChartUpdatePeriodSelected(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnDataTimer(wxTimerEvent& event);
    void OnChartUpdateTimer(wxTimerEvent& event);
    void OnViewPortChanged(wxCommandEvent& event); // updates the chart if it needs updating

    // addPlot() helper functions
    int getNextDefaultColor();
    void addLatestValueText(const char* plottitle);

    // Chart and data update functions
    void GetData();
    void DrawChart();
    
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

    // wxWidgets buttons and dropdown boxes
    wxToggleButton* m_playButton;
    wxToggleButton* m_pauseButton;
    wxButton* m_saveButton;
    wxChoice* m_updatePeriodSelector;

    // Miscellaneous wxWidgets members
    vector<wxTextCtrl*> m_latestValueTextCtrls;
    wxColour m_bgColour;
    wxString m_chartTitle;
    wxString m_xlabel;
    wxString m_ylabel;

    // wxWidgets timers
    wxTimer* m_dataRateTimer;
    wxTimer* m_chartUpdateTimer;

    // Chart proper member variables
    DataBuffer<double> m_timeStamps;               // The timestamps for the data series
    ColorSequenceMode m_colorSequenceMode;
    vector<shared_ptr<TeleconPlot>> m_plots;

    // Pointer to the chart viewer - main body of panel
    wxChartViewer* m_chartViewer;
};

enum
{
    ID_REALTIMETRACK = wxID_HIGHEST,
    ID_CHARTVIEWER,
    ID_PLAY,
    ID_PAUSE,
    ID_UPDATE_PERIOD,
    ID_DATA_TIMER,
    ID_UPDATE_TIMER
};
