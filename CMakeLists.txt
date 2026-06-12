cmake_minimum_required(VERSION 3.10)

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(Desktop-GUI-Mockup CXX)

# --- Find packages installed by vcpkg ---
find_package(OpenGL REQUIRED)
find_package(glfw3  CONFIG REQUIRED)
find_package(imgui  CONFIG REQUIRED)
find_package(glad   CONFIG REQUIRED)

# --- Collect sources ---
file(GLOB_RECURSE SOURCES
    src/*.cpp
    src/desktop/*.cpp
    src/windows/*.cpp
    src/utils/*.cpp
)

add_executable(Desktop-GUI-Mockup ${SOURCES} "src/AppState.h" "src/windows/BaseWindow.h" "src/desktop/Desktop.h" "src/windows/WindowManager.h"  "src/utils/TextureLoader.h" "src/AppState.cpp" "src/desktop/Desktop.cpp" "src/utils/TextureLoader.cpp" "src/windows/WindowManager.cpp"  "src/taskbar/Taskbar.h" "src/taskbar/Taskbar.cpp" "src/windows/CalculatorWindow.h" "src/windows/NotepadWindow.h" )

# --- C++ standard ---
set_property(TARGET Desktop-GUI-Mockup PROPERTY CXX_STANDARD 20)
set_property(TARGET Desktop-GUI-Mockup PROPERTY CXX_STANDARD_REQUIRED ON)

# --- Include directories ---
target_include_directories(Desktop-GUI-Mockup PRIVATE src)

# --- Link libraries ---
target_link_libraries(Desktop-GUI-Mockup PRIVATE
    OpenGL::GL
    glfw
    imgui::imgui
    glad::glad
)

# --- Copy assets to build output directory ---
add_custom_command(TARGET Desktop-GUI-Mockup POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
        $<TARGET_FILE_DIR:Desktop-GUI-Mockup>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Desktop-GUI-Mockup>/assets
    COMMENT "Copying assets to output directory"
)