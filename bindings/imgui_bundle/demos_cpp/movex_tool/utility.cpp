/**
 * @file utility.cpp
 * @author yanxin.xing (sdkxyx@hotmail.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <array>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <strings.h>

#include "utility.hpp"

namespace mtool
{

int parse_nums_from_buffer(const char* buffer, std::vector<double>& nums, uint32_t parse_limit){
  int offset = 0;
  int read_num = 0;
  double x;
  while (sscanf(buffer + offset, "%lf %n", &x, &read_num) == 1)
  {
    nums.push_back(x);
    offset += read_num + 1;
    if (nums.size() >= parse_limit) {
      break;
    }
  }
  return 0;
}

int load_box(const char* buffer, int length, Box& box) {
  std::vector<double> data; //size: 3+2n, pose and edge point
  parse_nums_from_buffer(buffer, data);
  if (data.size() < 3 || (data.size() % 2) == 0) {
    printf("load failed: %zu, %s\n", data.size(), buffer);
    return -1;
  }

  box.pose[0] = data[0];
  box.pose[1] = data[1];
  box.pose[2] = data[2];

  for (int i = 3; i < data.size(); i+=2) {
    box.outline_x.push_back(data[i]);
    box.outline_y.push_back(data[i + 1]);
    if(i > 3) {
      printf("new point: %f\n", hypot(data[i]-data[i - 2], data[i + 1]-data[i - 1]));
    }
  }
  if (box.outline_x.size() > 0) {
    printf("new point: %f\n", hypot(box.outline_x.front()-box.outline_x.back(), box.outline_y.front()-box.outline_y.back()));
  }
  return 0;
}

int load_boxs(const char* file, std::vector<Box>& boxs, int start_line) {
  FILE* fp = fopen(file, "r");
  if (!fp) return -1;

  char buffer[4096];
  int line_count = 0;
  while(line_count < start_line) {
    fgets(buffer, 4096, fp);
    ++line_count;
  }

  int count = 0;
  while(fgets(buffer, 4096, fp)) {
    ++count;
    // printf(">>%s<<\n", buffer);
    Box box;



    if(load_box(buffer, 4096, box) == 0) {
      boxs.push_back(box);
    }
    bzero(buffer, 4096);
  }

  fclose(fp);
  return count;
}

int parse_box(
  const std::array<double, 2>& point1,
  const std::array<double, 2>& point2,
  const std::array<double, 2>& point3,
  const std::array<double, 2>& point4,
  Box& box,
  bool transform
  ) {
  if(transform) {
    box.pose = {-(point1[1] + point2[1] + point3[1] + point4[1]) / 4.f, (point1[0] + point2[0] + point3[0] + point4[0]) / 4.f, 0.f};
    box.outline_x = {-point1[1], -point2[1], -point3[1], -point4[1]};
    box.outline_y = {point1[0], point2[0], point3[0], point4[0]};
  } else {
    box.pose = {(point1[0] + point2[0] + point3[0] + point4[0]) / 4.f, (point1[1] + point2[1] + point3[1] + point4[1]) / 4.f, 0.f};
    box.outline_x = {point1[0], point2[0], point3[0], point4[0]};
    box.outline_y = {point1[1], point2[1], point3[1], point4[1]};
  }

  return 0;
}

int parse_box(
  const std::array<double, 3>& pose,
  const std::array<double, 2>& size,
  const std::array<double, 2>& offset,
  Box& box,
  bool transform
  ) {

  std::array<double, 2> op1 = { size[0] / 2 + offset[0],  size[1] / 2 + offset[1]};
  std::array<double, 2> op2 = {-size[0] / 2 + offset[0],  size[1] / 2 + offset[1]};
  std::array<double, 2> op3 = {-size[0] / 2 + offset[0], -size[1] / 2 + offset[1]};
  std::array<double, 2> op4 = { size[0] / 2 + offset[0], -size[1] / 2 + offset[1]};

  std::array<double, 2> rp1 = {op1[0] * cos(pose[2]) - op1[1] * sin(pose[2]), op1[0] * sin(pose[2]) + op1[1] * cos(pose[2])};
  std::array<double, 2> rp2 = {op2[0] * cos(pose[2]) - op2[1] * sin(pose[2]), op2[0] * sin(pose[2]) + op2[1] * cos(pose[2])};
  std::array<double, 2> rp3 = {op3[0] * cos(pose[2]) - op3[1] * sin(pose[2]), op3[0] * sin(pose[2]) + op3[1] * cos(pose[2])};
  std::array<double, 2> rp4 = {op4[0] * cos(pose[2]) - op4[1] * sin(pose[2]), op4[0] * sin(pose[2]) + op4[1] * cos(pose[2])};

  box.pose = pose;
  box.outline_x = {rp1[0] + pose[0], rp2[0] + pose[0], rp3[0] + pose[0], rp4[0] + pose[0]};
  box.outline_y = {rp1[1] + pose[1], rp2[1] + pose[1], rp3[1] + pose[1], rp4[1] + pose[1]};

  if(transform) {
    box.pose = {-pose[1], pose[0], pose[2]};
    box.outline_x = {-rp1[1] - pose[1], -rp2[1] - pose[1], -rp3[1] - pose[1], -rp4[1] - pose[1]};
    box.outline_y = {rp1[0] + pose[0], rp2[0] + pose[0], rp3[0] + pose[0], rp4[0] + pose[0]};
  } else {
    box.pose = pose;
    box.outline_x = {rp1[0] + pose[0], rp2[0] + pose[0], rp3[0] + pose[0], rp4[0] + pose[0]};
    box.outline_y = {rp1[1] + pose[1], rp2[1] + pose[1], rp3[1] + pose[1], rp4[1] + pose[1]};
  }

  return 0;
}

int load_box2(const char* buffer, int length, Box& box) {
  std::vector<double> data; //size: 3+2n, pose and edge point
  parse_nums_from_buffer(buffer, data);
  if (data.size() != 7) {
    printf("load failed: %zu, %s\n", data.size(), buffer);
    return -1;
  }

  parse_box({data[0], data[1], data[2]}, {data[3], data[4]}, {data[5], data[6]}, box);
  return 0;
}


int load_boxs2(const char* file, std::vector<Box>& boxs, int start_line) {
  FILE* fp = fopen(file, "r");
  if (!fp) return -1;

  char buffer[4096];
  int line_count = 0;
  while(line_count < start_line) {
    fgets(buffer, 4096, fp);
    ++line_count;
  }

  int count = 0;
  while(fgets(buffer, 4096, fp)) {
    ++count;
    // printf(">>%s<<\n", buffer);
    Box box;



    if(load_box2(buffer, 4096, box) == 0) {
      boxs.push_back(box);
    }
    bzero(buffer, 4096);
  }

  fclose(fp);
  return count;
}

}