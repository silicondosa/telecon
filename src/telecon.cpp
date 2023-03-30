#include "telecon.h"

using namespace std;

shared_ptr<thread> Telecon::t = nullptr;

void Telecon::teleconAppInit(promise<Telecon*> mainAppInstancePromise)
{
    Telecon* telecon = new Telecon();
    wxApp::SetInstance(telecon);
    int argCount = 0;
    char** argv = nullptr;
    if (!wxEntryStart(argCount, argv)) {
        cerr << "wx failed to start\n";
        wxExit();
    }
    wxTheApp->CallOnInit();
    // Telecon has been initialized and we are ready to keep our promise
    mainAppInstancePromise.set_value(telecon);
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    wxEntryCleanup();
}

future<Telecon*> Telecon::teleconStart()
{
    promise<Telecon*> teleconPromise;
    future<Telecon*> teleconFuture = teleconPromise.get_future();
    t = make_shared<thread>(teleconAppInit, move(teleconPromise));
    return teleconFuture;
}

void Telecon::teleconJoin()
{
    t->join();
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
    teleconMain();

    for(TeleconWindow* window : m_windows){
        TeleconFrame* frame = new TeleconFrame(window);
        m_frames.push_back(frame);
        frame->drawWindow();
        frame->Show(true);
    }

    return true;
}

BEGIN_EVENT_TABLE(TeleconFrame, wxFrame)
END_EVENT_TABLE()