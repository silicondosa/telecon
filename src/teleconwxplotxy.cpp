#include "teleconwxplotxy.h"

TeleconWxPlotXY::TeleconWxPlotXY(string plotTitle, int color, int lineWidth, LineType lineType, bool hasSymbol, int symbol, bool fillSymbol, int symbolSize, int depth)
    : TeleconWxPlot(plotTitle, color, depth), m_dataToAdd(new list<pair<double, double>>), m_xTimestamps(m_depth), m_yData(m_depth), m_lineWidth(lineWidth), m_lineType(lineType), m_hasSymbol(hasSymbol), m_symbol(symbol), m_fillSymbol(fillSymbol), m_symbolSize(symbolSize) {}

TeleconWxPlotXY::~TeleconWxPlotXY()
{
    const lock_guard<mutex> lock(m_dataToAddLock);
    delete m_dataToAdd;
}

list<pair<double, double>>* TeleconWxPlotXY::swapAndGetDataToAdd()
{
    list<pair<double, double>>* newDataToAdd = new list<pair<double, double>>();
    list<pair<double, double>>* oldDataToAdd = m_dataToAdd;

    const lock_guard<mutex> lock(m_dataToAddLock);
    m_dataToAdd = newDataToAdd;
    return oldDataToAdd;
}

void TeleconWxPlotXY::prepDataForDraw()
{
    list<pair<double, double>>* dataToAdd = swapAndGetDataToAdd();

    for (const auto& xyPair : *dataToAdd) {
        m_xTimestamps.insertNewValue(xyPair.first);
        m_yData.insertNewValue(xyPair.second);
    }

    delete dataToAdd;
}

double TeleconWxPlotXY::getLeftmostX() const
{
    return m_xTimestamps[0];
}

double TeleconWxPlotXY::getRightmostX() const
{
    return m_xTimestamps[m_xTimestamps.size() - 1];
}

string TeleconWxPlotXY::getLatestValueString() const
{
    // Can't believe this is still the only way to do this in C++17 (formatting directly into c++ string isn't added until C++20)
    int size_s = std::snprintf(nullptr, 0, "%.2f", m_yData[m_yData.size() - 1]) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf(new char[size_s]);
    std::snprintf(buf.get(), size_s, "%.2f", m_yData[m_yData.size() - 1]);
    return string(buf.get());
}

bool TeleconWxPlotXY::isIncludedInLegend() const
{
    return true;
}

void TeleconWxPlotXY::addToChart(XYChart* chart) {
    if (m_yData.size() <= 0) {
        return;
    }
    // This integer represents both the color and dash status (solid, dashed, or none) of the chart
    int chartDirColor;
    if (m_lineType == LT_SOLID) {
        chartDirColor = m_color;
    }
    else { // Solid or none
        chartDirColor = chart->dashLineColor(m_color, Chart::DashLine);
    }
    LineLayer* layer = chart->addLineLayer();

    DataSet* dataSet = layer->addDataSet(DoubleArray(&m_yData[0], (int)m_yData.size()), chartDirColor, (string("\\") + m_plotTitle).c_str());

    dataSet->setLineWidth(m_lineWidth);

    if (m_hasSymbol) {
        dataSet->setDataSymbol(m_symbol, m_symbolSize, m_fillSymbol ? m_color : Chart::Transparent, m_color);
    }

    // The x-coordinates are the timeStamps.
    layer->setXData(DoubleArray(&m_xTimestamps[0], (int)m_xTimestamps.size()));
}

size_t TeleconWxPlotXY::size() const
{
    return m_xTimestamps.size();
}

void TeleconWxPlotXY::pushData(double xTimestamp, double yData)
{
    const lock_guard<mutex> lock(m_dataToAddLock);

    m_dataToAdd->push_back(make_pair(xTimestamp, yData));

    if (m_dataToAdd->size() > m_depth) {
        m_dataToAdd->pop_front();
    }

    // lock_guard automatically releases m_dataToAddLock when it goes out of scope
}

bool TeleconWxPlotXY::isSymbolFilled() const
{
    return m_fillSymbol;
}

int TeleconWxPlotXY::getSymbol() const
{
    return m_symbol;
}

int TeleconWxPlotXY::getSymbolSize() const
{
    return m_symbolSize;
}