#include "teleconwxrasterplot.h"

list<pair<double, bool>>* TeleconWxRasterPlot::swapAndGetDataToAdd()
{
    list<pair<double, bool>>* newDataToAdd = new list<pair<double, bool>>();
    list<pair<double, bool>>* oldDataToAdd = m_dataToAdd;

    const lock_guard<mutex> lock(m_dataToAddLock);
    m_dataToAdd = newDataToAdd;
    return oldDataToAdd;
}

TeleconWxRasterPlot::TeleconWxRasterPlot(string plotTitle, double yValue, int color, int symbol, bool fillSymbol, int symbolSize, int depth)
    : TeleconWxPlot(plotTitle, color, depth), m_dataToAdd(new list<pair<double, bool>>), m_xTimestamps(depth), m_yValue(yValue), m_latestValue(false), m_yValueArray(nullptr), m_symbol(symbol), m_fillSymbol(fillSymbol), m_symbolSize(symbolSize) {}

TeleconWxRasterPlot::~TeleconWxRasterPlot()
{
    delete m_yValueArray;
    const lock_guard<mutex> lock(m_dataToAddLock);
    delete m_dataToAdd;
}

double TeleconWxRasterPlot::getYValue() const
{
    return m_yValue;
}

size_t TeleconWxRasterPlot::size() const
{
    return m_xTimestamps.size();
}

void TeleconWxRasterPlot::prepDataForDraw()
{
    list<pair<double, bool>>* dataToAdd = swapAndGetDataToAdd();

    for (const auto& activationValue : *dataToAdd) {
        if (activationValue.second) {
            m_xTimestamps.insertNewValue(activationValue.first);
        }
        m_latestValue = activationValue.second;
    }

    delete dataToAdd;
}

void TeleconWxRasterPlot::addToChart(XYChart* chart)
{
    if (m_xTimestamps.size() <= 0) {
        return;
    }
    delete m_yValueArray;
    m_yValueArray = new double[m_xTimestamps.size()]();
    std::fill_n(m_yValueArray, m_xTimestamps.size(), m_yValue);
    ScatterLayer* layer = chart->addScatterLayer(DoubleArray(&m_xTimestamps[0], (int)m_xTimestamps.size()), DoubleArray(m_yValueArray, (int)m_xTimestamps.size()), (string("notitle\\") + m_plotTitle).c_str(), m_symbol, m_symbolSize, m_fillSymbol ? m_color : Chart::Transparent, m_color);
}

double TeleconWxRasterPlot::getLeftmostX() const
{
    return m_xTimestamps[0];
}

double TeleconWxRasterPlot::getRightmostX() const
{
    return m_xTimestamps[m_xTimestamps.size() - 1];
}

string TeleconWxRasterPlot::getLatestValueString() const
{
    if (m_latestValue) {
        return "active";
    }
    return "inactive";
}

bool TeleconWxRasterPlot::isIncludedInLegend() const
{
    return false;
}

void TeleconWxRasterPlot::pushData(double xTimestamp, bool isActive)
{
    const lock_guard<mutex> lock(m_dataToAddLock);

    m_dataToAdd->push_back(make_pair(xTimestamp, isActive));

    if (m_dataToAdd->size() > m_depth) {
        m_dataToAdd->pop_front();
    }
}

bool TeleconWxRasterPlot::isSymbolFilled() const
{
    return m_fillSymbol;
}

int TeleconWxRasterPlot::getSymbol() const
{
    return m_symbol;
}

int TeleconWxRasterPlot::getSymbolSize() const
{
    return m_symbolSize;
}
