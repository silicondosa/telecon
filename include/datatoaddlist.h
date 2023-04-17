#pragma once

#include <mutex>
#include <list>
#include <memory>

/**
 * Header-only template class to add data to plots in a thread-safe fashion.
 * For use with TeleconPlots.
 */
template <typename T> class DataToAddList
{
private:
    // Lock to provide thread-safety, allowing data to be moved from the controller thread(s) to the UI thread.
    mutable mutex m_lock;

    /*
     * The list of values that should be added to the plot the next time it is drawn.
     * We use a list rather than a vector for efficiency: every list operation we use is O(1), while with a vector we might have O(n) operations.
     */
    shared_ptr<list<T>> m_dataToAdd;

    /*
     * The maximum possible size of the list.
     * Should be the same as the depth of the parent plot; there's no reason to keep more values in his list than can be added to the plot, as the oldest ones would be discarded.
     */
    const size_t m_depth;
public:
    /**
     * Constructs a DataToAddList with the given maximum size.
     * 
     * \param depth the depth (maximum size) of the list.
     */
    DataToAddList(size_t depth) : m_depth(depth), m_dataToAdd(make_shared<list<T>>()) {}

    /**
     * Adds a data point to the list to be drawn later.
     * 
     * \param dataPoint the data point to be added.
     */
    void addDataPoint(T dataPoint)
    {
        const lock_guard<mutex> lk(m_lock);
        m_dataToAdd->push_back(dataPoint);
        // There's no point in keeping more data than can possibly be added in the next update
        if (m_dataToAdd->size() > m_depth) {
            m_dataToAdd->pop_front();
        }
    }

    /**
     * Clears the list, and returns its previous contents.
     * Should be called before a plot is drawn to the screen.
     * 
     * \return A pointer to a list of every data point added since the last time the list was cleared.
     */
    shared_ptr<list<T>> getDataAndClearList()
    {
        // After swap, will contain the old data that should be returned
        shared_ptr<list<T>> oldDataToAdd = make_shared<list<T>>();

        const lock_guard<mutex> lk(m_lock);
        m_dataToAdd.swap(oldDataToAdd);
        return oldDataToAdd;
    }

    /**
     * \return The current size of the buffer (always <= depth).
     */
    size_t getSize()
    {
        const lock_guard<mutex> lk(m_lock);
        return m_dataToAdd->size();
    }

    /**
     * \return The depth (maximum possible size) of the buffer (always >= size).
     */
    size_t getDepth()
    {
        return m_depth;
    }
};
