#include "teleconimplchartdir.h"

TeleconImplChartDir::TeleconImplChartDir()
    : m_teleconWxApp(nullptr) {}

TeleconImplChartDir::~TeleconImplChartDir()
{
    teleconStop();
}

shared_ptr<TeleconWindowImplChartDir> TeleconImplChartDir::getWindowImpl(int index)
{
    return m_windows[index];
}

void TeleconImplChartDir::teleconAppInit()
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

void TeleconImplChartDir::initializeWindows()
{
    for (shared_ptr<TeleconWindowImplChartDir> window : m_windows) {
        window->initialize();
    }
}

shared_ptr<TeleconWindow> TeleconImplChartDir::addWindow(string name)
{
    if (m_hasStarted) {
        cout << "telecon: Telecon has already started, windows may not be added." << endl;
        return shared_ptr<TeleconWindow>();
    }
    shared_ptr<TeleconWindowImplChartDir> window = make_shared<TeleconWindowImplChartDir>(name);
    m_windows.push_back(window);
    return window;
}

shared_ptr<TeleconWindow> TeleconImplChartDir::getWindow(int index)
{
    return getWindowImpl(index);
}

size_t TeleconImplChartDir::getNumWindows() const
{
    return m_windows.size();
}

shared_ptr<TeleconControls> TeleconImplChartDir::addControls(string name)
{
    shared_ptr<TeleconControls> telecon_controls = make_shared<TeleconControls>(name);
    m_controls.push_back(telecon_controls);
    return telecon_controls;
}

shared_ptr<TeleconControls> TeleconImplChartDir::getControls(int index)
{
    return m_controls[index];
}

size_t TeleconImplChartDir::getNumControls()
{
    return m_controls.size();
}