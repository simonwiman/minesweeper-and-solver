#pragma once

#include <raylib.h>

void print_mouse_position();
bool mouse_overlap_rectangle(Rectangle rec);
bool mouse_lclicked_rectangle(Rectangle rec);
bool mouse_lreleased_rectangle(Rectangle rec);
bool mouse_lholding_rectangle(Rectangle rec);
bool mouse_rclicked_rectangle(Rectangle rec);
