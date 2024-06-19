#!/bin/bash  
  
# 检查build目录是否存在  
if [ -d "build" ]; then  
    # 如果存在，则删除build目录及其所有内容  
    rm -rf build  
    echo "build directory has been removed."  
else  
    echo "build directory does not exist."  
fi

if [ -d "lib" ]; then  
    # 如果存在，则删除build目录及其所有内容  
    rm -rf lib  
    echo "lib directory has been removed."  
else  
    echo "lib directory does not exist."  
fi