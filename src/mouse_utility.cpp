#include "mouse_utility.h"
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

bool mouse_clicked_rectangle(Rectangle rec)
{
    return mouse_overlap_rectangle(rec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}
