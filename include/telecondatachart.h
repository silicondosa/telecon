#pragma once

#include "teleconchart.h"
#include "teleconwxphaseportraitplot.h"
#include "linestyle.h"

/**
 * Chart implementation that inherits from TeleconChart for charts with non-time data on the x-axis.
 * Currently usable only for phase portrait plots.
 */
class TeleconDataChart : public TeleconChart
{
public:
    /**
     * Constructor for TeleconRealtimeChart. See the parent constructor, which has the same values.
     *
     * \sa TeleconChart::TeleconChart
     */
    TeleconDataChart(string title, double memoryDepthSeconds = 60.0, int dataRateMillis = 100, string xLabel = "", string yLabel = "", ColorSequenceMode colorSequenceMode = CSM_BLACK);

    /**
     * Adds a temporal phase portrait to the chart with the given parameters.
     * 
     * \param plottitle the title of the plot, which will be displayed in the legend.
     * \param lineStyle describes how the line used to connect the data points should look, as described in ::LineStyle
     * \param symbolStyle describes how the symbol used to represent data points should look, as described in ::SymbolStyle
     * \param memoryDepth The number of data points that will be remembered by the plot at one time.
     * If a value of -1 is given, this will be auto-calculated based on the memory depth of the chart and the data rate.
     * \return A pointer to the constructed temporal phase portrait object.
     */
    shared_ptr<TeleconPhasePortraitPlot> addPhasePortraitPlot(std::string plottitle, const LineStyle& lineStyle = TeleconPhasePortraitPlot::defaultLineStyle, const SymbolStyle& symbolStyle = TeleconPhasePortraitPlot::defaultSymbolStyle, size_t memoryDepth = -1);

    /**
     * \copydoc TeleconChart::getDefaultXAxisSpan
     * 
     * For this data chart, the units will be the same as the plots given.
     */
    double getDefaultXAxisSpan() override;

    /**
     * \copydoc TeleconChart::getChartXAxisType
     * 
     * For this data chart, guaranteed to return non-time type (::CAXT_ARBITRARY).
     */
    ChartXAxisType getChartXAxisType() override;
};

