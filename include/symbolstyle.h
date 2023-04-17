#pragma once

#include "enums.h"

class SymbolStyle {
private:
    PlotSymbol m_symbol;
    int m_symbolColor;
    bool m_fillSymbol;
    int m_symbolSize;
public:
    SymbolStyle(PlotSymbol symbol = SYMBOL_CIRCLE, int symbolColor = COLOR_DEFAULT, bool fillSymbol = true, int symbolSize = 5);
    void setSymbol(PlotSymbol symbol);
    PlotSymbol getSymbol() const;
    void setSymbolColor(int symbolColor);
    int getSymbolColor() const;
    void setFillSymbol(bool fillSymbol);
    bool getFillSymbol() const;
    void setSymbolSize(int symbolSize);
    int getSymbolSize() const;
};
