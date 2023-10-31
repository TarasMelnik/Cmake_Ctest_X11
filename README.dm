# This project use the Cmake version 3.22.1
# X11 use to view emulation of move luggage and cache keyboard event.

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
 # X11  - use
 # openCV - not use
 # graphics.h library - not use
 # gnuplot - not use

##type for init project
mkdir build
cd build
./cmake ..

##build
.cmake --build .

## run project
./src/luggege_belts
or
cd src && ./luggege_belts

## enjoy 

## Tested for build to run the project
- Windows WSL Ubuntu 20.04 passed (Get real time delay not work property)
- Ubuntu 20.04 passed (Get real time delay not work property)

# File description:
    # CmakeLists.txt is the root CMake, and it sets up the project name, C++ configuration (such as the standard required), 
    and includes the subdirectories src and find X11 libs with find_package(...) and tests with add_subdirectory(...).
    # luggege_belts.cpp main project

# run VScode from WSL terminal
 # code .