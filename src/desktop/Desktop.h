#pragma once

#include <string>
#include <imgui.h>
#include <glad/glad.h>

class Desktop {
public:
    void init(const std::string& wallpaperPath);
    void render(ImDrawList* bgDrawList, ImVec2 displaySize);
private:
    void drawWallpaper(ImDrawList* drawList, ImVec2 displaySize);
    void drawClock(ImVec2 displaySize);
    void drawPowerButton(ImVec2 displaySize);

    GLuint m_wallpaperTex = 0;
    int m_texW = 0, m_texH = 0;
};