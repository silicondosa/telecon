#include "telecondatachart.h"

#include <iostream>

TeleconDataChart::TeleconDataChart(string title, double memoryDepthSeconds, int dataRateMillis, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode)
    : TeleconChart(title, memoryDepthSeconds, dataRateMillis, xLabel, yLabel, colorSequenceMode) {}

shared_ptr<TeleconPhasePortraitPlot> TeleconDataChart::addPhasePortraitPlot(std::string plottitle, const LineStyle& lineStyle, const SymbolStyle& symbolStyle, size_t memoryDepth)
{
    if (m_hasStarted) {
        cout << "telecon: Telecon has already started, plots may not be added." << endl;
        return shared_ptr<TeleconPhasePortraitPlot>();
    }
    LineStyle plotLineStyle(lineStyle);
    SymbolStyle plotSymbolStyle(symbolStyle);
    if (lineStyle.getLineColor() == COLOR_DEFAULT) {
        plotLineStyle.setLineColor(getNextDefaultColor());
    }
    if (symbolStyle.getSymbolColor() == COLOR_DEFAULT) {
        plotSymbolStyle.setSymbolColor(plotLineStyle.getLineColor());
    }
    // The plus one is because of fencepost effect: in ten seconds (inclusive), sampling one data point per second, you get 11 data points
    size_t depth = memoryDepth == -1 ? (size_t)(m_memoryDepthSeconds / (m_dataRateMillis / 1000.0) + 1) : memoryDepth;
    shared_ptr<TeleconPhasePortraitPlot> phasePortrait = make_shared<TeleconWxPhasePortraitPlot>(plottitle, depth, plotLineStyle, plotSymbolStyle);
    m_plots.push_back(phasePortrait);
    return phasePortrait;
}

double TeleconDataChart::getDefaultXAxisSpan()
{
    return 0.0;
}

CHART_X_AXIS_TYPE TeleconDataChart::getChartXAxisType()
{
    return CAXT_ARBITRARY;
}
