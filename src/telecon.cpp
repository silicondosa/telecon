#include "telecon.h"

using namespace std;

Telecon::Telecon()
    : m_teleconWxApp(nullptr), m_hasStartedInitialization(false), m_hasFinishedInitialization(false), m_hasStopped(false) {}

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
    unique_lock lock(m_hasFinishedInitializationLock);
    m_hasFinishedInitialization = true;
    lock.unlock();
    m_hasFinishedInitializationCV.notify_all();
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    wxEntryCleanup();
    m_hasStopped = true;
}

void Telecon::teleconStart()
{
    m_hasStartedInitialization = true;
    for (auto& window : m_windows) {
        window->initialize();
    }
    m_wxAppThread = thread(&Telecon::teleconAppInit, this);
}

void Telecon::teleconStartBlocking()
{
    teleconStart();
    teleconWaitUntilInitialized();
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

bool Telecon::hasStartedInitialization()
{
    return m_hasStartedInitialization;
}

bool Telecon::hasFinishedInitialization()
{
    lock_guard lock(m_hasFinishedInitializationLock);
    return m_hasFinishedInitialization;
}

void Telecon::teleconWaitUntilInitialized()
{
    if (!m_hasStartedInitialization) {
        cout << "telecon: Attempted to wait until Telecon object has finished initializing, but no initialization was started." << endl;
    }
    unique_lock lock(m_hasFinishedInitializationLock);
    while (!m_hasFinishedInitialization) {
        m_hasFinishedInitializationCV.wait(lock);
    }
}

bool Telecon::hasStopped()
{
    return m_hasStopped;
}

shared_ptr<TeleconWindow> Telecon::addWindow(string name)
{
    if (m_hasStartedInitialization) {
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