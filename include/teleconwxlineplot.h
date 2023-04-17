#pragma once

#include "teleconwxplot.h"
#include "teleconlineplot.h"
#include "datatoaddlist.h"

// Prevents compiler warnings about inheritance from multiple overlapping classes
// We perform diamond inheritance, which can cause issues, but the way we do it is safe (only one definition for each function)
# pragma warning( disable : 4250)

/** Helper struct for the data-to-add list */
struct LinePlotDataPoint
{
    /** The timestamp at which the data point was created, described in TeleconLinePlot::pushData */
    double xTimestamp;
    /** The data carried by the data point */
    double yData;
};

/**
 * Line plot GUI implementation.
 * 
 * This is an implementation class and should not be interacted with directly by the user.
 */
class TeleconWxLinePlot : public TeleconWxPlot, virtual public TeleconLinePlot {
protected:
    /** The data to be added to the plot upon the next update. */
    DataToAddList<LinePlotDataPoint> m_dataToAdd;
    /** The timestamps of the data points that have been added to the plot. */
    DataBuffer<double> m_xTimestamps;
    /** The data of the data points that have been added to the plot. */
    DataBuffer<double> m_yData;

    /** The ::LineStyle representing how the line connecting points (if any) should be displayed. */
    shared_ptr<LineStyle> m_lineStyle;
public:

	/**
	 * Constructs a line plot object.
	 *
	 * \param plotTitle the title of the plot, as displayed in the legend.
	 * \param depth the depth (maximum size) of the plot. Always >= size.
	 * \param lineStyle the ::LineStyle representing how the line connecting points (if any) should be displayed.
	 * \param symbolStyle the ::SymbolStyle representing how the symbol representing points (if any) should be displayed.
	 */
	TeleconWxLinePlot(string plotTitle, size_t depth, const LineStyle& lineStyle, const SymbolStyle& symbolStyle);

    // Inherited via TeleconWxPlot
    /**
     * \copydoc TeleconWxPlot::prepDataForDraw
     */
    virtual void prepDataForDraw() override;

    /**
     * \copydoc TeleconWxPlot::addToChart
     */
    virtual void addToChart(XYChart* chart) override;

    /**
     * \copydoc TeleconWxPlot::getLeftmostX
     * 
     * For line plots, returns the oldest timestamp.
     */
    virtual double getLeftmostX() const override;

    /**
     * \copydoc TeleconWxPlot::getRightmostX
     *
     * For line plots, returns the newest timestamp.
     */
    virtual double getRightmostX() const override;

    /**
     * \copydoc TeleconWxPlot::getLatestValueString
     */
    virtual string getLatestValueString() const override;

    /**
     * \copydoc TeleconWxPlot::isIncludedInLegend
     */
    virtual bool isIncludedInLegend() const override;

    // Inherited via TeleconLinePlot
    /**
     * \copydoc TeleconPlot::size
     */
    virtual size_t size() const override;

    /**
     * \copydoc TeleconLinePlot::pushData
     */
    virtual void pushData(double xTimestamp, double yData) override;

    /**
     * \copydoc TeleconLinePlot::getLineStyle
     */
    virtual shared_ptr<const LineStyle> getLineStyle() const override;
};
