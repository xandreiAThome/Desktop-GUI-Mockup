#pragma once

// BaseWindow.h
class BaseWindow {
public:
    BaseWindow(const std::string& name) : windowName(name), openFlag(false){}
    virtual ~BaseWindow() = default;
    virtual void render() = 0;        // Called by WindowManager each frame

    const std::string& getName() const { return windowName; }
    void show() { openFlag = true; }

protected:
    bool openFlag;        
    std::string windowName;
};