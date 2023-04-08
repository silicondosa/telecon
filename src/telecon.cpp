#include "telecon.h"

using namespace std;

Telecon::Telecon()
    : m_teleconWxApp(nullptr), m_hasStarted(false), m_hasStopped(false) {}

Telecon::~Telecon()
{
    // m_teleconWxApp is automatically deleted by wxwidgets on close
    teleconStop();
}

void Telecon::teleconAppInit()
{
    m_teleconWxApp = new TeleconWxApp(this);
    wxApp::SetInstance(m_teleconWxApp);
    int argCount = 0;
    char** argv = nullptr;
    if (!wxEntryStart(argCount, argv)) {
        cerr << "wx failed to start\n";
        wxExit();
    }
    wxTheApp->CallOnInit();
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    wxEntryCleanup();
    m_hasStopped = true;
}

void Telecon::teleconStart()
{
    if (m_hasStarted) {
        cout << "telecon: Telecon has already started, cannot be started again" << endl;
        return;
    }
    m_hasStarted = true;
    for (auto& window : m_windows) {
        window->initialize();
    }
    m_wxAppThread = thread(&Telecon::teleconAppInit, this);
}

void Telecon::teleconStop()
{
    for (auto& window : m_windows) {
        window->requestQuit();
    }
    for (auto& window : m_windows) {
        window->waitUntilQuit();
    }
    if (m_wxAppThread.joinable()) {
        m_wxAppThread.join();
    }
}

bool Telecon::hasStarted()
{
    return m_hasStarted;
}

bool Telecon::hasStopped()
{
    return m_hasStopped;
}

shared_ptr<TeleconWindow> Telecon::addWindow(string name)
{
    if (m_hasStarted) {
        cout << "telecon: Telecon has already started, windows may not be added." << endl;
        return shared_ptr<TeleconWindow>();
    }
    shared_ptr<TeleconWindow> window = make_shared<TeleconWindow>(name);
    m_windows.push_back(window);
    return window;
}

shared_ptr<TeleconWindow> Telecon::getWindow(int index)
{
    return m_windows[index];
}

size_t Telecon::getNumWindows() const
{
    return m_windows.size();
}

shared_ptr<TeleconWindow> Telecon::getWindowByName(string name)
{
    for (auto window : m_windows) {
        if (name.compare(window->getTitle()) == 0) {
            return window;
        }
    }
    return nullptr;
}

shared_ptr<TeleconChart> Telecon::getChartByName(string windowName, string chartName)
{
    shared_ptr<TeleconWindow> window = getWindowByName(windowName);
    return window == nullptr ? nullptr : window->getChartByName(chartName);
}

shared_ptr<TeleconPlot> Telecon::getPlotByName(string windowName, string chartName, string plotName)
{
    shared_ptr<TeleconWindow> window = getWindowByName(windowName);
    if (window == nullptr) {
        return nullptr;
    }
    shared_ptr<TeleconChart> chart = window->getChartByName(chartName);
    return chart == nullptr ? nullptr : chart->getPlotByName(plotName);
}