/**
 * @file app_gui.hpp
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

namespace mtool
{

void GuiNavagation(GuiContext& context);
void GuiLogger(GuiContext& context);
void GuiHome(GuiContext& context);
void GuiDataVisualization(GuiContext& context);
void GuiCanvas(GuiContext& context);
void GuiStatusBar(GuiContext& context);

void GuiImguiDemo(GuiContext& context);
} // namespace mtool
