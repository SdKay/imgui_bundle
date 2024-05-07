/**
 * @file gui_imgui_demo.cpp
 * @author yanxin.xing (sdkxyx@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "app_gui.hpp"

#include "hello_imgui/hello_imgui.h"

namespace mtool
{
void GuiImguiDemo(GuiContext& context){
  ImGui::ShowDemoWindow();
}
} // namespace mtool
