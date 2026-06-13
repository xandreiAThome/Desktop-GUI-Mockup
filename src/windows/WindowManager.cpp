#include "WindowManager.h"
#include <memory>
#include <string>

// singleton
WindowManager& WindowManager::get() {
	static WindowManager instance;
	return instance;
}

void WindowManager::registerWindow(const std::string& name, std::unique_ptr<BaseWindow> win) {
	m_windows[name] = std::move(win);
}

void WindowManager::showWindow(const std::string& name) {
	m_windows[name]->show();
}

void WindowManager::renderAll() {
	for (auto& [name, window] : m_windows) {
		window->render();
	}
}