#include <iostream>
#include <vector>
#include <math.h>

#include "shape.h"
#include "utils.h"

using namespace std;

Shape::Shape(Window *win, int x, int y, int width, int height, char fill_char)
{
    this->win = win;
    this->x = x;
    this->y = y;
    this->xMax = win->xMax - width + 1;
    this->yMax = win->yMax - height + 1;

    this->width = width;
    this->height = height;
    this->fill_char = fill_char;
    update_bounds();
}

// Updates shape boundary, fits to drawable area
void Shape::update_bounds(bool safe)
{

    if (safe)
    {
        int newBounds[4];
        newBounds[0] = y;
        newBounds[1] = x + width - 1;
        newBounds[2] = y + height - 1;
        newBounds[3] = x;

        // enable enclosing
        if (newBounds[0] < win->yMin)
        {
            y = win->yMin;
        }
        if (newBounds[2] > win->yMax)
        {
            y = win->yMax - height + 1;
        }
        if (newBounds[3] < win->xMin)
        {
            x = win->xMin;
        }
        if (newBounds[1] > win->xMax)
        {
            x = win->xMax - width + 1;
        }
    };

    // After adjustment, recompute bounds:
    bounds[0] = y;
    bounds[1] = x + width - 1;
    bounds[2] = y + height - 1;
    bounds[3] = x;

    // //enable clipping
    // bounds[0] = std::max(0, y);
    // bounds[1] = std::min(x + width - 1, win->xMax);
    // bounds[2] = std::min(y + height - 1, win->yMax);
    // bounds[3] = std::max(0, x);
    // }
}

// check if an index is on or inside shape boundary
bool Shape::isBounded(index point) const
{
    return !(point.x > bounds[1] ||
             point.x < bounds[3] ||
             point.y > bounds[2] ||
             point.y < bounds[0]);
}

bool Shape::isBounded(int x, int y) const
{
    return !(x > bounds[1] ||
             x < bounds[3] ||
             y > bounds[2] ||
             y < bounds[0]);
}

void Shape::move(int x, int y, bool safe)
{
    this->x = x;
    this->y = y;

    update_bounds(safe);
}

// get indices of shape within the bounds
vector<index> Shape::get_indices() const
{
    vector<index> indices;
    for (int y = bounds[0]; y <= bounds[2]; y++)
    {
        for (int x = bounds[3]; x <= bounds[1]; x++)
        {
            index temp;
            temp.x = x;
            temp.y = y;
            if (isBounded(temp))
            {
                indices.push_back(temp);
            }
        }
    }
    return indices;
}

void Shape::render()
{
    vector<index> indices = get_indices();
    win->set_char(indices, fill_char);
}

// for circle
// vector<index> Circle::get_indices() const
// {
//     vector<index> indices;
//     for (int i = bounds[0]; i < bounds[2]; i++)
//     {
//         for (int j = bounds[3]; j < bounds[1]; j++)
//         {
//             if (pow((i - h), 2) + pow((j - k), 2) <= pow(radius, 2))
//             {
//                 index temp;
//                 temp.x = i;
//                 temp.y = j;
//                 indices.push_back(temp);
//             }
//         }
//     }
//     return indices;
// }

// void Circle::move(int x, int y)
// {
//     this->X = x;
//     this->Y = y;
//     this->h = this->X + radius + 1;
//     this->k = this->Y + radius + 1;
//     update_bounds();
// }

// bool intersect(const Shape &sh1, const Shape &sh2)
// {
//     return !(sh1.bounds[2] < sh2.bounds[0] || // sh1 right < sh2 left
//              sh1.bounds[0] > sh2.bounds[2] || // sh1 left > sh2 right
//              sh1.bounds[1] < sh2.bounds[3] || // sh1 top < sh2 bottom
//              sh1.bounds[3] > sh2.bounds[1]);  // sh1 bottom > sh2 top
// }
