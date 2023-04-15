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

class TeleconWxApp : public wxApp 
{
private:
    Telecon* m_telecon;
    vector<TeleconWxWindow*> m_frames;
    vector<TeleconWxControlsWindow*> m_controls_windows;
public:
    TeleconWxApp(Telecon* telecon);
    bool OnInit() override;
};