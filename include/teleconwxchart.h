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
 */
class TeleconWxChart : public wxPanel {
public:

    /**
     * Constructor.
     * 
     * \param chart
     * \param parent
     * \param winid
     * \param pos
     * \param size
     * \param style
     * \param name
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
     * Default deconstructor.
     * 
     */
    ~TeleconWxChart();

    /**
     * Function to redraw the chart if needed.
     * 
     */
    void OnChartRefreshTimer();

    /**
     * Setter function for play status, used in TeleconWxWindow.
     */
    void setPlay();

    /**
     * Setter function for pause status, used in TeleconWxWindow.
     */
    void setPause();

    /**
     * Helper function that saves the chart as a file, used in TeleconWxWindow.
     * 
     * \param i which order the current chart is in in its window as int (for user to see)
     * \param windowName the window name of the chart (for user to see)
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
