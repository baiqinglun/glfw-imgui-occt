#pragma once

#include "component.h"
#include "ImGuiFileDialog/ImGuiFileDialog.h"
#include "ImGuiFileDialog/ImGuiFileDialogConfig.h"
#include "openFileDialog.h"
#include "memory"
#include "attributeDialog.h"

namespace ui
{
	class MainMenuBar : public ui::Component
	{
	public:
		void render() override;

	private:
		std::unique_ptr<OpenFileDialog> fileDialog;
		std::unique_ptr<AttributeDialog> attributeDialog;
		void openFile();
		void saveFile();
		void createPoint();
		static bool is_open_file_;
		static bool is_open_attr_;
	};
}