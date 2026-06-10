#pragma once

// BaseWindow.h
class BaseWindow {
public:
    virtual ~BaseWindow() = default;
    virtual void render() = 0;        // Called by WindowManager each frame
    virtual const char* title() const = 0;
    bool* openFlag = nullptr;         // Points into AppState::windows
};