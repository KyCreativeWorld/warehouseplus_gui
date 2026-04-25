#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>

int main() {
    if (!glfwInit()) return 1;
    // ... setup window and context ...
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // If it compiles, you have successfully installed ImGui!
}