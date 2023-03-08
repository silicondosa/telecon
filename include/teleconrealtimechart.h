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
#include "enums.h"

using namespace std;

class TeleconRealTimeChart : public wxPanel {
public:
    TeleconRealTimeChart(wxWindow *parent,
                                wxWindowID winid = wxID_ANY,
                                const wxPoint &pos = wxDefaultPosition,
                                const wxSize &size = wxDefaultSize,
                                const wxString title = "",
                                const wxString xLabel = "",
                                const wxString yLabel = "",
                                long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                                const wxString &name = wxASCII_STR(wxPanelNameStr),
                                ColorSequenceMode colorSequenceMode = CSM_BLACK,
                                int dataInterval = 100,
                                int memoryDepth = 1000);

    /// Destructor
    ~TeleconRealTimeChart();
    // Copy & move constructors and assignment operators are unneeded, and are deleted to comply with Rule of Five
    // See: https://en.wikipedia.org/wiki/Rule_of_three_(C%2B%2B_programming)
    TeleconRealTimeChart(TeleconRealTimeChart&) = delete;
    TeleconRealTimeChart& operator=(TeleconRealTimeChart&) = delete;
    TeleconRealTimeChart(TeleconRealTimeChart&&) = delete;
    TeleconRealTimeChart& operator=(TeleconRealTimeChart&&) = delete;

    // Will create a new dynamic TeleconPlot object and add it to plotList
    /**
     * Adds a line plot to the chart with the given parameters.
     * 
     * \param plottitle the title of the plot, which will be displayed in the legend.
     * \param plotcolor the color of the plot. Can be specified as an ARGB hexcode or by the provided COLOR enum.
     * \param lineType the type of the line, eiher solid or dashed.
     * \param lineWidth the width of the line in pixels.
     * \param symbol the symbol used on each data point. Can be specified by the provided SYMBOL enum.
     * \param fillSymbol if true, the symbol will (if drawn) be filled with the same color as the line. If false, the cener of the symbol will be transparent.
     * \param symbolSize the size of the symbol (if drawn) in pixels.
     */
    void addLinePlot(const char * plottitle, long plotcolor = COLOR_DEFAULT, LineType lineType = LT_SOLID, int lineWidth = 1, int symbol = SYMBOL_NO_SYMBOL, bool fillSymbol = true, int symbolSize = 5);
    /**
     * Adds a scatter plot to the chart with the given parameters. Parameters, where present, are identical to those in addLinePlot.
     * 
     * \sa TeleconRealTimeChart::addLinePlot
     */
    void addScatterPlot(const char * plottitle, long plotcolor = COLOR_DEFAULT, int symbol = SYMBOL_SQUARE, bool fillSymbol = true, int symbolSize = 5);

    /**
     * \param index the index of the TeleconPlot to return.
     * \return A pointer to the TeleconPlot requested.
     */
    shared_ptr<TeleconPlot> getPlot(int index);
    /**
     * \return The number of TeleconPlots added to the chart.
     */
    size_t getNumPlots() const;

    // Iterator functions
    /**
     * For use with range-based for loops.
     * \return Iterator to the first TeleconPlot added.
     */
    vector<shared_ptr<TeleconPlot>>::iterator begin();
    /**
     * For use with range-based for loops.
     * \return Iterator to the element following the last TeleconPlot added.
     */
    vector<shared_ptr<TeleconPlot>>::iterator end();

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
    void OnChartUpdateTimer(wxTimerEvent& event);
    void OnViewPortChanged(wxCommandEvent& event); // updates the chart if it needs updating

    // addPlot() helper functions
    int getNextDefaultColor();
    void addLatestValueText(const char* plottitle);

    // Chart and data update functions
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
    TextBox* m_titleBox;

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
    wxTimer* m_chartUpdateTimer;

    // Chart proper member variables
    ColorSequenceMode m_colorSequenceMode;
    vector<shared_ptr<TeleconPlot>> m_plots;
    int m_dataInterval;
    int m_memoryDepth;

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
