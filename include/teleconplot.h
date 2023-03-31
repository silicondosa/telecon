#pragma once

#include <string>

using namespace std;

class TeleconPlot {
public:
    // Returns the current size of the data buffer(s)
    virtual size_t size() const = 0;
    // Returns the capacity (maximum size) of the data buffer(s)
    virtual size_t depth() const = 0;
    virtual int getColor() const = 0;
    virtual const string getPlotTitle() const = 0;
};