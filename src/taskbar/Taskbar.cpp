#include "Taskbar.h"
#include "AppState.h"
#include "utils/TextureLoader.h"
#include <imgui.h>
#include "windows/WindowManager.h"

void Taskbar::init() {
    // Initialize icons
    TaskbarIcon calculator;
    calculator.windowName = "Calculator"; 
    calculator.texture = loadTexture("assets/calculator.png");

    TaskbarIcon notepad;
    notepad.windowName = "Notepad";
    notepad.texture = loadTexture("assets/notepad.png");

    TaskbarIcon taskManager;
    taskManager.windowName = "Task Manager"; 
    taskManager.texture = loadTexture("assets/taskmanager.png");

    m_icons.push_back(calculator);
    m_icons.push_back(notepad);
    m_icons.push_back(taskManager);

    
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

    for (size_t i = 0; i < m_icons.size(); i++) {
        TaskbarIcon& icon = m_icons[i];

        if (ImGui::ImageButton(
            icon.windowName.c_str(),
            (ImTextureID)(intptr_t)icon.texture,
            imageSize
        )) {
            WindowManager::get().showWindow(icon.windowName);
        }

        ImGui::SameLine();
    }

    ImGui::PopStyleVar();

    ImGui::End();
}