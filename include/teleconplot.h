#pragma once

#include <string>
#include <mutex>
#include <list>

#include "chartdir.h"
#include "databuffer.h"

using namespace std;

class TeleconPlot {
protected:
    list<pair<double, double>>* m_dataToAdd;
    mutex m_dataToAddLock;
    const int m_depth;
    DataBuffer<double> m_xTimestamps;
    DataBuffer<double> m_yData;
	int m_color; // Represented as an RGB hexadecimal code (one byte per channel)
	string m_plotTitle;
public:
	TeleconPlot(int depth, int color, string plotTitle);
	// Fetches all of the data out of m_dataToAdd and updates the timestamps/data buffers
    virtual void prepDataForDraw() = 0;
    // Adds a layer representing the plot to the given chart
	virtual void addToChart(XYChart* chart) = 0;
    void pushData(double xTimestamp, double yData);
    double getEarliestTimestamp() const;
    double getLatestTimestamp() const;
    double getLastestValue() const;
	// Returns the current size of the data buffer
	size_t size() const;
	// Returns the capacity (maximum size) of the data buffer
	int depth() const;
	int getColor() const;
	
	const string& getPlotTitle() const;
};