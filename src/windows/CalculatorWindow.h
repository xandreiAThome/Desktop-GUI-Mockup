#pragma once
#include "BaseWindow.h"
#include <imgui.h>

class CalculatorWindow : public BaseWindow {
public:
    CalculatorWindow(bool* openFlag) {
        this->openFlag = openFlag;
    }

    const char* title() const override { return "Calculator"; }

    void render() override {
        if (!openFlag || !*openFlag) return;

        ImGui::SetNextWindowSize(ImVec2(240, 320), ImGuiCond_FirstUseEver);

        if (ImGui::Begin(title(), openFlag, ImGuiWindowFlags_NoResize)) {
            ImGui::BeginChild("DisplayBox", ImVec2(0, 40), true);
            ImGui::Text("42"); 
            ImGui::EndChild();

            ImGui::Spacing();

            ImVec2 btnSize(45, 45);

            if (ImGui::Button("7", btnSize)) {} ImGui::SameLine();
            if (ImGui::Button("8", btnSize)) {} ImGui::SameLine();
            if (ImGui::Button("9", btnSize)) {} ImGui::SameLine();
            if (ImGui::Button("/", btnSize)) {}

            if (ImGui::Button("4", btnSize)) {} ImGui::SameLine();
            if (ImGui::Button("5", btnSize)) {} ImGui::SameLine();
            if (ImGui::Button("6", btnSize)) {} ImGui::SameLine();
            if (ImGui::Button("*", btnSize)) {}

            if (ImGui::Button("1", btnSize)) {} ImGui::SameLine();
            if (ImGui::Button("2", btnSize)) {} ImGui::SameLine();
            if (ImGui::Button("3", btnSize)) {} ImGui::SameLine();
            if (ImGui::Button("-", btnSize)) {}

            if (ImGui::Button("C", btnSize)) {} ImGui::SameLine();
            if (ImGui::Button("0", btnSize)) {} ImGui::SameLine();
            if (ImGui::Button("=", btnSize)) {} ImGui::SameLine();
            if (ImGui::Button("+", btnSize)) {}
        }
        ImGui::End();
    }
};