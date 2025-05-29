#ifndef WINDOW_H
#define WINDOW_H

#include <vector>
#include <iostream>

// structure for a co-ordinate
struct index
{
    int x; // horizontal (columns)
    int y; // vertical (rows)
};

class Window
{

    // Creating canvas
private:
    int boundaryWidth = 1;
    char **canvas;
    bool boundary;
    int height;
    int width;
    int consoleWidth;
    int consoleHeight;
    char bgFill;
    void get_console_size();

public:
    int ibounds[4];
    int yMax;
    int xMax;
    int yMin;
    int xMin;

    Window(int width = 5, int height = 4, bool boundary = true, char bgFill = ' '); // ensure odd columns
    int *canvas_size();
    void set_char(int x, int y, char c);
    void set_char(std::vector<index> indices, char c);

    char get_char(int x, int y);

    bool isBounded(index indx) const;
    bool isBounded(int bounds[4]) const;
    
    void reset_canvas(char background);
    void reset_canvas();

    void render_canvas();

};

#endif