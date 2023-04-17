#pragma once

#include <vector>
#include <memory>
#include <cstring>

using namespace std;

/**
 * Header-only template class representing a fixed-size buffer, used to buffer data for the plots.
 */
template <typename T> class DataBuffer {
private:
	// The maximum possible size of the buffer.
	const size_t m_depth;

	// Vector of values that represent the buffer.
	vector<T> m_dataBuffer;

	// Circular buffer implementation. If the buffer is full, remove the oldest value and shift all other values down to make space.
	void shiftDataAndInsert(T newValue) {
		memmove(&m_dataBuffer[0], &m_dataBuffer[1], sizeof(T) * (m_dataBuffer.size() - 1));
		m_dataBuffer[m_dataBuffer.size() - 1] = newValue;
	}
public:
	/**
	 * Constructs a DataBuffer with the given maximum size.
	 * 
	 * \param depth the depth (maximum size) of the databuffer.
	 */
	DataBuffer(size_t depth) : m_depth(depth) {}

    /**
     * Index operator, gets the value in buffer at given index at returns it as a reference.
     * In most cases, this should not be used.
     * If possible, prefer constant index operator (for reading) or insertNewValue (for writing).
     *
     * \param index index of value to get.
     * \return The value at index.
     * \sa DataBuffer::operator[](size_t index) const
     * \sa DataBuffer::insertNewValue
     */
	T& operator[](size_t index) {
		return m_dataBuffer[index];
	}

	/**
	 * Constant index operator, gets the value in buffer at given index and returns it as a constant reference.
	 * 
	 * \param index index of value to get
	 * \return The value at index
	 */
	const T& operator[](size_t index) const {
		return m_dataBuffer[index];
	}

	/**
	 * \return The current size of the buffer (always <= depth).
	 */
	size_t size() const {
		return m_dataBuffer.size();
	}

	/**
	 * \return The depth (maximum possible size) of the buffer (always >= size).
	 */
	size_t depth() const {
		return m_depth;
	}

	/**
	 * Pushes back a value into the databuffer.
	 * Will insert the value at the end, dropping the oldest value if need be.
	 * 
	 * \param newValue value to push back into the buffer.
	 */
	void insertNewValue(T newValue) {
		if (m_dataBuffer.size() < m_depth) {
			m_dataBuffer.push_back(newValue);
		} else {
			shiftDataAndInsert(newValue);
		}
	}
};
