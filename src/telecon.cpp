#include "telecon.h"

using namespace std;

shared_ptr<thread> Telecon::t = nullptr;

void Telecon::teleconAppInit(promise<Telecon*> mainAppInstancePromise)
{
    Telecon* telecon = new Telecon();
    wxApp::SetInstance(telecon);
    int argCount = 0;
    char** argv = nullptr;
    if (!wxEntryStart(argCount, argv)) {
        cerr << "wx failed to start\n";
        wxExit();
    }
    wxTheApp->CallOnInit();
    // Telecon has been initialized and we are ready to keep our promise
    mainAppInstancePromise.set_value(telecon);
    wxTheApp->OnRun();
    wxTheApp->OnExit();
    wxEntryCleanup();
}

future<Telecon*> Telecon::teleconStart()
{
    promise<Telecon*> teleconPromise;
    future<Telecon*> teleconFuture = teleconPromise.get_future();
    t = make_shared<thread>(teleconAppInit, move(teleconPromise));
    return teleconFuture;
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

TeleconWindow* Telecon::getWindow(int index)
{
    return frameList[index];
}

size_t Telecon::getNumWindows() const
{
    return frameList.size();
}

bool Telecon::OnInit()
{
    teleconMain();

    for(wxFrame* frame : frameList){
        frame->Show(true);
    }

    return true;
}

vector<TeleconWindow*>::iterator Telecon::begin()
{
    return frameList.begin();
}

vector<TeleconWindow*>::iterator Telecon::end()
{
    return frameList.end();
}

BEGIN_EVENT_TABLE(TeleconWindow, wxFrame)
END_EVENT_TABLE()