#pragma once

#include <memory>
#include <vector>
#include "BaseWindow.h"

class WindowManager {
public:
    void registerWindow(std::unique_ptr<BaseWindow> win);
    void renderAll();                 // Iterates and calls render() on open windows
private:
    std::vector<std::unique_ptr<BaseWindow>> m_windows;
};