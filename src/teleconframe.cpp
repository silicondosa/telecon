#include "teleconframe.h"

TeleconFrame::TeleconFrame(TeleconWindow* window)
    : wxFrame((wxFrame*)NULL, -1, window->getTitle(), wxDefaultPosition, wxDefaultSize), m_window(window)
{

    wxBoxSizer* itemBoxSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(itemBoxSizer);

    for (auto panel_element : m_charts) {
        itemBoxSizer->Add(panel_element, 1, wxGROW);
    }

    SetSizerAndFit(itemBoxSizer);
}

void TeleconFrame::drawWindow()
{
    for (int i = 0; i < m_window->getNumCharts(); i++) {
        TeleconRealTimeChart* chart = new TeleconRealTimeChart(m_window->getChart(i), this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxNO_BORDER, wxASCII_STR(wxPanelNameStr));
        m_charts.push_back(chart);
    }
    wxBoxSizer* itemBoxSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(itemBoxSizer);
    for (auto panel_element : m_charts) {
        itemBoxSizer->Add(panel_element, 1, wxGROW);
    }
    SetSizerAndFit(itemBoxSizer);
}
