#pragma once

#include "teleconwxplot.h"
#include "teleconlineplot.h"

// Prevents compiler warnings about inheritance from multiple overlapping classes
// We perform diamond inheritance, which can cause issues, but the way we do it is safe (only one definition for each function)
# pragma warning( disable : 4250)

/**
 * Plot and GUI implementation that takes in points as (x,y), inherits from TeleconWxPlot and TeleconLineScatterPlot.
 */
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

	/**
	 * Constructor.
	 * 
	 * \param plotTitle title of the plot as string
	 * \param color color of the plot as int (enum)
	 * \param lineWidth width of the plot line as int
	 * \param lineType the type of the plot line as type LineType
	 * \param hasSymbol whether the plot has a symbol or not as bool
	 * \param symbol symbol type as int (enum)
	 * \param fillSymbol whether or not the plot line is filled or dotted as bool
	 * \param symbolSize symbol size as an int
	 * \param depth depth of the internal buffer as int
	 */
	TeleconWxPlotXY(string plotTitle, int color, int lineWidth, LineType lineType, bool hasSymbol, int symbol, bool fillSymbol, int symbolSize, int depth);
    
	/**
	 * Default deconstructor.
	 * 
	 */
	~TeleconWxPlotXY();

    /* Functions inherited from TeleconWxPlot */

	/**
	 * Fetches all data out of the controller threadand adds it to make it visible to UI thread.
	 *
	 */
	virtual void prepDataForDraw() override;

	/**
	 * Adds a layer representing the plot to the given chart.
	 *
	 * \param chart of type XYChart*
	 */
	virtual void addToChart(XYChart* chart) override;

	/**
	 * Getter function for left most x.
	 *
	 * \return left most x value as double
	 */
	virtual double getLeftmostX() const override;

	/**
	 * Getter function for right most x.
	 *
	 * \return right most x value as a double
	 */
	virtual double getRightmostX() const override;

	/**
	 * Getter function for latest value.
	 *
	 * \return latest value as a string
	 */
	virtual string getLatestValueString() const override;

	/**
	 * Helper function to know if the plot is included in the legend.
	 *
	 * \return included in legend status as bool
	 */
    virtual bool isIncludedInLegend() const override;

	/* Functions inherited from TeleconPlot*/

	/**
	 * Getter funcction for size of the plot.
	 * 
	 * \return size of the plot as type size_t
	 */
	virtual size_t size() const override;

	/* Functions inherited from TeleconLineScatterPlot*/
	/**
	 * Appends one data point to the plot, removing the oldest point if the maximum depth has been reached.
	 *
	 * \param xTimestamp the time that this data point was generated. It is interpreted by the chart for display purposes as seconds since January 1, year 1.
	 * \param yData the datum to be added to the plot.
	 */
	void pushData(double xTimestamp, double yData) override;

	/**
	 * Getter function for whether the plot line is filled or not.
	 * 
	 * \return filled status as bool
	 */
	bool isSymbolFilled() const override;

	/**
	 * Getter function for symbol type of the plot.
	 * 
	 * \return symbol type as an int (enum)
	 */
	int getSymbol() const override;

	/**
	 * Getter function for symbol size of the plot.
	 * 
	 * \return symbol size as an int
	 */
	int getSymbolSize() const override;
};
