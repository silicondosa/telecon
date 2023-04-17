#pragma once

#include "teleconwxplot.h"
#include "teleconphaseportraitplot.h"
#include "datatoaddlist.h"

// Prevents compiler warnings about inheritance from multiple overlapping classes
// We perform diamond inheritance, which can cause issues, but the way we do it is safe (only one definition for each function)
# pragma warning( disable : 4250)

/**
 * Data point struct for phase portrait plots.
 */
struct PhasePortraitDataPoint
{
    /**
     * Timestamp as a double.
     */
    double timestamp;

    /**
     * x value as a double.
     */
    double xData;

    /**
     * y value as a double.
     */
    double yData;
};

class TeleconWxPhasePortraitPlot : public TeleconWxPlot, virtual public TeleconPhasePortraitPlot
{
protected:
    // XY Data member values
    DataToAddList<PhasePortraitDataPoint> m_dataToAdd;
    DataBuffer<double> m_timestamps;
    DataBuffer<double> m_xData;
    DataBuffer<double> m_yData;

    // Display options member values
    shared_ptr<LineStyle> m_lineStyle;

public:
    TeleconWxPhasePortraitPlot(string plotTitle, size_t depth, const LineStyle& lineStyle, const SymbolStyle& symbolStyle);

    // Inherited via TeleconWxPlot
    virtual size_t size() const override;
    virtual void prepDataForDraw() override;
    virtual void addToChart(XYChart* chart) override;
    virtual double getLeftmostX() const override;
    virtual double getRightmostX() const override;
    virtual string getLatestValueString() const override;
    virtual bool isIncludedInLegend() const override;

    // Inherited via TeleconPhasePortraitPlot
    virtual void pushData(double timestamp, double xData, double yData) override;
    virtual shared_ptr<const LineStyle> getLineStyle() const override;
};
