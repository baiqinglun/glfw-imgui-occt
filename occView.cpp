#include "occView.h"

#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <AIS_Shape.hxx>
#include <Aspect_Handle.hxx>
#include <Aspect_DisplayConnection.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <AIS_ViewCube.hxx>
#include <Message.hxx>
#include <Message_Messenger.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <TopAbs_ShapeEnum.hxx>

#include <GLFW/glfw3.h>

namespace
{
    //! Convert GLFW mouse button into Aspect_VKeyMouse.
    static Aspect_VKeyMouse mouseButtonFromGlfw(int theButton)
    {
        switch (theButton)
        {
        case GLFW_MOUSE_BUTTON_LEFT:   return Aspect_VKeyMouse_LeftButton;
        case GLFW_MOUSE_BUTTON_RIGHT:  return Aspect_VKeyMouse_RightButton;
        case GLFW_MOUSE_BUTTON_MIDDLE: return Aspect_VKeyMouse_MiddleButton;
        }
        return Aspect_VKeyMouse_NONE;
    }

    //! Convert GLFW key modifiers into Aspect_VKeyFlags.
    static Aspect_VKeyFlags keyFlagsFromGlfw(int theFlags)
    {
        Aspect_VKeyFlags aFlags = Aspect_VKeyFlags_NONE;
        if ((theFlags & GLFW_MOD_SHIFT) != 0)
        {
            aFlags |= Aspect_VKeyFlags_SHIFT;
        }
        if ((theFlags & GLFW_MOD_CONTROL) != 0)
        {
            aFlags |= Aspect_VKeyFlags_CTRL;
        }
        if ((theFlags & GLFW_MOD_ALT) != 0)
        {
            aFlags |= Aspect_VKeyFlags_ALT;
        }
        if ((theFlags & GLFW_MOD_SUPER) != 0)
        {
            aFlags |= Aspect_VKeyFlags_META;
        }
        return aFlags;
    }
}

GlfwOcctView::GlfwOcctView(Handle(GlfwOcctWindow)& myOcctWindow_) : myOcctWindow(myOcctWindow_)
{
}

GlfwOcctView::~GlfwOcctView()
{
    cleanup();
}

const Handle(GlfwOcctWindow)& GlfwOcctView::getOcctWindow() const
{
    return myOcctWindow;
}
const Handle(V3d_View)& GlfwOcctView::getView() const
{
    return myView;
}
const Handle(AIS_InteractiveContext)& GlfwOcctView::getContext() const
{
    
    return myContext;
}

// 主执行函数
void GlfwOcctView::run()
{
    connect();
    initViewer();
    initDemoScene();
    if (myView.IsNull())
    {
        return;
    }
    myView->MustBeResized();
    myOcctWindow->Map();
    refrash();
}

// 连接窗口事件
void GlfwOcctView::connect()
{
    glfwSetWindowUserPointer(myOcctWindow->getGlfwWindow(), this);
    glfwSetWindowSizeCallback(myOcctWindow->getGlfwWindow(), GlfwOcctView::onResizeCallback);
    glfwSetFramebufferSizeCallback(myOcctWindow->getGlfwWindow(), GlfwOcctView::onFBResizeCallback);
    glfwSetScrollCallback(myOcctWindow->getGlfwWindow(), GlfwOcctView::onMouseScrollCallback);
    glfwSetMouseButtonCallback(myOcctWindow->getGlfwWindow(), GlfwOcctView::onMouseButtonCallback);
    glfwSetCursorPosCallback(myOcctWindow->getGlfwWindow(), GlfwOcctView::onMouseMoveCallback);
}

// 初始化视图
void GlfwOcctView::initViewer()
{
    if (myOcctWindow.IsNull()
        || myOcctWindow->getGlfwWindow() == nullptr)
    {
        return;
    }

    Handle(OpenGl_GraphicDriver) aGraphicDriver
        = new OpenGl_GraphicDriver(myOcctWindow->GetDisplay(), Standard_False);
    aGraphicDriver->SetBuffersNoSwap(Standard_True);

    Handle(V3d_Viewer) aViewer = new V3d_Viewer(aGraphicDriver);
    aViewer->SetDefaultLights();
    aViewer->SetLightOn();
    aViewer->SetDefaultTypeOfView(V3d_PERSPECTIVE);
    aViewer->ActivateGrid(Aspect_GT_Rectangular, Aspect_GDM_Lines);
    myView = aViewer->CreateView();
    myView->SetImmediateUpdate(Standard_False);
    myView->SetWindow(myOcctWindow, myOcctWindow->NativeGlContext());
    myView->ChangeRenderingParams().ToShowStats = Standard_True;

    myContext = new AIS_InteractiveContext(aViewer);
}

