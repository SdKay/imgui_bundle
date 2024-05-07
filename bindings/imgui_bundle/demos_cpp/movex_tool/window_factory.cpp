/**
 * @file window_factory.cpp
 * @author yanxin.xing (sdkxyx@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include "window_factory.hpp"
#include "app_gui.hpp"

#include <map>
#include <string>

namespace mtool
{

namespace
{

std::map<std::string, void(*)(GuiContext& context)> g_guiCallbacks = 
{
  {"navagation", GuiNavagation},
  {"logger", GuiLogger},
  {"home", GuiHome},
  {"data_visualization", GuiDataVisualization},
  {"canvas", GuiCanvas},
  {"status_bar", GuiStatusBar},
  {"Dear ImGui Demo", GuiImguiDemo}
};


} // namespace


HelloImGui::DockableWindow CreateWindow(const char* label, const char* docker_space_name, GuiContext& context, bool isVisible)
{
  HelloImGui::DockableWindow window;
  window.label = label;
  window.dockSpaceName = docker_space_name;
  window.isVisible = isVisible;
  window.GuiFunction = [&context, label] { g_guiCallbacks[std::string(label)](context); };

  return window;
}

} // namespace mtool