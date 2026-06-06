#pragma once

#include <imgui.h>
class Desktop {
public:
    void render(ImDrawList* bgDrawList, ImVec2 displaySize);
private:
    void drawWallpaper(ImDrawList* dl, ImVec2 sz);
    void drawClock(ImVec2 displaySize);
    void drawPowerButton(ImVec2 displaySize);
};