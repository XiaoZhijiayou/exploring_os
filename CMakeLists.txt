cmake_minimum_required(VERSION 3.10)

# 项目信息
project(ExploringOS VERSION 1.0)

# 指定 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

## 查找必要的库
find_package(Threads REQUIRED)

# 添加子目录
add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
add_subdirectory(day04_05)
add_subdirectory(day06)
add_subdirectory(day07)
add_subdirectory(day08)
add_subdirectory(day09)