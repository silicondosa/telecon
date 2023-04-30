#pragma once

#include "teleconchartimplchartdir.h"
#include "telecondatachart.h"
#include "teleconwxphaseportraitplot.h"

/**
 * The wxChartDir implementation of the TeleconDataChart interface.
 */
class TeleconDataChartImplChartDir : public TeleconChartImplChartDir, virtual public TeleconDataChart
{
public:
    /**
     * \copydoc TeleconDataChart::TeleconDataChart
     */
    TeleconDataChartImplChartDir(string title, double memoryDepthSeconds = 60.0, int dataRateMillis = 100, string xLabel = "", string yLabel = "", ColorSequenceMode colorSequenceMode = CSM_BLACK);
    
    /**
     * \copydoc TeleconDataChart::addPhasePortraitPlot
     */
    shared_ptr<TeleconPhasePortraitPlot> addPhasePortraitPlot(std::string plottitle, const LineStyle& lineStyle = TeleconPhasePortraitPlot::defaultLineStyle, const SymbolStyle& symbolStyle = TeleconPhasePortraitPlot::defaultSymbolStyle, size_t memoryDepth = -1) override;
};
