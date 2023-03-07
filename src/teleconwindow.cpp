#include "teleconwindow.h"

TeleconWindow::TeleconWindow(const wxString& title)
    : wxFrame((wxFrame*)NULL, -1, title, wxDefaultPosition, wxDefaultSize)
{

    wxBoxSizer* itemBoxSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(itemBoxSizer);

    for (auto panel_element : list_charts) {
        itemBoxSizer->Add(panel_element, 1, wxGROW);
    }

    SetSizerAndFit(itemBoxSizer);
}

TeleconRealTimeChart* TeleconWindow::addChart(string title, string ylabel, string xlabel, int dataInterval, int memoryDepth, ColorSequenceMode colorSequenceMode)
{
    TeleconRealTimeChart* realTimePanel = new TeleconRealTimeChart(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, title, xlabel, ylabel, wxTAB_TRAVERSAL | wxNO_BORDER, wxASCII_STR(wxPanelNameStr), colorSequenceMode, dataInterval, memoryDepth);
    list_charts.push_back(realTimePanel);
    return realTimePanel;
}

void TeleconWindow::drawWindow()
{
    wxBoxSizer* itemBoxSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(itemBoxSizer);
    for (auto panel_element : list_charts) {
        itemBoxSizer->Add(panel_element, 1, wxGROW);
    }
    SetSizerAndFit(itemBoxSizer);
}

vector<TeleconRealTimeChart*>::iterator TeleconWindow::begin()
{
    return list_charts.begin();
}

vector<TeleconRealTimeChart*>::iterator TeleconWindow::end()
{
    return list_charts.end();
}

TeleconRealTimeChart* TeleconWindow::getChart(int index)
{
    return list_charts[index];
}

size_t TeleconWindow::getNumCharts() const
{
    return list_charts.size();
}
