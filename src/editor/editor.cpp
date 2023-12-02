#include "editor/editor.hpp"

#include "imgui.h"

namespace maple {
    void RenderUI(float& mix) {
        ImGui::Begin("Settings");
        ImGui::Button("Hello");
        ImGui::DragFloat("Value", &mix, 0.01f, 0.0f, 1.0f);
        ImGui::End();

        // ImGui::ShowDemoWindow();
    }
}