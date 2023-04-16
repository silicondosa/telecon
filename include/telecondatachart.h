#pragma once

#include "teleconchart.h"
#include "teleconwxphaseportraitplot.h"

/**
 * Chart implementation for charts with non-time data on the x-axis, inherits from TeleconChart. More suitable for phase portrait plots
 */
class TeleconDataChart : public TeleconChart
{
protected:
public:
    /**
     * Constructor for TeleconRealtimeChart. See the parent constructor, which has the same values.
     *
     * \sa TeleconChart::TeleconChart
     */
    TeleconDataChart(string title, double memoryDepthSeconds = 60.0, int dataRateMillis = 100, string xLabel = "", string yLabel = "", ColorSequenceMode colorSequenceMode = CSM_BLACK);

    /**
     * Adds a line plot to the chart with the given parameters.
     *
     * \param plottitle the title of the plot, which will be displayed in the legend.
     * \param plotcolor the color of the plot. Can be specified as an ARGB hexcode or by the provided COLOR enum.
     * A value of COLORS::COLOR_DEFAULT means the color will be automatically determined based on the ColorSequenceMode of the chart.
     * \param lineType the type of the line, eiher solid or dashed.
     * \param lineWidth the width of the line in pixels.
     * \param symbol the symbol used on each data point.
     * The exact interpretation of integer values will depend on the underlying interpretation, except for values specified by the provided SYMBOL enum.
     * For the default implementation, wxChartDir, the symbol values are the same as the ChartDirector shapes.
     * \param fillSymbol if true, the symbol will (if drawn) be filled with the same color as the line. If false, the cener of the symbol will be transparent.
     * \param symbolSize the size of the symbol (if drawn) in pixels.
     * \sa https://www.advsofteng.com/doc/cdpydoc/shapespec.htm
     */
    shared_ptr<TeleconPhasePortraitPlot> addPhasePortraitPlot(std::string plottitle, long plotcolor = COLOR_DEFAULT, int lineWidth = 2, LineType lineType = LT_SOLID, int symbol = SYMBOL_SQUARE, bool fillSymbol = true, int symbolSize = 5, size_t memoryDepth = -1);

    /**
     * Getter function that returns the default width of the chart, to be used when few or no data have been provided.
     * For a realtime chart, this is measured in seconds, and is provided in the constructor as memoryDepthSeconds.
     *
     * \return The number of seconds that the chart will use as its default width.
     */
    double getDefaultXAxisSpan() override;

    /**
     * Getter function that returns x axis type (whether it displays time or arbitrary data on the x-axis).
     * For a realtime chart, guaranteed to return time type.
     *
     * \return Chart x-axis type (guaranteed to be CAXT_TIME)
     */
    CHART_X_AXIS_TYPE getChartXAxisType() override;
};

