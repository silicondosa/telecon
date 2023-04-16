#pragma once

#include <string>
#include <vector>

#include "colors.h"
#include "teleconwxplot.h"

using namespace std;

/**
 * The type of the chart: whether it has time data on the x-axis,or arbitrary non-time data.
 */
enum CHART_X_AXIS_TYPE {
    CAXT_TIME, // x axis represents a timespan
    CAXT_ARBITRARY, // x axis represents some arbitrary non-time data
};

/**
 * Chart implementation. Has title, data rate, x/y labels, color, and vector of plots.
 */
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
    /**
     * Constructs a new chart to be added to a TeleconWindow.
     * 
     * \param title the title displayed above the chart.
     * \param memoryDepthSeconds the default number of seconds for which to store data.
     * This can be overridden on individual plots, but may result in odd spacing if non-default values are used.
     * \param dataRateMillis the rate at which data will be provided to the plots via pushData functions.
     * If the actual data rate differs from the value provided here, it will result in spacing issues but no fatal errors.
     * \param xLabel the label displayed beneath the x-axis.
     * \param yLabel the label displayed adjacent to the y-axis.
     * \param colorSequenceMode Describes how plots using the default color will be colored.
     * Each ColorSequenceMode represents an ordered set of colors.
     * Plots using the default color will assigned one of these colors when added, based on the order in which it was added.
     * Plots using a specified (non-default) color are unaffected by the ColorSequenceMode.
     */
    TeleconChart(string title, double memoryDepthSeconds, int dataRateMillis, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode);

    /**
     * Getter function for chart title.
     * 
     * \return Title of the chart.
     */
    string getTitle();

    /**
     * Getter function for chart x-axis label.
     *
     * \return x-axis label.
     */
    string getXLabel();

    /**
     * Getter function for chart y-axis label.
     *
     * \return y-axis label.
     */
    string getYLabel();

    /**
     * Getter function for chart color sequence mode.
     * See constructor for a description of color sequence modes.
     *
     * \return Color sequence mode.
     * \sa TeleconChart::TeleconChart
     */
    ColorSequenceMode getColorSequenceMode();

    /**
     * Getter function that returns the default width of the chart, to be used when few or no data have been provided.
     * Interpretation of the units will depend on the x-axis type
     * 
     * \return default x-axis span as double
     * \sa TeleconChart::getChartXAxisType
     */
    virtual double getDefaultXAxisSpan() = 0;

    /**
     * Getter function that returns x axis type (whether it displays time or arbitrary data on the x-axis).
     *
     * \return Default x-axis type.
     */
    virtual CHART_X_AXIS_TYPE getChartXAxisType() = 0;

    /**
     * Initializer function. After this has been called, no further changes to the chart may be made.
     * This function will be called by the parent TeleconWindow object, and likely should not be called directly by the user.
     */
    void initialize();
    
    /**
     * \param index the index of the TeleconPlot to return, relative to the order added.
     * \return A pointer to the TeleconPlot requested.
     */
    shared_ptr<TeleconPlot> getPlot(int index);

    /**
     * \return The number of TeleconPlots added to the chart
     */
    size_t getNumPlots();

    /**
     * Getter function that returns a plot of the chart given a specified plot name.
     *
     * \param name name of plot as string
     * \return a shared_ptr to the TeleconPlot object plot
     */
    shared_ptr<TeleconPlot> getPlotByName(string name);

};