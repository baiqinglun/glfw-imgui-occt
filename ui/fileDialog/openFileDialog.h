#pragma once
#include "component.h"
#include "ImGuiFileDialog/ImGuiFileDialog.h"
#include "ImGuiFileDialog/ImGuiFileDialogConfig.h"

namespace ui
{
	class OpenFileDialog : public Component
	{
	public:
		void render() override;
		const std::string getFilePathName() const;
		const std::string getFilePath() const;

	private:
		std::string file_path_name_;
		std::string file_path_;

		float min_width_ = 800;
		float min_height_ = 600;
		float max_width_ = 1000;
		float max_height_ = 700;
	};

}