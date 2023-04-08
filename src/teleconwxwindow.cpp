#include "teleconwxwindow.h"

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/tglbtn.h>

static const int chartRefreshIntervals[8] = { 250, 500, 750, 1000, 1250, 1500, 1750, 2000 };

TeleconWxWindow::TeleconWxWindow(shared_ptr<TeleconWindow> window)
    : wxFrame((wxFrame*)NULL, -1, window->getTitle(), wxDefaultPosition, wxDefaultSize), m_window(window)
{

    wxBoxSizer* itemBoxSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(itemBoxSizer);

    m_viewOptionsBox = new wxStaticBox(this, wxID_ANY, wxEmptyString);
    m_viewOptionsBoxSizer = new wxStaticBoxSizer(m_viewOptionsBox, wxHORIZONTAL);
    itemBoxSizer->Add(m_viewOptionsBoxSizer, 0, wxGROW | wxALL, FromDIP(3));;

    m_playButton = new wxToggleButton(m_viewOptionsBox, ID_PLAY, _(" &Run"), wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
    m_viewOptionsBoxSizer->Add(m_playButton, 0, wxGROW | wxALL, FromDIP(3));
    m_pauseButton = new wxToggleButton(m_viewOptionsBox, ID_PAUSE, _(" &Freeze"), wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
    m_viewOptionsBoxSizer->Add(m_pauseButton, 0, wxGROW | wxALL, FromDIP(3));
    m_saveButton = new wxButton(m_viewOptionsBox, wxID_SAVE, _(" &Save"), wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
    m_viewOptionsBoxSizer->Add(m_saveButton, 0, wxGROW | wxALL, FromDIP(3));
    wxStaticText* graphRefreshIntervalStaticText = new wxStaticText(m_viewOptionsBox, wxID_STATIC, _("Refresh Interval (ms)"), wxDefaultPosition, wxDefaultSize, 0);
    m_viewOptionsBoxSizer->Add(graphRefreshIntervalStaticText, 0, wxALIGN_TOP | wxALL, FromDIP(3));
    wxArrayString m_refreshIntervalStrings;
    for (auto i : chartRefreshIntervals)
    {
        m_refreshIntervalStrings.Add(wxString::Format("%d", i));
    }
    m_refreshIntervalSelector = new wxChoice(m_viewOptionsBox, ID_REFRESH_INTERVAL, wxDefaultPosition, wxDefaultSize, m_refreshIntervalStrings, 0);
    m_refreshIntervalSelector->SetStringSelection(wxString::Format("%d", chartRefreshIntervals[0]));
    m_viewOptionsBoxSizer->Add(m_refreshIntervalSelector, 0, wxGROW | wxALL, FromDIP(3));

    //add charts to main sizer
    for (int i = 0; i < m_window->getNumCharts(); i++) {
        TeleconWxChart* chart = new TeleconWxChart(m_window->getChart(i), this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxNO_BORDER, wxASCII_STR(wxPanelNameStr));
        m_charts.push_back(chart);
    }
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

EVT_TOGGLEBUTTON(ID_PLAY, TeleconWxWindow::OnPlayClick)
EVT_TOGGLEBUTTON(ID_PAUSE, TeleconWxWindow::OnPauseClick)
EVT_CHOICE(ID_REFRESH_INTERVAL, TeleconWxWindow::OnChartRefreshIntervalSelected)
//EVT_BUTTON(wxID_SAVE, TeleconWxWindow::OnSave)

END_EVENT_TABLE()

// Event handler
void TeleconWxWindow::OnPlayClick(wxCommandEvent& event)
{
    m_playButton->SetValue(true);
    m_pauseButton->SetValue(false);
    for (int i = 0; i < m_window->getNumCharts(); i++) {
        m_charts[i]->setPlay();
    }
}

// Event handler
void TeleconWxWindow::OnPauseClick(wxCommandEvent& event)
{
    m_playButton->SetValue(false);
    m_pauseButton->SetValue(true);
    for (int i = 0; i < m_window->getNumCharts(); i++) {
        m_charts[i]->setPause();
    }
}

// Event handler
void TeleconWxWindow::OnChartRefreshIntervalSelected(wxCommandEvent& event)
{
    long interval;
    (m_refreshIntervalSelector->GetString(m_refreshIntervalSelector->GetSelection())).ToLong(&interval);
    for (int i = 0; i < m_window->getNumCharts(); i++) {
        m_charts[i]->setRefresh(interval);
    }
}
 
//// Event handler
//void TeleconWxWindow::OnSave(wxCommandEvent& event)
//{
//    wxFileDialog saveFileDialog(this, _("Save graphics file"), "", "chartdirector_demo",
//        "PNG (*.png)|*.png|JPG (*.jpg)|*.jpg|GIF (*.gif)|*.gif|BMP (*.bmp)|*.bmp|SVG (*.svg)|*.svg|PDF (*.pdf)|*.pdf", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
//    if (saveFileDialog.ShowModal() == wxID_CANCEL)
//        return; // the user changed idea...
//
//    // save the current contents in the file;
//    wxString fileName = saveFileDialog.GetPath();
//    if (!fileName.IsEmpty())
//    {
//        // Save the chart
//        BaseChart* c = m_chartViewer->getChart();
//        if (0 != c)
//        {
//            c->makeChart(fileName.ToUTF8());
//        }
//    }
//}

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
