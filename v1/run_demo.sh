#!/bin/bash  

# 检查build目录是否存在  
if [ -d "build" ]; then  
    cd bin
    ./CALIBRATION
    sleep 3
    ./GET_CNT
    sleep 3
    ./GET_CURRENT_LIMITED
    sleep 3
    ./GET_CURRENT_PID
    sleep 3
    ./GET_CURRENT
    sleep 3
    ./GET_ERRORCODE
    sleep 3
    ./GET_FIRMWARE_VERSION
    sleep 3
    ./GET_IP
    sleep 3
    ./GET_POS_LIMITED
    sleep 3
    ./GET_POS_PID
    sleep 3
    ./GET_POS
    sleep 3
    ./GET_STATUS
    sleep 3
    ./GET_VELOCITY_LIMITED
    sleep 3
    ./GET_VELOCITY_PID
    sleep 3
    ./GET_VELOCITY
    sleep 3
    ./SET_CURRENT_LIMITED
    sleep 3
    ./SET_CURRENT
    sleep 3
    ./SET_PD_CONTROL
    sleep 3
    ./SET_POS_ALL
    sleep 3
    ./SET_POS_PID
    sleep 3
    ./SET_POS
    sleep 3
    ./SET_PWM
    ./USER
else
    echo "build file is not exit, please run bash build.sh"
fi