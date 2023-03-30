#pragma once

#include <string>
#include <atomic>
#include <vector>

#include "colors.h"
#include "teleconrealtimechart.h"

class TeleconWindow {
private:
	std::atomic<bool> m_hasQuit;
	const std::string m_title;

	std::vector<TeleconChart*> m_charts;
public:
	TeleconWindow(std::string title);
	TeleconWindow();

	void quit();
	bool hasQuit();
	std::string getTitle();

	/**
	 * Adds a chart to the window. Charts will be displayed in the order added, from top to bottom.
	 *
	 * \param title the title displayed above the chart.
	 * \param ylabel the label displayed adjacent to the y-axis.
	 * \param xlabel the label displayed beneath the x-axis.
	 * \param dataInterval the expected time, in milliseconds, between data pushes. This will only affect the area of the plot displayed, and will not cause an error if the actual time between pushes differs from this value.
	 * \param memoryDepth the maximum number of data points that will be held in the data buffer before old values start to be dropped.
	 * \param colorSequenceMode the sequence of colors that will be used for added plots if the color is left unspecified.
	 * \return A pointer to the TeleconRealTimeChart object created.
	 */
	TeleconRealtimeChart* addRealtimeChart(std::string title = "", std::string xLabel = "", std::string yLabel = "", ColorSequenceMode colorSequenceMode = CSM_BLACK, double defaultTimespan = 1.0);
	TeleconChart* getChart(size_t index);
	size_t getNumCharts() const;

	TeleconChart* getChartByName(string name);
	TeleconPlot* getPlotByName(string chartName, string plotName);
};