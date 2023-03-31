#pragma once

#include "teleconwxplot.h"
#include "teleconlineplot.h"

// Prevents compiler warnings about inheritance from multiple overlapping classes
// We perform diamond inheritance, which can cause issues, but the way we do it is safe (only one definition for each function)
# pragma warning( disable : 4250)

class TeleconWxPlotXY : public TeleconWxPlot, virtual public TeleconLineScatterPlot {
protected:
	// XY Data member values
	list<pair<double, double>>* m_dataToAdd;
	mutex m_dataToAddLock;
	DataBuffer<double> m_xTimestamps;
	DataBuffer<double> m_yData;

	// Display options member values
	int m_lineWidth;
	LineType m_lineType;
	bool m_hasSymbol;
	bool m_fillSymbol;
	int m_symbol;
	int m_symbolSize;

	list<pair<double, double>>* swapAndGetDataToAdd();
public:
	TeleconWxPlotXY(int depth, int color, string plotTitle, int lineWidth, LineType lineType, bool hasSymbol, int symbol, bool fillSymbol, int symbolSize);
	/* Functions inherited from TeleconWxPlot */
	virtual void prepDataForDraw() override;
	virtual void addToChart(XYChart* chart) override;
	virtual double getLeftmostX() const override;
	virtual double getRightmostX() const override;
	virtual string getLatestValueString() const override;

	/* Functions inherited from TeleconPlot*/
	virtual size_t size() const override;

	/* Functions inherited from TeleconLineScatterPlot*/
	/**
	 * Appends one data point to the plot, removing the oldest point if the maximum depth has been reached.
	 *
	 * \param xTimestamp the time that this data point was generated. It is interpreted by the chart for display purposes as seconds since January 1, year 1.
	 * \param yData the datum to be added to the plot.
	 */
	void pushData(double xTimestamp, double yData) override;
	bool isSymbolFilled() const override;
	int getSymbol() const override;
	int getSymbolSize() const override;
};
