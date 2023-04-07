#include "teleconwxapp.h"

TeleconWxApp::TeleconWxApp(Telecon* telecon)
	: m_telecon(telecon) {}

bool TeleconWxApp::OnInit()
{
    for (int i = 0; i < m_telecon->getNumWindows(); ++i) {
        shared_ptr<TeleconWindow> window = m_telecon->getWindow(i);
        TeleconWxWindow* frame = new TeleconWxWindow(window);
        m_frames.push_back(frame);
        frame->Show(true);
    }

    return true;
}
