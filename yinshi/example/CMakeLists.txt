cmake_minimum_required(VERSION 3.0)
project(HandControl)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(API_SRC "${PROJECT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE LIBSOURCE ${API_SRC})
add_executable(HandControl example/main.cpp ${LIBSOURCE})

# target_link_libraries(HandControl PRIVATE ${CMAKE_SOURCE_DIR}/lib/libHandControl.a pthread)
target_link_libraries(HandControl pthread)