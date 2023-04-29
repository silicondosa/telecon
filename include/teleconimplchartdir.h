#pragma once

#include "telecon.h"
#include "teleconwindowimplchartdir.h"
#include "teleconwxapp.h"

class TeleconWxApp; // Forward declaration needed due to circular dependency between telecon and app

/**
 * The wxChartDir implementation of the Telecon interface..
 */
class TeleconImplChartDir : public Telecon {
private:
    /** A reference to the TeleconWxApp object, which sets up the UI as directed by the Telecon object. */
    TeleconWxApp* m_teleconWxApp;

    /** A list of the windows that have been added to the app. */
    vector<shared_ptr<TeleconWindowImplChartDir>> m_windows;
public:
    /**
     * \copydoc Telecon::Telecon
     */
    TeleconImplChartDir();
    /**
     * Closes and windows that are still open and exits, then deletes the Telecon object.
     * This may be a long-running operation if there are still windows open.
     */
    ~TeleconImplChartDir();
    /**
     * \param index the index of the TeleconWindow to return as a TeleconWindowImplChartDir, relative to the order added.
     * \return A pointer to the TeleconWindow requested.
     */
    shared_ptr<TeleconWindowImplChartDir> getWindowImpl(int index);

    /** Starts running the app. */
    virtual void teleconAppInit() override;

    /** Initializes the windows, preventing them from being changed. */
    virtual void initializeWindows() override;

    /**
     * \copydoc Telecon::addWindow
     */
    virtual shared_ptr<TeleconWindow> addWindow(string name) override;

    /**
     * \copydoc Telecon::getWindow
     */
    virtual shared_ptr<TeleconWindow> getWindow(int index) override;

    /**
     * \copydoc Telecon::getNumWindows
     */
    virtual size_t getNumWindows() const override;

    /**
     * \copydoc Telecon::addControls
     */
    virtual shared_ptr<TeleconControls> addControls(string name) override;

    /**
     * \copydoc Telecon::getControls
     */
    virtual shared_ptr<TeleconControls> getControls(int index) override;

    /**
     * \copydoc Telecon::getNumcontrols
     */
    virtual size_t getNumControls() override;
};
