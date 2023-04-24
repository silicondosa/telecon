#pragma once

#include "teleconrealtimechart.h"
#include "teleconchartimplchartdir.h"
#include "teleconwxlineplot.h"
#include "teleconwxscatterplot.h"
#include "teleconwxrasterplot.h"

class TeleconRealtimeChartImplChartDir : public TeleconChartImplChartDir, virtual public TeleconRealtimeChart
{
public:
    TeleconRealtimeChartImplChartDir(string title, double memoryDepthSeconds = 60.0, int dataRateMillis = 100, string xLabel = "", string yLabel = "", ColorSequenceMode colorSequenceMode = CSM_BLACK);
    shared_ptr<TeleconLinePlot> addLinePlot(std::string plottitle, const LineStyle& lineStyle = TeleconLinePlot::defaultLineStyle, const SymbolStyle& symbolStyle = TeleconLinePlot::defaultSymbolStyle, size_t memoryDepth = -1) override;
    shared_ptr<TeleconScatterPlot> addScatterPlot(std::string plottitle, const SymbolStyle& symbolStyle = TeleconScatterPlot::defaultSymbolStyle, size_t memoryDepth = -1) override;
    shared_ptr<TeleconRasterPlot> addRasterPlot(std::string plottitle, double yValue, const SymbolStyle& symbolStyle = TeleconRasterPlot::defaultSymbolStyle, size_t memoryDepth = -1) override;
};
