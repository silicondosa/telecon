#pragma once

#include <vector>
#include <memory>
#include <cstring>

using namespace std;

template <typename T> class DataBuffer {
private:
	const size_t m_depth;
	vector<T> m_dataBuffer;
	void shiftDataAndInsert(T newValue) {
		memmove(&m_dataBuffer[0], &m_dataBuffer[1], sizeof(T) * (m_dataBuffer.size() - 1));
		m_dataBuffer[m_dataBuffer.size() - 1] = newValue;
	}
public:
	DataBuffer(size_t depth) : m_depth(depth) {}
	T& operator[](size_t index) {
		return m_dataBuffer[index];
	}
	const T& operator[](size_t index) const {
		return m_dataBuffer[index];
	}
	// Returns the current size of the buffer (always <= depth)
	size_t size() const {
		return m_dataBuffer.size();
	}
	// Returns the maximum possible size of the buffer (always >= size)
	size_t depth() const {
		return m_depth;
	}
	void insertNewValue(T newValue) {
		if (m_dataBuffer.size() < m_depth) {
			m_dataBuffer.push_back(newValue);
		} else {
			shiftDataAndInsert(newValue);
		}
	}
};
