#include "WindowManager.h"
#include <memory>

void WindowManager::registerWindow(std::unique_ptr<BaseWindow> win) {
	m_windows.push_back(std::move(win));
}

void WindowManager::renderAll() {
	for (const auto &win : m_windows) {
		win->render();
	}
}