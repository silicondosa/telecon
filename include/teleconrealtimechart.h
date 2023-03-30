#pragma once

#include "teleconchart.h"

class TeleconRealtimeChart : public TeleconChart {
protected:
public:
    TeleconRealtimeChart(string title, string xLabel = "", string yLabel = "", ColorSequenceMode colorSequenceMode = CSM_BLACK, double defaultTimespan = 1.0);
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
    TeleconWxLinePlot* addLinePlot(std::string plottitle, int memoryDepth = 1000, long plotcolor = COLOR_DEFAULT, LineType lineType = LT_SOLID, int lineWidth = 1, int symbol = SYMBOL_NO_SYMBOL, bool fillSymbol = true, int symbolSize = 5);
    /**
     * Adds a scatter plot to the chart with the given parameters. Parameters, where present, are identical to those in addLinePlot.
     *
     * \sa TeleconRealTimeChart::addLinePlot
     */
    TeleconWxScatterPlot* addScatterPlot(std::string plottitle, int memoryDepth = 1000, long plotcolor = COLOR_DEFAULT, int symbol = SYMBOL_SQUARE, bool fillSymbol = true, int symbolSize = 5);

    CHART_X_AXIS_TYPE getChartXAxisType() override;
};