cmake_minimum_required(VERSION 3.10)

project(Arch-Update-Helper)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Arch-Update-Helper main.cpp)

target_link_libraries(Arch-Update-Helper Qt6::Widgets)

#add_compile_definitions(DEBUG)

