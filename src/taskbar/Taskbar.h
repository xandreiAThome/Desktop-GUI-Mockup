#pragma once
#include <imgui.h>
#include <glad/glad.h>
#include <string>
#include <vector>

struct TaskbarIcon {
    std::string windowName;  // WindowManager target
    GLuint texture = 0;
};

class Taskbar {
public:
	void render(ImVec2 displaySize);
	void init();

private:
	std::vector<TaskbarIcon> m_icons;
};