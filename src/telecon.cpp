#include "telecon.h"

using namespace std;

shared_ptr<thread> Telecon::t = nullptr;

void Telecon::teleconAppInit(Telecon* mainAppInstance)
{
    wxApp::SetInstance(mainAppInstance);
    int argCount = 0;
    char** argv = nullptr;
    if (!wxEntryStart(argCount, argv)) {
        cerr << "wx failed to start\n";
        wxExit();
    }
    wxTheApp->CallOnInit();
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    wxEntryCleanup();
}

Telecon* Telecon::teleconStart()
{
    Telecon* telecon = new Telecon();
    t = make_shared<thread>(teleconAppInit, telecon);
    return telecon;
}

void Telecon::teleconJoin()
{
    t->join();
}

TeleconWindow* Telecon::addWindow(string name)
{
    TeleconWindow* window = new TeleconWindow(name);
    frameList.push_back(window);
    return window;

}
bool Telecon::OnInit()
{
    teleconMain();

    for(wxFrame* frame : frameList){
        frame->Show(true);
    }

    return true;
}

BEGIN_EVENT_TABLE(TeleconWindow, wxFrame)
END_EVENT_TABLE()