#pragma once

#include <string>

struct AppState {
	static AppState& get();

	bool shouldQuit = false;
	std::string clockString;

	void update();
};