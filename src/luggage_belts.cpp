
#include "luggage_belts.h"

extern "C" {
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
}

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <thread>
#include <queue>
#include <array>
#include "Luggage.h"
// #include "Belts.h"

// #define DISPLAY_HEIGHT 640
// #define DISPLAY_WIDHT  640


// #define NO_LUGGAGE "No luggage"


// #define BELTS_LEN 10.0f
// #define LUGGAGE_SPEED_MULT 0.00017f

#define DISPLAY_HEIGHT 640
#define DISPLAY_WIDHT  640

using namespace std;

// GUI
Display *dis;
Screen *screen;
int scrn_num;
Window win;
GC gc;
unsigned long black, white, red, blue;
void init_gui(void);
void gui_task(std::queue<int> & _b1);
void _close(void);
unsigned long RGB(int r, int g, int b);


Belts belts[MAX_BELTS];
Luggage luggage[MAX_LUGGAGE];

void one_second_loop();

int main() {
    std::array<std::queue<int>, MAX_BELTS> q_belts;

    char str[10] = BELTS_NAME;
    char tmp_str[20];
    for (int i = 0; i < MAX_BELTS; i++) {
        sprintf(tmp_str,"%d",i+1);
        strcat(str,tmp_str);
        belts[i].set_name(str);
        memset(str,0,sizeof(str));
        sprintf(str,BELTS_NAME);
        if(i != MAX_BELTS-1){
            belts[i].set_speed(1.0f);
            belts[i].start_task(i, std::ref(q_belts[i]), std::ref(q_belts[i+1]));
        } else{
            belts[i].set_speed(2.0f);
            belts[i].start_task(i, std::ref(q_belts[i]), std::ref(q_belts[0]));
        }
       belts[i].luggage = luggage;
    }

    memset(str,0,sizeof(str));
    sprintf(str,LUGGAGE_NAME);
    for (int i = 0; i < MAX_LUGGAGE; i++) {
        sprintf(tmp_str,"%d",i+1);
        strcat(str,tmp_str);
        luggage[i].set_name(str);
        memset(str,0,sizeof(str));
        sprintf(str,LUGGAGE_NAME);
    }


    init_gui();
    std::thread th_gui(gui_task, std::ref(q_belts[0]));
    std::thread th(one_second_loop);
    
    th.join();
    th_gui.join();
    
    return 0;
}

void one_second_loop(){
    while (1) {

        std::this_thread::sleep_for(std::chrono::seconds(1));//sleep(1); // wait 1 second
        printf("\ec"); // clear terminal
        for(int i= 0; i < MAX_BELTS; i++){
            printf("%s %d ",belts[i].get_name(), belts[i].get_count_l());
        }
        printf("\n");
        
        bool no_luggege = true;
        for(int i= 0; i < MAX_LUGGAGE; i++){
            if(luggage[i].enable){
                printf("%s %d %.1f \n",luggage[i].get_name(), luggage[i].belts_num, luggage[i].distanse);
                //printf("%s %d %.1f  x %d y %d\n",luggage[i].get_name(), luggage[i].belts_num, luggage[i].distanse, luggage[i].dot.x, luggage[i].dot.y );
                no_luggege = false;
            }
        }

        if(no_luggege){
            printf("NO_LUGGAGE\n");
        }
    }
}

