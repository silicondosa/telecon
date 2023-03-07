#pragma once

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <vector>
#include <memory>
#include <thread>
#include <future>

#include "chartdir.h"
#include "teleconrealtimechart.h"
#include "teleconwindow.h"

using namespace std;

class Telecon : public wxApp
{
private:
    static shared_ptr<thread> t;

    vector<TeleconWindow*> frameList;

    static void teleconAppInit(promise<Telecon*> mainAppInstancePromise);

    // Private constructor because Telecon should only be created via teleconStart()
    Telecon() = default;

public:
    static future<Telecon*> teleconStart();
    static void teleconJoin();

    TeleconWindow* addWindow(std::string name);
    bool OnInit() override;

    TeleconWindow* getWindow(int index);
    size_t getNumWindows() const;

    // Iterator functions
    vector<TeleconWindow*>::iterator begin();
    vector<TeleconWindow*>::iterator end();

    virtual void teleconMain();
};