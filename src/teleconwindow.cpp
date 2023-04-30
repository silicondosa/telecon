#include "teleconwindow.h"

#include <iostream>

TeleconWindow::TeleconWindow(std::string title)
	: m_title(title), m_hasRequestedQuit(false), m_hasQuit(false), m_hasStarted(false) {}

void TeleconWindow::requestQuit()
{
	m_hasRequestedQuit = true;
}

bool TeleconWindow::hasRequestedQuit()
{
	return m_hasRequestedQuit;
}

void TeleconWindow::setHasQuit()
{
	std::unique_lock lock(m_hasQuitLock);
	m_hasQuit = true;
	lock.unlock();
	m_hasQuitCV.notify_all();
}

bool TeleconWindow::hasQuit()
{
	std::lock_guard lock(m_hasQuitLock);
	return m_hasQuit;
}

void TeleconWindow::waitUntilQuit()
{
	std::unique_lock lock(m_hasQuitLock);
	while (!m_hasQuit) {
		m_hasQuitCV.wait(lock);
	}
}

std::string TeleconWindow::getTitle()
{
	return m_title;
}