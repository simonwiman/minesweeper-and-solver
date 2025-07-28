#pragma once

#include <raylib.h>
#include <functional>


class Button
{
public:
    Button(std::function<void()> on_click, Texture2D texture_normal, Texture2D texture_hovered, Rectangle rect);
    void update();
    std::function<void()> on_click;

private:
    Texture2D texture_normal;
    Texture2D texture_hovered;
    Rectangle rect;
    bool is_hovered;

};
