

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
#include <unistd.h>

#include <pthread.h>

#include <thread>

#define NO_LUGGAGE "No luggage"
#define MAX_LUGGEGE 4
#define MAX_BELTS 4

using namespace std;
class Luggege
{
public:
    Luggege();

	void set_name(const char* text){strncpy(_name,text, sizeof(_name)); }
    char* get_name(){return &_name[0];};
    bool enable {0};
    float distanse {0};
	unsigned char belts_num {0};
    long int start {0};
private:
    char _name[4];
};
Luggege::Luggege(){};

class Belts {
public:
    // Belts(char[] , float);
    Belts();
    
    //void update(void);

	int get_speed(){ return _speed;};
	void set_speed(float speed){_speed = speed;};
	void set_name(const char* text){strncpy(_name,text, sizeof(_name)); }
    char* get_name(){return &_name[0];};
    int luggeg;
    int len {10}; // meter
private: 
    char _name[4];
    float _speed;
};

Belts::Belts(){}
// char name[], float speed){
//     set_name(name);
//     set_speed(speed);
// };

void init();
// class student
// {
//     int rno;
//     char name[50];
//     double fee;
//     public:
//     student(int,char[],double);
//     student(student &t)       //copy constructor
//     {
//         rno=t.rno;
//         strcpy(name,t.name);
//         fee=t.fee;
//     }
//     void display();
     
// };
//     student::student(int no,char n[],double f)
//     {
//         rno=no;
//         strcpy(name,n);
//         fee=f;
//     }   


// GUI
Display *dis;
Screen *screen;
int scrn_num;
Window win;
GC gc;
unsigned long black, white, red, blue;
void init_gui(void);
void run_gui(void);
void _close(void);
void draw(void);
unsigned long RGB(int r, int g, int b);
struct coord {
 int x;
 int y;
} dot;


Belts belts[MAX_BELTS];
Luggege luggage[MAX_LUGGEGE];
void one_second_loop();
void update();

int main() {

    init();
    init_gui();

    thread t1(one_second_loop);
   printf("FUCKUP111111");
    thread t2(run_gui);
    // printf("FUCKUP222222");
    // t2.join();
    // printf("FUCKUP3333333");
    // t1.join();
    // printf("FUCKUP4444444");
    // pthread_t pthread;
    // int i1 = pthread_create(&pthread, NULL, one_second_loop, (void*) NULL);
    // pthread_join(pthread, NULL);

    while (1){
        printf("FUCKUP");
        //one_second_loop();
        // run_gui();
    }
    
    return 0;
}

void  update(){
    static unsigned int tic;
    // static unsigned short tic_old;
    usleep(1);
    tic += 1;
    // unsigned short diff_tic = tic - tic_old;
    // if(diff_tic >= 1000){
    //     tic_old = tic;
    //     printf("tic  %d\n", tic);
    // }

    // belts
    if(luggage[0].enable){
        if(luggage[0].start)
        luggage[0].start = tic;
    }
}

void init(){

    belts[0].set_name("B1");
    belts[0].set_speed(1);
    belts[1].set_name("B2");
    belts[1].set_speed(1);
    belts[2].set_name("B3");
    belts[2].set_speed(1);
    belts[3].set_name("B4");
    belts[3].set_speed(2);
    
    luggage[0].set_name("L1");
    luggage[1].set_name("L2");
    luggage[2].set_name("L3");
    luggage[3].set_name("L4");
    
}

void one_second_loop(){
    static time_t seconds;
    while (1)
    {

    sleep(1);

    // if(time(NULL) - seconds >= 1){
    //     seconds = time(NULL);
        
    //     // printf("\ec"); // clear terminal
    //     for(int i= 0; i < MAX_BELTS; i++){
    //         printf("%s %d ",belts[i].get_name(), belts[i].luggeg);
    //     }
    //     printf("\n");
        
    //     bool no_luggege = true;
    //     for(int i= 0; i < MAX_LUGGEGE; i++){
    //         if(luggage[i].enable){
    //             printf("%s %.1f \n",luggage[i].get_name(), luggage[i].distanse);
    //             no_luggege = false;
    //         }
    //     }
    //     if(no_luggege){
            printf("NO_LUGGAGE\n");
    //     }
        
    // }
    }
}

void run_gui(void){
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
                    
                    for(int i = 0; i < MAX_LUGGEGE; i++){
                        if((char)(i+49) == text[0]){ // 49 = '1'
                            if(luggage[i].enable){
                                luggage[i].enable = false;
                            }else {
                                luggage[i].enable = true;
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


