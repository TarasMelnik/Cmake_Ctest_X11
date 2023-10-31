#include "Luggage.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>


void Luggage::set_name(const char* text){
    strncpy(_name,text, sizeof(_name)); 
}

char* Luggage::get_name(){
    return &_name[0];
}