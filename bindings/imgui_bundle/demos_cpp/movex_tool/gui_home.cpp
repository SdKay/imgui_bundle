/**
 * @file gui_home.cpp
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
void GuiHome(GuiContext& context){
  ImGui::BeginTable("table1", 2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg);
    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    if(ImGui::Button("Box Plot", ImVec2(-FLT_MIN, 350.0f))) {
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
    }
    ImGui::Separator();
    ImGui::TextWrapped("The quick brown fox jumps over the lazy dog.");

    ImGui::TableSetColumnIndex(1);
    ImGui::Button("RESERVE_BUTTON##1", ImVec2(-FLT_MIN, 350.0f));
    ImGui::Text("aaaa");

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::Button("RESERVE_BUTTON##2", ImVec2(-FLT_MIN, 350.0f));
    ImGui::Text("aaaa");

    ImGui::TableSetColumnIndex(1);
    ImGui::Button("RESERVE_BUTTON##3", ImVec2(-FLT_MIN, 350.0f));
    ImGui::Text("aaaa");
  ImGui::EndTable();
}
} // namespace mtool