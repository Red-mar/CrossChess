#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "sdl.hpp"
#include "timer.h"
#include "shapes.h"

class Window
{
    public:
        Window(unsigned int width, unsigned int height, std::string tittle="");
        virtual ~Window();

        void destroy();
        void renderImage(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* renderQuad, double angle, SDL_Point* center, SDL_RendererFlip flip);

        SDL_Texture * loadImage(std::string filename);

        void freeImage(SDL_Texture * image);
        //void freeImage(SDL_Surface * iamge);

        void refresh();

        bool toggleFullscreen();

        void minimize();

        void maximize();

        void restore();

        void setIcon(std::string filepath);
        void create(std::string title, int width, int height, int windowFlags = 0, int rendererFlags = 0);
        void resize(int width, int height, int windowFlags = 0);

        void center();
        void move(int x, int y);
        void fill(SDL_Color color);

        void clear();
        void setBackgroundColor(SDL_Color color={0,0,0,0});

        void setTitle(std::string title);

        void setFramerateLimit(int limit);
        int getFramerateLimit();

        SDL_Window* window;
                //SDL_Surface* surface;
        SDL_Renderer* renderer;
        

        int mWidth;
        int mHeight;

        int originalWidth;
        int originalHeight;

        bool isFullscreen;

        void delayFramerateIfNeeded();
        unsigned int getTicks();
        float getDelta();
        void drawBox(RotatedRectangle* r, SDL_Color color);
        void drawHexagon(Hexagon* hexagon, SDL_Color color);
        void drawFilledHexagon(Hexagon* hexagon, SDL_Color color);

    private:
        std::string mTitle;
        SDL_Color bg_color;

        
        Timer framerateTimer;
        Timer deltaTimer;

        unsigned int framerate;

        unsigned int frame_delay;

        unsigned int current_frame_delta;
};


#endif // !WINDOW_H
