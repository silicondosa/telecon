#pragma once

#include "teleconwxplotxy.h"

// Prevents compiler warnings about inheritance from multiple overlapping classes
// We perform diamond inheritance, which can cause issues, but the way we do it is safe (only one definition for each function)
# pragma warning( disable : 4250)

/**
 * Line Plot and GUI implementation, inherits from TeleconWxPlotXY and TeleconLinePlot.
 */
class TeleconWxLinePlot : public TeleconWxPlotXY, virtual public TeleconLinePlot {
public:

	/**
	 * Constructor that creates a line plot object.
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
	TeleconWxLinePlot(string plotTitle, int color, int lineWidth, LineType lineType, bool hasSymbol, int symbol, bool fillSymbol, int symbolSize, int depth);

	/* Functions inherited from TeleconLinePlot */

	/**
	 * Getter function for plot line width.
	 *
	 * \return Line width in pixels as int.
	 */
	int getLineWidth() const override;

	/**
	 * Getter function for plot line type (solid or dashed).
	 *
	 * \return Line type as type LineType.
	 */
	LineType getLineType() const override;

	/**
	 * Getter function to see if plot has a symbol. If not, only the line will be displayed.
	 *
	 * \return True if a symbol will be drawn, or false otherwise as bool.
	 */
	bool hasSymbol() const override;
};
