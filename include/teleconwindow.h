#pragma once

#include <string>
#include <atomic>
#include <vector>

#include "colors.h"
#include "teleconrealtimechart.h"

class TeleconWindow {
private:
	std::atomic_bool m_hasRequestedQuit;
	mutex m_hasQuitLock;
	condition_variable m_hasQuitCV;
	bool m_hasQuit;
	const std::string m_title;

    bool m_hasStarted;

	std::vector<shared_ptr<TeleconChart>> m_charts;
public:

	/**
	 * Constructs a new window element with given title.
	 * 
	 * \param title
	 */
	TeleconWindow(std::string title);

	/**
	 * Default constructor that creates a window element with a blank title.
	 * 
	 */
	TeleconWindow();

	/**
	 * Setter function to set requested quit boolean value (m_hasRequestedQuit) to true.
	 * 
	 */
	void requestQuit();

	/**
	 * Helper function that returns the requested quit boolean value (m_hasRequestedQuit).
	 * Used to determine if quit has been requested.
	 * 
	 * \return 
	 */
	bool hasRequestedQuit();

	/**
	 * Setter function that makes the quit status true.
	 * Inside lock for thread safety, and notifys all threads on completion.
	 * 
	 */
	void setHasQuit();

	/**
	 * Helper function that returns if the window has quit.
	 * Inisde lock for thread safety.
	 * 
	 * \return m_hasQuit as bool
	 */
	bool hasQuit();

	/**
	 * Helper function that loops until the window has quit.
	 * Used so other parts of the program can wait until the window has successfully quit.
	 * 
	 */
	void waitUntilQuit();

	/**
	 * Getter function that returns the window title as a string.
	 * 
	 * \return 
	 */
	std::string getTitle();

	/**
	 * Initializer function. Calls initialize on all chart objects of the window.
	 * 
	 */
    void initialize();

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
	shared_ptr<TeleconRealtimeChart> addRealtimeChart(std::string title = "", double memoryDepthSeconds = 60.0, int dataRateMillis = 100, std::string xLabel = "", std::string yLabel = "", ColorSequenceMode colorSequenceMode = CSM_BLACK);
	
	/**
	 * Getter function that returns a chart of the window given a specified index.
	 *
	 * \param index of chart as int
	 * \return a shared_ptr to the TeleconChart object chart
	 */
	shared_ptr<TeleconChart> getChart(size_t index);

	/**
	 * Getter function that returns the number of charts in the window.
	 * 
	 * \return m_charts.size as size_t
	 */
	size_t getNumCharts() const;

	/**
	 * Getter function that returns a chart of the window given a specified chart name.
	 *
	 * \param name of chart as string
	 * \return a shared_ptr to the TeleconChart object chart
	 */
	shared_ptr<TeleconChart> getChartByName(string name);

	/**
	 * Getter funtion that returns a plot of a chart of the window given a plot name and chart name.
	 * Uses TeleconChart's getChartByName() function.
	 * 
	 * \param chartName as string
	 * \param plotName as string
	 * \return a shared_ptr to the TeleconPlot object plot
	 */
	shared_ptr<TeleconPlot> getPlotByName(string chartName, string plotName);
};