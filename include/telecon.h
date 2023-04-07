#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <vector>
#include <memory>
#include <thread>
#include <future>

#include "chartdir.h"
#include "teleconwindow.h"
#include "teleconwxapp.h"

class TeleconWxApp; // Forward declaration needed due to circular dependency between telecon and app

using namespace std;

class Telecon
{
private:
    thread m_wxAppThread;

    std::atomic_bool m_hasStartedInitialization;
    mutex m_hasFinishedInitializationLock;
    condition_variable m_hasFinishedInitializationCV;
    bool m_hasFinishedInitialization;
    std::atomic_bool m_hasStopped;

    TeleconWxApp* m_teleconWxApp;

    vector<shared_ptr<TeleconWindow>> m_windows;

    void teleconAppInit();

public:
    void teleconStart();
    void teleconStartBlocking();
    void teleconStop();
    Telecon();
    ~Telecon();

    bool hasStartedInitialization();
    bool hasFinishedInitialization();
    void teleconWaitUntilInitialized();
    bool hasStopped();

    /**
     * Adds a window to the application and returns a pointer to it. The window must later be drawn with drawWindow().
     * 
     * \param name the name that will be displayed on the window.
     * \return A pointer to the TeleconWindow object created.
     */
    shared_ptr<TeleconWindow> addWindow(string name);

    /**
     * \param index the index of the TeleconWindow to return.
     * \return A pointer to the TeleconWindow requested.
     */
    shared_ptr<TeleconWindow> getWindow(int index);
    /**
     * \return The number of TeleconWindows added to the application.
     */
    size_t getNumWindows() const;

    shared_ptr<TeleconWindow> getWindowByName(string name);
    shared_ptr<TeleconChart> getChartByName(string windowName, string chartName);
    shared_ptr<TeleconPlot> getPlotByName(string windowName, string chartName, string plotName);
};