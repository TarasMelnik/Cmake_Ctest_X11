

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

#define DISPLAY_HEIGHT 640
#define DISPLAY_WIDHD  640
#define NO_LUGGAGE "No luggage"
#define MAX_LUGGAGE 4
#define MAX_BELTS 4
#define BELTS_LEN 10.0f

using namespace std;
class Luggege
{
public:
    Luggege(){};

	void set_name(const char* text){strncpy(_name,text, sizeof(_name)); }
    char* get_name(){return &_name[0];};
    bool enable {0};
    float distanse {0};
	int belts_num {-1};
    long int start {0};
private:
    char _name[3];
};

class Belts {
public:  
    Belts(): len (BELTS_LEN){};
    struct coord {
        int x;
        int y;
    } dot;

    //void _thread(void);
    void set_luggege(int id);
    void del_luggege(int id);
    int get_luggege(int cnt){return luggage_num[cnt]; }
	float get_speed(){ return _speed;};
	void set_speed(float speed){_speed = speed;};
	void set_name(const char* text){strncpy(_name,text, sizeof(_name)); }
    char* get_name(){return &_name[0];};
    int count_luggage {0};
    int len;
private: 
   
    int luggage_num[MAX_LUGGAGE];
    char _name[3];
    float _speed;
};

void Belts::set_luggege(int id){
    if(count_luggage < MAX_LUGGAGE){
        luggage_num[count_luggage] = id;
        count_luggage += 1;
    }
}

