#include "Belts.h"
#include "Luggage.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

void Belts::set_luggege(int id){
    if(count_luggage < MAX_LUGGAGE){
        for(int i = 0; i < count_luggage; i++){ // check duplicate
            if(luggage_num[i] == id){
                return;
            }
        }

        luggage_num[count_luggage] = id;
        count_luggage += 1;
    }
}

void Belts::del_luggege(int id){
    for(int i = 0; i < count_luggage; i++){
        if(luggage_num[i] == id){
            for (int j = 0; j < count_luggage - i; j++) {
                if(i+1+j >= MAX_LUGGAGE){ 
                    luggage_num[i+j] = 0;
                } else {
                    luggage_num[i+j] = luggage_num[i+1+j];
                }
            } 
            count_luggage -= 1;
            break;
        }
    }
}

void Belts::task(int id, std::queue<int> & get, std::queue<int> & send){
    int l_id;
    while (!stop_thread){
        // usleep(THREAD_SLEEP);
        std::this_thread::sleep_for(std::chrono::microseconds(THREAD_SLEEP));
        if(!get.empty()){ // get new luggege
            l_id = get.front();
            if(count_luggage < MAX_LUGGAGE){
                if(luggage[l_id].enable){
                    set_luggege(l_id);
                    luggage[l_id].belts_num = id+1;
                }
                get.pop();
            } else {
                get.pop();
            }
        }

        for (int i = 0; i < count_luggage; i++){
            int l_num = get_luggege(i);
            if(luggage[l_num].enable){
                luggage[l_num].distanse += (LUGGAGE_SPEED_MULT * get_speed());
                if(luggage[l_num].distanse >= len){
                    del_luggege(l_num);
                    send.push(l_num);
                    luggage[l_num].distanse = 0.0f;
                }
            }
        }
    }
}
