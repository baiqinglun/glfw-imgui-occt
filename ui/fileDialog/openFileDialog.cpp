#include "openFileDialog.h"

void ui::OpenFileDialog::render()
{

    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey",32,{min_width_,min_height_},{max_width_,max_height_}))
    {
        // action if OK
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            file_path_name_ = ImGuiFileDialog::Instance()->GetFilePathName();
            file_path_ = ImGuiFileDialog::Instance()->GetCurrentPath();
            std::cout << file_path_name_ << "\n" << file_path_ << std::endl;
        }

        // close
        ImGuiFileDialog::Instance()->Close();
    }
}

const std::string ui::OpenFileDialog::getFilePathName() const
{
    return file_path_name_;
}

const std::string ui::OpenFileDialog::getFilePath() const
{
    return file_path_;
}
