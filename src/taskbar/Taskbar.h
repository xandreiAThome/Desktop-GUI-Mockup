#pragma once
#include <imgui.h>
#include <glad/glad.h>

class Taskbar {
public:
	void render(ImVec2 displaySize);
	void init();

private:
	GLuint m_taskManagerTex = 0;
	int m_tmTexW = 0, m_tmTexH = 0;
};