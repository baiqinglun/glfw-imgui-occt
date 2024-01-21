#pragma once

#include <Aspect_DisplayConnection.hxx>
#include <Aspect_RenderingContext.hxx>
#include <Aspect_Window.hxx>
#include <Graphic3d_Vec.hxx>
#include <TCollection_AsciiString.hxx>

struct GLFWwindow;

class GlfwOcctWindow : public Aspect_Window
{
	DEFINE_STANDARD_RTTI_INLINE(GlfwOcctWindow, Aspect_Window)

public:
    GlfwOcctWindow(int theWidth, int theHeight, const TCollection_AsciiString& theTitle);
    virtual ~GlfwOcctWindow() { Close(); }
    void Close();
    const Handle(Aspect_DisplayConnection)& GetDisplay() const { return myDisplay; }
    GLFWwindow* getGlfwWindow() { return myGlfwWindow; }
    Aspect_RenderingContext NativeGlContext() const;
    Graphic3d_Vec2i CursorPosition() const;

public:
    virtual Aspect_Drawable NativeHandle() const Standard_OVERRIDE;
    virtual Aspect_Drawable NativeParentHandle() const Standard_OVERRIDE { return 0; }
    virtual Aspect_TypeOfResize DoResize() Standard_OVERRIDE;
    virtual Standard_Boolean IsMapped() const Standard_OVERRIDE;
    virtual Standard_Boolean DoMapping() const Standard_OVERRIDE { return Standard_True; }
    virtual void Map() const Standard_OVERRIDE;
    virtual void Unmap() const Standard_OVERRIDE;
    virtual void Position(Standard_Integer& theX1, Standard_Integer& theY1,
        Standard_Integer& theX2, Standard_Integer& theY2) const Standard_OVERRIDE
    {
        theX1 = myXLeft;
        theX2 = myXRight;
        theY1 = myYTop;
        theY2 = myYBottom;
    }
    virtual Standard_Real Ratio() const Standard_OVERRIDE
    {
        return Standard_Real(myXRight - myXLeft) / Standard_Real(myYBottom - myYTop);
    }
    virtual void Size(Standard_Integer& theWidth, Standard_Integer& theHeight) const Standard_OVERRIDE
    {
        theWidth = myXRight - myXLeft;
        theHeight = myYBottom - myYTop;
    }
    virtual Aspect_FBConfig NativeFBConfig() const Standard_OVERRIDE { return nullptr; }

protected:
    Handle(Aspect_DisplayConnection) myDisplay;
    GLFWwindow* myGlfwWindow;
    Standard_Integer myXLeft;
    Standard_Integer myYTop;
    Standard_Integer myXRight;
    Standard_Integer myYBottom;
};