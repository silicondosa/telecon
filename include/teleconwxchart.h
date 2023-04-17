#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/tglbtn.h>

#include <memory>
#include <map>

#include "chartdir.h"
#include "wxchartviewer.h"
#include "teleconchart.h"
#include "teleconwxplot.h"
#include "colors.h"
#include "enums.h"

using namespace std;

/**
 * Chart GUI implementation, inherits from wxPanel.
 * 
 * This is an implementation class and should not be interacted with directly by the user.
 */
class TeleconWxChart : public wxPanel {
public:

    /**
     * Constructs the chart based on the specification of the provided ::TeleconChart object.
     *
     * \param chart a pointer to the ::TeleconChart object representing the chart.
     * \param parent the wxWidgets parent of this wxPanel.
     * \param winid the wxWidgets window id of this panel. Not used by this app, so set to wxID_ANY.
     * \param pos the wxWidgets position of the wxPanel. Left as default.
     * \param size the wxWidgets size of the wxPanel. Left as default.
     * \param style the wxWidgets style of the wxPanel. Left as default.
     * \param name the wxWidgets name of the wxPanel. Not to be confused with the actual title of the chart, as set in ::TeleconChart, which is separate; this value is unused by our app.
     */
    TeleconWxChart(
        shared_ptr<TeleconChart> chart,
        wxWindow* parent,
        wxWindowID winid = wxID_ANY,
        const wxPoint& pos = wxDefaultPosition,
        const wxSize& size = wxDefaultSize,
        long style = wxTAB_TRAVERSAL | wxNO_BORDER,
        const wxString& name = wxASCII_STR(wxPanelNameStr)
    );

    /**
     * Deconstructs the chart.
     */
    ~TeleconWxChart();

    /**
     * Function to redraw the chart if needed upon timer timeout.
     */
    void OnChartRefreshTimer();

    /**
     * Sets the chart to play values (update).
     */
    void setPlay();

    /**
     * Sets the chart to stop playing values (freeze).
     */
    void setPause();

    /**
     * Helper function that saves the chart as a file, used in TeleconWxWindow.
     * 
     * \param i the index of the current chart in in its window
     * \param windowName the name of the parent window of the chart
     */
    void doSave(int i, string windowName);

    DECLARE_EVENT_TABLE()

private:
    // Setup functions 
    void SetUpLatestValueBox();
    void SetUpChartBox();

    // wxWidgets event handler functions
    void OnViewPortChanged(wxCommandEvent& event); // updates the chart if it needs updating

    // addPlot() helper functions
    void addLatestValueText(int index, string plottitle);

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
    unordered_map<int, wxTextCtrl*> m_latestValueTextCtrls; // Maps index in chart to control
    wxColour m_bgColour;

    shared_ptr<TeleconChart> m_chart;
    bool m_isRefreshEnabled;

    // Pointer to the chart viewer - main body of panel
    wxChartViewer* m_chartViewer;
};

enum
{
    ID_CHARTVIEWER = wxID_HIGHEST + 1
};
