#!/bin/bash  

# 检查build目录是否存在  
if [ -d "build" ]; then  
    cd build
    ./api
else
    echo "build file is not exit, please run bash build.sh"
fi