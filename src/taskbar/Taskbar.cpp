#include "Taskbar.h"
#include "AppState.h"
#include "utils/TextureLoader.h"
#include <imgui.h>

void Taskbar::init() {
    m_taskManagerTex = loadTexture("assets/taskmanager.png", m_tmTexW, m_tmTexH);
    
}

void Taskbar::render(ImVec2 displaySize) {
    const float menuBarHeight = displaySize.y / 10;
    const float menuBarWidth = displaySize.x;

    const float diameter = menuBarHeight - 16.0f;

    const ImVec2 buttonSize(diameter, diameter); // Normal button size
    const ImVec2 imageSize( // Image button size
        buttonSize.x - ImGui::GetStyle().FramePadding.x * 2.0f,
        buttonSize.y - ImGui::GetStyle().FramePadding.y * 2.0f
    );

    ImGuiWindowFlags window_flags = 0
        | ImGuiWindowFlags_NoTitleBar
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoMove
        | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoSavedSettings
        | ImGuiWindowFlags_NoBringToFrontOnFocus;


    ImGui::SetNextWindowPos(ImVec2(
        0,
        displaySize.y - menuBarHeight + 1
    ));

    ImGui::SetNextWindowSize(ImVec2(
        menuBarWidth,
        menuBarHeight
    ));

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);

    ImGui::Begin("Taskbar", nullptr, window_flags);
    ImGui::PopStyleVar();

    // Buttons
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 100.0f);

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
    if (ImGui::Button("App 1", buttonSize)) {
        AppState::get().app1Open = true;
    };
    ImGui::PopStyleColor();

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 1.0f, 0.0f, 1.0f));
    ImGui::SameLine();
    if (ImGui::Button("App 2", buttonSize)) {
        AppState::get().app2Open = true;
    };
    ImGui::PopStyleColor();

    ImGui::SameLine();
    if (ImGui::ImageButton("TMIcon", (ImTextureID)(intptr_t)m_taskManagerTex, imageSize)) {
        AppState::get().tmOpen = true;
    };
    ImGui::PopStyleVar();

    ImGui::End();
}