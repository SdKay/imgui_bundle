/**
 * @file window_factory.hpp
 * @author yanxin.xing (sdkxyx@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#include "gui_context.hpp"

#include "hello_imgui/hello_imgui.h"


namespace mtool
{
HelloImGui::DockableWindow CreateWindow(
  const char* label,
  const char* docker_space_name,
  GuiContext& context,
  bool isVisible = true
);
} // namespace mtool
