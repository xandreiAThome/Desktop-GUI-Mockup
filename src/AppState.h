#pragma once

#include <string>

struct AppState {
	static AppState& get();

	bool shouldQuit = false;
	std::string clockString;
	std::string dateString;

	// open flags
	bool app1Open = false;
	bool app2Open = false;
	bool tmOpen = false;


	void update();
};