#include "glfwConfig.h"
#include "imguiConfig.h"
#include "occtWindow.h"
#include "occView.h"
#include "configs.h"
//#include "mainMenuBar.h"

int main(int, char**)
{
    slab::initFlgw();

    Handle(GlfwOcctWindow) glfwOcctWindow = new GlfwOcctWindow(kWindow_width, kWindow_height,kWindow_name);
    GlfwOcctView *glfwOcctView = new GlfwOcctView(glfwOcctWindow);
    if(glfwOcctView != nullptr)
        glfwOcctView->run();
    GLFWwindow* window = glfwOcctWindow->getGlfwWindow();
    if (window == nullptr)
        return 1;

    slab::initImgui(window);
    
    //ui::MainMenuBar *mainMenuBar = new ui::MainMenuBar;

    // 主循环
    while (!glfwWindowShouldClose(window))
    {
        // 模式
        glfwPollEvents();

        // 新建帧
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 窗口组件
        slab::imguiRun();
        glfwOcctView->refrash();
        //mainMenuBar->render();
        // 渲染
        ImGui::Render();

        // 清除
        glClear(GL_COLOR_BUFFER_BIT);
        glfwOcctView->getView()->Redraw(); // 清除完颜色缓冲区后再渲染一次occt，否则会黑屏

        // 缓冲区交换
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        
    }
    // imgui清除
    slab::imguiClear();

    return 0;
}
