# Desktop GUI Mockup

Desktop GUI mockup for **CSOPESY OS**, built with C++20, OpenGL, GLFW, and Dear ImGui.

## Dependencies

- [vcpkg](https://github.com/microsoft/vcpkg) with triplet `x64-windows`
- OpenGL, GLFW3, glad, imgui (with glfw + opengl3 bindings), stb

## Build

```sh
cmake --preset x64-debug
cmake --build out/build/x64-debug
```

## Usage

Run the executable from `out/build/x64-debug/` (assets are copied automatically).

## Project Structure

```
src/
├── main.cpp               Entry point & main loop
├── AppState.h/.cpp         Shared application state
├── desktop/                Desktop layer (wallpaper, icons)
├── windows/                Window management system
└── utils/                  Texture loader
```
