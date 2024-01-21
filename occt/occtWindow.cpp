#include "occtWindow.h"

#if defined (__APPLE__)
#undef Handle // avoid name collisions in macOS headers
#define GLFW_EXPOSE_NATIVE_COCOA
#define GLFW_EXPOSE_NATIVE_NSGL
#elif defined (_WIN32)
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#else
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
#endif

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

GlfwOcctWindow::GlfwOcctWindow(int theWidth, int theHeight, const std::string& theTitle)
    : myGlfwWindow(glfwCreateWindow(theWidth, theHeight, theTitle.c_str(), nullptr, nullptr)),
    myXLeft(0),
    myYTop(0),
    myXRight(0),
    myYBottom(0)
{
    if (myGlfwWindow != nullptr)
    {
        int aWidth = 0, aHeight = 0;
        glfwGetWindowPos(myGlfwWindow, &myXLeft, &myYTop);
        glfwGetWindowSize(myGlfwWindow, &aWidth, &aHeight);
        myXRight = myXLeft + aWidth;
        myYBottom = myYTop + aHeight;
        glfwMakeContextCurrent(myGlfwWindow);
    }
}

// �رմ���
void GlfwOcctWindow::Close()
{
    if (myGlfwWindow != nullptr)
    {
        glfwDestroyWindow(myGlfwWindow);
        myGlfwWindow = nullptr;
    }
}

// �ײ㴰��
Aspect_Drawable GlfwOcctWindow::NativeHandle() const
{
#if defined (__APPLE__)
    return (Aspect_Drawable)glfwGetCocoaWindow(myGlfwWindow);
#elif defined (_WIN32)
    return (Aspect_Drawable)glfwGetWin32Window(myGlfwWindow);
#else
    return (Aspect_Drawable)glfwGetX11Window(myGlfwWindow);
#endif
}

// �ײ�opengl����
Aspect_RenderingContext GlfwOcctWindow::NativeGlContext() const
{
#if defined (__APPLE__)
    return (NSOpenGLContext*)glfwGetNSGLContext(myGlfwWindow);
#elif defined (_WIN32)
    return glfwGetWGLContext(myGlfwWindow);
#else
    return glfwGetGLXContext(myGlfwWindow);
#endif
}

// ��鴰�ڵ�ǰ�Ƿ�����Ļ�Ͽɼ�
Standard_Boolean GlfwOcctWindow::IsMapped() const
{
    return glfwGetWindowAttrib(myGlfwWindow, GLFW_VISIBLE) != 0;
}

// ��ʾ��Ļ
void GlfwOcctWindow::Map() const
{
    glfwShowWindow(myGlfwWindow);
}

// ������Ļ
void GlfwOcctWindow::Unmap() const
{
    glfwHideWindow(myGlfwWindow);
}

// ���ô�С
Aspect_TypeOfResize GlfwOcctWindow::DoResize()
{
    if (glfwGetWindowAttrib(myGlfwWindow, GLFW_VISIBLE) == 1)
    {
        int anXPos = 0, anYPos = 0, aWidth = 0, aHeight = 0;
        glfwGetWindowPos(myGlfwWindow, &anXPos, &anYPos);
        glfwGetWindowSize(myGlfwWindow, &aWidth, &aHeight);
        myXLeft = anXPos;
        myXRight = anXPos + aWidth;
        myYTop = anYPos;
        myYBottom = anYPos + aHeight;
    }
    return Aspect_TOR_UNKNOWN;
}

// ��ȡ���λ��
Graphic3d_Vec2i GlfwOcctWindow::CursorPosition() const
{
    Graphic3d_Vec2d aPos;
    glfwGetCursorPos(myGlfwWindow, &aPos.x(), &aPos.y());
    return Graphic3d_Vec2i((int)aPos.x(), (int)aPos.y());
}