/**
 * @file gui_data_visualization.cpp
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
#include "implot/implot.h"
#include "utility.hpp"

#include <map>

namespace mtool
{



struct StyledBox{
  Box box;
  ImVec4 color = {1,0.5f,1,1};
};


void GuiCanvas(GuiContext& context){
  static bool fit_plot = false;
  static std::map<std::string, StyledBox> boxs;
  if(fit_plot) {
    ImPlot::SetNextAxesToFit();
  }
  if (ImPlot::BeginPlot("box tool", ImVec2(-1,1000), ImPlotFlags_Equal | ImPlotFlags_NoMouseText)) {
    ImPlot::SetupAxes(nullptr, nullptr, ImPlotAxisFlags_NoTickLabels, ImPlotAxisFlags_NoTickLabels);
    for(auto & sb : boxs) {
      ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.25f);
      ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 15.f, sb.second.color, 1.f, sb.second.color);
      ImPlot::PlotScatter(sb.first.c_str(), &sb.second.box.pose[0], &sb.second.box.pose[1], 1);
      if (sb.second.box.outline_x.size() > 0) {
        ImPlot::SetNextLineStyle(sb.second.color, ImPlotColormap_Jet);
        ImPlot::PlotLine(sb.first.c_str(), sb.second.box.outline_x.data(), sb.second.box.outline_y.data(), sb.second.box.outline_y.size(), ImPlotLineFlags_Loop);
      }
      ImPlot::PlotText(sb.first.c_str(), sb.second.box.pose[0], sb.second.box.pose[1] + 0.2);
      ImPlot::PopStyleVar();
    }
    ImPlot::EndPlot();
  }

  static bool realtime_mode = false;
  static char box_name[128] = "box1";
  ImGui::PushFont(*context.title_font);
  ImGui::SeparatorText("Config");
  ImGui::PopFont();
  ImGui::InputText("box_name##1", box_name, IM_ARRAYSIZE(box_name));
  ImGui::Separator();
  static std::array<double, 3> box_pose = {0.f, 0.f, 0.f};
  static std::array<double, 2> box_size = {1.f, 1.f};
  static std::array<double, 2> box_offset = {0.f, 0.f};

  static std::array<double, 2> point1 = {0.f, 0.f};
  static std::array<double, 2> point2 = {0.f, 0.f};
  static std::array<double, 2> point3 = {0.f, 0.f};
  static std::array<double, 2> point4 = {0.f, 0.f};

  static uint8_t tab_id = 0;

  if (ImGui::BeginTabBar("box_bar", 0))
  {
    if (ImGui::BeginTabItem("by size"))
    {
      tab_id = 0;
      ImGui::DragDouble3("box_pose##1", box_pose.data(), 0.1, -FLT_MAX, +FLT_MAX, "%.3f", 0);
      ImGui::DragDouble2("box_size##1", box_size.data(), 0.1, 0.0f, +FLT_MAX, "%.3f", 0);
      ImGui::DragDouble2("box_offset##1", box_offset.data(), 0.1, -FLT_MAX, +FLT_MAX, "%.3f", 0);
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("boy point"))
    {
      tab_id = 1;
      ImGui::DragDouble2("point1##1", point1.data(), 0.1, -FLT_MAX, +FLT_MAX, "%.3f", 0);
      ImGui::DragDouble2("point2##2", point2.data(), 0.1, -FLT_MAX, +FLT_MAX, "%.3f", 0);
      ImGui::DragDouble2("point3##3", point3.data(), 0.1, -FLT_MAX, +FLT_MAX, "%.3f", 0);
      ImGui::DragDouble2("point4##4", point4.data(), 0.1, -FLT_MAX, +FLT_MAX, "%.3f", 0);
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }
  ImGui::Separator();
  static ImVec4 color = {0.36078,0.60392f,1,1};
  ImGui::ColorEdit3("box_color##1", (float*)&color, 0);
  ImGui::Separator();
  if (realtime_mode) {
    StyledBox sbox;
    sbox.color = color;
    if(tab_id == 0) {
      parse_box(box_pose, box_size, box_offset, sbox.box, true);
    } else {
      parse_box(point1, point2, point3, point4, sbox.box, true);
    }
    boxs[std::string(box_name)] = sbox;
  }

  if (ImGui::Button("Add##1")) {
    if (boxs.find(std::string(box_name)) == boxs.end()) {
      printf("add: %s\n", box_name);
      StyledBox sbox;
      sbox.color = color;
      if(tab_id == 0) {
        parse_box(box_pose, box_size, box_offset, sbox.box, true);
      } else {
        parse_box(point1, point2, point3, point4, sbox.box, true);
      }
      boxs[std::string(box_name)] = sbox;
    } else {
      printf("already exist: %s\n", box_name);
      // state.message = "already exist";//, box_name);
      // ImGui::OpenPopup("box_exist##1");
    }
  }

  ImGui::SameLine();
  if (ImGui::Button("Remove##1")) {
    auto it = boxs.find(std::string(box_name));
    if (it != boxs.end()) {
      boxs.erase(it);
    }
  }

  ImGui::SameLine();
  if (ImGui::Button("Clear##1")) {
    printf("click\n");
    boxs.clear();
  }
  ImGui::SameLine();
  ImGui::Checkbox("realtime_mode##1", &realtime_mode);

  if (ImGui::BeginPopup("box_exist##1")) {
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 1.0f, 1.0f), "box with same name [%s] already exist!", box_name);
    ImGui::EndPopup();
  }
}
} // namespace mtool