include_directories(${PROJECT_SOURCE_DIR}/HandSocket/include)

set(SOCKET_SRC "${PROJECT_SOURCE_DIR}/HandSocket/source/*.cpp")

set(SOURCE_INTERFACE ${SOCKET_SRC})

file(GLOB_RECURSE LIBSOURCE ${SOURCE_INTERFACE})  

add_library(HandSocket SHARED ${LIBSOURCE})  
# add_library(HandCommunication STATIC ${LIBSOURCE})  

# 如果你的库需要包含头文件，你可以使用以下命令安装这些头文件  
file(GLOB_RECURSE LIBINCLUDE "${PROJECT_SOURCE_DIR}/HandSocket/include/*.h")  
install(FILES ${LIBINCLUDE} DESTINATION include)  

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

add_executable(socket main.cpp ${LIBSOURCE})

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)