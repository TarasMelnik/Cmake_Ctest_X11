
##build

/build/cmake --build ..
## install file:
sudo apt-get install cmake
sudo apt-get update && sudo apt-get install build-essential

DISCLAIMER: I am not a linux professional, just found a way for my own problem with glibc not found error msg:

maybe you cannot use the binary since it was compiled with gcc-11 and your gcc version of your linux distribution and version only is gcc-9 and therefore only provides glibc_2.31 (I guess). you can try to compile the program yourself from source. 
I had to do this with the new stockfish version 15, which also uses updated glibc_2.32/2.33/2.34 and my linux-mint does not provide that. 
But compiling from source worked like a charm. Maybe this is an option for you.


## GUI:
- X11  - use
- openCV - not use
- graphics.h library - not use
- gnuplot - not use

sudo apt install libx11-dev
sudo apt-get install libx11-dev libxrandr-dev
 ???? sudo apt-get install libx11-dev libxpm-dev libxft-dev libxext-dev mesa-common-dev
 
# finde:
find /usr/lib -iname *x11*

