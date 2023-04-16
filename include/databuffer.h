#pragma once

#include <vector>
#include <memory>
#include <cstring>

using namespace std;

/**
 * DataBuffer template used for buffering data from data source to be used in the plots.
 */
template <typename T> class DataBuffer {

private:

	/**
	 * Variable to keep track of depth.
	 */
	const size_t m_depth;

	/**
	 * Vector of values that represent the buffer.
	 */
	vector<T> m_dataBuffer;

	/**
	 * Circular buffer implementation. If the buffer is full, remove the first value and shift all other values down to make space.
	 * 
	 * \param newValue value to add to the end of the buffer
	 */
	void shiftDataAndInsert(T newValue) {
		memmove(&m_dataBuffer[0], &m_dataBuffer[1], sizeof(T) * (m_dataBuffer.size() - 1));
		m_dataBuffer[m_dataBuffer.size() - 1] = newValue;
	}

public:

	/**
	 * Constructor that takes in depth as parameter.
	 * 
	 * \param depth depth of the databuffer
	 */
	DataBuffer(size_t depth) : m_depth(depth) {}
	T& operator[](size_t index) {
		return m_dataBuffer[index];
	}

	/**
	 * Index operator, gets the value in buffer at given index.
	 * 
	 * \param index index of value to get
	 * \return value address at index
	 */
	const T& operator[](size_t index) const {
		return m_dataBuffer[index];
	}
	/**
	 * Getter function for buffer size.
	 * 
	 * \return the current size of the buffer (always <= depth)
	 */
	size_t size() const {
		return m_dataBuffer.size();
	}

	/**
	 * Getter function for buffer depth (m_depth).
	 * 
	 * \return the maximum possible size of the buffer(always >= size)
	 */
	size_t depth() const {
		return m_depth;
	}

	/**
	 * Function to push back a value into the databuffer.
	 * 
	 * \param newValue generic type to push back into the buffer
	 */
	void insertNewValue(T newValue) {
		if (m_dataBuffer.size() < m_depth) {
			m_dataBuffer.push_back(newValue);
		} else {
			shiftDataAndInsert(newValue);
		}
	}
};
