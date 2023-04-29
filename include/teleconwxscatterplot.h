#pragma once

#include "teleconwxplot.h"
#include "teleconscatterplot.h"
#include "datatoaddlist.h"

// Prevents compiler warnings about inheritance from multiple overlapping classes
// We perform diamond inheritance, which can cause issues, but the way we do it is safe (only one definition for each function)
# pragma warning( disable : 4250)

/**
 * Struct to represent a scatter plot data point.
 */
struct ScatterPlotDataPoint
{
    /**
     * Time of the data point.
     */
    double xTimestamp;

    /**
     * y value of the data point.
     */
    double yData;
};

/**
 * Scatter plot GUI implementation.
 *
 * This is an implementation class and should not be interacted with directly by the user.
 */
class TeleconWxScatterPlot : public TeleconWxPlot, virtual public TeleconScatterPlot {
protected:
    /** The data to be added to the plot upon the next update. */
    DataToAddList<ScatterPlotDataPoint> m_dataToAdd;
    /** The timestamps of the data points that have been added to the plot. */
    DataBuffer<double> m_xTimestamps;
    /** The data of the data points that have been added to the plot. */
    DataBuffer<double> m_yData;
public:

    /**
     * Constructs a scatter plot object.
     *
     * \param plotTitle the title of the plot, as displayed in the legend.
     * \param depth the depth (maximum size) of the plot. Always >= size.
     * \param symbolStyle the ::SymbolStyle representing how the symbol representing points (if any) should be displayed.
     */
	TeleconWxScatterPlot(string plotTitle, size_t depth, const SymbolStyle& symbolStyle);

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

    // Inherited via TeleconScatterPlot
    /**
     * \copydoc TeleconPlot::size
     */
    virtual size_t size() const override;

    /**
     * \copydoc TeleconScatterPlot::pushData
     */
    virtual void pushData(double xTimestamp, double yData) override;
};