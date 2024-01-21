#pragma once
#include "../imgui/imconfig.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/imgui_impl_opengl3_loader.h"
#include "../imgui/imgui_internal.h"
#include "../imgui/imstb_rectpack.h"
#include "../imgui/imstb_textedit.h"
#include "../imgui/imstb_truetype.h"

#include "../configs.h"

namespace ui
{
	class Component
	{
	public:
		virtual void render() = 0;
	};
}