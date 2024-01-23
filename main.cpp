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

    // ��ѭ��
    while (!glfwWindowShouldClose(window))
    {
        // ģʽ
        glfwPollEvents();

        // �½�֡
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // �������
        slab::imguiRun();
        glfwOcctView->refrash();
        //mainMenuBar->render();
        // ��Ⱦ
        ImGui::Render();

        // ���
        glClear(GL_COLOR_BUFFER_BIT);
        glfwOcctView->getView()->Redraw(); // �������ɫ������������Ⱦһ��occt����������

        // ����������
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
        
    }
    // imgui���
    slab::imguiClear();

    return 0;
}
