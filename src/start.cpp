

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <thread>
#include <mutex>

#include "base.h"

using namespace std;

shared_ptr<thread> t;

void telecon_start_function(){
    wxApp::SetInstance( new MainApp() );
    int argCount = 1;
    char* argv[1] = { (char*)"telecon"};
    if(! wxEntryStart(argCount, argv)) {
        cerr << "wx failed to start\n";
        wxExit();
    }
    wxTheApp->CallOnInit();
    wxTheApp->OnRun();
}
void teleconStart(){
    t = make_shared<thread>(telecon_start_function);
}

void teleconJoin(){
    t->join();
}