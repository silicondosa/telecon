#include "telecon.h"

using namespace std;

Telecon::Telecon()
    : m_hasStarted(false), m_hasStopped(false) {}

void Telecon::teleconStart()
{
    if (m_hasStarted) {
        cout << "telecon: Telecon has already started, cannot be started again" << endl;
        return;
    }
    m_hasStarted = true;
    initializeWindows();
    m_wxAppThread = thread(&Telecon::teleconAppInit, this);
}

void Telecon::teleconStop()
{
    for (int i = 0; i < getNumWindows(); i++) {
        shared_ptr<TeleconWindow> window = getWindow(i);
        window->requestQuit();
    }
    for (int i = 0; i < getNumWindows(); i++) {
        shared_ptr<TeleconWindow> window = getWindow(i);
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

shared_ptr<TeleconWindow> Telecon::getWindowByName(string name)
{
    for (int i = 0; i < getNumWindows(); i++) {
        shared_ptr<TeleconWindow> window = getWindow(i);
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