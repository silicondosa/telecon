#pragma once

#include "teleconwxplot.h"
#include "teleconrasterplot.h"
#include "datatoaddlist.h"

// Prevents compiler warnings about inheritance from multiple overlapping classes
// We perform diamond inheritance, which can cause issues, but the way we do it is safe (only one definition for each function)
# pragma warning( disable : 4250)

struct RasterDataPoint
{
    double xTimestamp;
    bool isActive;
};

/**
 * Raster plot GUI implementation.
 *
 * This is an implementation class and should not be interacted with directly by the user.
 */
class TeleconWxRasterPlot : public TeleconWxPlot, virtual public TeleconRasterPlot
{
protected:
    /** The data to be added to the plot upon the next update. */
    DataToAddList<RasterDataPoint> m_dataToAdd;
    /** The timestamps of the data points that have been added to the plot. */
    DataBuffer<double> m_xTimestamps;
    /** The y-values of the data points that have been added to the plot. Will either be equal to m_yValue or Chart::NoValue. */
    DataBuffer<double> m_yValueBuffer;
    /**  The y-value at which active points will be displayed. */
    double m_yValue;

public:
    /**
     * Constructs a raster plot object.
     *
     * \param plotTitle the title of the plot, as displayed in the legend.
     * \param yValue the y-value at which active points will be displayed.
     * \param depth the depth (maximum size) of the plot. Always >= size.
     * \param symbolStyle the ::SymbolStyle representing how the symbol representing points (if any) should be displayed.
     */
    TeleconWxRasterPlot(string plotTitle, double yValue, size_t depth, const SymbolStyle& symbolStyle);

    /**
     * \return The y-value at which active points will be displayed.
     */
    double getYValue() const;

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

    // Inherited via TeleconRasterPlot
    /**
     * \copydoc TeleconPlot::size
     */
    virtual size_t size() const override;
    /**
     * \copydoc TeleconRasterPlot::pushData
     */
    virtual void pushData(double xTimestamp, bool isActive = true) override;
};
