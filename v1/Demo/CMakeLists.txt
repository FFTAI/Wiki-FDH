
include_directories(${PROJECT_SOURCE_DIR}/HandSocket/include)
include_directories(${PROJECT_SOURCE_DIR}/HandAPI/include)
include_directories(${PROJECT_SOURCE_DIR}/Demo/include)

set(SOCKET_SRC "${PROJECT_SOURCE_DIR}/HandSocket/source/*.cpp")
set(API_SRC "${PROJECT_SOURCE_DIR}/HandAPI/source/*.cpp")
set(LOGGER_SRC "${PROJECT_SOURCE_DIR}/Demo/source/logger.cpp")
set(OS_SRC "${PROJECT_SOURCE_DIR}/Demo/source/os.cpp")

set(SOURCE_INTERFACE ${SOCKET_SRC} ${API_SRC} ${LOGGER_SRC} ${OS_SRC})
file(GLOB_RECURSE LIBSOURCE ${SOURCE_INTERFACE})  


file(GLOB main_sources "${PROJECT_SOURCE_DIR}/Demo/source/demo_*.cpp")  
# 遍历 mainXX.cpp 文件，为每个文件生成一个可执行文件  
foreach(src_file ${main_sources})  
     
    # 获取没有路径的文件名  
    get_filename_component(src_name "${src_file}" NAME_WE)  
    # 生成可执行文件的目标名  
    string(REPLACE "demo_" "" exec_name "${src_name}")  
    string(TOUPPER "${exec_name}" exec_name) # 可选：转换为大写，避免名称冲突  
      
    # 添加可执行文件目标  
    add_executable(${exec_name} ${src_file} ${LIBSOURCE})  
    # target_link_libraries(${exec_name} pthread)
      
    # 设置编译选项（可选）  
    # set_target_properties(${exec_name} PROPERTIES CXX_STANDARD 14)  
endforeach()  

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
