# Wiki-Fdh-Sdk-c++

This repository provides a guidance for Fourier Dexterous Hand SDK install and control. VERSION : "0.0.0.9"



### Directory Structure

```bash
|-- Wiki-Fdh-Sdk-c++
    |-- Demo                # demo directory
    |-- HandAPI             # HandAPI function directory
    |-- HandSocket          # Hand Socket communication function directory
    |-- build.sh            # build bash file
    |-- clean.sh            # clean bash file
    |-- run_demo.sh         # demo run bash file
    |-- CMakeLists.txt      # Cmakelist file for function and demo
    |-- README.md           # English Readme
    |-- README.CN.md        # Chinese Readme
```

### Getting Started
- #### Build
```
bash build.sh
-------or-------
sudo chmod +x build.sh
./build.sh
```
- #### Clean
```
bash clean.sh
-------or-------
sudo chmod +x clean.sh
./clean.sh
```

### Communication Configuration
- Connect the computer to Hand using an Ethernet cable and set the corresponding network card to static IP: 192.168.137.xxx.
- Set handip in code:
```
Right hand : 192.168.137.19
Left hand  : 192.168.137.39 
```

### Running Example Scripts
This demo provides the example for dexterous hand reset, calibration and set position.
```
bash run_demo.sh
```


### User Description
The FDH-SDK provides c++ programming functions, including get sensor params and set config params.

- ##### Get sensor params
- ###### ip: 192.168.137.xxx  port: 2334

    This repository provides get Fourier Dexterous Hand sensor params:
        - Finger order is [Index, Middle, Ring, Little, Thumb, Thumb-Yaw]
    ```
    send: 0x01　　// get encoder pulse counts　     
    send: 0x02　　// get position　                  
    send: 0x03　　// get veloctity                   
    send: 0x04　　// get current                     
    send: 0x05　　// get motor status              
                 // 0:before calibration/start，１:after calibration, 2:after execution, 3:execute, 4:error
    send: 0x06　　// get error code                  
    send: 0x08　　// get pid position params         
    send: 0x09　　// get pid velocity params        
    send: 0x0a　　// get pid current params         
    send: 0x0b　　// get limited position bound　   
    send: 0x0c　　// get limited velocity bound　   
    send: 0x0d　　// get limited current bound     
    send: 0x0e　　// get version                   
    send: 0x0f　　// get hand ip　                  
    ```
- ##### Set config params
- ###### ip: 192.168.137.xxx  port: 2333
    This repository provides set Fourier Dexterous Hand config params including one finger control and all fingers control:

    ```
    send: 0x01 0x01 // calibration　                                 
    send: 0x01 0x0b // emergency        

    ## one finger                              
    send: 0x01 0x02 0x00 id data // set position       | range : [low: 0.0 - high: 12.0]                   
    send: 0x01 0x04 0x00 id data // set velocity       | range : [low: 0 - high: 10000.0]                  
    send: 0x01 0x04 0x00 id data // set current        | range : [low: 0.0 - high: 1000.0]               
    send: 0x01 0x05 0x00 id data_p data_i data_d // set pid position params                   
    send: 0x01 0x06 0x00 id data_p data_i data_d // set pid velocity params         
    send: 0x01 0x07 0x00 id data_p data_i data_d // set pid current params       
    send: 0x01 0x08 0x00 id data_start data_end  // set limited position bound          
    send: 0x00 0x09 0x00 id data // set limited velocity bound　    
    send: 0x01 0x0a 0x00 id data // get limited current bound　    
    send: 0x01 0x21 0x00 id data omega　　// set pdcontrol position       
    
    ## all fingers
    send: 0x01 0x11 0x00 0x00 pos1 pos2 pos3 pos4 pos5 pos6 // set all finger position     | range : [low: 0.0 - high: 12.0]                   
    send: 0x01 0x14 0x00 0x00 pos1 pos2 pos3 pos4 pos5 pos6 // set all finger pwm control  | range : [low: -200 - high: 200]　                  
    ```


