cmake_minimum_required(VERSION 3.16)
project(dh-sdk-cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)


file(GLOB main_sources "${PROJECT_SOURCE_DIR}/source/demo_*.cpp")  
  
# 遍历 mainXX.cpp 文件，为每个文件生成一个可执行文件  
foreach(src_file ${main_sources})  
     
    # 获取没有路径的文件名  
    get_filename_component(src_name "${src_file}" NAME_WE)  
    # 生成可执行文件的目标名  
    string(REPLACE "demo_" "" exec_name "${src_name}")  
    string(TOUPPER "${exec_name}" exec_name) # 可选：转换为大写，避免名称冲突  
      
    # 添加可执行文件目标  
    add_executable(${exec_name} ${src_file} ${PROJECT_SOURCE_DIR}/source/dh.cpp ${PROJECT_SOURCE_DIR}/source/logger.cpp ${PROJECT_SOURCE_DIR}/source/os.cpp)  
    target_link_libraries(${exec_name} pthread)
      
    # 设置编译选项（可选）  
    set_target_properties(${exec_name} PROPERTIES CXX_STANDARD 14)  
endforeach()  


set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)