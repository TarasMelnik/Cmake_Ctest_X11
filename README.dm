# This project use the Cmake version 3.22.1
# X11 view emulation of move luggage and cache keyboard. 

#Command button on window X11 "Luggage_belt" :
    # '1' add/delate luggage to belt
    # '2' add/delate luggage to belt
    # '3' add/delate luggage to belt
    # '4' add/delate luggage to belt
#To quit from program
    # 'q' quit or press Ctrl+C in terminal

## install Cmake file:
sudo apt-get install cmake
sudo apt-get update && sudo apt-get install build-essential

## Install GUI pkg
sudo apt-get install libx11-dev libxrandr-dev

## GUI:
- X11  - use
- openCV - not use
- graphics.h library - not use
- gnuplot - not use

##type for init project
cd build
./cmake ..

##build
.cmake --build .

## run project
./luggege_belts

## enjoy 

## Tested
- Windows WSL Ubuntu 20.04 passed
- Ubuntu 20.04 passed
