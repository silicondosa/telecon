#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <vector>
#include "telecon.h"
#include "teleconwxwindow.h"
#include "teleconwxcontrolswindow.h"

class Telecon; // Forward declaration needed due to circular dependency between telecon and app

/**
 * Main GUI for telecon object, inherits from wxApp.
 * Holds references to all subsections of the app, such as TeleconWxWindows.
 * 
 * As opposed to ::Telecon, this object is an _implementation_ of the data described in ::Telecon and related objects.
 * It is created automatically by ::Telecon, and should not be interacted with directly by the user.
 * 
 * This class, and all classes starting with the prefix TeleconWx, are wxChartDir-based implementations of charts and plots.
 * In the future, Telecon may support other implementations using other frameworks, which would use the same user-level objects to interact (such as ::Telecon, ::TeleconWindow, ::TeleconChart, and ::TeleconPlot).
 */
class TeleconWxApp : public wxApp 
{
private:
    Telecon* m_telecon;
    vector<TeleconWxWindow*> m_frames;
    vector<TeleconWxControlsWindow*> m_controls_windows;
public:
    /**
     * Constructs the app based on the specification of the provided ::Telecon object.
     * 
     * \param telecon A pointer to the ::Telecon object representing the app.
     */
    TeleconWxApp(Telecon* telecon);

    /**
     * Initializes the app, adding windows according to the specifications of the ::Telecon object.
     * 
     * \return True (initialization completed successfully).
     */
    bool OnInit() override;
};