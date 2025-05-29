#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "utils.h"
#include "shape.h"
#include "gameLoop.h"
#include "Window.h"

std::vector<index> bgIndices;

int gameLoop::start(int frameRate) {

    Window win(129, 65, false, '-');
    Shape sqr(&win, 5, 5, 10, 50, 'm');
    sqr.pack();
    
    is_running  = true;
    
    //thread to keep caching the keyboard input     
    std::thread kbd_inputs(&gameLoop::cache_kbd_input,this);
    
    // clear the terminal
    system("cls");
    
    // Preparing a fresh canvas
    ShowConsoleCursor(FALSE);
    win.reset_canvas();
    win.render_canvas();
    


    while (true)
    {

        // system("cls");
        ClearScreen();

        if(key_in == 'd')
        {
        sqr.x += 2;
        sqr.move(sqr.x, sqr.y);
        }

        else if(key_in == 'a')
        {
        sqr.y-= 2;
        sqr.move(sqr.x,sqr.y);
        }
        
        sqr.pack();

        //DO NOT CHANGE
        win.render_canvas();
        win.reset_canvas();

        // reset the key input to eleminate continuous input
        key_in = '=';

        //set framerate
        std::this_thread::sleep_for(std::chrono::milliseconds(1000/frameRate -5));
    }
    kbd_inputs.join();


    ShowConsoleCursor(TRUE);
    return 0;
}



void gameLoop::cache_kbd_input()
{
    while (is_running)
    {
        if (kbhit)
        {
            key_in = getch();
            fflush(stdin);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
