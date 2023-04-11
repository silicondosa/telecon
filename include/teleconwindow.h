#pragma once

#include <string>
#include <atomic>
#include <vector>

#include "colors.h"
#include "teleconrealtimechart.h"
#include "telecondatachart.h"

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
	 * Requests that the given window should be closed. On the next chart refresh, the implementation should close the window.
	 * 
	 */
	void requestQuit();

	/**
	 * \return True if requestQuit has been called, or false otherwise.
	 */
	bool hasRequestedQuit();

	/**
	 * Indicates that the given window has been closed, either manually by the user or in response to requestQuit.
	 * This function will be called by the implementation; it should never be called directly by the user.
	 */
	void setHasQuit();

	/**
	 * Helper function that returns if the window has quit.
	 * Inisde lock for thread safety.
	 * 
	 * \return True if the window has been closed, either manually by the user or in response to requestQuit, or false otherwise.
	 */
	bool hasQuit();

	/**
	 * Blocks the calling thread until this window has been closed (i.e. hasQuit returns true).
	 * 
	 */
	void waitUntilQuit();

	/**
	 * \return The title of the window
	 */
	std::string getTitle();

	/**
	 * Initializer function. After this has been called, no further changes to the window may be made.
     * This function will be called by the parent Telecon object, and likely should not be called directly by the user.
	 * 
	 */
    void initialize();

    /**
     * Adds a realtime chart to the window.
     * Realtime charts have time data on the x-axis.
     * Charts will be displayed in the order added, from top to bottom.
     * 
     * \param title the title displayed above the chart.
     * \param memoryDepthSeconds the default number of seconds for which to store data.
     * This can be overridden on individual plots, but may result in odd spacing if non-default values are used.
     * \param dataRateMillis the rate at which data will be provided to the plots via pushData functions.
     * If the actual data rate differs from the value provided here, it will result in spacing issues but no fatal errors.
     * \param xLabel the label displayed beneath the x-axis.
     * \param yLabel the label displayed adjacent to the y-axis.
     * \param colorSequenceMode Describes how plots using the default color will be colored. For a full description, see TeleconChart::TeleconChart.
     * \return A pointer to the TeleconRealtimeChart object created.
     */
	shared_ptr<TeleconRealtimeChart> addRealtimeChart(std::string title = "", double memoryDepthSeconds = 60.0, int dataRateMillis = 100, std::string xLabel = "", std::string yLabel = "", ColorSequenceMode colorSequenceMode = CSM_BLACK);

    /**
     * Adds a data chart to the window.
     * Data charts have arbitrary non-time data on the x-axis.
     * For parameters, see addRealtimeChart, which has the same parameters.
     * 
     * \return A pointer to the TeleconDataChart object created.
     * \sa TeleconWindow::addRealtimeChart
     */
    shared_ptr<TeleconDataChart> addDataChart(std::string title = "", double memoryDepthSeconds = 60.0, int dataRateMillis = 100, std::string xLabel = "", std::string yLabel = "", ColorSequenceMode colorSequenceMode = CSM_BLACK);
	
	/**
     * \param index the index of the TeleconChart to return, relative to the order added.
     * \return A pointer to the TeleconChart requested.
	 */
	shared_ptr<TeleconChart> getChart(size_t index);

	/**
	 * \return The number of TeleconCharts added to the window.
	 */
	size_t getNumCharts() const;

	/**
     * \param name the name of the TeleconChart to return. If multiple windows share the same name, no guarantee is made about which will be returned.
     * \return A pointer to a chart with the given name, or a null pointer if no chart has that name.
	 */
	shared_ptr<TeleconChart> getChartByName(string name);

	/**
     * \param chartName the name of the TeleconChart in which to search for a plot with the given name. If multiple charts share the same name, no guarantee is made about which will be returned.
     * \param plotName the name of the TeleconPlot to return. If multiple plots share the same name, no guarantee is made about which will be returned.
     * \return A pointer to a plot with the given name, or a null pointer if no plot in the given chart and window has that name.
	 */
	shared_ptr<TeleconPlot> getPlotByName(string chartName, string plotName);
};