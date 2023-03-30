#pragma once

#include <string>
#include <mutex>
#include <list>

#include "chartdir.h"
#include "databuffer.h"

using namespace std;

class TeleconWxPlot {
protected:
    list<pair<double, double>>* m_dataToAdd;
    mutex m_dataToAddLock;
    const size_t m_depth;
    DataBuffer<double> m_xTimestamps;
    DataBuffer<double> m_yData;
	int m_color; // Represented as an RGB hexadecimal code (one byte per channel)
	string m_plotTitle;
public:
	TeleconWxPlot(size_t depth, int color, string plotTitle);
	// Fetches all of the data out of m_dataToAdd and updates the timestamps/data buffers
    virtual void prepDataForDraw() = 0;
    // Adds a layer representing the plot to the given chart
	virtual void addToChart(XYChart* chart) = 0;
    /**
     * Appends one data point to the plot, removing the oldest point if the maximum depth has been reached.
     * 
     * \param xTimestamp the time that this data point was generated. It is interpreted by the chart for display purposes as seconds since January 1, year 1.
     * \param yData the datum to be added to the plot.
     */
    void pushData(double xTimestamp, double yData);
    virtual double getLeftmostX() = 0;
    virtual double getRightmostX() = 0;
    virtual string getLatestValueString() = 0;
	// Returns the current size of the data buffer
	size_t size() const;
	// Returns the capacity (maximum size) of the data buffer
	size_t depth() const;
	int getColor() const;
	
	const string& getPlotTitle() const;
};