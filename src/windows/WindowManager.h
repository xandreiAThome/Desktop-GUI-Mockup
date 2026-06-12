#pragma once

#include <memory>
#include <unordered_map>
#include <string>
#include "BaseWindow.h"

class WindowManager {
public:
    static WindowManager& get(); // singleton
    void registerWindow(const std::string& name, std::unique_ptr<BaseWindow> win);
    void showWindow(const std::string& name);
    void hideWindow(const std::string& name);
    void renderAll();                 // Iterates and calls render() on open windows
private:
    std::unordered_map<std::string, std::unique_ptr<BaseWindow>> m_windows;
};