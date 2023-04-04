#include "telecon.h"

using namespace std;

void Telecon::teleconAppInit()
{
    wxApp::SetInstance(this);
    int argCount = 0;
    char** argv = nullptr;
    if (!wxEntryStart(argCount, argv)) {
        cerr << "wx failed to start\n";
        wxExit();
    }
    hasStopped = false;
    wxTheApp->CallOnInit();
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    hasStopped = true;
    // wxEntryCleanup();
}

void Telecon::teleconStart()
{
    t = thread(&Telecon::teleconAppInit, this);
}

void Telecon::teleconJoin()
{
    t.join();
    wxEntryCleanup();
}

TeleconWindow* Telecon::addWindow(string name)
{
    TeleconWindow* window = new TeleconWindow(name);
    m_windows.push_back(window);
    return window;
}

TeleconWindow* Telecon::getWindow(int index)
{
    return m_windows[index];
}

size_t Telecon::getNumWindows() const
{
    return m_windows.size();
}

TeleconWindow* Telecon::getWindowByName(string name)
{
    for (vector<TeleconWindow*>::iterator i = m_windows.begin(); i != m_windows.end(); ++i) {
        if (name.compare((*i)->getTitle()) == 0) {
            return *i;
        }
    }
    return nullptr;
}

TeleconChart* Telecon::getChartByName(string windowName, string chartName)
{
    TeleconWindow* window = getWindowByName(windowName);
    return window == nullptr ? nullptr : window->getChartByName(chartName);
}

TeleconPlot* Telecon::getPlotByName(string windowName, string chartName, string plotName)
{
    TeleconWindow* window = getWindowByName(windowName);
    if (window == nullptr) {
        return nullptr;
    }
    TeleconChart* chart = window->getChartByName(chartName);
    return chart == nullptr ? nullptr : chart->getPlotByName(plotName);
}

bool Telecon::OnInit()
{
    for (TeleconWindow* window : m_windows) {
        TeleconWxWindow* frame = new TeleconWxWindow(window);
        m_frames.push_back(frame);
        frame->drawWindow();
        frame->Show(true);
    }

    return true;
}

BEGIN_EVENT_TABLE(TeleconWxWindow, wxFrame)
END_EVENT_TABLE()