#include "teleconwxapp.h"

TeleconWxApp::TeleconWxApp(TeleconImplChartDir* telecon)
	: m_telecon(telecon) {}

bool TeleconWxApp::OnInit()
{
    for (int i = 0; i < m_telecon->getNumWindows(); ++i) {
        shared_ptr<TeleconWindowImplChartDir> window = m_telecon->getWindowImpl(i);
        TeleconWxWindow* frame = new TeleconWxWindow(window);
        m_frames.push_back(frame);
        frame->Show(true);
    }

    // shared_ptr<TeleconControls> controls = make_shared<TeleconControls>("Controls Window");
    // controls->addToggle("Button1");
    // controls->addToggle("Button2");
    
    for(int i = 0; i < m_telecon->getNumControls(); i++){
        shared_ptr<TeleconControls> controls = m_telecon->getControls(i);
        TeleconWxControlsWindow* window = new TeleconWxControlsWindow(controls);
        m_controls_windows.push_back(window);
        window->Show(TRUE);

        // window->QueueEvent()
    }
    
    // TeleconWxControlsWindow* window = new TeleconWxControlsWindow(controls);
    // window->Show(TRUE);

    return true;
}
