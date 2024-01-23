#include "imguiConfig.h"
#include "mainMenuBar.h"
#include <memory>

void slab::initImgui(GLFWwindow* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    ImGui::StyleColorsDark();

#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif

    ImGui_ImplGlfw_InitForOpenGL(window, true);
}

void slab::imguiRun()
{
    //ui::MainMenuBar* mainMenuBar = new ui::MainMenuBar();
    //mainMenuBar->render();
    std::unique_ptr<ui::MainMenuBar> mainMenuBar = std::make_unique<ui::MainMenuBar>();
    mainMenuBar.get()->render();

    

    //delete mainMenuBar;
}

void slab::imguiClear()
{
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
