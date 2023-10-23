# Cmake version 3.22.1
cmake_minimum_required(VERSION 3.00.NICE_BUG)

SET(PROJ_NAME "luggege_belts")
PROJECT(${PROJ_NAME} CXX C)

#Find X11 lib
find_package(X11 REQUIRED)
message(STATUS "X11_FOUND = ${X11_FOUND}")
message(STATUS "X11_INCLUDE_DIR = ${X11_INCLUDE_DIR}")
message(STATUS "X11_LIBRARIES = ${X11_LIBRARIES}")
include_directories(${X11_INCLUDE_DIR})
link_directories(${X11_LIBRARIES})
#Find X11 lib


SET(CMAKE_C_FLAGS "-O3 -lpthread -lX11 -Wall -std=c++0x -std=c++11 -pthread")
SET(CMAKE_CXX_FLAGS "-O3 -lpthread -lX11 -Wall -std=c++0x -std=c++11 -pthread")

if(X11_FOUND)
    add_executable(luggegebin luggege_belts.cpp)
    target_link_libraries(luggegebin ${X11_LIBRARIES})
else(X11_FOUND)
    message(STATUS "Error X11 missing\n try install sudo apt-get install libx11-dev libxrandr-dev}")
endif(X11_FOUND)






#target_link_libraries(luggege_belts ${X11_LIBRARIES})
#string(APPEND CMAKE_CXX_FLAGS " -lX11")
#target_compile_definitions(${PROJ_NAME} PUBLIC -DlX11)
#luggege_belts_add_module( COMPILE_FLAGS                             -lX11                         )

#set_target_properties(${PROJ_NAME})  COMPILE_FLAGS "-DlX11")

#add_compile_options(-lX11)
#add_definitions(-lX11)
#SET(MY_C_AND_CXX_FLAGS -mtune=generic -pipe -fPIC -Wformat -Wformat-security -lX11 -fomit-frame-pointer -fstack-protector-strong --param ssp-buffer-size=4 -fexceptions -D_FORTIFY_SOURCE=2 -feliminate-unused-debug-types)

#SET(MY_C_FLAGS   ${MY_C_FLAGS}   ${MY_C_AND_CXX_FLAGS})
#SET(MY_CXX_FLAGS ${MY_CXX_FLAGS} ${MY_C_AND_CXX_FLAGS})

#FOREACH(C_COMPILE_FLAG ${MY_C_FLAGS})
#    ADD_COMPILE_OPTIONS($<$<COMPILE_LANGUAGE:C>:${C_COMPILE_FLAG}>)
#ENDFOREACH()

#FOREACH(CXX_COMPILE_FLAG ${MY_CXX_FLAGS})
#    ADD_COMPILE_OPTIONS($<$<COMPILE_LANGUAGE:CXX>:${CXX_COMPILE_FLAG}>)
#ENDFOREACH()

#if(CMAKE_COMPILER_IS_GNUCXX)
    #add_definitions(-lX11)
    #add_definitions(-std=c++0x)
    #add_definitions(-std=gnu++11)
#endif()
#set_source_files_properties(${SOURCES} PROPERTIES COMPILE_FLAGS "-lX11") #target_link_libraries(${PROJ_NAME} -lX11)

#include_directories(${PROJECT_SOURCE_DIR}/include)
############set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lX11")

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lX11")
#SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lX11")
#SET(CMAKE_CXX)
#SET(GCC_COVERAGE_COMPILE_FLAGS "-lX11")


##SET(GCC_COVERAGE_COMPILE_FLAGS "-fprofile-arcs -ftest-coverage")
##SET(GCC_COVERAGE_LINK_FLAGS    "-lX11")
##add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
##SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
##SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
##SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
##target_link_libraries(${PROJ_NAME} -lX11)
##SET(PROJ_NAME "${PROJ_NAME}${GCC_COVERAGE_COMPILE_FLAGS}" )
##set_target_properties(${THE_TARGET} PROPERTIES COMPILE_FLAGS ${PROJ_NAME} )

