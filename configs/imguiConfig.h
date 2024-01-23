#pragma once
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//#include "mainMenuBar.h"

namespace slab
{
	void initImgui(GLFWwindow* window);
	void imguiRun();
	void imguiClear();
}
