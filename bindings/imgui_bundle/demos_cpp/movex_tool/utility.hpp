/**
 * @file box.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#include <array>
#include <limits.h>
#include <vector>

namespace mtool
{

struct Box
{
  std::array<double, 3> pose;
  std::vector<double> outline_x;
  std::vector<double> outline_y;
};

int parse_nums_from_buffer(const char* buffer, std::vector<double>& nums, uint32_t parse_limit = UINT_MAX);

int load_box(const char* buffer, int length, Box& box);

int load_boxs(const char* file, std::vector<Box>& boxs, int start_line = 0);

int parse_box(
  const std::array<double, 2>& point1,
  const std::array<double, 2>& point2,
  const std::array<double, 2>& point3,
  const std::array<double, 2>& point4,
  Box& box,
  bool transform = false
  );

int parse_box(
  const std::array<double, 3>& pose,
  const std::array<double, 2>& size,
  const std::array<double, 2>& offset,
  Box& box,
  bool transform = false
  );

int load_box2(const char* buffer, int length, Box& box);
int load_boxs2(const char* file, std::vector<Box>& boxs, int start_line = 0);

}