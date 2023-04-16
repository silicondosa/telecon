#pragma once

#include <mutex>
#include <list>
#include <memory>

template <typename T> class DataToAddList
{
private:
    mutable mutex m_lock;
    shared_ptr<list<T>> m_dataToAdd;
    const size_t m_depth;
public:
    DataToAddList(size_t depth) : m_depth(depth), m_dataToAdd(make_shared<list<T>>()) {}
    void addDataPoint(T dataPoint)
    {
        const lock_guard<mutex> lk(m_lock);
        m_dataToAdd->push_back(dataPoint);
        // There's no point in keeping more data than can possibly be added in the next update
        if (m_dataToAdd->size() > m_depth) {
            m_dataToAdd->pop_front();
        }
    }
    shared_ptr<list<T>> getDataAndClearList()
    {
        // After swap, will contain the old data that should be returned
        shared_ptr<list<T>> oldDataToAdd = make_shared<list<T>>();

        const lock_guard<mutex> lk(m_lock);
        m_dataToAdd.swap(oldDataToAdd);
        return oldDataToAdd;
    }
    size_t getSize()
    {
        const lock_guard<mutex> lk(m_lock);
        return m_dataToAdd->size();
    }
    size_t getDepth()
    {
        return m_depth;
    }
};
