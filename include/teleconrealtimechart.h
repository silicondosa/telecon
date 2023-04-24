#pragma once

#include "teleconchart.h"
#include "teleconlineplot.h"
#include "teleconscatterplot.h"
#include "teleconrasterplot.h"
#include "linestyle.h"

 /**
  * Chart implementation that inherits from TeleconChart for charts with time data on the x-axis.
  * Currently usable for line, scatter, and raster plots.
  */
class TeleconRealtimeChart : virtual public TeleconChart {
public:
    /**
    * Constructor for TeleconRealtimeChart. See the parent constructor, which has the same values.
    * 
    * \sa TeleconChart::TeleconChart
    */
    TeleconRealtimeChart(string title, double memoryDepthSeconds = 60.0, int dataRateMillis = 100, string xLabel = "", string yLabel = "", ColorSequenceMode colorSequenceMode = CSM_BLACK);
    
    /**
    * Adds a line plot to the chart with the given parameters.
    *
    * \param plottitle the title of the plot, which will be displayed in the legend.
    * \param lineStyle describes how the line used to connect the data points should look, as described in ::LineStyle
    * \param symbolStyle describes how the symbol used to represent data points should look, as described in ::SymbolStyle
    * \param memoryDepth The number of data points that will be remembered by the plot at one time.
    * If a value of -1 is given, this will be auto-calculated based on the memory depth of the chart and the data rate.
    * \return A pointer to the constructed line plot object.
    */
    virtual shared_ptr<TeleconLinePlot> addLinePlot(std::string plottitle, const LineStyle& lineStyle = TeleconLinePlot::defaultLineStyle, const SymbolStyle& symbolStyle = TeleconLinePlot::defaultSymbolStyle, size_t memoryDepth = -1) = 0;
    
    /**
    * Adds a scatter plot to the chart with the given parameters.
    *
    * \param plottitle the title of the plot, which will be displayed in the legend.
    * \param symbolStyle describes how the symbol used to represent data points should look, as described in ::SymbolStyle
    * \param memoryDepth The number of data points that will be remembered by the plot at one time.
    * If a value of -1 is given, this will be auto-calculated based on the memory depth of the chart and the data rate.
    * \return A pointer to the constructed scatter plot object.
    */
    virtual shared_ptr<TeleconScatterPlot> addScatterPlot(std::string plottitle, const SymbolStyle& symbolStyle = TeleconScatterPlot::defaultSymbolStyle, size_t memoryDepth = -1) = 0;

    /**
    * Adds a raster plot to the chart with the given parameters.
    *
    * \param plottitle the title of the plot, which will be displayed in the legend.
    * \param yValue The y-value at which active data points will be displayed.
    * \param symbolStyle describes how the symbol used to represent data points should look, as described in ::SymbolStyle
    * \param memoryDepth The number of data points that will be remembered by the plot at one time.
    * If a value of -1 is given, this will be auto-calculated based on the memory depth of the chart and the data rate.
    * \return A pointer to the constructed raster plot object.
    */
    virtual shared_ptr<TeleconRasterPlot> addRasterPlot(std::string plottitle, double yValue, const SymbolStyle& symbolStyle = TeleconRasterPlot::defaultSymbolStyle, size_t memoryDepth = -1) = 0;

    /**
     * \copydoc TeleconChart::getDefaultXAxisSpan
     *
     * For this realtime chart, the units will be seconds.
     */
    virtual double getDefaultXAxisSpan() override;

    /**
     * \copydoc TeleconChart::getChartXAxisType
     *
     * For this realtime chart, guaranteed to return time type (::CAXT_TIME).
     */
    virtual ChartXAxisType getChartXAxisType() override;
};