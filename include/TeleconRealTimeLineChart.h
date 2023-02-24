
#ifndef __TELECON_REAL_TIME_LINE_CHART
#define __TELECON_REAL_TIME_LINE_CHART

#include <wx/wxprec.h>
#include <wx/panel.h>
#include <wx/tglbtn.h>

#include "chartdir.h"
#include "TeleconChartPanel.h"
#include "wxchartviewer.h"

class TeleconRealTimeLineChart : public TeleconChartPanel
{
public:
    TeleconRealTimeLineChart(wxWindow *parent,
                             wxWindowID winid = wxID_ANY,
                             const wxPoint &pos = wxDefaultPosition,
                             const wxSize &size = wxDefaultSize,
                             long style = wxTAB_TRAVERSAL | wxNO_BORDER,
                             const wxString &name = wxASCII_STR(wxPanelNameStr));

    // ~TeleconChartPanel(){ }
    bool createWindow(const wxString& caption, int width, int height);
        // Will create a new dynamic teleconWindow object and add it to windowList

    /// Destructor
    ~TeleconRealTimeLineChart();
        // Delete each teleconPlot object, teleconChart object and each teleconWindow object

    void addPlot(const wxString& plotname, double (*ptr)(), int plotcolor, const char* plottitle);
    // Will create a new dynamic teleconPlot object and add it to plotList   

    void initChart(const wxString title, const wxString ylabel);
    // Will create a new dynamic teleconChart object and add it to chartList  

    typedef double (*FuncPtr)();  

    // Get new data values
    void GetData(std::vector<FuncPtr>& funcArray);

    BaseChart *my_base_chart;

    DECLARE_EVENT_TABLE()

private: 
    /// private member functions
    void Init();

    // The "Run" or "Freeze" button has been pressed
    void OnRunFreezeChanged(bool run);

    // The chart update timer interval has changed.
    void OnUpdatePeriodChanged(const wxString& value);

    /// Creates the controls and sizers
    void CreatePlotControls();

    // Update the chart.
    void UpdateChart();

    // Draw the chart.
    void DrawChart();

    void TrackLineLegend(XYChart* c, int mouseX);

    /// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for ID_POINTER
    void OnPlayClick(wxCommandEvent& event);

    /// wxEVT_COMMAND_CHECKBOX_CLICKED event handler for wxID_ZOOM_IN
    void OnPauseClick(wxCommandEvent& event);

    /// wxEVT_COMMAND_CHOICE_SELECTED event handler for ID_UPDATE_PERIOD
    void OnUpdatePeriodSelected(wxCommandEvent& event);

    void OnDataTimer(wxTimerEvent& event);
    void OnChartUpdateTimer(wxTimerEvent& event);

    void OnViewPortChanged(wxCommandEvent& event);
    void OnMouseMovePlotArea(wxCommandEvent& event);

    void OnSave(wxCommandEvent& event);

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource(const wxString& name);

    int w_width;
    int w_height;

    wxToggleButton* m_playButton;
    wxToggleButton* m_pauseButton;
    wxButton* m_saveButton;
    wxColour        m_bgColour;
    wxPanel* itemPanel2;
    wxFlexGridSizer* itemFlexGridSizer3;
    wxBoxSizer* itemBoxSizer3;
    wxString m_chartTitle;
    wxString m_ylabel;

    wxChoice* m_updatePeriod;

    wxTimer* m_dataRateTimer;
    wxTimer* m_chartUpdateTimer;

    int    m_currentIndex;            // Index of the array position to which new values are added.
    std::vector<double> m_timeStamps;	// The timestamps for the data series
    std::vector<FuncPtr> funcArray;
    std::vector<std::vector<double>> m_dataSeries;
    std::vector<int> m_colorSeries;
    std::vector<const char*> m_plottitleSeries;
    std::vector<wxTextCtrl*> m_dataValues;

    wxDateTime m_nextDataTime;           // Used by the random number generator to generate realtime data.

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

#endif
