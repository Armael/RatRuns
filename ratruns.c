#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <X11/Xlib.h>

typedef struct Binding {
    unsigned int button;
    char* cmd;
} Binding;

#define Left_Click Button1
#define Middle_Click Button2
#define Right_Click Button3
#define Roll_Top Button4
#define Roll_Bottom Button5

#include "config.h"

static Window w;
static Display* dpy;

void die(int sig) {
    XDestroyWindow(dpy, w);
    exit(1);
}

void init() {
    signal(SIGINT, die);
    signal(SIGTERM, die);
    signal(SIGSTOP, die);
    signal(SIGHUP, die);
}

void spawn(char* cmd) {
    if(fork() == 0) {
        setsid();
        execl("/bin/sh", "/bin/sh", "-c", cmd, (char*)NULL);
    }
}

int main()
{
    Window root;
    int bindings_nb = sizeof(bindings) / sizeof(Binding);

    if(!(dpy = XOpenDisplay(0x0))) return 1;
    root = DefaultRootWindow(dpy);

    w = XCreateSimpleWindow(dpy, root, 100, 100, window_width, window_height, 0, 0, 0);
    XMapWindow(dpy, w);

    XSelectInput(dpy, w, ButtonPressMask|StructureNotifyMask);

    init();
    XEvent ev;
    for(;;) {
        int i;

        XNextEvent(dpy, &ev);

        if(ev.type == DestroyNotify) {
            printf("Destroyed\n");
            exit(0);
        } else if(ev.type == ButtonPress) {
            for(i=0; i < bindings_nb; i++) {
                if(ev.xbutton.button == bindings[i].button) {
                    printf("Spawning \"%s\"\n", bindings[i].cmd);
                    spawn(bindings[i].cmd);
                }
            }
        }
    }

    return 0;
}
