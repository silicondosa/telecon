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
#include "teleconwxwindow.h"
#include "teleconwindow.h"

using namespace std;

class Telecon : public wxApp
{
private:
    static shared_ptr<thread> t;

    vector<TeleconWindow*> m_windows;
    vector<TeleconWxWindow*> m_frames;

    static void teleconAppInit(promise<Telecon*> mainAppInstancePromise);

    // Private constructor because Telecon should only be created via teleconStart()
    Telecon() = default;

public:
    static future<Telecon*> teleconStart();
    static void teleconJoin();

    /**
     * Adds a window to the application and returns a pointer to it. The window must later be drawn with drawWindow().
     * 
     * \param name the name that will be displayed on the window.
     * \return A pointer to the TeleconWindow object created.
     */
    TeleconWindow* addWindow(string name);
    bool OnInit() override;

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
    TeleconWxPlot* getPlotByName(string windowName, string chartName, string plotName);

    /**
     * The initialization function for Telecon. All windows, charts, and plots should be added and drawn here.
     */
    virtual void teleconMain();
};