#pragma once

#include <string>
#include <vector>

#include "colors.h"
#include "teleconplot.h"

using namespace std;

/**
 * The type of the chart: whether it has time data on the x-axis,or arbitrary non-time data.
 */
enum ChartXAxisType {
    /** x-axis represents a timespan. */
    CAXT_TIME,
    /** x-axis represents some arbitrary non-time data */
    CAXT_ARBITRARY
};

/**
 * The user-level chart interface.
 * It describes features such as the title, data rate, x/y labels, and color sequence that will be used.
 * 
 * This class is abstract.
 * A subclass such as TeleconRealtimeChart or TeleconDataChart should be used to add plots.
 */
class TeleconChart {
protected:
    /** The title that will be displayed at the top of the plot. */
    const string m_title;
    /**
    * The default number of seconds for which data will be remembered by plots added to this chart.
    * This default can be overridden manually when a plot is being added. */
    const double m_memoryDepthSeconds;
    /**
     * The rate at which data will be sent to the plots on the chart.
     * Used only to calculate the starting width of the chart; the actual rate at which data are sent may safely differ.
     */
    const int m_dataRateMillis;
    /** The label that will be displayed below the x-axis */
    const string m_xLabel;
    /**  The label that will be displayed adjacent to the y-axis */
    const string m_yLabel;
    /**
     * Describes how plots using the default color will be colored.
     * See ::ColorSequenceMode for more details.
     */
    const ColorSequenceMode m_colorSequenceMode;
    /** True if the Telecon app has started running and no further changes are permitted, or false before then. */
    bool m_hasStarted;
    /** Returns the next color, represented as described in ::PlotColor, that should be used for default-color plots according to the ::ColorSequenceMode. */
    long getNextDefaultColor();
public:
    /**
     * Constructs a new chart to be added to a TeleconWindow.
     * 
     * \param title the title displayed above the chart.
     * \param memoryDepthSeconds the default number of seconds for which data will be remembered by plots added to this chart.
     * This default can be overridden manually when a plot is being added.
     * \param dataRateMillis the rate at which data will be sent to the plots on the chart.
     * Used only to calculate the starting width of the chart; the actual rate at which data are sent may safely differ.
     * \param xLabel the label displayed below the x-axis.
     * \param yLabel the label displayed adjacent to the y-axis.
     * \param colorSequenceMode describes how plots using the default color will be colored.
     * See ::ColorSequenceMode for more details.
     */
    TeleconChart(string title, double memoryDepthSeconds, int dataRateMillis, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode);

    /**
     * \return The title of the chart.
     */
    string getTitle();

    /**
     * \return The label below the x-axis.
     */
    string getXLabel();

    /**
     * \return The label adjacent to the y-axis.
     */
    string getYLabel();

    /**
     * \return Color sequence mode, as described in ::ColorSequenceMode.
     */
    ColorSequenceMode getColorSequenceMode();

    /**
     * \return The default x-axis width, to be used when few or no data have been provided.
     * Interpretation of the units will depend on the x-axis type.
     * \sa ::ChartXAxisType
     */
    virtual double getDefaultXAxisSpan() = 0;

    /**
     * \return Default x-axis type, as specified in ::ChartXAxisType.
     */
    virtual ChartXAxisType getChartXAxisType() = 0;
    
    /**
     * \param index the index of the TeleconPlot to return, relative to the order added.
     * \return A pointer to the TeleconPlot requested.
     */
    virtual shared_ptr<TeleconPlot> getPlot(int index) = 0;

    /**
     * \return The number of TeleconPlots added to the chart
     */
    virtual size_t getNumPlots() = 0;

    /**
     * \param name the name of the TeleconPlot to return. If multiple plots share the same name, no guarantee is made about which will be returned.
     * \return A pointer to a plot with the given name, or a null pointer if no plot in the given chart and window has that name.
     */
    virtual shared_ptr<TeleconPlot> getPlotByName(string name) = 0;

};