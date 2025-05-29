#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <conio.h>
#include <algorithm>
#include <vector>
#include "utils.h"
#include "shape.h"
#include "GameLoop.h"
#include "Window.h"
#include "Object.h"


std::vector<index> bgIndices;

// window with canvas
Window win(50, 20, true, ' ');

// square object
Shape sqrShape(&win, 0, 0, 5, 5, 'M');
Shape *sPtr = &sqrShape;
Object sqr(sPtr, 25); // 25kg

GameLoop::GameLoop()
{
    is_running = true;
};

void GameLoop::setup()
{
    is_running = true;
    // // clear the terminal
    system("cls");
    
    // Preparing a fresh canvas
    win.reset_canvas();
    ClearCanvas();
}



void GameLoop::cache_kbd_input()
{
    while (is_running)
    {
        if (_kbhit())
        {
            key_in = _getch();
            // std::cout << key_in << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}



int GameLoop::run(int targetFPS)
{
    this->framerate = targetFPS;
    ShowConsoleCursor(FALSE);

    std::thread kbd_inputs(&GameLoop::cache_kbd_input, this);

    setup();

    using clock = std::chrono::high_resolution_clock;
    using ms = std::chrono::milliseconds;
    const ms frameDuration(1000 / targetFPS);

    auto previousFrameTime = clock::now();

    TVector velocity(7,3);
    sqr.setVelocity(velocity);

    while (is_running)
    {
        auto frameStart = clock::now();

        std::chrono::duration<float> dtDuration = frameStart - previousFrameTime;
        previousFrameTime = frameStart;
        float dt = dtDuration.count();

        this->dt = dt;  

        loop();

        key_in = '=';

        auto frameEnd = clock::now();
        auto elapsed = std::chrono::duration_cast<ms>(frameEnd - frameStart);

        if (elapsed < frameDuration)
        {
            std::this_thread::sleep_for(frameDuration - elapsed);
        }
        // else{
        //     std::cout<<"Took longer than frametime!"<<std::endl;
        // }
    }

    kbd_inputs.join();
    ShowConsoleCursor(TRUE);
    return 0;
}


int GameLoop::loop()
{
    ClearCanvas();
    sqrShape.render();
    
    win.render_canvas();
    win.reset_canvas();
    
    TVector force(0, 250);
    sqr.applyForce(force, dt);
    sqr.update(dt);
    

    if (key_in == 'd')
    {
        int nextX = sqr.x + 2;
        sqr.move(nextX, sqr.y);
    }

    else if (key_in == 'a')
    {
        int nextX = sqr.x - 2;
        sqr.move(nextX, sqr.y);
    }

    else if (key_in == 'w')
    {
        int nextY = sqr.y - 2;
        sqr.move(sqr.x, nextY);
    }
    else if (key_in == 's')
    {
        int nextY = sqr.y + 2;
        sqr.move(sqr.x, nextY);
    }
    else if (key_in == 'q')
    {
        is_running = false;
    }



    return 0;
}

