#pragma once

#include <string>
#include <vector>

#include "colors.h"
#include "teleconwxplot.h"
#include "teleconwxlineplot.h"
#include "teleconwxscatterplot.h"

using namespace std;

enum CHART_X_AXIS_TYPE {
    CAXT_TIME, // x axis represents a timespan
    CAXT_ARBITARY, // x axis represents some arbitrary non-time data
    CAXT_BOTH // x axis may represent both time and non-time data for different plots
};

class TeleconChart {
protected:
    const string m_title;
    const double m_memoryDepthSeconds;
    const int m_dataRateMillis;
    const string m_xLabel;
    const string m_yLabel;
    const ColorSequenceMode m_colorSequenceMode;

    bool m_hasStarted;

    vector<shared_ptr<TeleconPlot>> m_plots;

    long getNextDefaultColor();
public:
    TeleconChart(string title, double memoryDepthSeconds, int dataRateMillis, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode);

    /**
     * Getter function for chart title.
     * 
     * \return title as a string
     */
    string getTitle();

    /**
     * Getter function for chart x-axis label.
     *
     * \return x-axis label as a string
     */
    string getXLabel();

    /**
     * Getter function for chart y-axis label.
     *
     * \return y-axis label as a string
     */
    string getYLabel();

    /**
     * Getter function for chart color sequence mode.
     *
     * \return color sequence mode as a ColorSequenceMode object
     */
    ColorSequenceMode getColorSequenceMode();

    /**
     * Virtual getter function for default x axis span.
     * 
     * \return default x axis span as double
     */
    virtual double getDefaultXAxisSpan() = 0;

    /**
     * Virtual getter function for default x axis type.
     *
     * \return default x axis type as CHART_X_AXIS_TYPE object
     */
    virtual CHART_X_AXIS_TYPE getChartXAxisType() = 0;

    /**
     * Initializer function. Sets m_hasStarted to true.
     * 
     */
    void initialize();
    
    /**
     * Getter function that returns a plot of the chart given a specified index.
     * 
     * \param index of plot as int
     * \return a shared_ptr to the TeleconPlot object plot
     */
    shared_ptr<TeleconPlot> getPlot(int index);

    /**
     * Getter function that returns the number of plots currently stored in the chart.
     * 
     * \return number of plots as size_t
     */
    size_t getNumPlots();

    /**
     * Getter function that returns a plot of the chart given a specified plot name.
     *
     * \param name of plot as string
     * \return a shared_ptr to the TeleconPlot object plot
     */
    shared_ptr<TeleconPlot> getPlotByName(string name);

};