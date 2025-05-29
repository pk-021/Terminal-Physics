#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "Window.h"

class Shape
{

public:
    int x;
    int y;
    int xMax;
    int yMax;
    int width;
    int height;
    int bounds[4];
    Window *win;
    char fill_char;

    Shape(Window *win, int x = 0, int y = 0, int width = 50, int height = 50, char fill_char = '0');
    void update_bounds(bool safe = true);
    bool isBounded(index point) const;
    bool isBounded(int x, int y) const;
    void virtual move(int X, int Y, bool safe = true);
    std::vector<index> virtual get_indices() const;
    void render();

    // constructor

};

bool intersect(const Shape &sh1, const Shape &sh2);
;

#endif