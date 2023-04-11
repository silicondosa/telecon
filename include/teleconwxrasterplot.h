#pragma once

#include "teleconwxplot.h"
#include "teleconrasterplot.h"

// Prevents compiler warnings about inheritance from multiple overlapping classes
// We perform diamond inheritance, which can cause issues, but the way we do it is safe (only one definition for each function)
# pragma warning( disable : 4250)

class TeleconWxRasterPlot : public TeleconWxPlot, virtual public TeleconRasterPlot
{
private:
    // XY Data member values
    list<pair<double, bool>>* m_dataToAdd;
    mutex m_dataToAddLock;
    DataBuffer<double> m_xTimestamps;
    DataBuffer<double> m_yValueBuffer;
    double m_yValue;

    // Display options member values
    bool m_fillSymbol;
    int m_symbol;
    int m_symbolSize;

    list<pair<double, bool>>* swapAndGetDataToAdd();
public:
    TeleconWxRasterPlot(string plotTitle, double yValue, int color, int symbol, bool fillSymbol, int symbolSize, int depth);
    ~TeleconWxRasterPlot();

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
    virtual bool isSymbolFilled() const override;
    virtual int getSymbol() const override;
    virtual int getSymbolSize() const override;
};
