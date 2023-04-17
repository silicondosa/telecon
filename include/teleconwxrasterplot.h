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

class TeleconWxRasterPlot : public TeleconWxPlot, virtual public TeleconRasterPlot
{
protected:
    // XY Data member values
    DataToAddList<RasterDataPoint> m_dataToAdd;
    DataBuffer<double> m_xTimestamps;
    DataBuffer<double> m_yValueBuffer;
    double m_yValue;

public:
    TeleconWxRasterPlot(string plotTitle, double yValue, size_t depth, const SymbolStyle& symbolStyle);

    double getYValue() const;

    // Inherited via TeleconWxPlot
    virtual size_t size() const override;
    virtual void prepDataForDraw() override;
    virtual void addToChart(XYChart* chart) override;
    virtual double getLeftmostX() const override;
    virtual double getRightmostX() const override;
    virtual string getLatestValueString() const override;
    virtual bool isIncludedInLegend() const override;

    // Inherited via TeleconRasterPlot
    virtual void pushData(double xTimestamp, bool isActive = true) override;
};
