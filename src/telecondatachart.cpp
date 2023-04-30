#include "telecondatachart.h"

#include <iostream>

TeleconDataChart::TeleconDataChart(string title, double memoryDepthSeconds, int dataRateMillis, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode)
    : TeleconChart(title, memoryDepthSeconds, dataRateMillis, xLabel, yLabel, colorSequenceMode) {}

double TeleconDataChart::getDefaultXAxisSpan()
{
    return 0.0;
}

ChartXAxisType TeleconDataChart::getChartXAxisType()
{
    return CAXT_ARBITRARY;
}
