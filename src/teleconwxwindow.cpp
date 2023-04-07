#include "teleconwxwindow.h"

TeleconWxWindow::TeleconWxWindow(shared_ptr<TeleconWindow> window)
    : wxFrame((wxFrame*)NULL, -1, window->getTitle(), wxDefaultPosition, wxDefaultSize), m_window(window)
{
    for (int i = 0; i < m_window->getNumCharts(); i++) {
        TeleconWxChart* chart = new TeleconWxChart(m_window->getChart(i), this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxNO_BORDER, wxASCII_STR(wxPanelNameStr));
        m_charts.push_back(chart);
    }
    wxBoxSizer* itemBoxSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(itemBoxSizer);
    for (auto panel_element : m_charts) {
        itemBoxSizer->Add(panel_element, 1, wxGROW);
    }
    SetSizerAndFit(itemBoxSizer);

    m_checkQuitTimer = new wxTimer(this, ID_QUIT_TIMER);
    m_checkQuitTimer->Start(100);
}

TeleconWxWindow::~TeleconWxWindow() {
    m_checkQuitTimer->Stop();
}

BEGIN_EVENT_TABLE(TeleconWxWindow, wxFrame)

EVT_CLOSE(TeleconWxWindow::onClose)
EVT_TIMER(ID_QUIT_TIMER, TeleconWxWindow::checkQuit)

END_EVENT_TABLE()

void TeleconWxWindow::checkQuit(wxTimerEvent& event)
{
    if (m_window->hasRequestedQuit()) {
        Close();
    }
}

void TeleconWxWindow::onClose(wxCloseEvent& event)
{
    m_window->setHasQuit();
    event.Skip();
}
