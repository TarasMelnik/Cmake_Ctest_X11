

#define BELTS_NAME "B"
#define MAX_BELTS 4
#define BELTS_LEN 10.0f
#define LUGGAGE_SPEED_MULT 0.00017f
#define THREAD_SLEEP 100


#pragma once

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <thread>
#include <queue>

#include "Luggage.h"
#include "luggage_belts.h"


class Luggage;

class Belts {
public:  
    Belts(): len (BELTS_LEN), th(), _speed (1.0f) {};
    ~Belts(){
        stop_thread = true;
        if(th.joinable())th.join();
        };
    struct coord {
        int start_x;
        int start_y;
        int end_x;
        int end_y;
    } line;
    Luggage *luggage;
    // std::vector<Luggage> get;
    void task(int id, std::queue<int> & get, std::queue<int> & send);
    void start_task(int id, std::queue<int> & get, std::queue<int> & send) {
        th = std::thread (&Belts::task, this, id, std::ref(get), std::ref(send));
    }

    void set_luggege(int id);
    void del_luggege(int id);
    int get_luggege(int cnt){return luggage_num[cnt]; }
	float get_speed(){ return _speed;}
	void set_speed(float speed){_speed = speed;}
	void set_name(const char* text){strncpy(_name,text, sizeof(_name)); }
    char* get_name(){return &_name[0];}
    int get_count_l(){return count_luggage;}
    int len;


    //for debug
    int* get_lug_num(){return luggage_num;}
private:
    int count_luggage {0};
    bool stop_thread = false;
    int id;
    std::thread th;
    int luggage_num[MAX_LUGGAGE];
    char _name[3];
    float _speed;
};
