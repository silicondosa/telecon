#pragma once

#include "teleconwxplot.h"
#include "teleconlineplot.h"
#include "datatoaddlist.h"

// Prevents compiler warnings about inheritance from multiple overlapping classes
// We perform diamond inheritance, which can cause issues, but the way we do it is safe (only one definition for each function)
# pragma warning( disable : 4250)

struct LinePlotDataPoint
{
    double xTimestamp;
    double yData;
};

/**
 * Line Plot and GUI implementation, inherits from TeleconWxPlotXY and TeleconLinePlot.
 */
class TeleconWxLinePlot : public TeleconWxPlot, virtual public TeleconLinePlot {
protected:
    DataToAddList<LinePlotDataPoint> m_dataToAdd;
    DataBuffer<double> m_xTimestamps;
    DataBuffer<double> m_yData;

    shared_ptr<LineStyle> m_lineStyle;
public:

	/**
	 * Constructor that creates a line plot object.
	 *
	 * \param plotTitle title of the plot as string
	 * \param color color of the plot as int (enum)
	 * \param lineWidth width of the plot line as int
	 * \param lineType the type of the plot line as type LineType
	 * \param hasSymbol whether the plot has a symbol or not as bool
	 * \param symbol symbol type as int (enum)
	 * \param fillSymbol whether or not the plot line is filled or dotted as bool
	 * \param symbolSize symbol size as an int
	 * \param depth depth of the internal buffer as int
	 */
	TeleconWxLinePlot(string plotTitle, size_t depth, const LineStyle& lineStyle, const SymbolStyle& symbolStyle);

    // Inherited via TeleconWxPlot
    /**
     * Fetches all data out of the controller threadand adds it to make it visible to UI thread.
     *
     */
    virtual void prepDataForDraw() override;

    /**
     * Adds a layer representing the plot to the given chart.
     *
     * \param chart of type XYChart*
     */
    virtual void addToChart(XYChart* chart) override;

    /**
     * Getter function for left most x.
     *
     * \return left most x value as double
     */
    virtual double getLeftmostX() const override;

    /**
     * Getter function for right most x.
     *
     * \return right most x value as a double
     */
    virtual double getRightmostX() const override;

    /**
     * Getter function for latest value.
     *
     * \return latest value as a string
     */
    virtual string getLatestValueString() const override;

    /**
     * Helper function to know if the plot is included in the legend.
     *
     * \return included in legend status as bool
     */
    virtual bool isIncludedInLegend() const override;

    /**
     * Getter funcction for size of the plot.
     *
     * \return size of the plot as type size_t
     */
    virtual size_t size() const override;

    // Inherited via TeleconScatterPlot
    virtual void pushData(double xTimestamp, double yData) override;

    // Inherited via TeleconLinePlot
    virtual shared_ptr<const LineStyle> getLineStyle() const override;
};
