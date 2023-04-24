#pragma once

#include "telecon.h"
#include "teleconwindowimplchartdir.h"
#include "teleconwxapp.h"

class TeleconWxApp; // Forward declaration needed due to circular dependency between telecon and app

class TeleconImplChartDir : public Telecon {
private:
    /** A reference to the TeleconWxApp object, which sets up the UI as directed by the Telecon object. */
    TeleconWxApp* m_teleconWxApp;

    /** A list of the windows that have been added to the app. */
    vector<shared_ptr<TeleconWindowImplChartDir>> m_windows;

    vector<shared_ptr<TeleconControls>> m_controls;
public:
    TeleconImplChartDir();
    /**
     * Closes and windows that are still open and exits, then deletes the Telecon object.
     * This may be a long-running operation if there are still windows open.
     */
    ~TeleconImplChartDir();
    shared_ptr<TeleconWindowImplChartDir> getWindowImpl(int index);

    // Inherited via Telecon
    virtual void teleconAppInit() override;
    virtual void initializeWindows() override;
    virtual shared_ptr<TeleconWindow> addWindow(string name) override;
    virtual shared_ptr<TeleconWindow> getWindow(int index) override;
    virtual size_t getNumWindows() const override;
    virtual shared_ptr<TeleconControls> addControls(string name) override;
    virtual shared_ptr<TeleconControls> getControls(int index) override;
    virtual size_t getNumControls() override;
};
