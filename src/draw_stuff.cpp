#include "draw_stuff.h"
#include <raylib.h>
#include <iostream> 


void print_mouse_position()
{
    std::cout << "(" << GetMouseX() << ", " << GetMouseY() << ")\n";
}


bool mouse_overlap_rectangle(Rectangle rec)
{
    return CheckCollisionRecs(rec, (Rectangle){(float)GetMouseX(), (float)GetMouseY(), 0, 0});
}

