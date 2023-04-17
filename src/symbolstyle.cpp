#include "symbolstyle.h"

SymbolStyle::SymbolStyle(PlotSymbol symbol, int symbolColor, bool fillSymbol, int symbolSize)
    : m_symbol(symbol), m_symbolColor(symbolColor), m_fillSymbol(fillSymbol), m_symbolSize(symbolSize) {}

void SymbolStyle::setSymbol(PlotSymbol symbol)
{
    m_symbol = symbol;
}

PlotSymbol SymbolStyle::getSymbol() const
{
    return m_symbol;
}

void SymbolStyle::setSymbolColor(int symbolColor)
{
    m_symbolColor = symbolColor;
}

int SymbolStyle::getSymbolColor() const
{
    return m_symbolColor;
}

void SymbolStyle::setFillSymbol(bool fillSymbol)
{
    m_fillSymbol = fillSymbol;
}

bool SymbolStyle::getFillSymbol() const
{
    return m_fillSymbol;
}

void SymbolStyle::setSymbolSize(int symbolSize)
{
    m_symbolSize = symbolSize;
}

int SymbolStyle::getSymbolSize() const
{
    return m_symbolSize;
}