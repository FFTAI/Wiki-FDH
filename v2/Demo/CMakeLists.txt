
include_directories(${PROJECT_SOURCE_DIR}/HandSocket/include)
include_directories(${PROJECT_SOURCE_DIR}/HandAPI/include)

set(SOCKET_SRC "${PROJECT_SOURCE_DIR}/HandSocket/source/*.cpp")
set(API_SRC "${PROJECT_SOURCE_DIR}/HandAPI/source/*.cpp")

set(SOURCE_INTERFACE ${SOCKET_SRC} ${API_SRC})
file(GLOB_RECURSE LIBSOURCE ${SOURCE_INTERFACE})  


set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
add_executable(demo demo.cpp ${LIBSOURCE})


