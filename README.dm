This project use the Cmake version 3.22.1
X11 view emulation of move luggage and cache keyboard 

Command button:
 - '1' add/delate luggage to belt
 - '2' add/delate luggage to belt
 - '3' add/delate luggage to belt
 - '4' add/delate luggage to belt
To quit from program
 - 'q' quit or press Ctrl+C in terminal

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
./cmake .

##build
.cmake --build .

## run project
./luggege_belts

## Tested
- WSL Ubuntu 20.04 passed
- Raspberry Ubuntu 20.04 passed??















/build/cmake --build ..
## install GUI pkg
------------------------------------------------------------------------------sudo apt install libx11-dev
sudo apt-get install libx11-dev libxrandr-dev
-------------------------------------------------------------------- ???? sudo apt-get install libx11-dev libxpm-dev libxft-dev libxext-dev mesa-common-dev
 
-------------------------------------------------------------------# finde:
--------------------------------------------------------------------find /usr/lib -iname *x11*

