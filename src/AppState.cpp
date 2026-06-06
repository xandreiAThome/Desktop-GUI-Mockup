#include "AppState.h"
#include <ctime>

// singleton
AppState& AppState::get() {
	static AppState instance;
	return instance;
}

void AppState::update() {
	std::time_t now = std::time(nullptr);
	std::tm* tm = std::localtime(&now);
	char timeBuf[32], dateBuf[32];
	std::strftime(timeBuf, sizeof(timeBuf), "%A    %H:%M:%S", tm);
	std::strftime(dateBuf, sizeof(dateBuf), "%B %d, %Y", tm);
	clockString = timeBuf;
	dateString = dateBuf;
}