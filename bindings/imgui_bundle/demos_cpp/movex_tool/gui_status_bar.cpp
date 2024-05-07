/**
 * @file gui_status_bar.cpp
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
void GuiStatusBar(GuiContext& context){
  if (context.rocket_state == mtool::GuiContext::RocketState::Preparing)
  {
      ImGui::Text("Rocket completion: ");
      ImGui::SameLine();
      ImGui::ProgressBar(context.rocket_progress, HelloImGui::EmToVec2(7.0f, 1.0f));
  }
}
} // namespace mtool