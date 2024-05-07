/**
 * @file gui_navagation.cpp
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
#include "imgui.h"

namespace mtool
{

void GuiNavagation(GuiContext& context){
  // ImGui::PushFont(gTitleFont); ImGui::Text("Navigation Panel"); ImGui::PopFont();
  // ImGui::TextWrapped("The widgets below will interact with the log window");
  {
    ImGui::PushFont(*context.title_font);
    static char str0[32];
    ImGui::SetNextItemWidth(HelloImGui::EmSize(7.f));
    ImGui::InputText("##search_input", str0, 32);
    ImGui::SameLine();
    if (ImGui::Button(ICON_FA_SEARCH"  Search tool")) {
      ImGui::PopFont();
      HelloImGui::Log(HelloImGui::LogLevel::Info, "Button was pressed: %s", str0);
    } else {
      ImGui::PopFont();
    }
  }

  ImGui::Separator();

  {
    ImGui::PushFont(*context.title_font);
    if (ImGui::Button(ICON_FA_HOME"  Home"))
    {
      ImGui::PopFont();
      HelloImGui::Log(HelloImGui::LogLevel::Info, "Button was pressed");
      
      auto boxPlotWindowPtr = HelloImGui::GetRunnerParams()->dockingParams.dockableWindowOfName("home");
      if (boxPlotWindowPtr)
      {
        if(boxPlotWindowPtr->isVisible) {
          ImGui::SetWindowFocus("home");
        } else {
          boxPlotWindowPtr->isVisible = true;
        }
      }
    } else {
      ImGui::PopFont();
    }
  }

  ImGui::SeparatorText("Visualization");
  {
    ImGui::PushFont(*context.title_font);
    if (ImGui::Button(ICON_FA_CLONE"  Box Plot"))
    {
      ImGui::PopFont();
      HelloImGui::Log(HelloImGui::LogLevel::Info, "Button was pressed");
      auto boxPlotWindowPtr = HelloImGui::GetRunnerParams()->dockingParams.dockableWindowOfName("data_visualization");
      if (boxPlotWindowPtr)
      {
        if (!boxPlotWindowPtr->isVisible) {
          boxPlotWindowPtr->isVisible = true;
        } else {
          ImGui::SetWindowFocus("data_visualization");
        }
      }
    } else {
      ImGui::PopFont();
    }
  }

  ImGui::Separator();
}


} // namespace mtool
