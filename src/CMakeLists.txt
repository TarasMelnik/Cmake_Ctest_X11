# 
#add_library(${PROJ_NAME} luggege_belts.cpp)

#target_include_directories(${PROJ_NAME} PUBLIC_HEADER include)
#add_executable(${PROJ_NAME} luggege_belts.cpp)
#SET(PROJ_NAME "luggege_belts")
#PROJECT(${PROJ_NAME} CXX C)

#Find X11 lib
find_package(X11 REQUIRED)
message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")
include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})
#End Find X11 lib

SET(CMAKE_C_FLAGS   "-O3 -lpthread -lX11 -Wall -std=c++0x -std=c++11 -pthread")
SET(CMAKE_CXX_FLAGS "-O3 -lpthread -lX11 -Wall -std=c++0x -std=c++11 -pthread")

if(X11_FOUND)
    add_executable(${PROJ_NAME} luggage_belts.cpp
                                Luggage.cpp
                                Belts.cpp
                                )
    target_link_libraries(${PROJ_NAME} ${X11_LIBRARIES})
else(X11_FOUND)
    message(STATUS "Error X11 missing\n try install sudo apt-get install libx11-dev libxrandr-dev}")
endif(X11_FOUND)