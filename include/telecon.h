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
#include "teleconcontrols.h"

class TeleconWxApp; // Forward declaration needed due to circular dependency between telecon and app

using namespace std;

/**
 * This is the primary user-level entry point for all Telecon behavior.
 * This class creates and manages windows, which in turn create and manage lower-level items such as charts and plots.
 * 
 * There should only ever be one Telecon object active (started) at a time.
 * After a Telecon object is stopped or deleted, it is safe to start another if necessary.
 * However, each object can only be run once. After the object is stopped, it may not be started again.
 * 
 * Telecon is inherently thread-safe with regard to the controller (calling) thread and the UI thread (which is created and managed by Telecon).
 * However, if a Telecon object is used by multiple controller threads, external synchronization must be used to prevent concurrent access to member functions.
 */
class Telecon
{
private:
    /** The UI thread, in which all long-running actions must occur. */
    thread m_wxAppThread;

    /** True if Telecon::teleconStart has been called, or false before then. */
    std::atomic_bool m_hasStarted;
    /**
     * True once all UI elements have completely closed and finished any cleanup, or false before then.
     * Could be true even if Telecon::teleconStop has not been called; for example, if the user closes all windows manually.
     */
    std::atomic_bool m_hasStopped;

    /** A reference to the TeleconWxApp object, which sets up the UI as directed by the Telecon object. */
    TeleconWxApp* m_teleconWxApp;

    /** A list of the windows that have been added to the app. */
    vector<shared_ptr<TeleconWindow>> m_windows;

    vector<shared_ptr<TeleconControls>> m_controls;

    /** Starts running the app. */
    void teleconAppInit();

public:
    /**
     * Starts the actual windows that display content, based on the TeleconWindow objects previously added.
     * This function should only be called once.
     */
    void teleconStart();

    /**
     * Closes any windows that are still open and exits.
     */
    void teleconStop();

    /**
     * Constructs a new empty Telecon object with no windows.
     * 
     */
    Telecon();

    /**
     * Closes and windows that are still open and exits, then deletes the Telecon object.
     * This may be a long-running operation if there are still windows open.
     */
    ~Telecon();

    /**
     * \return Returns true if the Telecon object has already started (or finished) initializing displayed windows, or false before then.
     */
    bool hasStarted();

    /**
     * \return Returns true if all windows have been closed (either manually by the user or by teleconStop) and Telecon has finished its subsequent cleanup.
     * 
     * \sa Telecon::teleconStop
     */
    bool hasStopped();

    /**
     * Adds a window to the application that will be displayed when teleconStart is called.
     * Should not be called after teleconStart.
     * 
     * \param name the name that will be displayed on the window.
     * \return A pointer to the TeleconWindow object created.
     */
    shared_ptr<TeleconWindow> addWindow(string name);

    /**
     * \param index the index of the TeleconWindow to return, relative to the order added.
     * \return A pointer to the TeleconWindow requested.
     */
    shared_ptr<TeleconWindow> getWindow(int index);

    /**
     * \return The number of TeleconWindows added to the application.
     */
    size_t getNumWindows() const;

    /**
     * \param name the name of the TeleconWindow to return. If multiple windows share the same name, no guarantee is made about which will be returned.
     * \return A pointer to a window with the given name, or a null pointer if no window has that name.
     */
    shared_ptr<TeleconWindow> getWindowByName(string name);

    /**
     * \param windowName the name of the TeleconWindow in which to search for a chart with the given name. If multiple windows share the same name, no guarantee is made about which will be returned.
     * \param chartName the name of the TeleconChart to return. If multiple charts share the same name, no guarantee is made about which will be returned.
     * \return A pointer to a chart with the given name, or a null pointer if no chart in the given window has that name.
     */
    shared_ptr<TeleconChart> getChartByName(string windowName, string chartName);

    /**
     * \param windowName the name of the TeleconWindow in which to search for a plot with the given name. If multiple windows share the same name, no guarantee is made about which will be returned.
     * \param chartName the name of the TeleconChart in which to search for a plot with the given name. If multiple charts share the same name, no guarantee is made about which will be returned.
     * \param plotName the name of the TeleconPlot to return. If multiple plots share the same name, no guarantee is made about which will be returned.
     * \return A pointer to a plot with the given name, or a null pointer if no plot in the given chart and window has that name.
     */
    shared_ptr<TeleconPlot> getPlotByName(string windowName, string chartName, string plotName);

    /**
     * Adds a controls window to the application that will be displayed when teleconStart is called.
     * Should not be called after teleconStart.
     * 
     * \param name the name that will be displayed on the window.
     * \return A pointer to the TeleconControls object created.
     */
    shared_ptr<TeleconControls> addControls(string name);

     /**
     * \param index the index of the TeleconControls to return, relative to the order added.
     * \return A pointer to the TeleconControls requested.
     */
    shared_ptr<TeleconControls> getControls(int index);

    /**
     * \return The number of TeleconControls added to the application.
     */
    size_t getNumControls();


};