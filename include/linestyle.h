#pragma once

#include "enums.h"

/**
 * A class to represent what the line that a plot draws to connect data points should look like.
 */
/* Implementation note: this is a full class, rather than just a struct, to leave open the future possibility of managing thread safety with locks.
Currently, thread safety for plots is managed by marking line styles constant after construction. */
class LineStyle
{
private:
    // The color of the line, represented as described in PlotColor
    int m_lineColor;
    // The width of the line in pixels
    int m_lineWidth;
    // The type of the line, as described in PlotLineType
    PlotLineType m_lineType;
public:
    /**
     * Constructs a LineStyle with the given parameters.
     * 
     * If no line is desired, set the line width to 0.
     * 
     * \param lineColor the color of the line, represented as described in ::PlotColor.
     * \param lineWidth the width of the line in pixels.
     * \param lineType the type of the line, as described in ::PlotLineType.
     */
    LineStyle(int lineColor = COLOR_DEFAULT, int lineWidth = 1, PlotLineType lineType = LT_SOLID);
    
    /**
     * Setter for line color.
     * 
     * \param lineColor the color of the line, represented as described in ::PlotColor.
     */
    void setLineColor(int lineColor);
    
    /**
     * \return The color of the line, represented as described in ::PlotColor.
     */
    int getLineColor() const;

    /**
     * Setter for line width.
     * 
     * \param lineWidth the width of the line in pixels.
     */
    void setLineWidth(int lineWidth);

    /**
     * \return The width of the line in pixels.
     */
    int getLineWidth() const;

    /**
     * Setter for line type.
     * 
     * \param lineType the type of the line, as described in ::PlotLineType.
     */
    void setLineType(PlotLineType lineType);

    /**
     * \return The type of the line, as described in ::PlotLineType.
     */
    PlotLineType getLineType() const;
};
