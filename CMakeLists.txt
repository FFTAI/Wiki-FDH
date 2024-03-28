cmake_minimum_required(VERSION 3.0)
project(HandControl)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(HandControl example/main.cpp)

target_link_libraries(HandControl PRIVATE ${CMAKE_SOURCE_DIR}/lib/libHandControl.a pthread)