void gui_task(std::queue<int> & _b1){
    XEvent event;
    KeySym key;
    char text[255];
    XNextEvent(dis, &event);
    while (1){
        std::this_thread::sleep_for(std::chrono::microseconds(THREAD_SLEEP));
        while (XPending(dis) > 0) {  
            XNextEvent(dis, &event);
            if(event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key,0) == 1) {
                if(text[0] == 'q'){
                    _close();
                }
                
                for(int i = 0; i < MAX_LUGGAGE; i++){
                    if((char)(i+49) == text[0]){ // 49 = '1'
                        if(luggage[i].enable){
                            if(luggage[i].belts_num > 0){ // delate luggege from belts
                                belts[luggage[i].belts_num-1].del_luggege(i);
                                luggage[i].belts_num = -1;
                                luggage[i].distanse = 0.0f;
                            }
                            luggage[i].enable = false;
                        }else {
                            luggage[i].enable = true;
                            _b1.push(i);
                        }
                    }
                }
            }
        }
        // need ADD WAIT SIMHROnization ON vsync??????
        XClearWindow(dis, win);
        for(int j = 0; j < MAX_BELTS; j++){
            XSetForeground(dis,gc,blue);
            XDrawLine(dis,win,gc,
            belts[j].line.start_x,
            belts[j].line.start_y,
            belts[j].line.end_x,
            belts[j].line.end_y
            );
            XSetForeground(dis,gc,red);
            XDrawString(dis,win,gc,
            belts[j].line.end_x,
            belts[j].line.end_y,
            belts[j].get_name(),
            strlen(belts[j].get_name())
            );
        
            for (int i = 0; i < belts[j].get_count_l(); i++){
                int l_num = belts[j].get_luggege(i);
                if(luggage[l_num].enable){

                    int diff_x = belts[j].line.end_x - belts[j].line.start_x;
                    int diff_y = belts[j].line.end_y - belts[j].line.start_y;
                    float distanse = luggage[l_num].distanse;
                    if(diff_x == 0){
                        luggage[l_num].dot.x = belts[j].line.start_x;
                        luggage[l_num].dot.y = (uint32_t) belts[j].line.start_y + (diff_y * distanse)/ belts[j].len;
                    } else if(diff_y == 0) {
                        luggage[l_num].dot.x = (uint32_t) belts[j].line.start_x + (diff_x * distanse)/ belts[j].len;
                        luggage[l_num].dot.y = belts[j].line.start_y;
                    } 
                    memset(text,0,sizeof(text));
                    
                    sprintf(text, "%s %0.1f",luggage[l_num].get_name(), luggage[l_num].distanse);
                    
                    XSetForeground(dis,gc,white);
                    XDrawString(dis,win,gc,luggage[l_num].dot.x,luggage[l_num].dot.y,text,strlen(text));
                    XDrawPoint(dis,win,gc, luggage[l_num].dot.x,luggage[l_num].dot.y);
                    
                }
            }

            XSetForeground(dis,gc,white);
            //test
            // XDrawString(dis,win,gc,
            // 0,//DISPLAY_WIDHT,
            // 100,//DISPLAY_HEIGHT,
            // belts[0].get_name(),
            // strlen(belts[0].get_name())
            // );
            for(int i= 0; i < MAX_BELTS; i++){
                int* b_lu_arr = belts[i].get_lug_num();
                memset(text,0,sizeof(text));
                sprintf(text, "%s %d | ",belts[i].get_name(), belts[i].get_count_l());
                for(int i= 0; i < MAX_LUGGAGE; i++){
                    char tmp[20];
                    // memset(tmp,0,sizeof(text));
                    sprintf(tmp, " %d ",b_lu_arr[i]);
                    strcat(text,tmp);
                }
                XDrawString(dis,win,gc,0,11*i+10,text,strlen(text));
            }
            
            for(int i= 0; i < MAX_LUGGAGE; i++){
                memset(text,0,sizeof(text));
                sprintf(text, "%s %d %.1f x=%d y=%d",luggage[i].get_name(), luggage[i].belts_num, luggage[i].distanse, luggage[i].dot.x, luggage[i].dot.y);
                XDrawString(dis,win,gc,0,11*i+(11*MAX_BELTS)+10,text,strlen(text));
            }

        
        }
    }
}

void init_gui() {
    // neend rewrite to array
    belts[0].line.start_x = DISPLAY_WIDHT/2 - (DISPLAY_WIDHT/4);
    belts[0].line.start_y = DISPLAY_HEIGHT/2 + (DISPLAY_HEIGHT/4);
    belts[0].line.end_x =   DISPLAY_WIDHT/2 + (DISPLAY_WIDHT/4);
    belts[0].line.end_y =   DISPLAY_HEIGHT/2 + (DISPLAY_HEIGHT/4);
    
    belts[1].line.start_x = belts[0].line.end_x;  
    belts[1].line.start_y = belts[0].line.end_y; 
    belts[1].line.end_x = DISPLAY_WIDHT/2 + (DISPLAY_WIDHT/4);
    belts[1].line.end_y = DISPLAY_HEIGHT/2 - (DISPLAY_HEIGHT/4);

    belts[2].line.start_x = belts[1].line.end_x; 
    belts[2].line.start_y = belts[1].line.end_y; 
    belts[2].line.end_x = DISPLAY_WIDHT/2 - (DISPLAY_WIDHT/4);
    belts[2].line.end_y = DISPLAY_HEIGHT/2 - (DISPLAY_HEIGHT/4);

    belts[3].line.start_x = belts[2].line.end_x;  
    belts[3].line.start_y = belts[2].line.end_y; 
    belts[3].line.end_x = DISPLAY_WIDHT/2 - (DISPLAY_WIDHT/4);
    belts[3].line.end_y = DISPLAY_HEIGHT/2 + (DISPLAY_HEIGHT/4);
    // neend rewrite

    dis = XOpenDisplay((char *)0);
    scrn_num = DefaultScreen(dis);
    black = BlackPixel(dis, scrn_num);
    white = WhitePixel(dis, scrn_num);
    red = RGB(255,0,0);
    blue = RGB(0,0,255);
    screen = ScreenOfDisplay(dis, scrn_num);
    // dot.x = 0;(screen->width/2 - screen->width/10); // start position
    // dot.y = 0;(screen->height/2 - screen->height/10); 
    win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 0, 0, DISPLAY_WIDHT, DISPLAY_HEIGHT, 5, white, black);
    XSetStandardProperties(dis, win, "Luggage belts", NULL, None, NULL, 0, NULL);
    XSelectInput(dis, win, ExposureMask  | KeyPressMask);//| ButtonPressMask
    gc = XCreateGC(dis, win, 0,0);
    XSetBackground(dis,gc,white);
    XSetForeground(dis,gc,black);
    XClearWindow(dis, win);
    XMapRaised(dis, win);
}

void _close() {
    XFreeGC(dis, gc);
    XDestroyWindow(dis, win);
    XCloseDisplay(dis);
    exit(0);
}

inline unsigned long RGB(int r, int g, int b) {
    return b + (g<<8) + (r<<16);
}


