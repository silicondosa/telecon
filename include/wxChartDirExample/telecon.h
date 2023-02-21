#pragma once
#ifndef _TELECON_H_
#define _TELECON_H_

/*!
 * Includes
 */

#include "wx/frame.h"
#include "wx/tglbtn.h"
#include "wx/scrolbar.h"

#include "wxchartviewer.h"
#include "chartdir.h"
#include <vector>


//class teleconPlot
//{
//public:
//    teleconPlot();
//};
//
//class teleconChart
//{
//private:
//    std::vector<teleconPlot> plotList;
//
////public:
//    //
//};
//
//class teleconWindow
//{
//private:
//    std::vector<teleconChart> chartList;
//
////public:
//    //
//};

/*!
* Telecon class declaration
*/

class Telecon : public wxDialog
{
    DECLARE_CLASS(Telecon)
        DECLARE_EVENT_TABLE()

private:
    // Private member variables
    //std::vector<teleconWindow> windowList;

    /// Control identifiers
    enum {
        ID_REALTIMETRACK = 10000,
        ID_CHARTVIEWER,
        ID_PLAY,
        ID_PAUSE,
        ID_UPDATE_PERIOD,
        ID_DATA_TIMER,
        ID_UPDATE_TIMER
    };

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
    typedef double (*FuncPtr)();
    std::vector<FuncPtr> funcArray;
    std::vector<std::vector<double>> m_dataSeries;
    std::vector<int> m_colorSeries;
    std::vector<char*> m_plottitleSeries;
    std::vector<wxTextCtrl*> m_dataValues;

    wxDateTime m_nextDataTime;           // Used by the random number generator to generate realtime data.

    wxChartViewer* m_chartViewer;

public:
    

    /// Constructors
    Telecon();

    bool createWindow(const wxString& caption, int width, int height);
        // Will create a new dynamic teleconWindow object and add it to windowList

    /// Destructor
    ~Telecon();
        // Delete each teleconPlot object, teleconChart object and each teleconWindow object

    void AddPlot(const wxString& plotname, double (*ptr)(), int plotcolor, char* plottitle);
    // Will create a new dynamic teleconPlot object and add it to plotList   

    void AddChart(const wxString title, const wxString ylabel);
    // Will create a new dynamic teleconChart object and add it to chartList    

    // Get new data values
    void GetData(std::vector<FuncPtr>& funcArray);
};

#endif // _TELECON_H_
