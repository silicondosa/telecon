#pragma once

#include "teleconchart.h"

class TeleconRealtimeChart : public TeleconChart {
protected:
public:
    TeleconRealtimeChart(string title, double memoryDepthSeconds = 60.0, int dataRateMillis = 100, string xLabel = "", string yLabel = "", ColorSequenceMode colorSequenceMode = CSM_BLACK);
    
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
    shared_ptr<TeleconLinePlot> addLinePlot(std::string plottitle, long plotcolor = COLOR_DEFAULT, LineType lineType = LT_SOLID, int lineWidth = 1, int symbol = SYMBOL_NO_SYMBOL, bool fillSymbol = true, int symbolSize = 5, int memoryDepth = -1);
    
    /**
     * Adds a scatter plot to the chart with the given parameters. Parameters, where present, are identical to those in addLinePlot.
     *
     * \sa TeleconRealTimeChart::addLinePlot
     */
    shared_ptr<TeleconScatterPlot> addScatterPlot(std::string plottitle, long plotcolor = COLOR_DEFAULT, int symbol = SYMBOL_SQUARE, bool fillSymbol = true, int symbolSize = 5, int memoryDepth = -1);

    /**
     * Getter function that returns x axis span.
     * Overide TeleconChart's getDefaultXAxisSpan() virtual function.
     * 
     * \return m_memoryDepthSeconds as a double
     */
    double getDefaultXAxisSpan() override;

    /**
     * Getter function that returns x axis type.
     * Overide TeleconChart's getChartXAxisType() virtual function.
     *
     * \return CAXT_TIME as a CHART_X_AXIS_TYPE object
     */
    CHART_X_AXIS_TYPE getChartXAxisType() override;
};