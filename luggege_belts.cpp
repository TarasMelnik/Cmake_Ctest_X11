

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
    float distanse{0};
	unsigned char belts_num{0};
private:
    char _name[4];
};
Luggege::Luggege(){};

class Belts {
public:
    //friend class Luggage;
    Belts();
    
    //void update(void);

	int get_speed(){ return _speed;};
	void set_speed(float speed){_speed = speed;};
	void set_name(const char* text){strncpy(_name,text, sizeof(_name)); }
    char* get_name(){return &_name[0];};
    int luggeg;
private: 
    char _name[4];
    float _speed;
};
Belts::Belts(){};


// GUI
Display *dis;
Screen *screen;
int scrn_num;
Window win;
GC gc;
unsigned long black, white, red, blue;
void init_gui(void);
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

int main() {

    belts[0].set_name("B1");
    belts[0].set_speed(2);
    belts[1].set_name("B2");
    belts[2].set_name("B3");
    belts[3].set_name("B4");
    
    luggage[0].set_name("L1");
    luggage[1].set_name("L2");
    luggage[2].set_name("L3");
    luggage[3].set_name("L4");

    init_gui();
    XEvent event;
    KeySym key;
    char text[255];
    
    while (1)
    {
        one_second_loop();
        while (XPending(dis) > 0) {
        
            XNextEvent(dis, &event);
            if(event.type == Expose && event.xexpose.count == 0) {
                draw();
            }
            if(event.type == KeyPress && XLookupString(&event.xkey, text, 255, &key,0) == 1) {
                switch (text[0])
                {
                case 'q':
                    _close();
                    break;
                case '1':
                    if(luggage[0].enable){
                        luggage[0].enable = false;
                    }else {
                        luggage[0].enable = true;
                    }
                    // printf("%s %d %s %d\n",belts[0].get_name(), belts[0].luggeg, luggage[1].get_name(), (int)luggage[0].enable);
                    break;
                case '2':
                    if(luggage[1].enable){
                        luggage[1].enable = false;
                    }else {
                        luggage[1].enable = true;
                    }
                    break;
                case '3':
                    if(luggage[2].enable){
                        luggage[2].enable = false;
                    }else {
                        luggage[2].enable = true;
                    }
                    break;
                case '4':
                    if(luggage[3].enable){
                        luggage[3].enable = false;
                    }else {
                        luggage[3].enable = true;
                    }
                    break;
                
                default:
                    //_X_ATTRIBUTE_PRINTF("You pressed the %s key!\n",text);
                    // printf("You pressed the %s key!\n",text);
                    // std::cout << "You pressed the " << text << " key!\n";
                    break;
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
    
    return 0;
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
    win = XCreateSimpleWindow(dis, DefaultRootWindow(dis), 0, 0, 640, 480, 5, white, black);
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

void one_second_loop(){
static int useconds;

    usleep(1);//wait 1 usecond
    useconds += 1;
    if(useconds > 10000){
        useconds = 0;
        printf("\ec"); // clear terminal
        for(int i= 0; i < MAX_BELTS; i++){
            printf("%s %d ",belts[i].get_name(), belts[i].luggeg);
        }
        printf("\n");
        
        bool no_luggege = true;
        for(int i= 0; i < MAX_LUGGEGE; i++){
            if(luggage[i].enable){
                printf("%s %.1f \n",luggage[i].get_name(), luggage[i].distanse);
                no_luggege = false;
            }
        }
        if(no_luggege){
            printf("NO_LUGGAGE\n");
        }
    }
}

