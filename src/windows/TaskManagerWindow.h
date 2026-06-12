#pragma once
#include "BaseWindow.h"
#include <imgui.h>
#include <vector>
#include <string>

struct ProcessDummyData {
    std::string name;
    std::string status;
    float cpu;
    float memory;
};

class TaskManagerWindow : public BaseWindow {
private:
    // dummy data
    std::vector<ProcessDummyData> m_dummyProcesses = {
        {"System", "Running", 1.5f, 120.5f},
        {"Window Manager", "Running", 4.2f, 85.0f},
        {"Web Browser", "Running", 45.3f, 1024.0f}, // sample high usage
        {"Background Sync", "Suspended", 0.0f, 12.0f},
        {"Code Editor", "Running", 12.1f, 450.2f},
        {"Audio Service", "Running", 0.5f, 35.8f}
    };
    
public:
    TaskManagerWindow() : BaseWindow("Task Manager") {}
    TaskManagerWindow(const std::string& name) : BaseWindow(name) {}

    void render() override {
        if (!openFlag) return;

        ImGui::SetNextWindowSize(ImVec2(500, 350), ImGuiCond_FirstUseEver);

        if (ImGui::Begin(getName().c_str(), &openFlag)) {
            
            // Tab bar
            if (ImGui::BeginTabBar("TaskManagerTabs")) {
                
                // active tab
                if (ImGui::BeginTabItem("Processes")) {
                    
                    static ImGuiTableFlags flags = ImGuiTableFlags_Resizable | 
                                                   ImGuiTableFlags_RowBg | 
                                                   ImGuiTableFlags_BordersOuter | 
                                                   ImGuiTableFlags_BordersV | 
                                                   ImGuiTableFlags_ScrollY;
                    
                    // Data grid
                    if (ImGui::BeginTable("ProcessesTable", 4, flags, ImVec2(0.0f, -FLT_MIN))) {
                        // Freeze top row so headers remain when scrolling
                        ImGui::TableSetupScrollFreeze(0, 1); 
                        
                        ImGui::TableSetupColumn("Name");
                        ImGui::TableSetupColumn("Status");
                        ImGui::TableSetupColumn("CPU");
                        ImGui::TableSetupColumn("Memory");
                        ImGui::TableHeadersRow();

                        // Populate the dummy data
                        for (const auto& proc : m_dummyProcesses) {
                            ImGui::TableNextRow();
                            
                            // Name
                            ImGui::TableSetColumnIndex(0);
                            ImGui::Text("%s", proc.name.c_str());

                            // Status
                            ImGui::TableSetColumnIndex(1);
                            if (proc.status == "Suspended") {
                                ImGui::TextDisabled("%s", proc.status.c_str());
                            } else {
                                ImGui::Text("%s", proc.status.c_str());
                            }

                            // CPU usage (with colors based on usage)
                            ImGui::TableSetColumnIndex(2);
                            if (proc.cpu > 30.0f) {
                                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImVec4(0.8f, 0.2f, 0.2f, 0.4f))); 
                            } else if (proc.cpu > 10.0f) {
                                ImGui::TableSetBgColor(ImGuiTableBgTarget_CellBg, ImGui::GetColorU32(ImVec4(0.8f, 0.6f, 0.2f, 0.4f))); 
                            }
                            ImGui::Text("%.1f%%", proc.cpu);

                            // Memory
                            ImGui::TableSetColumnIndex(3);
                            ImGui::Text("%.1f MB", proc.memory);
                        }
                        ImGui::EndTable();
                    }
                    ImGui::EndTabItem();
                }
                
                // placeholder performance tab
                if (ImGui::BeginTabItem("Performance")) {
                    ImGui::TextDisabled("Performance metrics graph placeholder.");
                    ImGui::EndTabItem();
                }
                
                ImGui::EndTabBar();
            }
        }
        ImGui::End();
    }
};