void Belts::del_luggege(int id){
    for(int i = 0; i < count_luggage; i++){
        if(luggage_num[i] == id){
            //sort arr
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

void init();

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
void draw(void);
unsigned long RGB(int r, int g, int b);
struct coord {
 int x;
 int y;
} dot;


Belts belts[MAX_BELTS];
Luggege luggage[MAX_LUGGAGE];
void one_second_loop();
void update();

void belts1_task(int id, std::queue<int> & get, std::queue<int> & send){

    while (1){
        usleep(1);

        if(!get.empty()){ // get new luggege
            int l_id = get.front(); // need rewrite to get pointer luggege[X]
            if(l_id < MAX_LUGGAGE){
                if(luggage[l_id].enable){
                    belts[id].set_luggege(l_id);
                    luggage[l_id].belts_num = id+1;
                }
                get.pop();
            } else {
                get.pop();
            }
        }

        for (int i = 0; i < belts[id].count_luggage; i++){
            int l_num = belts[id].get_luggege(i);
            if(luggage[l_num].enable){
                luggage[l_num].distanse += (0.0001f * belts[id].get_speed());
                if(luggage[l_num].distanse >= belts[id].len){
                    luggage[l_num].distanse = 0.0f;
                    belts[id].del_luggege(l_num);
                    send.push(l_num);
                }
            }
        }
        
    }
}
void belts2_task(int id, std::queue<int> & get, std::queue<int> & send){
   
    while (1){
        usleep(1);

        if(!get.empty()){ // get new luggege
            int l_id = get.front();
            if(l_id < MAX_LUGGAGE){
                if(luggage[l_id].enable){
                    belts[id].set_luggege(l_id);
                    luggage[l_id].belts_num = id+1;
                }
                get.pop();
            } else {
                get.pop();
            }
        }

        for (int i = 0; i < belts[id].count_luggage; i++){
            int l_num = belts[id].get_luggege(i);
            if(luggage[l_num].enable){
                luggage[l_num].distanse += (0.0001f * belts[id].get_speed());
                if(luggage[l_num].distanse >= belts[id].len){
                    luggage[l_num].distanse = 0.0f;
                    belts[id].del_luggege(l_num);
                    send.push(l_num);
                }
            }
        }
        
    }
}
void belts3_task(int id, std::queue<int> & get, std::queue<int> & send){
    
    while (1){
        usleep(1);

        if(!get.empty()){ // get new luggege
            int l_id = get.front();
            if(l_id < MAX_LUGGAGE){
                if(luggage[l_id].enable){
                    belts[id].set_luggege(l_id);
                    luggage[l_id].belts_num = id+1;
                }
                get.pop();
            } else {
                get.pop();
            }
        }

        for (int i = 0; i < belts[id].count_luggage; i++){
            int l_num = belts[id].get_luggege(i);
            if(luggage[l_num].enable){
                luggage[l_num].distanse += (0.0001f * belts[id].get_speed());
                if(luggage[l_num].distanse >= belts[id].len){
                    luggage[l_num].distanse = 0.0f;
                    belts[id].del_luggege(l_num);
                    send.push(l_num);
                }
            }
        } 
    }
}
void belts4_task(int id, std::queue<int> & get, std::queue<int> & send){
    
    while (1){
        usleep(1);

        if(!get.empty()){ // get new luggege
            int l_id = get.front();
            if(l_id < MAX_LUGGAGE){
                if(luggage[l_id].enable){
                    belts[id].set_luggege(l_id);
                    luggage[l_id].belts_num = id+1;
                }
                get.pop();
            } else {
                get.pop();
            }
        }

        for (int i = 0; i < belts[id].count_luggage; i++){
            int l_num = belts[id].get_luggege(i);
            if(luggage[l_num].enable){
                luggage[l_num].distanse += (0.0001f * belts[id].get_speed());
                if(luggage[l_num].distanse >= belts[id].len){
                    luggage[l_num].distanse = 0.0f;
                    belts[id].del_luggege(l_num);
                    send.push(l_num);
                }
            }
        }
        
    }
}

int main() {
    std::queue<int> belts_1;
    std::queue<int> belts_2;
    std::queue<int> belts_3;
    std::queue<int> belts_4;
    init();
    init_gui();

    std::thread th(one_second_loop);
    std::thread th_gui(gui_task, std::ref(belts_1));
    std::thread th_b1(belts1_task, 0, std::ref(belts_1), std::ref(belts_2));
    std::thread th_b2(belts2_task, 1, std::ref(belts_2), std::ref(belts_3));
    std::thread th_b3(belts3_task, 2, std::ref(belts_3), std::ref(belts_4));
    std::thread th_b4(belts4_task, 3, std::ref(belts_4), std::ref(belts_1));
    
    th.join();
    th_gui.join();
    th_b1.join();
    th_b2.join();
    th_b3.join();
    th_b4.join();

    while (1){exit(0);}
    
    return 0;
}

void init(){

    belts[0].set_name("B1");
    belts[0].set_speed(1.0f);
    belts[1].set_name("B2");
    belts[1].set_speed(1.0f);
    belts[2].set_name("B3");
    belts[2].set_speed(1.0f);
    belts[3].set_name("B4");
    belts[3].set_speed(2.0f);
    
    luggage[0].set_name("L1");
    luggage[1].set_name("L2");
    luggage[2].set_name("L3");
    luggage[3].set_name("L4");
    
}

void one_second_loop(){
    while (1) {

        sleep(1); // wait 1 second
        printf("\ec"); // clear terminal
        for(int i= 0; i < MAX_BELTS; i++){
            printf("%s %d ",belts[i].get_name(), belts[i].count_luggage);
        }
        printf("\n");
        
        bool no_luggege = true;
        for(int i= 0; i < MAX_LUGGAGE; i++){
            if(luggage[i].enable){
                printf("%s %d %.1f \n",luggage[i].get_name(), luggage[i].belts_num, luggage[i].distanse);
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
    while (1){
        while (XPending(dis) > 0) {
            
            XNextEvent(dis, &event);
            if(event.type == Expose && event.xexpose.count == 0) {
                draw();
            }
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
                            }
                            luggage[i].enable = false;
                        }else {
                            luggage[i].enable = true;
                            _b1.push(i);
                        }
                    }
                }
            }

            if(event.type == ButtonPress) {
                int x = event.xbutton.x, y=event.xbutton.y;
                XSetForeground(dis,gc,red);
                XDrawLine(dis,win,gc,dot.x,dot.y,x,y);
                XSetForeground(dis,gc,blue);
                strcpy(text,"1");
                XDrawString(dis,win,gc,x,y,text,strlen(text));
                dot.x = x;
                dot.y = y;
            }
        }
        XClearWindow(dis, win);
        for(int j = 0; j < MAX_BELTS; j++){
            for (int i = 0; i < belts[id].count_luggage; i++){
                int l_num = belts[id].get_luggege(i);
                if(luggage[l_num].enable){
                    luggage[l_num].distanse += (0.0001f * belts[id].get_speed());
                    if(luggage[l_num].distanse >= belts[id].len){
                        luggage[l_num].distanse = 0.0f;
                        belts[id].del_luggege(l_num);
                        send.push(l_num);
                    }
                }
            }
        }
        for(int i= 0; i < MAX_LUGGAGE; i++){
            if(luggage[i].enable){
                XDrawPoint(Display *display, Drawable d, GC gc, int x, int y);
                XDrawPoint(dis,win,gc,dot.x,dot.y);
            }
        }
    }
}

void init_gui() {
    dis = XOpenDisplay((char *)0);
    scrn_num = DefaultScreen(dis);
    black = BlackPixel(dis, scrn_num);
    white = WhitePixel(dis, scrn_num);
    red = RGB(255,0,0);
    blue = RGB(0,0,255);
    screen = ScreenOfDisplay(dis, scrn_num);
    dot.x = 0;(screen->width/2 - screen->width/10); // start position
    dot.y = 0;(screen->height/2 - screen->height/10); 
    win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 0, 0, 640, 640, 5, white, black);
    XSetStandardProperties(dis, win, "Luggege belts", NULL, None, NULL, 0, NULL);
    XSelectInput(dis, win, ExposureMask | ButtonPressMask | KeyPressMask);
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

void draw() {
    XClearWindow(dis, win);
}

inline unsigned long RGB(int r, int g, int b) {
    return b + (g<<8) + (r<<16);
}


