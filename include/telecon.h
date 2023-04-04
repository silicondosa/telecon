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

    TeleconWxApp* m_teleconWxApp;

    vector<TeleconWindow*> m_windows;

    void teleconAppInit();

public:
    void teleconStart();
    void teleconJoin();

    /**
     * Adds a window to the application and returns a pointer to it. The window must later be drawn with drawWindow().
     * 
     * \param name the name that will be displayed on the window.
     * \return A pointer to the TeleconWindow object created.
     */
    TeleconWindow* addWindow(string name);

    /**
     * \param index the index of the TeleconWindow to return.
     * \return A pointer to the TeleconWindow requested.
     */
    TeleconWindow* getWindow(int index);
    /**
     * \return The number of TeleconWindows added to the application.
     */
    size_t getNumWindows() const;

    TeleconWindow* getWindowByName(string name);
    TeleconChart* getChartByName(string windowName, string chartName);
    TeleconPlot* getPlotByName(string windowName, string chartName, string plotName);
};