#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <string>

#include "teleconrealtimechart.h"

using namespace std;

class TeleconWindow : public wxFrame
{
public:
    TeleconWindow(const wxString& title);

    /**
     * Adds a chart to the window. Charts will be displayed in the order added, from top to bottom.
     * 
     * \param title the title displayed above the chart.
     * \param ylabel the label displayed adjacent to the y-axis.
     * \param xlabel the label displayed beneath the x-axis.
     * \param dataInterval the expected time, in milliseconds, between data pushes. This will only affect the area of the plot displayed, and will not cause an error if the actual time between pushes differs from this value.
     * \param memoryDepth the maximum number of data points that will be held in the data buffer before old values start to be dropped.
     * \param colorSequenceMode the sequence of colors that will be used for added plots if the color is left unspecified.
     * \return A pointer to the TeleconRealTimeChart object created.
     */
    TeleconRealTimeChart* addChart(string title, string ylabel, string xlabel = "", int dataInterval = 100, int memoryDepth = 1000, ColorSequenceMode colorSequenceMode = CSM_BLACK);
    /**
     * Draws the charts within the window. Must be called in Telecon::teleconMain after all charts are added.
     */
    void drawWindow();

    /**
     * \param index the index of the TeleconRealTimeChart to return.
     * \return A pointer to the TeleconRealTimeChart requested.
     */
    TeleconRealTimeChart* getChart(int index);
    /**
     * \return The number of TeleconRealTimeCharts added to the window.
     */
    size_t getNumCharts() const;

    // Iterator functions
    /**
     * For use with range-based for loops.
     * \return Iterator to the first TeleconRealTimeChart added.
     */
    vector<TeleconRealTimeChart*>::iterator begin();
    /**
     * For use with range-based for loops.
     * \return Iterator to the element following the last TeleconRealTimeChart added.
     */
    vector<TeleconRealTimeChart*>::iterator end();

    DECLARE_EVENT_TABLE()
private:
    vector<TeleconRealTimeChart*> list_charts;
};