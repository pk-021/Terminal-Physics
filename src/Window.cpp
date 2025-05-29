
#include <iostream>
#include <cstring>
#include <sstream>
#include <chrono>
#include <thread>
#include <windows.h>

#include "Window.h"

using namespace std;

  Window::Window(int width, int height, bool boundary, char bgFill) // ensure odd columns
    {
        get_console_size();
        this->boundary = boundary;
        this->width = width;
        this->height = height;
        this->bgFill = bgFill;


        canvas = new char *[consoleHeight];
        for (int i = 0; i < consoleHeight; i++)
        {
            canvas[i] = new char[consoleWidth-1];
        };

        if (boundary)
        {
            xMax = (width - 1) - boundaryWidth;
            yMax = (height -1)  - boundaryWidth;
            xMin = boundaryWidth;
            yMin = boundaryWidth;
        }
        else
        {
            xMax = width-1;
            yMax = height-1;
            xMin = 0;
            yMin = 0;
        }

        //internal drawing area bounds
        ibounds[0] = yMin;
        ibounds[1] = xMax;
        ibounds[2] = yMax;
        ibounds[3] = xMin;


        reset_canvas(bgFill);
    }


void Window::get_console_size()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    consoleHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

// return array of Canvas size
int *Window::canvas_size()
{
    static int size[] = {height, width};
    return size;
}

// Set a character in the Canvas
void Window::set_char(int x, int y, char c)
{
    index point;
    point.x = x;
    point.y = y;

    if (isBounded(point))
    {
        canvas[y][x] = c;
    }
    else{
        throw std::out_of_range("Point not drawable, Index out of Range.");
    }
}

// set characters using vector of indices, has clipping
void Window::set_char(vector<index> indices, char character)
{
    for (int i = 0; i < indices.size(); i++)
    {
        if (isBounded(indices[i]))
        {
            canvas[indices[i].y][indices[i].x] = character;
        }
        else{
            throw std::out_of_range("Point not drawable, Index out of Range.");
        }
    }
}

// Get a character at canvas position
char Window::get_char(int x, int y)
{
    return canvas[y][x];
}

// Make the Canvas blank
void Window::reset_canvas(char background)
{
    for (int y = 0; y < height; ++y)
    {
        std::fill(canvas[y], canvas[y] + width, background);
    }
}
void Window::reset_canvas()
{
    for (int y = 0; y < height; ++y)
    {
        std::fill(canvas[y], canvas[y] + width, bgFill);
    }

    if (boundary)
    {
        for (int y = 0; y < boundaryWidth; y++)
        {
            std::fill(canvas[y], canvas[y] + width, '-');
            std::fill(canvas[height - 1 - y], canvas[height - 1 - y] + width, '-');
        };

        for (int y = 0; y < height; y++)
        {
            std::fill(canvas[y], canvas[y] + boundaryWidth, '|');
            std::fill(canvas[y] + width - boundaryWidth, canvas[y] + width, '|');
        };

        canvas[boundaryWidth-1][boundaryWidth-1] = '+';                 
        canvas[boundaryWidth-1][width-boundaryWidth] = '+';
        canvas[height-boundaryWidth][boundaryWidth-1] = '+';
        canvas[height-boundaryWidth][width-boundaryWidth] = '+';
    }
}

// Print the Canvas in the terminal
void Window::render_canvas()
{
    std::ostringstream oss; // Using string stream for buffering output
    for (int y = 0; y < height; ++y)
    {

        for (int x = 0; x < width; ++x)
        {
            oss << get_char(x, y);
        }
        oss << "\n";
    }
    std::cout << oss.str();
}
// check if a point is bounded within drawable canvas
bool Window::isBounded(index point) const
{
    return !(point.x > xMax ||
             point.x < xMin ||
             point.y > yMax ||
             point.y < yMin);
}

bool Window::isBounded(int _bounds[4]) const
{
    return !(_bounds[0] < yMin || // sh1 left > sh2 right
             _bounds[1] > xMax || // sh1 top < sh2 bottom
             _bounds[2] > yMax || // sh1 right < sh2 left
             _bounds[3] < xMin);  // sh1 bottom > sh2 top}
}