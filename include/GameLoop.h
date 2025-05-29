#ifndef GAMELOOP_H
#define GAMELOOP_H
#include "Window.h"
#include "Shape.h"

class GameLoop
{
private:
    char key_in;
    int framerate;
    float dt;
public:
    GameLoop();
    void cache_kbd_input();
    int run(int framerate = 30);
    void setup();
    int loop();

    // void animate( int frameRate);
    bool is_running;

    void error();
};

#endif