#include "Desktop.h"
#include "AppState.h"
#include "utils/TextureLoader.h"

void Desktop::init(const std::string& wallpaperPath) {
	m_wallpaperTex = loadTexture(wallpaperPath);
}

void Desktop::render(ImDrawList* bgDrawList, ImVec2 displaySize) {
	drawWallpaper(bgDrawList, displaySize);
	drawClock(displaySize);
	drawPowerButton(displaySize);
}

void Desktop::drawWallpaper(ImDrawList* drawList, ImVec2 displaySize) {
	if (m_wallpaperTex) {
		drawList->AddImage(
			(ImTextureID)(intptr_t)m_wallpaperTex,
			{ 0.f, 0.f },
			displaySize
		);
	}
	else {
		drawList->AddRectFilledMultiColor(
			{ 0.f, 0.f }, displaySize,
			IM_COL32(10, 15, 40, 255),
			IM_COL32(10, 15, 40, 255),
			IM_COL32(15, 45, 55, 255),
			IM_COL32(10, 25, 45, 255)
		);
	}
}

void Desktop::drawClock(ImVec2 displaySize) {
    const std::string& time = AppState::get().clockString;
    const std::string& date = AppState::get().dateString;

    const float winW = 200.f, winH = 56.f;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));
    ImGui::SetNextWindowPos({ displaySize.x - winW - 8.f, 12.f });
    ImGui::SetNextWindowSize({ winW, winH });
    ImGui::SetNextWindowBgAlpha(0.f);
    ImGui::Begin("##clock", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoInputs |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings);

    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2      wPos = ImGui::GetWindowPos();
    float       timeW = ImGui::CalcTextSize(time.c_str()).x;
    float       dateW = ImGui::CalcTextSize(date.c_str()).x;
    float       contentW = std::max(timeW, dateW);
    float       padX = 12.f, padY = 6.f;

    ImVec2 rectMin = { wPos.x + winW - contentW - padX * 2.f, wPos.y + padY };
    ImVec2 rectMax = { wPos.x + winW,                          wPos.y + winH - padY };
    dl->AddRectFilled(rectMin, rectMax, IM_COL32(0, 0, 0, 130), 8.f);

    ImGui::SetCursorPosX(winW - timeW - padX);
    ImGui::SetCursorPosY(10.f);
    ImGui::TextColored({ 0.95f, 0.95f, 1.00f, 1.00f }, "%s", time.c_str());

    ImGui::SetCursorPosX(winW - dateW - padX);
    ImGui::SetCursorPosY(30.f);
    ImGui::TextColored({ 0.9f, 0.9f, 0.9f, 1.f }, "%s", date.c_str());

    ImGui::End();
    ImGui::PopStyleVar(2);
}

void Desktop::drawPowerButton(ImVec2 displaySize) {
    const float sz = 40.f, margin = 12.f;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));

    ImGui::SetNextWindowPos({ margin, margin });
    ImGui::SetNextWindowSize({ sz, sz });
    ImGui::SetNextWindowBgAlpha(0.f);

    ImGui::Begin("##power", nullptr,
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings |
        ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoScrollWithMouse
    );

    ImGui::SetCursorPos({ 0.f, 0.f });

    // Draw button
    ImGui::PushStyleColor(ImGuiCol_Button, IM_COL32(0, 0, 0, 130));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, IM_COL32(40, 40, 40, 160));
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 8.f);

    if (ImGui::Button("##pwrbtn", ImVec2(sz, sz))) {
        AppState::get().shouldQuit = true;
    };

    ImGui::PopStyleVar();
    ImGui::PopStyleColor(2);

    // Draw power icon on top of button
    ImVec2      wPos = ImGui::GetWindowPos();
    ImDrawList* dl = ImGui::GetWindowDrawList();
    ImVec2      center = { wPos.x + sz * 0.5f, wPos.y + sz * 0.5f };
    
    dl->AddCircle(center, 13.f, IM_COL32(255, 51, 51, 220), 32, 2.f);
    dl->AddLine(
        { center.x, center.y - 16.f },
        { center.x, center.y - 3.f },
        IM_COL32(255, 51, 51, 230),
        2.5f
    );

    ImGui::End();
    ImGui::PopStyleVar(2);
}