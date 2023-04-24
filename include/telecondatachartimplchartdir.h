#pragma once

#include "teleconchartimplchartdir.h"
#include "telecondatachart.h"
#include "teleconwxphaseportraitplot.h"

class TeleconDataChartImplChartDir : public TeleconChartImplChartDir, virtual public TeleconDataChart
{
public:
    TeleconDataChartImplChartDir(string title, double memoryDepthSeconds = 60.0, int dataRateMillis = 100, string xLabel = "", string yLabel = "", ColorSequenceMode colorSequenceMode = CSM_BLACK);
    shared_ptr<TeleconPhasePortraitPlot> addPhasePortraitPlot(std::string plottitle, const LineStyle& lineStyle = TeleconPhasePortraitPlot::defaultLineStyle, const SymbolStyle& symbolStyle = TeleconPhasePortraitPlot::defaultSymbolStyle, size_t memoryDepth = -1) override;

    // Inherited via TeleconChartImplChartDir
    using TeleconDataChart::getDefaultXAxisSpan;
    using TeleconDataChart::getChartXAxisType;
};
