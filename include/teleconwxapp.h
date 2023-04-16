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
 * Main GUI for telecon object, inherits from wxApp. Contains a vector of TeleconWxWindows (m_frames)
 */
class TeleconWxApp : public wxApp 
{
private:
    Telecon* m_telecon;
    vector<TeleconWxWindow*> m_frames;
    vector<TeleconWxControlsWindow*> m_controls_windows;
public:
    /**
     * Constructor that takes in a telecon object pointer.
     * 
     * \param telecon type Telecon*
     */
    TeleconWxApp(Telecon* telecon);

    /**
     * Initialization function that overrides wxApp's OnInit() function.
     * 
     * \return true after done initializing
     */
    bool OnInit() override;
};