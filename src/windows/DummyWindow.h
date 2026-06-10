
#include "BaseWindow.h"
#include <imgui.h>
#include <string>

class DummyWindow : public BaseWindow {
public:

	DummyWindow(const char* title, bool* openFlag) {
		this->m_title = title;
		this->openFlag = openFlag;
	}

	void render()  {
		if (!openFlag)
			return;

		if (*openFlag) {
			ImGui::Begin(title(), openFlag);
			ImGui::Text("Hello from %s", title());
			ImGui::End();
		}
	}

	const char* title() const {
		return this->m_title;
	}
private:
	const char* m_title;
};