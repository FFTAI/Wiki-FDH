#!/bin/bash  

# 检查build目录是否存在  
if [ -d "build" ]; then  
    rm -rf build  
fi

if [ -d "lib" ]; then  
    rm -rf lib  
fi

mkdir -p build  
 
  
# 进入build目录  
cd build  
  
# 运行cmake  
cmake ..  
  
# 检查cmake是否成功  
if [ $? -eq 0 ]; then  
    # 如果cmake成功，运行make  
    make  
else  
    echo "cmake failed"  
    exit 1  
fi