// 初始化案例模型
void GlfwOcctView::initDemoScene()
{
    if (myContext.IsNull())
    {
        return;
    }

    myView->TriedronDisplay(Aspect_TOTP_LEFT_LOWER, Quantity_NOC_GOLD, 0.08, V3d_WIREFRAME);

    gp_Ax2 anAxis;
    anAxis.SetLocation(gp_Pnt(0.0, 0.0, 0.0));
    Handle(AIS_Shape) aBox = new AIS_Shape(BRepPrimAPI_MakeBox(anAxis, 50, 50, 50).Shape());
    myContext->Display(aBox, AIS_Shaded, 0, false);
    anAxis.SetLocation(gp_Pnt(25.0, 125.0, 0.0));
    Handle(AIS_Shape) aCone = new AIS_Shape(BRepPrimAPI_MakeCone(anAxis, 25, 0, 50).Shape());
    myContext->Display(aCone, AIS_Shaded, 0, false);

    Handle(AIS_ViewCube) aCube = new AIS_ViewCube();
    aCube->SetSize(55);
    aCube->SetFontHeight(12);
    aCube->SetAxesLabels("", "", "");
    aCube->SetTransformPersistence(new Graphic3d_TransformPers(Graphic3d_TMF_TriedronPers, Aspect_TOTP_RIGHT_LOWER, Graphic3d_Vec2i(100, 100)));
    aCube->SetViewAnimation(this->ViewAnimation());
    aCube->SetFixedAnimationLoop(false);
    myContext->Display(aCube, false);

    TCollection_AsciiString aGlInfo;
    {
        TColStd_IndexedDataMapOfStringString aRendInfo;
        myView->DiagnosticInformation(aRendInfo, Graphic3d_DiagnosticInfo_Basic);
        for (TColStd_IndexedDataMapOfStringString::Iterator aValueIter(aRendInfo); aValueIter.More(); aValueIter.Next())
        {
            if (!aGlInfo.IsEmpty()) { aGlInfo += "\n"; }
            aGlInfo += TCollection_AsciiString("  ") + aValueIter.Key() + ": " + aValueIter.Value();
        }
    }
    //Message::DefaultMessenger()->Send(TCollection_AsciiString("OpenGL info:\n") + aGlInfo, Message_Info);
}

// mainloop
void GlfwOcctView::refrash()
{
    if (!myView.IsNull())
    {
        FlushViewEvents(myContext, myView, Standard_True);
    }
}

// 清楚内存
void GlfwOcctView::cleanup()
{
    if (!myView.IsNull())
    {
        myView->Remove();
    }
    if (!myOcctWindow.IsNull())
    {
        myOcctWindow->Close();
    }
}

// 重置大小事件函数
void GlfwOcctView::onResize(int theWidth, int theHeight)
{
    if (theWidth != 0 && theHeight != 0 && !myView.IsNull())
    {
        myView->Window()->DoResize();
        myView->MustBeResized();
        myView->Invalidate();
        myView->Redraw();
    }
}

// 鼠标滚轮事件函数
void GlfwOcctView::onMouseScroll(double theOffsetX, double theOffsetY)
{
    ImGuiIO& aIO = ImGui::GetIO();
    if (!myView.IsNull() && !aIO.WantCaptureMouse)
    {
        UpdateZoom(Aspect_ScrollDelta(myOcctWindow->CursorPosition(), int(theOffsetY * 8.0)));
    }
}

// 鼠标按钮事件函数
void GlfwOcctView::onMouseButton(int theButton, int theAction, int theMods)
{
    ImGuiIO& aIO = ImGui::GetIO();
    if (myView.IsNull() || aIO.WantCaptureMouse)
    {
        return;
    }

    const Graphic3d_Vec2i aPos = myOcctWindow->CursorPosition();
    if (theAction == GLFW_PRESS)
    {
        PressMouseButton(aPos, mouseButtonFromGlfw(theButton), keyFlagsFromGlfw(theMods), false);
    }
    else
    {
        ReleaseMouseButton(aPos, mouseButtonFromGlfw(theButton), keyFlagsFromGlfw(theMods), false);
    }
}

// 鼠标移动事件函数
void GlfwOcctView::onMouseMove(int thePosX, int thePosY)
{
    if (myView.IsNull())
    {
        return;
    }

    ImGuiIO& aIO = ImGui::GetIO();
    if (aIO.WantCaptureMouse)
    {
        myView->Redraw();
    }
    else
    {
        const Graphic3d_Vec2i aNewPos(thePosX, thePosY);
        UpdateMousePosition(aNewPos, PressedMouseButtons(), LastMouseFlags(), Standard_False);
    }
}


GlfwOcctView* GlfwOcctView::toView(GLFWwindow* theWin)
{
    return static_cast<GlfwOcctView*>(glfwGetWindowUserPointer(theWin));
}

void GlfwOcctView::errorCallback(int theError, const char* theDescription)
{
    Message::DefaultMessenger()->Send(TCollection_AsciiString("Error") + theError + ": " + theDescription, Message_Fail);
}