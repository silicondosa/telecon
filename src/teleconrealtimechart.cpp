#include "teleconrealtimechart.h"

#include <iostream>

TeleconRealtimeChart::TeleconRealtimeChart(string title, double memoryDepthSeconds, int dataRateMillis, string xLabel, string yLabel, ColorSequenceMode colorSequenceMode)
	: TeleconChart(title, memoryDepthSeconds, dataRateMillis, xLabel, yLabel, colorSequenceMode) {}

double TeleconRealtimeChart::getDefaultXAxisSpan()
{
	return m_memoryDepthSeconds;
}

ChartXAxisType TeleconRealtimeChart::getChartXAxisType()
{
	return CAXT_TIME;
}
