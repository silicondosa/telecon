#include "telecondatachart.h"

#include <iostream>

TeleconDataChart::TeleconDataChart(string title, double memoryDepthSeconds, int dataRateMillis, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode)
    : TeleconChart(title, memoryDepthSeconds, dataRateMillis, xLabel, yLabel, colorSequenceMode) {}

shared_ptr<TeleconPhasePortraitPlot> TeleconDataChart::addPhasePortraitPlot(std::string plottitle, long plotcolor, int lineWidth, LineType lineType, int symbol, bool fillSymbol, int symbolSize, int memoryDepth)
{
    if (m_hasStarted) {
        cout << "telecon: Telecon has already started, plots may not be added." << endl;
        return shared_ptr<TeleconPhasePortraitPlot>();
    }
    long color = plotcolor == COLOR_DEFAULT ? getNextDefaultColor() : plotcolor;
    // The plus one is because of fencepost effect: in ten seconds (inclusive), sampling one data point per second, you get 11 data points
    int depth = (int)(memoryDepth == -1 ? m_memoryDepthSeconds / (m_dataRateMillis / 1000.0) : memoryDepth) + 1;
    shared_ptr<TeleconPhasePortraitPlot> phasePortrait = make_shared<TeleconWxPhasePortraitPlot>(plottitle, color, lineWidth, lineType, symbol != Chart::NoSymbol, symbol, fillSymbol, symbolSize, depth);
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
