#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>
#include <desktop/Desktop.h>
#include <AppState.h>

#include "windows/WindowManager.h"
#include "taskbar/Taskbar.h"
#include "windows/CalculatorWindow.h"
#include "windows/NotepadWindow.h"

// Theme
static void ApplyOSTheme() {
    ImGuiStyle& s = ImGui::GetStyle();
    s.WindowRounding = 8.f;
    s.FrameRounding = 4.f;
    s.ScrollbarRounding = 4.f;
    s.WindowBorderSize = 1.f;
    s.FramePadding = { 8.f, 5.f };
    s.ItemSpacing = { 8.f, 6.f };

    ImVec4* c = s.Colors;
    c[ImGuiCol_WindowBg] = { 0.10f, 0.11f, 0.13f, 0.95f };
    c[ImGuiCol_TitleBg] = { 0.07f, 0.08f, 0.10f, 1.f };
    c[ImGuiCol_TitleBgActive] = { 0.16f, 0.29f, 0.55f, 1.f };
    c[ImGuiCol_Button] = { 0.20f, 0.22f, 0.27f, 1.f };
    c[ImGuiCol_ButtonHovered] = { 0.27f, 0.52f, 0.95f, 0.80f };
    c[ImGuiCol_ButtonActive] = { 0.27f, 0.52f, 0.95f, 1.f };
}

int main() {
    if (!glfwInit()) {
        fprintf(stderr, "GLFW init failed\n");
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "CSOPESY OS", nullptr, nullptr);
    if (!window) { fprintf(stderr, "Window creation failed\n"); glfwTerminate(); return 1; }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);   // vsync

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "GLAD init failed\n"); return 1;
    }

    // imgui init

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::GetIO().IniFilename = nullptr;   // no imgui.ini
    ApplyOSTheme();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    Desktop desktop;
    desktop.init("assets/starry-night.jpg");

    Taskbar taskbar;
    taskbar.init();

    WindowManager::get().registerWindow("Calculator", std::make_unique<CalculatorWindow>());
    WindowManager::get().registerWindow("Notepad", std::make_unique<NotepadWindow>());
    WindowManager::get().registerWindow("Task Manager", std::make_unique<CalculatorWindow>("Task Manager")); // CHANGE THIS
   

    // main loop

    while (!glfwWindowShouldClose(window) && !AppState::get().shouldQuit) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Update shared state (clock string etc.)
        AppState::get().update();

        // desktop layer
        int fbW, fbH;
        glfwGetFramebufferSize(window, &fbW, &fbH);
        ImVec2 displaySize = { (float)fbW, (float)fbH };
        desktop.render(ImGui::GetBackgroundDrawList(), displaySize);

        // taskbar
        taskbar.render(displaySize);
        
        // windows
        WindowManager::get().renderAll();


        ImGui::Render();
        glViewport(0, 0, fbW, fbH);
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}