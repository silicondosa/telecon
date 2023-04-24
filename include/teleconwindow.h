#pragma once

#include <string>
#include <atomic>
#include <vector>
#include <condition_variable>

#include "colors.h"
#include "teleconrealtimechart.h"
#include "telecondatachart.h"

/**
 * The user-level window interface.
 * It describes features such as the title and whether the window is still open.
 */
class TeleconWindow {
protected:
	std::atomic_bool m_hasRequestedQuit;
	mutex m_hasQuitLock;
	condition_variable m_hasQuitCV;
	bool m_hasQuit;
	const std::string m_title;

    bool m_hasStarted;
public:

	/**
	 * Constructs a new window element with given title.
	 * 
	 * \param title the title displayed on top of the window.
	 */
	TeleconWindow(std::string title = "");

	/**
	 * Requests that the given window should be closed. On the next refresh, the window's implementation should close the window.
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
	 */
	void waitUntilQuit();

	/**
	 * \return The title displayed on top of the window
	 */
	std::string getTitle();

    /**
     * Adds a realtime chart to the window.
     * Realtime charts have time data on the x-axis.
     * Charts will be displayed in the order added, from top to bottom.
     * 
     * \param title the title displayed above the chart.
     * \param memoryDepthSeconds the default number of seconds for which data will be remembered by plots added to this chart.
     * This default can be overridden manually when a plot is being added.
     * \param dataRateMillis the rate at which data will be sent to the plots on the chart.
     * Used only to calculate the starting width of the chart; the actual rate at which data are sent may safely differ.
     * \param xLabel the label displayed below the x-axis.
     * \param yLabel the label displayed adjacent to the y-axis.
     * \param colorSequenceMode describes how plots using the default color will be colored.
     * See ::ColorSequenceMode for more details.
     * \return A pointer to the TeleconRealtimeChart object created.
     */
	virtual shared_ptr<TeleconRealtimeChart> addRealtimeChart(std::string title = "", double memoryDepthSeconds = 60.0, int dataRateMillis = 100, std::string xLabel = "", std::string yLabel = "", ColorSequenceMode colorSequenceMode = CSM_BLACK) = 0;

    /**
     * Adds a data chart to the window.
     * Data charts have arbitrary non-time data on the x-axis.
     * For parameters, see addRealtimeChart, which has the same parameters.
     * 
     * \return A pointer to the TeleconDataChart object created.
     * \sa TeleconWindow::addRealtimeChart
     */
    virtual shared_ptr<TeleconDataChart> addDataChart(std::string title = "", double memoryDepthSeconds = 60.0, int dataRateMillis = 100, std::string xLabel = "", std::string yLabel = "", ColorSequenceMode colorSequenceMode = CSM_BLACK) = 0;
	
	/**
     * \param index the index of the TeleconChart to return, relative to the order added.
     * \return A pointer to the TeleconChart requested.
	 */
	virtual shared_ptr<TeleconChart> getChart(size_t index) = 0;

	/**
	 * \return The number of TeleconCharts added to the window.
	 */
	virtual size_t getNumCharts() const = 0;

	/**
     * \param name the name of the TeleconChart to return. If multiple windows share the same name, no guarantee is made about which will be returned.
     * \return A pointer to a chart with the given name, or a null pointer if no chart has that name.
	 */
	virtual shared_ptr<TeleconChart> getChartByName(string name) = 0;

	/**
     * \param chartName the name of the TeleconChart in which to search for a plot with the given name. If multiple charts share the same name, no guarantee is made about which will be returned.
     * \param plotName the name of the TeleconPlot to return. If multiple plots share the same name, no guarantee is made about which will be returned.
     * \return A pointer to a plot with the given name, or a null pointer if no plot in the given chart and window has that name.
	 */
	virtual shared_ptr<TeleconPlot> getPlotByName(string chartName, string plotName) = 0;
};