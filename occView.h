#pragma once
#include "occtWindow.h"

#include <AIS_InteractiveContext.hxx>
#include <AIS_ViewController.hxx>
#include <V3d_View.hxx>

class GlfwOcctView : protected AIS_ViewController
{
public:
    GlfwOcctView(Handle(GlfwOcctWindow)& myOcctWindow_);

    ~GlfwOcctView();

    void run();
    const Handle(GlfwOcctWindow)& getOcctWindow() const;
    const Handle(V3d_View)& getView() const;
    const Handle(AIS_InteractiveContext)& getContext() const;
    void refrash();
    void initViewer();
    void initDemoScene();
    void cleanup();
    void connect();
private:
    void onResize(int theWidth, int theHeight);
    void onMouseScroll(double theOffsetX, double theOffsetY);
    void onMouseButton(int theButton, int theAction, int theMods);
    void onMouseMove(int thePosX, int thePosY);
private:

    static void errorCallback(int theError, const char* theDescription);
    static GlfwOcctView* toView(GLFWwindow* theWin);
    
    static void onResizeCallback(GLFWwindow* theWin, int theWidth, int theHeight)
    {
        toView(theWin)->onResize(theWidth, theHeight);
    }

    static void onFBResizeCallback(GLFWwindow* theWin, int theWidth, int theHeight)
    {
        toView(theWin)->onResize(theWidth, theHeight);
    }

    static void onMouseScrollCallback(GLFWwindow* theWin, double theOffsetX, double theOffsetY)
    {
        toView(theWin)->onMouseScroll(theOffsetX, theOffsetY);
    }

    static void onMouseButtonCallback(GLFWwindow* theWin, int theButton, int theAction, int theMods)
    {
        toView(theWin)->onMouseButton(theButton, theAction, theMods);
    }

    static void onMouseMoveCallback(GLFWwindow* theWin, double thePosX, double thePosY)
    {
        toView(theWin)->onMouseMove((int)thePosX, (int)thePosY);
    }

private:
    Handle(GlfwOcctWindow) myOcctWindow;
    Handle(V3d_View) myView;
    Handle(AIS_InteractiveContext) myContext;

};