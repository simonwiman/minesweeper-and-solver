#include <cassert>
#include "button.h"
#include "mouse_utility.h"


Button::Button(std::function<void()> on_click, Texture2D texture_normal, Texture2D texture_hovered, Rectangle rect) : on_click(on_click), texture_normal(texture_normal), texture_hovered(texture_hovered), rect(rect), is_hovered(false) {}

void Button::update()
{
    if ( mouse_lclicked_rectangle(rect) )
        on_click();
    if ( mouse_overlap_rectangle(rect) )
        is_hovered = true;
    else
        is_hovered = false;
}
