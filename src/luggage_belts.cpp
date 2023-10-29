

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

#define DISPLAY_HEIGHT 640
#define DISPLAY_WIDHT  640
#define BELTS_NAME "B"
#define LUGGAGE_NAME "L"
#define NO_LUGGAGE "No luggage"
#define MAX_LUGGAGE 10
#define MAX_BELTS 4
#define BELTS_LEN 10.0f
#define LUGGAGE_SPEED_MULT 0.00017f
#define THREAD_SLEEP 100

using namespace std;

class Luggege
{
    friend class Belts;
public:
    Luggege(){};
    struct coord {
        int x;
        int y;
    } dot;

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
    Luggege *luggage;
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

void Belts::set_luggege(int id){
    if(count_luggage < MAX_LUGGAGE){
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
        std::this_thread::sleep_for(std::chrono::microseconds(100));
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
struct coord {
    int x;
    int y;
} dot;

Belts belts[MAX_BELTS];
Luggege luggage[MAX_LUGGAGE];
void one_second_loop();
void update();

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

    // while (1){exit(0);}
    
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

        usleep(THREAD_SLEEP); // 50Hz
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


    dis = XOpenDisplay((char *)0);
    scrn_num = DefaultScreen(dis);
    black = BlackPixel(dis, scrn_num);
    white = WhitePixel(dis, scrn_num);
    red = RGB(255,0,0);
    blue = RGB(0,0,255);
    screen = ScreenOfDisplay(dis, scrn_num);
    dot.x = 0;(screen->width/2 - screen->width/10); // start position
    dot.y = 0;(screen->height/2 - screen->height/10); 
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


