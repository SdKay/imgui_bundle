/**
 * @file gui_context.hpp
 * @author yanxin.xing (sdkxyx@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-13
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#pragma once

#include "imgui/imgui.h"

#include <string>

namespace mtool
{

struct MyAppSettings
{
  std::string name = "Test";
  int value = 10;
};

struct GuiContext
{
  ImFont ** title_font;

  float f = 0.0f;
  int counter = 0;

  float rocket_launch_time = 0.f;
  float rocket_progress = 0.0f;

  enum class RocketState {
    Init,
    Preparing,
    Launched
  };
  RocketState rocket_state = RocketState::Init;

  MyAppSettings myAppSettings; // This values will be stored in the application settings
};


} // namespace mtool
