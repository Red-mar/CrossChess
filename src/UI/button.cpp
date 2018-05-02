#include "button.h"

Button::Button(Window *window, float x, float y, int w, int h, std::string filename) : window(window),
                                                                 UIElement(x, y, w, h),
                                                                 image(nullptr)
{
    image = new Sprite(window, filename);
    image->setSize(w,h);
}

Button::~Button()
{
    delete image;
}

void Button::update(float dt)
{
}

void Button::render(float cameraX, float cameraY)
{
    image->render((float)position->x - cameraX,
                  (float)position->y - cameraY);
}