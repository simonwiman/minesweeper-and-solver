#pragma once

#include <raylib.h>
#include <functional>


class Button
{
public:
    Button();
    Button(std::function<void()> on_click, Texture2D texture_normal, Texture2D texture_hovered, Rectangle rect);
    void update();
    std::function<void()> on_click;
    bool get_is_hovered();
    Texture2D get_texture_normal();
    Texture2D get_texture_hovered();
    Rectangle get_rect();
    void unload_textures();

private:
    Texture2D texture_normal;
    Texture2D texture_hovered;
    Rectangle rect;
    bool is_hovered;

};
