// windows/NotepadWindow.h
#pragma once
#include "BaseWindow.h"
#include <imgui.h>

class NotepadWindow : public BaseWindow {
private:
    char m_textBuffer[2048] = "To do\n- Buy groceries\n- Take dog for walk";

public:
    NotepadWindow(bool* openFlag) {
        this->openFlag = openFlag;
    }

    const char* title() const override { return "Notepad"; }

    void render() override {
        if (!openFlag || !*openFlag) return;

        ImGui::SetNextWindowSize(ImVec2(400, 300), ImGuiCond_FirstUseEver);

        if (ImGui::Begin(title(), openFlag)) {
            ImGui::InputTextMultiline("##notes_field", m_textBuffer, sizeof(m_textBuffer),
                ImVec2(-FLT_MIN, -FLT_MIN), ImGuiInputTextFlags_AllowTabInput);
        }
        ImGui::End();
    }
};