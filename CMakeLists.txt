# CMake 最低版本号要求

cmake_minimum_required (VERSION 2.8)
# 编译器
SET(CMAKE_C_COMPILER "arm-linux-gcc")
SET(CMAKE_CXX_COMPILER "arm-linux-g++")

# 项目信息
project (iot)

set(CMAKE_C_FLAGS "-std=c99 -g")

# 添加当前路径下的所有.c文件到SOURCE
aux_source_directory(./ SOURCE)
# 指定生成目标
add_executable(smart_house ${SOURCE})


target_link_libraries(smart_house pthread)



