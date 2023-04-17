#pragma once

#include "enums.h"

/**
 * A class to represent what the symbol that a plot uses to mark data points should look like.
 */
 /* Implementation note: this is a full class, rather than just a struct, to leave open the future possibility of managing thread safety with locks.
 Currently, thread safety for plots is managed by marking symbol styles constant after construction. */
class SymbolStyle {
private:
    // The symbol used, as described in PlotSymbol.
    PlotSymbol m_symbol;
    // The color of the symbol, represented as described in PlotColor
    int m_symbolColor;
    // True if the interior of the symbol will be colored, false if it will be left transparent.
    bool m_fillSymbol;
    // The size of the symbol in pixels.
    int m_symbolSize;
public:
    /**
     * Constructs a SymbolStyle with the given parameters.
     * 
     * If no symbol is desired, set the symbol to PlotSymbol::SYMBOL_NO_SYMBOL.
     * 
     * \param symbol the symbol used, as described in ::PlotSymbol.
     * \param symbolColor the color of the symbol, represented as described in ::PlotColor.
     * \param fillSymbol true if the interior of the symbol will be colored, false if it will be left transparent.
     * \param symbolSize the size of the symbol in pixels.
     */
    SymbolStyle(PlotSymbol symbol = SYMBOL_CIRCLE, int symbolColor = COLOR_DEFAULT, bool fillSymbol = true, int symbolSize = 5);

    /**
     * Setter for symbol.
     * 
     * \param symbol the symbol used, as described in ::PlotSymbol.
     */
    void setSymbol(PlotSymbol symbol);

    /**
     * \return The symbol used, as described in ::PlotSymbol.
     */
    PlotSymbol getSymbol() const;

    /**
     * Setter for symbol color.
     * 
     * \param symbolColor the color of the symbol, represented as described in ::PlotColor.
     */
    void setSymbolColor(int symbolColor);

    /**
     * \return The color of the symbol, represented as described in ::PlotColor.
     */
    int getSymbolColor() const;

    /**
     * Setter for fill symbol.
     * 
     * \param fillSymbol true if the interior of the symbol will be colored, false if it will be left transparent.
     */
    void setFillSymbol(bool fillSymbol);

    /**
     * \return True if the interior of the symbol will be colored, false if it will be left transparent.
     */
    bool getFillSymbol() const;

    /**
     * Setter for symbol size.
     * 
     * \param symbolSize the size of the symbol in pixels.
     */
    void setSymbolSize(int symbolSize);

    /**
     * \return The size of the symbol in pixels.
     */
    int getSymbolSize() const;
};
